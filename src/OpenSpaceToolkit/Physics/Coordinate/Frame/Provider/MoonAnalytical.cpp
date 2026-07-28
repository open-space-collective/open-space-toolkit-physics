/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/MoonAnalytical.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

using ostk::physics::coordinate::frame::provider::utilities::EquatorialFromEcliptic;
using ostk::physics::coordinate::frame::provider::utilities::FractionalPart;
using ostk::physics::coordinate::frame::provider::utilities::JulianCenturiesSinceJ2000;
using ostk::physics::time::Duration;

namespace
{

// Analytical Moon position series
// Ref: O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2

constexpr double Pi = M_PI;
constexpr double TwoPi = 2.0 * M_PI;
constexpr double ArcsecondsToRadians = Pi / (180.0 * 3600.0);

}  // namespace

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{

MoonAnalytical::MoonAnalytical() {}

MoonAnalytical::~MoonAnalytical() {}

MoonAnalytical* MoonAnalytical::clone() const
{
    return new MoonAnalytical(*this);
}

bool MoonAnalytical::isDefined() const
{
    return true;
}

Transform MoonAnalytical::getTransformAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Vector3d x_MOON_GCRF = MoonAnalytical::ComputePosition(anInstant);

    // Translational velocity via central finite difference of the analytical series

    static const Duration halfStep = Duration::Seconds(30.0);
    static const double halfStep_s = static_cast<double>(halfStep.inSeconds());

    const Vector3d v_MOON_GCRF = (MoonAnalytical::ComputePosition(anInstant + halfStep) -
                                  MoonAnalytical::ComputePosition(anInstant - halfStep)) /
                                 (2.0 * halfStep_s);

    return {
        anInstant,
        -x_MOON_GCRF,
        -v_MOON_GCRF,
        Quaternion::Unit(),
        Vector3d::Zero(),
        Transform::Type::Passive,
    };
}

Vector3d MoonAnalytical::ComputePosition(const Instant& anInstant)
{
    // Ref: Montenbruck & Gill, Section 3.3.2. Accuracy: ~0.1-0.3 deg in direction (< 0.1 deg over 2020-2026).

    const double T = JulianCenturiesSinceJ2000(anInstant);

    // Mean elements of lunar orbit

    const double L_0 = FractionalPart(0.606433 + 1336.851344 * T);  // Mean longitude [rev] w.r.t. J2000 equinox
    const double l = TwoPi * FractionalPart(0.374897 + 1325.552410 * T);  // Moon's mean anomaly [rad]
    const double lp = TwoPi * FractionalPart(0.993133 + 99.997361 * T);   // Sun's mean anomaly [rad]
    const double D = TwoPi * FractionalPart(0.827361 + 1236.853086 * T);  // Diff. long. Moon - Sun [rad]
    const double F = TwoPi * FractionalPart(0.259086 + 1342.227825 * T);  // Argument of latitude [rad]

    // Ecliptic longitude (w.r.t. equinox of J2000)

    const double dL = 22640.0 * std::sin(l) - 4586.0 * std::sin(l - 2.0 * D) + 2370.0 * std::sin(2.0 * D) +
                      769.0 * std::sin(2.0 * l) - 668.0 * std::sin(lp) - 412.0 * std::sin(2.0 * F) -
                      212.0 * std::sin(2.0 * l - 2.0 * D) - 206.0 * std::sin(l + lp - 2.0 * D) +
                      192.0 * std::sin(l + 2.0 * D) - 165.0 * std::sin(lp - 2.0 * D) - 125.0 * std::sin(D) -
                      110.0 * std::sin(l + lp) + 148.0 * std::sin(l - lp) - 55.0 * std::sin(2.0 * F - 2.0 * D);  // ["]

    const double L = TwoPi * FractionalPart(L_0 + dL / 1296.0e3);  // [rad]

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

    return EquatorialFromEcliptic({r * std::cos(L) * std::cos(B), r * std::sin(L) * std::cos(B), r * std::sin(B)});
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
