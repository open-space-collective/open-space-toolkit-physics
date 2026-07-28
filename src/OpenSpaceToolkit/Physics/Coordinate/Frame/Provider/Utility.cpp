/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Utility.hpp>

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
namespace utilities
{

Vector3d EquatorialFromEcliptic(const Vector3d& anEclipticVector)
{
    const double cosObliquity = std::cos(ObliquityOfEclipticJ2000_rad);
    const double sinObliquity = std::sin(ObliquityOfEclipticJ2000_rad);

    return {
        anEclipticVector.x(),
        cosObliquity * anEclipticVector.y() - sinObliquity * anEclipticVector.z(),
        sinObliquity * anEclipticVector.y() + cosObliquity * anEclipticVector.z(),
    };
}

double JulianCenturiesSinceJ2000(const Instant& anInstant)
{
    // Computed from the elapsed duration since the J2000 epoch (2000-01-01 12:00:00 [TT], i.e. MJD 51544.5 [TT]):
    // elapsed SI seconds equal elapsed TT seconds (TT - TAI is a constant offset),
    // which avoids a costly Instant -> DateTime -> Modified Julian Date conversion.

    static const Instant j2000_TT = Instant::J2000();

    return static_cast<double>((anInstant - j2000_TT).inSeconds()) / (36525.0 * 86400.0);
}

double FractionalPart(const double aValue)
{
    return aValue - std::floor(aValue);
}

}  // namespace utilities
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
