/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Utility.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace object
{
namespace celestial
{
namespace utilities
{

using ostk::physics::time::Scale;

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
    return static_cast<double>(anInstant.getModifiedJulianDate(Scale::TT) - 51544.5) / 36525.0;
}

double FractionalPart(const double aValue)
{
    return aValue - std::floor(aValue);
}

}  // namespace utilities
}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk
