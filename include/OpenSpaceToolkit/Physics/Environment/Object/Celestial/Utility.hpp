/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Utility__
#define __OpenSpaceToolkit_Physics_Environment_Object_Celestial_Utility__

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

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

using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Instant;

/// @brief Mean obliquity of the ecliptic at the J2000 epoch [rad]
constexpr double ObliquityOfEclipticJ2000_rad = 23.43929111 * M_PI / 180.0;

/// @brief Rotate a vector from the J2000 ecliptic plane to the mean equator and equinox of J2000.
Vector3d EquatorialFromEcliptic(const Vector3d& anEclipticVector);

/// @brief Julian centuries (TT) since J2000, i.e. (MJD_TT - 51544.5) / 36525.
double JulianCenturiesSinceJ2000(const Instant& anInstant);

/// @brief Return the fractional part of a value.
double FractionalPart(const double aValue);

}  // namespace utilities
}  // namespace celestial
}  // namespace object
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
