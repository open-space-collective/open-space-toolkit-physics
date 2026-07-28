/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/SunAnalytical.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

using ostk::physics::coordinate::frame::provider::utilities::EquatorialFromEcliptic;
using ostk::physics::coordinate::frame::provider::utilities::FractionalPart;
using ostk::physics::coordinate::frame::provider::utilities::JulianCenturiesSinceJ2000;
using ostk::physics::time::Duration;

namespace
{

// Analytical Sun position series
// Ref: O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2

constexpr double TwoPi = 2.0 * M_PI;

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

SunAnalytical::SunAnalytical() {}

SunAnalytical::~SunAnalytical() {}

SunAnalytical* SunAnalytical::clone() const
{
    return new SunAnalytical(*this);
}

bool SunAnalytical::isDefined() const
{
    return true;
}

Transform SunAnalytical::getTransformAt(const Instant& anInstant) const
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    const Vector3d x_SUN_GCRF = SunAnalytical::ComputePosition(anInstant);

    // Translational velocity via central finite difference of the analytical series

    static const Duration halfStep = Duration::Seconds(30.0);
    static const double halfStep_s = static_cast<double>(halfStep.inSeconds());

    const Vector3d v_SUN_GCRF =
        (SunAnalytical::ComputePosition(anInstant + halfStep) - SunAnalytical::ComputePosition(anInstant - halfStep)) /
        (2.0 * halfStep_s);

    return {
        anInstant,
        -x_SUN_GCRF,
        -v_SUN_GCRF,
        Quaternion::Unit(),
        Vector3d::Zero(),
        Transform::Type::Passive,
    };
}

Vector3d SunAnalytical::ComputePosition(const Instant& anInstant)
{
    // Ref: Montenbruck & Gill, Section 3.3.2.
    // Accuracy: < 0.1 deg in direction over 2020-2026,
    // dominated by a slow drift (~11.6 arcsec/year) due to the neglected motion of the Earth's perihelion.

    const double T = JulianCenturiesSinceJ2000(anInstant);

    // Mean anomaly, ecliptic longitude and radius

    const double M = TwoPi * FractionalPart(0.9931267 + 99.9973583 * T);  // [rad]
    const double L = TwoPi * FractionalPart(
                                 0.7859444 + (M / TwoPi) + (6892.0 * std::sin(M) + 72.0 * std::sin(2.0 * M)) / 1296.0e3
                             );                                                        // [rad]
    const double r = 149.619e9 - 2.499e9 * std::cos(M) - 0.021e9 * std::cos(2.0 * M);  // [m]

    // Equatorial position vector

    return EquatorialFromEcliptic({r * std::cos(L), r * std::sin(L), 0.0});
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
