////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Model__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Model__

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>

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
using ostk::physics::coord::spherical::LLA ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Atmospheric model (interface)

class Model
{

    public:

        /// @brief              Constructor (default)

                                Model                                       ( ) ;

        /// @brief              Destructor (pure virtual)

        virtual                 ~Model                                      ( ) = 0 ;

        /// @brief              Clone the atmospheric model (pure virtual)
        ///
        /// @return             Pointer to atmospheric model

        virtual Model*          clone                                       ( ) const = 0 ;

        /// @brief              Get the atmospheric density value at a given position and instant
        ///
        /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
        /// @param              [in] anInstant An instant
        /// @return             Atmospheric density value [kg.m^-3]

        virtual Real            getDensityAt                                (   const   LLA&                        aLLA,
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
