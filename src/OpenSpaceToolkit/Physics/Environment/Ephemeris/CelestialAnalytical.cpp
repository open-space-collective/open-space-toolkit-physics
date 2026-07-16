/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Dynamic.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/CelestialAnalytical.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

using ostk::physics::coordinate::Transform;
using ostk::physics::time::Duration;

namespace
{

// Analytical Sun/Moon position series
// Ref: O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2

constexpr double Pi = M_PI;
constexpr double TwoPi = 2.0 * M_PI;
constexpr double ArcsecondsToRadians = Pi / (180.0 * 3600.0);
constexpr double ObliquityOfEclipticJ2000_rad = 23.43929111 * Pi / 180.0;

}  // namespace

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{

CelestialAnalytical::CelestialAnalytical(const Celestial::Type& aType)
    : type_(aType)
{
    if ((type_ != Celestial::Type::Sun) && (type_ != Celestial::Type::Moon))
    {
        throw ostk::core::error::runtime::Wrong("Type");
    }
}

CelestialAnalytical::~CelestialAnalytical() {}

CelestialAnalytical* CelestialAnalytical::clone() const
{
    return new CelestialAnalytical(*this);
}

bool CelestialAnalytical::isDefined() const
{
    return true;
}

Shared<const Frame> CelestialAnalytical::accessFrame() const
{
    using DynamicProvider = ostk::physics::coordinate::frame::provider::Dynamic;

    const String frameName = String::Format("{} (Analytical)", CelestialAnalytical::StringFromType(type_));

    if (const auto frameSPtr = Frame::WithName(frameName))
    {
        return frameSPtr;
    }

    const Celestial::Type type = type_;

    const Shared<const DynamicProvider> transformProviderSPtr = std::make_shared<const DynamicProvider>(
        [type](const Instant& anInstant) -> Transform
        {
            const Vector3d x_BODY_GCRF = CelestialAnalytical::ComputePosition(type, anInstant);

            // Translational velocity via central finite difference of the analytical series

            static const Duration halfStep = Duration::Seconds(30.0);
            static const double halfStep_s = static_cast<double>(halfStep.inSeconds());

            const Vector3d v_BODY_GCRF = (CelestialAnalytical::ComputePosition(type, anInstant + halfStep) -
                                          CelestialAnalytical::ComputePosition(type, anInstant - halfStep)) /
                                         (2.0 * halfStep_s);

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

Celestial::Type CelestialAnalytical::getType() const
{
    return type_;
}

String CelestialAnalytical::StringFromType(const Celestial::Type& aType)
{
    using ostk::core::container::Map;

    static const Map<Celestial::Type, String> typeStringMap = {
        {Celestial::Type::Sun, "Sun"},
        {Celestial::Type::Moon, "Moon"},
    };

    return typeStringMap.at(aType);
}

Vector3d CelestialAnalytical::ComputePosition(const Celestial::Type& aType, const Instant& anInstant)
{
    switch (aType)
    {
        case Celestial::Type::Sun:
            return CelestialAnalytical::ComputeSunPosition(anInstant);

        case Celestial::Type::Moon:
            return CelestialAnalytical::ComputeMoonPosition(anInstant);

        default:
            throw ostk::core::error::runtime::Wrong("Type");
    }
}

Vector3d CelestialAnalytical::ComputeSunPosition(const Instant& anInstant)
{
    // Ref: Montenbruck & Gill, Section 3.3.2.
    // Accuracy: < 0.1 deg in direction over 2020-2026,
    // dominated by a slow drift (~11.6 arcsec/year) due to the neglected motion of the Earth's perihelion.

    const double T = CelestialAnalytical::JulianCenturiesSinceJ2000(anInstant);

    // Mean anomaly, ecliptic longitude and radius

    const double M = TwoPi * CelestialAnalytical::FractionalPart(0.9931267 + 99.9973583 * T);  // [rad]
    const double L = TwoPi * CelestialAnalytical::FractionalPart(
                                 0.7859444 + (M / TwoPi) + (6892.0 * std::sin(M) + 72.0 * std::sin(2.0 * M)) / 1296.0e3
                             );                                                        // [rad]
    const double r = 149.619e9 - 2.499e9 * std::cos(M) - 0.021e9 * std::cos(2.0 * M);  // [m]

    // Equatorial position vector

    return CelestialAnalytical::EquatorialFromEcliptic({r * std::cos(L), r * std::sin(L), 0.0});
}

Vector3d CelestialAnalytical::ComputeMoonPosition(const Instant& anInstant)
{
    // Ref: Montenbruck & Gill, Section 3.3.2. Accuracy: ~0.1-0.3 deg in direction (< 0.1 deg over 2020-2026).

    const double T = CelestialAnalytical::JulianCenturiesSinceJ2000(anInstant);

    // Mean elements of lunar orbit

    const double L_0 =
        CelestialAnalytical::FractionalPart(0.606433 + 1336.851344 * T);  // Mean longitude [rev] w.r.t. J2000 equinox
    const double l =
        TwoPi * CelestialAnalytical::FractionalPart(0.374897 + 1325.552410 * T);  // Moon's mean anomaly [rad]
    const double lp =
        TwoPi * CelestialAnalytical::FractionalPart(0.993133 + 99.997361 * T);  // Sun's mean anomaly [rad]
    const double D =
        TwoPi * CelestialAnalytical::FractionalPart(0.827361 + 1236.853086 * T);  // Diff. long. Moon - Sun [rad]
    const double F =
        TwoPi * CelestialAnalytical::FractionalPart(0.259086 + 1342.227825 * T);  // Argument of latitude [rad]

    // Ecliptic longitude (w.r.t. equinox of J2000)

    const double dL = 22640.0 * std::sin(l) - 4586.0 * std::sin(l - 2.0 * D) + 2370.0 * std::sin(2.0 * D) +
                      769.0 * std::sin(2.0 * l) - 668.0 * std::sin(lp) - 412.0 * std::sin(2.0 * F) -
                      212.0 * std::sin(2.0 * l - 2.0 * D) - 206.0 * std::sin(l + lp - 2.0 * D) +
                      192.0 * std::sin(l + 2.0 * D) - 165.0 * std::sin(lp - 2.0 * D) - 125.0 * std::sin(D) -
                      110.0 * std::sin(l + lp) + 148.0 * std::sin(l - lp) - 55.0 * std::sin(2.0 * F - 2.0 * D);  // ["]

    const double L = TwoPi * CelestialAnalytical::FractionalPart(L_0 + dL / 1296.0e3);  // [rad]

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

    return CelestialAnalytical::EquatorialFromEcliptic(
        {r * std::cos(L) * std::cos(B), r * std::sin(L) * std::cos(B), r * std::sin(B)}
    );
}

Vector3d CelestialAnalytical::EquatorialFromEcliptic(const Vector3d& anEclipticVector)
{
    const double cosObliquity = std::cos(ObliquityOfEclipticJ2000_rad);
    const double sinObliquity = std::sin(ObliquityOfEclipticJ2000_rad);

    return {
        anEclipticVector.x(),
        cosObliquity * anEclipticVector.y() - sinObliquity * anEclipticVector.z(),
        sinObliquity * anEclipticVector.y() + cosObliquity * anEclipticVector.z(),
    };
}

double CelestialAnalytical::JulianCenturiesSinceJ2000(const Instant& anInstant)
{
    // Computed from the elapsed duration since the J2000 epoch (2000-01-01 12:00:00 [TT], i.e. MJD 51544.5 [TT]):
    // elapsed SI seconds equal elapsed TT seconds (TT - TAI is a constant offset),
    // which avoids a costly Instant -> DateTime -> Modified Julian Date conversion.

    static const Instant j2000_TT = Instant::J2000();

    return static_cast<double>((anInstant - j2000_TT).inSeconds()) / (36525.0 * 86400.0);
}

double CelestialAnalytical::FractionalPart(const double aValue)
{
    return aValue - std::floor(aValue);
}

}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk
