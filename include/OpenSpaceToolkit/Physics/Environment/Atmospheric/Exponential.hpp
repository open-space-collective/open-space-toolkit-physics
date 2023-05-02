////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Exponential.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Exponential__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Exponential__

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>

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

using ostk::physics::time::Instant ;
using ostk::physics::units::Length ;
using ostk::physics::environment::atmospheric::Model ;

using ostk::core::ctnr::Array ;
using ostk::core::ctnr::Tuple ;
using ostk::core::types::String ;
using ostk::core::types::Integer ;
using ostk::core::types::Real ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Exponential Atmospheric model

class Exponential : public Model
{

    public:

        /// @brief              Constructor

                                Exponential                                  () ;

        /// @brief              Clone the Exponential Atmospheric model
        ///
        /// @return             Pointer to Exponential Atmospheric model

        virtual Exponential*    clone                                       ( ) const override ;

        /// @brief              Get the atmospheric density value at a given position and instant
        ///
        /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
        /// @param              [in] anInstant An instant
        /// @return             Atmospheric density value [kg.m^-3]

        virtual Real            getDensityAt                                (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        static Tuple<Real, Real, Real> getDensityBandValues                 (   const   Length&                     anAltitude                                  ) ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
