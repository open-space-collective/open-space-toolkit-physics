/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Dynamic.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SunMoonAnalytical.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Transform;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;

namespace
{

// Analytical Sun/Moon position series
// Ref: O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2

constexpr double Pi = M_PI;
constexpr double TwoPi = 2.0 * M_PI;
constexpr double ArcsecondsToRadians = Pi / (180.0 * 3600.0);
constexpr double ObliquityOfEclipticJ2000_rad = 23.43929111 * Pi / 180.0;

/// @brief Return the fractional part of a value.
double fractionalPart(const double aValue)
{
    return aValue - std::floor(aValue);
}

/// @brief Julian centuries (TT) since J2000, i.e. (MJD_TT - 51544.5) / 36525.
///
/// Computed from the elapsed duration since the J2000 epoch (2000-01-01 12:00:00 [TT], i.e. MJD 51544.5 [TT]):
/// elapsed SI seconds equal elapsed TT seconds (TT - TAI is a constant offset),
/// which avoids a costly Instant -> DateTime -> Modified Julian Date conversion.
double julianCenturiesSinceJ2000(const Instant& anInstant)
{
    static const Instant j2000_TT = Instant::J2000();

    return static_cast<double>((anInstant - j2000_TT).inSeconds()) / (36525.0 * 86400.0);
}

/// @brief Rotate a vector from the J2000 ecliptic plane to the mean equator and equinox of J2000.
Vector3d equatorialFromEcliptic(const Vector3d& anEclipticVector)
{
    const double cosObliquity = std::cos(ObliquityOfEclipticJ2000_rad);
    const double sinObliquity = std::sin(ObliquityOfEclipticJ2000_rad);

    return {
        anEclipticVector.x(),
        cosObliquity * anEclipticVector.y() - sinObliquity * anEclipticVector.z(),
        sinObliquity * anEclipticVector.y() + cosObliquity * anEclipticVector.z(),
    };
}

/// @brief Compute the Sun position [m], with respect to the mean equator and equinox of J2000 (treated as GCRF).
///
/// Ref: Montenbruck & Gill, Section 3.3.2.
/// Accuracy: < 0.1 deg in direction over 2020-2026,
/// dominated by a slow drift (~11.6 arcsec/year) due to the neglected motion of the Earth's perihelion.
Vector3d computeSunPosition(const Instant& anInstant)
{
    const double T = julianCenturiesSinceJ2000(anInstant);

    // Mean anomaly, ecliptic longitude and radius

    const double M = TwoPi * fractionalPart(0.9931267 + 99.9973583 * T);  // [rad]
    const double L = TwoPi * fractionalPart(
                                 0.7859444 + (M / TwoPi) + (6892.0 * std::sin(M) + 72.0 * std::sin(2.0 * M)) / 1296.0e3
                             );                                                        // [rad]
    const double r = 149.619e9 - 2.499e9 * std::cos(M) - 0.021e9 * std::cos(2.0 * M);  // [m]

    // Equatorial position vector

    return equatorialFromEcliptic({r * std::cos(L), r * std::sin(L), 0.0});
}

/// @brief Compute the Moon position [m], with respect to the mean equator and equinox of J2000 (treated as GCRF).
///
/// Ref: Montenbruck & Gill, Section 3.3.2. Accuracy: ~0.1-0.3 deg in direction (< 0.1 deg over 2020-2026).
Vector3d computeMoonPosition(const Instant& anInstant)
{
    const double T = julianCenturiesSinceJ2000(anInstant);

    // Mean elements of lunar orbit

    const double L_0 = fractionalPart(0.606433 + 1336.851344 * T);        // Mean longitude [rev] w.r.t. J2000 equinox
    const double l = TwoPi * fractionalPart(0.374897 + 1325.552410 * T);  // Moon's mean anomaly [rad]
    const double lp = TwoPi * fractionalPart(0.993133 + 99.997361 * T);   // Sun's mean anomaly [rad]
    const double D = TwoPi * fractionalPart(0.827361 + 1236.853086 * T);  // Diff. long. Moon - Sun [rad]
    const double F = TwoPi * fractionalPart(0.259086 + 1342.227825 * T);  // Argument of latitude [rad]

    // Ecliptic longitude (w.r.t. equinox of J2000)

    const double dL = 22640.0 * std::sin(l) - 4586.0 * std::sin(l - 2.0 * D) + 2370.0 * std::sin(2.0 * D) +
                      769.0 * std::sin(2.0 * l) - 668.0 * std::sin(lp) - 412.0 * std::sin(2.0 * F) -
                      212.0 * std::sin(2.0 * l - 2.0 * D) - 206.0 * std::sin(l + lp - 2.0 * D) +
                      192.0 * std::sin(l + 2.0 * D) - 165.0 * std::sin(lp - 2.0 * D) - 125.0 * std::sin(D) -
                      110.0 * std::sin(l + lp) + 148.0 * std::sin(l - lp) - 55.0 * std::sin(2.0 * F - 2.0 * D);  // ["]

    const double L = TwoPi * fractionalPart(L_0 + dL / 1296.0e3);  // [rad]

    // Ecliptic latitude

    const double S = F + (dL + 412.0 * std::sin(2.0 * F) + 541.0 * std::sin(lp)) * ArcsecondsToRadians;  // [rad]
    const double h = F - 2.0 * D;                                                                        // [rad]
    const double N = -526.0 * std::sin(h) + 44.0 * std::sin(l + h) - 31.0 * std::sin(-l + h) - 23.0 * std::sin(lp + h) +
                     11.0 * std::sin(-lp + h) - 25.0 * std::sin(-2.0 * l + F) + 21.0 * std::sin(-l + F);  // ["]

    const double B = (18520.0 * std::sin(S) + N) * ArcsecondsToRadians;  // [rad]

    // Distance [m]

    const double r = 385000e3 - 20905e3 * std::cos(l) - 3699e3 * std::cos(2.0 * D - l) - 2956e3 * std::cos(2.0 * D) -
                     570e3 * std::cos(2.0 * l) + 246e3 * std::cos(2.0 * l - 2.0 * D) - 205e3 * std::cos(lp - 2.0 * D) -
                     171e3 * std::cos(l + 2.0 * D) - 152e3 * std::cos(l + lp - 2.0 * D);

    // Equatorial position vector

    return equatorialFromEcliptic({r * std::cos(L) * std::cos(B), r * std::sin(L) * std::cos(B), r * std::sin(B)});
}

}  // namespace

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{

SunMoonAnalytical::SunMoonAnalytical(const SunMoonAnalytical::Body& aBody)
    : body_(aBody)
{
}

SunMoonAnalytical::~SunMoonAnalytical() {}

SunMoonAnalytical* SunMoonAnalytical::clone() const
{
    return new SunMoonAnalytical(*this);
}

bool SunMoonAnalytical::isDefined() const
{
    return true;
}

Shared<const Frame> SunMoonAnalytical::accessFrame() const
{
    using DynamicProvider = ostk::physics::coordinate::frame::provider::Dynamic;

    const String frameName = String::Format("{} (Analytical)", SunMoonAnalytical::StringFromBody(body_));

    if (const auto frameSPtr = Frame::WithName(frameName))
    {
        return frameSPtr;
    }

    const SunMoonAnalytical::Body body = body_;

    const Shared<const DynamicProvider> transformProviderSPtr = std::make_shared<const DynamicProvider>(
        [body](const Instant& anInstant) -> Transform
        {
            const auto computePosition =
                (body == SunMoonAnalytical::Body::Sun) ? &computeSunPosition : &computeMoonPosition;

            const Vector3d x_BODY_GCRF = computePosition(anInstant);

            // Translational velocity via central finite difference of the analytical series

            static const Duration halfStep = Duration::Seconds(30.0);
            static const double halfStep_s = static_cast<double>(halfStep.inSeconds());

            const Vector3d v_BODY_GCRF =
                (computePosition(anInstant + halfStep) - computePosition(anInstant - halfStep)) / (2.0 * halfStep_s);

            return {
                anInstant,
                -x_BODY_GCRF,
                -v_BODY_GCRF,
                Quaternion::Unit(),
                Vector3d::Zero(),
                Transform::Type::Passive,
            };
        }
    );

    return Frame::Construct(frameName, false, Frame::GCRF(), transformProviderSPtr);
}

SunMoonAnalytical::Body SunMoonAnalytical::getBody() const
{
    return body_;
}

String SunMoonAnalytical::StringFromBody(const SunMoonAnalytical::Body& aBody)
{
    using ostk::core::container::Map;

    static const Map<SunMoonAnalytical::Body, String> bodyStringMap = {
        {SunMoonAnalytical::Body::Sun, "Sun"},
        {SunMoonAnalytical::Body::Moon, "Moon"},
    };

    return bodyStringMap.at(aBody);
}

}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk
