////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Gravitational/Spherical.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Gravitational_Spherical__
#define __Library_Physics_Environment_Gravitational_Spherical__

#include <Library/Physics/Environment/Gravitational/Model.hpp>
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
namespace gravitational
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Real ;

using library::physics::units::Derived ;
using library::physics::time::Instant ;
using library::physics::environment::gravitational::Model ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Spherical gravitational model

class Spherical : public Model
{

    public:

        /// @brief              Constructor
        ///
        /// @param              [in] aGravitationalParameter A gravitational parameter

                                Spherical                                   (   const   Derived&                    aGravitationalParameter                     ) ;

        /// @brief              Clone the spherical gravitational model
        ///
        /// @return             Pointer to spherical gravitational model

        virtual Spherical*      clone                                       ( ) const override ;

        /// @brief              Get the gravitational field value at a given position and instant
        ///
        /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
        /// @param              [in] anInstant An instant
        /// @return             Gravitational field value, expressed in the gravitational object frame [m.s-2]

        virtual Vector3d        getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        Real                    gravitationalParameter_SI_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
