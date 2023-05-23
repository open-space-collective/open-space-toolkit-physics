/// Apache License 2.0 

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth__

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>
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
namespace gravitational
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Unique ;
using ostk::core::types::Integer ;
using ostk::core::types::Real ;
using ostk::core::fs::Directory ;

using ostk::io::URL ;

using ostk::physics::units::Derived ;
using ostk::physics::time::Instant ;
using ostk::physics::environment::gravitational::Model ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Earth gravitational model
///
///                             The gravitational potential is expanded as sum of spherical harmonics.
///
/// @ref                        https://en.wikipedia.org/wiki/Spherical_harmonics
/// @ref                        https://geographiclib.sourceforge.io/html/gravity.html

class Earth : public Model
{

    public:

        enum class Type
        {

            Spherical,          ///< The spherical gravity originating from a point source at the center of the Earth
            WGS84,              ///< The normal gravitational field for the reference ellipsoid. This includes the zonal coefficients up to order 20.
            EGM84,              ///< The Earth Gravity Model 1984, which includes terms up to degree 180.
            EGM96,              ///< The Earth Gravity Model 1996, which includes terms up to degree 360.
            EGM2008             ///< The Earth Gravity Model 2008, which includes terms up to degree 2190.

        } ;

        /// @brief              Constructor with max degree and order variables
        ///
        /// @param              [in] aType A gravitational model type
        /// @param              [in] (optional) aDataDirectory A gravitational model data directory
        /// @param              [in] (optional) aGravityModelDegree A gravitational model degree
        /// @param              [in] (optional) aGravityModelOrder A gravitational model order

                                Earth                                       (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              =   Directory::Undefined(),
                                                                                const   Integer&                    aGravityModelDegree                         =   Integer::Undefined(),
                                                                                const   Integer&                    aGravityModelOrder                          =   Integer::Undefined() ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] anEarthGravitationalModel An Earth model

                                Earth                                       (   const   Earth&                      anEarthGravitationalModel                   ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] anEarthGravitationalModel An Earth model
        /// @return             Reference to Earth model

        Earth&                  operator =                                  (   const   Earth&                      anEarthGravitationalModel                   ) ;

        /// @brief              Destructor

                                ~Earth                                      ( ) ;

        /// @brief              Clone the Earth gravitational model
        ///
        /// @return             Pointer to Earth gravitational model

        virtual Earth*          clone                                       ( ) const override ;

        /// @brief              Get gravitational model type
        ///
        /// @return             Gravitational model type

        Earth::Type             getType                                     ( ) const ;

        /// @brief              Get the gravitational field value at a given position and instant
        ///
        /// @param              [in] aPosition A position, expressed in the gravitational object frame [m]
        /// @param              [in] anInstant An instant
        /// @return             Gravitational field value, expressed in the gravitational object frame [m.s-2]

        virtual Vector3d        getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const override ;

    private:

        class Impl ;
        class SphericalImpl ;
        class ExternalImpl ;

        Unique<Impl>            implUPtr_ ;

        static Unique<Impl>     ImplFromType                                (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory,
                                                                                const   Integer&                    aGravityModelDegree,
                                                                                const   Integer&                    aGravityModelOrder                          ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
