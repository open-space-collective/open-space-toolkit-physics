/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Undefined__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Undefined__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::core::types::Real;

using ostk::physics::units::Derived;
using ostk::physics::time::Instant;
using ostk::physics::environment::gravitational::Model;

/// @brief						Gravitational Undefined model

class Undefined : public Model
{
   public:
    /// @brief              Constructor

    Undefined();

    /// @brief              Clone the undefined gravitational model
    ///
    /// @return             Pointer to undefined gravitational model

    virtual Undefined* clone() const override;

    /// @brief              Check if the undefined gravitational model is defined
    ///
    /// @return             True if the undefined gravitational model is defined

    bool isDefined() const;

    /// @brief              Get the gravitational field value at a given position and instant
    ///
    /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Gravitational field value, expressed in the gravitational object frame [T]

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

};

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
