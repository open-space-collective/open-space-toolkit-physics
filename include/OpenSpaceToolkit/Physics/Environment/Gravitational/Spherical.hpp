/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Spherical__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::core::type::Real;

using ostk::physics::environment::gravitational::Model;
using ostk::physics::time::Instant;
using ostk::physics::unit::Derived;

/// @brief Spherical gravitational model
class Spherical : public Model
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     Spherical model(parameters) ;
    /// @endcode
    ///
    /// @param [in] aParameterSet A set of gravitational parameters
    Spherical(const Model::Parameters& aParameterSet);

    /// @brief Clone the spherical gravitational model
    ///
    /// @code
    ///     Spherical* modelPtr = model.clone() ;
    /// @endcode
    ///
    /// @return Pointer to spherical gravitational model
    virtual Spherical* clone() const override;

    /// @brief Check if the spherical gravitational model is defined
    ///
    /// @code
    ///     bool isDefined = model.isDefined() ;
    /// @endcode
    ///
    /// @return True if the spherical gravitational model is defined
    virtual bool isDefined() const override;

    /// @brief Get the gravitational field value at a given position and instant
    ///
    /// @code
    ///     Vector3d fieldValue = model.getFieldValueAt(position, instant) ;
    /// @endcode
    ///
    /// @param [in] aPosition A position, expressed in the gravitational object frame [m]
    /// @param [in] anInstant An instant
    /// @return Gravitational field value, expressed in the gravitational object frame [m.s-2]
    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    Real gravitationalParameter_SI_;
};

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
