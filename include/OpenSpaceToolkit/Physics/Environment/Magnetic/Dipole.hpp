/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole__
#define __OpenSpaceToolkit_Physics_Environment_Magnetic_Dipole__

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Real ;

using ostk::physics::units::Derived ;
using ostk::physics::time::Instant ;
using ostk::physics::environment::magnetic::Model ;

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
