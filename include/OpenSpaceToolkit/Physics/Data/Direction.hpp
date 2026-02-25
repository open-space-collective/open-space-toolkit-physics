/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Direction__
#define __OpenSpaceToolkit_Physics_Data_Direction__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Data/Vector.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::type::Integer;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::data::Vector;
using ostk::physics::time::Instant;

/// @brief Direction
///
/// A unit vector, expressed in a given frame.
class Direction : public Vector
{
   public:
    /// @brief Construct a direction from a 3D vector and a reference frame.
    ///
    /// @code
    ///     Direction direction({1.0, 0.0, 0.0}, Frame::GCRF());
    /// @endcode
    ///
    /// @param [in] aValue A 3D vector (will be normalized)
    /// @param [in] aFrameSPtr A shared pointer to the reference frame
    Direction(const Vector3d& aValue, const Shared<const Frame>& aFrameSPtr);

    /// @brief Output stream operator.
    ///
    /// @code
    ///     std::cout << direction;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aDirection A direction
    /// @return A reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Direction& aDirection);

    /// @brief Construct an undefined direction.
    ///
    /// @code
    ///     Direction direction = Direction::Undefined();
    /// @endcode
    ///
    /// @return An undefined direction
    static Direction Undefined();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
