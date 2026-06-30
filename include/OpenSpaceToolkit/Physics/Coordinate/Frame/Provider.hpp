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

/// @brief Frame provider

class Provider
{
   public:
    /// @brief Default constructor.
    Provider();

    /// @brief Pure virtual destructor.
    virtual ~Provider() = 0;

    /// @brief Clone the provider.
    ///
    /// @return A pointer to the cloned provider
    virtual Provider* clone() const = 0;

    /// @brief Check if the provider is defined.
    ///
    /// @return True if the provider is defined
    virtual bool isDefined() const = 0;

    /// @brief Get the transform at a given instant.
    ///
    /// @param [in] anInstant An instant
    /// @return The transform at the given instant

    virtual Transform getTransformAt(const Instant& anInstant) const = 0;
};

}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
