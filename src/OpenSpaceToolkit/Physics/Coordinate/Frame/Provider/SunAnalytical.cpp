/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/SunAnalytical.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

using ostk::physics::time::Duration;

namespace
{

// Analytical Sun position series
// Ref: O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2

constexpr double Pi = M_PI;
constexpr double TwoPi = 2.0 * M_PI;
constexpr double ObliquityOfEclipticJ2000_rad = 23.43929111 * Pi / 180.0;

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

    const double T = SunAnalytical::JulianCenturiesSinceJ2000(anInstant);

    // Mean anomaly, ecliptic longitude and radius

    const double M = TwoPi * SunAnalytical::FractionalPart(0.9931267 + 99.9973583 * T);  // [rad]
    const double L = TwoPi * SunAnalytical::FractionalPart(
                                 0.7859444 + (M / TwoPi) + (6892.0 * std::sin(M) + 72.0 * std::sin(2.0 * M)) / 1296.0e3
                             );                                                        // [rad]
    const double r = 149.619e9 - 2.499e9 * std::cos(M) - 0.021e9 * std::cos(2.0 * M);  // [m]

    // Equatorial position vector

    return SunAnalytical::EquatorialFromEcliptic({r * std::cos(L), r * std::sin(L), 0.0});
}

Vector3d SunAnalytical::EquatorialFromEcliptic(const Vector3d& anEclipticVector)
{
    const double cosObliquity = std::cos(ObliquityOfEclipticJ2000_rad);
    const double sinObliquity = std::sin(ObliquityOfEclipticJ2000_rad);

    return {
        anEclipticVector.x(),
        cosObliquity * anEclipticVector.y() - sinObliquity * anEclipticVector.z(),
        sinObliquity * anEclipticVector.y() + cosObliquity * anEclipticVector.z(),
    };
}

double SunAnalytical::JulianCenturiesSinceJ2000(const Instant& anInstant)
{
    // Computed from the elapsed duration since the J2000 epoch (2000-01-01 12:00:00 [TT], i.e. MJD 51544.5 [TT]):
    // elapsed SI seconds equal elapsed TT seconds (TT - TAI is a constant offset),
    // which avoids a costly Instant -> DateTime -> Modified Julian Date conversion.

    static const Instant j2000_TT = Instant::J2000();

    return static_cast<double>((anInstant - j2000_TT).inSeconds()) / (36525.0 * 86400.0);
}

double SunAnalytical::FractionalPart(const double aValue)
{
    return aValue - std::floor(aValue);
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
