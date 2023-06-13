/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Magnetic_Undefined__
#define __OpenSpaceToolkit_Physics_Environment_Magnetic_Undefined__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{

using ostk::core::types::Real;

using ostk::physics::units::Derived;
using ostk::physics::time::Instant;
using ostk::physics::environment::magnetic::Model;

/// @brief						Magnetic Undefined model

class Undefined : public Model
{
   public:
    /// @brief              Constructor

    Undefined();

    /// @brief              Clone the undefined magnetic model
    ///
    /// @return             Pointer to undefined magnetic model

    virtual Undefined* clone() const override;

    /// @brief              Check if the undefined magnetic model is defined
    ///
    /// @return             True if the undefined magnetic model is defined

    bool isDefined() const;

    /// @brief              Get the magnetic field value at a given position and instant
    ///
    /// @param              [in] aPosition A position, expressed in the magnetic object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Magnetic field value, expressed in the magnetic object frame [T]

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

};

}  // namespace magnetic
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
