/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Direction__
#define __OpenSpaceToolkit_Physics_Data_Direction__

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Data/Vector.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::types::Shared;
using ostk::core::types::Integer;
using ostk::core::types::String;

using ostk::math::obj::Vector3d;

using ostk::physics::time::Instant;
using ostk::physics::coord::Frame;
using ostk::physics::data::Vector;

/// @brief                      Direction
///
///                             A unit vector, expressed in a given frame.

class Direction : public Vector
{
   public:
    Direction(const Vector3d& aValue, const Shared<const Frame>& aFrameSPtr);

    bool operator==(const Direction& aDirection) const;

    bool operator!=(const Direction& aDirection) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Vector& aVector);

    static Direction Undefined();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
