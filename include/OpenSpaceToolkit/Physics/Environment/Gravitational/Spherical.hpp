/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical__

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

/// @brief                      Spherical gravitational model

class Spherical : public Model
{
   public:
    /// @brief              Constructor
    ///
    /// @param              [in] aParameterSet A set of gravitational parameters

    Spherical(const Model::Parameters& aParameterSet);

    /// @brief              Clone the spherical gravitational model
    ///
    /// @return             Pointer to spherical gravitational model

    virtual Spherical* clone() const override;

    /// @brief              Check if the spherical gravitational model is defined
    ///
    /// @return             True if the spherical gravitational model is defined

    virtual bool isDefined() const override;

    /// @brief              Get the gravitational field value at a given position and instant
    ///
    /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
    /// @param              [in] anInstant An instant
    /// @return             Gravitational field value, expressed in the gravitational object frame [m.s-2]

    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    Real gravitationalParameter_SI_;
};

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
