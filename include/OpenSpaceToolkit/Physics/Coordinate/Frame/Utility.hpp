/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Utility__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Utility__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace utilities
{

using ostk::core::type::Real;

using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::coordinate::Transform;
using ostk::physics::unit::Length;

/// @brief North-East-Down (NED) frame
///
/// @code
///     Transform transform = NorthEastDownTransformAt(lla, equatorialRadius, flattening) ;
/// @endcode
///
/// @ref https://en.wikipedia.org/wiki/North_east_down

Transform NorthEastDownTransformAt(
    const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
);

}  // namespace utilities
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
