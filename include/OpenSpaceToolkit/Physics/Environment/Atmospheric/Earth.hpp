////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp
/// @author         Kyle Cochran <kyle.cochran@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth__

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

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

using ostk::core::types::Unique ;
using ostk::core::types::Real ;
using ostk::core::fs::Directory ;

using ostk::physics::coord::spherical::LLA ;
using ostk::physics::environment::atmospheric::Model ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Earth atmospheric model

class Earth : public Model
{

    public:

        enum class Type
        {
            Exponential,
            NRLMSISE00
        } ;

        /// @brief              Constructor
        ///
        /// @param              [in] aType An atmospheric model type
        /// @param              [in] (optional) aDataDirectory An atmospheric model data directory

                                Earth                                       (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              =   Directory::Undefined() ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] anEarthAtmosphericModel An Earth atmospheric model

                                Earth                                       (   const   Earth&                      anEarthAtmosphericModel                     ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] anEarthAtmosphericModel An Earth atmospheric model
        /// @return             Reference to Earth atmospheric model

        Earth&                  operator =                                  (   const   Earth&                      anEarthAtmosphericModel                     ) ;

        /// @brief              Destructor

                                ~Earth                                      ( ) ;

        /// @brief              Clone the Earth atmospheric model
        ///
        /// @return             Pointer to Earth atmospheric model

        virtual Earth*          clone                                       ( ) const override ;

        /// @brief              Get atmospheric model type
        ///
        /// @return             Atmospheric model type

        Earth::Type             getType                                     ( ) const ;

        /// @brief              Get the atmospheric density value at a given position and instant
        ///
        /// @param              [in] aPosition A Position
        /// @param              [in] anInstant An Instant
        /// @return             Atmospheric density value [kg.m^-3]

        virtual Real            getDensityAt                                (   const   Position&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const override ;

        /// @brief              Get the atmospheric density value at a given position and instant
        ///
        /// @param              [in] aLLA A position, expressed as latitude, longitude, altitude [deg, deg, m]
        /// @param              [in] anInstant An instant
        /// @return             Atmospheric density value [kg.m^-3]

        Real                    getDensityAt                                (   const   LLA&                        aLLA,
                                                                                const   Instant&                    anInstant                                   ) const ;



    private:

        class Impl ;
        class ExponentialImpl ;

        Unique<Impl>            implUPtr_ ;

        static Unique<Impl>     ImplFromType                                (   const   Type&                       aType,
                                                                                const   Directory&                  aDataDirectory                              = Directory::Undefined() ) ;
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
