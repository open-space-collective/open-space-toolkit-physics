/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider__

#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{

using ostk::physics::coordinate::Transform;
using ostk::physics::time::Instant;

/// @brief                      Frame provider

class Provider
{
   public:
    Provider();

    virtual ~Provider() = 0;

    virtual Provider* clone() const = 0;

    virtual bool isDefined() const = 0;

    virtual Transform getTransformAt(const Instant& anInstant) const = 0;
};

}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
