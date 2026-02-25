/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole__
#define __OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{

using ostk::core::type::Real;

using ostk::physics::environment::magnetic::Model;
using ostk::physics::time::Instant;
using ostk::physics::unit::Derived;

/// @brief Magnetic dipole model
///
/// @ref https://en.wikipedia.org/wiki/Magnetic_dipole
/// @ref https://en.wikipedia.org/wiki/Magnetic_moment
/// @ref https://en.wikipedia.org/wiki/Vacuum_permeability
/// @ref https://en.wikipedia.org/wiki/Dipole_model_of_the_Earth%27s_magnetic_field
class Dipole : public Model
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     Dipole model(magneticMoment);
    /// @endcode
    ///
    /// @param [in] aMagneticMoment A magnetic moment [A⋅m2]
    Dipole(const Vector3d& aMagneticMoment);

    /// @brief Clone the dipole magnetic model
    ///
    /// @code
    ///     Dipole* modelPtr = model.clone();
    /// @endcode
    ///
    /// @return Pointer to dipole magnetic model
    virtual Dipole* clone() const override;

    /// @brief Check if the dipole magnetic model is defined
    ///
    /// @code
    ///     bool isDefined = model.isDefined();
    /// @endcode
    ///
    /// @return True if the dipole magnetic model is defined
    virtual bool isDefined() const override;

    /// @brief Get the magnetic field value at a given position and instant
    ///
    /// @code
    ///     Vector3d fieldValue = model.getFieldValueAt(position, instant);
    /// @endcode
    ///
    /// @param [in] aPosition A position, expressed in the magnetic object frame [m]
    /// @param [in] anInstant An instant
    /// @return Magnetic field value, expressed in the magnetic object frame [T]
    virtual Vector3d getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const override;

   private:
    Vector3d magneticMoment_SI_;
};

}  // namespace magnetic
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
