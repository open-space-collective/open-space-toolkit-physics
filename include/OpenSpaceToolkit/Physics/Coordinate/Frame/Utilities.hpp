/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Utilities__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Utilities__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace utilities
{

using ostk::core::types::Real;

using ostk::physics::units::Length;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::coord::Transform;

/// @brief                      North-East-Down (NED) frame
///
/// @ref                        https://en.wikipedia.org/wiki/North_east_down

Transform NorthEastDownTransformAt(
    const LLA& aLLA, const Length& anEllipsoidEquatorialRadius, const Real& anEllipsoidFlattening
);

}  // namespace utilities
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
