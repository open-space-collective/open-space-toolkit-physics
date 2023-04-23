////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Model__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Model__

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Real ;

using ostk::math::obj::Vector3d ;

using ostk::physics::time::Instant ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Atmospheric model (interface)

class Model
{

    public:

        /// @brief              Constructor (default)

                                Model                                       ( ) ;

        /// @brief              Destructor (pure virtual)

        virtual                 ~Model                                      ( ) = 0 ;

        /// @brief              Clone the gravitational model (pure virtual)
        ///
        /// @return             Pointer to gravitational model

        virtual Model*          clone                                       ( ) const = 0 ;

        /// @brief              Get the gravitational field value at a given position and instant (pure virtual)
        ///
        /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
        /// @param              [in] anInstant An instant
        /// @return             Atmospheric field value, expressed in the gravitational object frame [m.s-2]

        virtual Real            getDensityAt                                (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const = 0 ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
