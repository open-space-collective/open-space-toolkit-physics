////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Gravitational/Earth.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Gravitational_Earth__
#define __Library_Physics_Environment_Gravitational_Earth__

#include <Library/Physics/Environment/Gravitational/Model.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Units/Derived.hpp>

#include <Library/IO/URL.hpp>

#include <Library/Core/FileSystem/Directory.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Unique.hpp>

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

using library::core::types::Unique ;
using library::core::types::Real ;
using library::core::fs::Directory ;

using library::io::URL ;

using library::physics::units::Derived ;
using library::physics::time::Instant ;
using library::physics::environment::gravitational::Model ;

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

            WGS84,              ///< The normal gravitational field for the reference ellipsoid. This includes the zonal coefficients up to order 20.
            EGM84,              ///< The Earth Gravity Model 1984, which includes terms up to degree 180.
            EGM96,              ///< The Earth Gravity Model 1996, which includes terms up to degree 360.
            EGM2008             ///< The Earth Gravity Model 2008, which includes terms up to degree 2190.

        } ;

        /// @brief              Constructor
        ///
        /// @param              [in] aType A gravitational model type
        /// @param              [in] (optional) aDataDirectory A gravitational model data directory

                                Earth                                       (   const   Earth::Type&                aType,
                                                                                const   Directory&                  aDataDirectory                              =   Directory::Undefined() ) ;

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

        Unique<Impl>            implUPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
