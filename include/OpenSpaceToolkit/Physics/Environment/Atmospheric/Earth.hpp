////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth__

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Model.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

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
using ostk::core::types::Integer ;
using ostk::core::types::Real ;
using ostk::core::fs::Directory ;

using ostk::io::URL ;

using ostk::physics::units::Derived ;
using ostk::physics::time::Instant ;
using ostk::physics::environment::atmospheric::Model ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Earth atmospheric model
///
///                             The atmospheric potential is expanded as sum of spherical harmonics.
///
/// @ref                        https://en.wikipedia.org/wiki/Spherical_harmonics
/// @ref                        https://geographiclib.sourceforge.io/html/gravity.html

class Earth : public Model
{

    public:

        enum class Type
        {
                NRLMSISE00           /// Naval Research Lab Model
                

        } ;

        /// @brief              Constructor with max degree and order variables
        ///
        /// @param              [in] aType A atmospheric model type
        /// @param              [in] (optional) aDataDirectory A atmospheric model data directory
        /// @param              [in] (optional) aGravityModelDegree A atmospheric model degree
        /// @param              [in] (optional) aGravityModelOrder A atmospheric model order

                                Earth                                       (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              =   Directory::Undefined()) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] anEarthAtmosphericModel An Earth model

                                Earth                                       (   const   Earth&                      anEarthAtmosphericModel                   ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] anEarthAtmosphericModel An Earth model
        /// @return             Reference to Earth model

        Earth&                  operator =                                  (   const   Earth&                      anEarthAtmosphericModel                   ) ;

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

        /// @brief              Get the atmospheric density at a given position and instant
        ///
        /// @param              [in] aPosition A position, expressed in the atmospheric object frame [m]
        /// @param              [in] anInstant An instant
        /// @return             Atmospheric field value, expressed in the atmospheric object frame [m.s-2]

        virtual Real            getDensityAt                                    (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        class Impl ;
        class SphericalImpl ;
        class ExternalImpl ;

        Unique<Impl>            implUPtr_ ;

        static Unique<Impl>     ImplFromType                                (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                             ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
