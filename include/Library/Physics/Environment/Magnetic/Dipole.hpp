////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Magnetic/Dipole.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole__
#define __OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole__

#include <Library/Physics/Environment/Magnetic/Model.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Units/Derived.hpp>

#include <Library/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace environment
{
namespace magnetic
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Real ;

using library::physics::units::Derived ;
using library::physics::time::Instant ;
using library::physics::environment::magnetic::Model ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief						Magnetic dipole model
///
/// @ref						https://en.wikipedia.org/wiki/Magnetic_dipole
/// @ref						https://en.wikipedia.org/wiki/Magnetic_moment
/// @ref                        https://en.wikipedia.org/wiki/Vacuum_permeability
/// @ref                        https://en.wikipedia.org/wiki/Dipole_model_of_the_Earth%27s_magnetic_field

class Dipole : public Model
{

    public:

        /// @brief              Constructor
        ///
        /// @param              [in] aMagneticMoment A magnetic moment [A⋅m2]

                                Dipole                                      (   const   Vector3d&                   aMagneticMoment                             ) ;

        /// @brief              Clone the dipole magnetic model
        ///
        /// @return             Pointer to dipole magnetic model

        virtual Dipole*         clone                                       ( ) const override ;

        /// @brief              Get the magnetic field value at a given position and instant
        ///
        /// @param              [in] aPosition A position, expressed in the magnetic object frame [m]
        /// @param              [in] anInstant An instant
        /// @return             Magnetic field value, expressed in the magnetic object frame [T]

        virtual Vector3d        getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        Vector3d                magneticMoment_SI_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
