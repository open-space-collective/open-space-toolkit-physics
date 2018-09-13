////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment__
#define __Library_Physics_Environment__

#include <Library/Physics/Environment/Objects/Celestial.hpp>
#include <Library/Physics/Environment/Object.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Geometry/3D/Object.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Shared.hpp>
#include <Library/Core/Types/Unique.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::Shared ;
using library::core::types::String ;
using library::core::ctnr::Array ;

using GeometricalObject = library::math::geom::d3::Object ;

using library::physics::time::Instant ;
using library::physics::env::Object ;
using library::physics::env::obj::Celestial ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Environment modeling

class Environment
{

    public:

        /// @brief              Constructor
        ///
        /// @param              [in] anInstant An instant
        /// @param              [in] An array of shared pointers to objects

                                Environment                                 (   const   Instant&                    anInstant,
                                                                                const   Array<Shared<Object>>&      anObjectArray                               ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] anEnvironment An environment

                                Environment                                 (   const   Environment&                anEnvironment                               ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] anEnvironment An environment
        /// @return             Reference to environment

        Environment&            operator =                                  (   const   Environment&                anEnvironment                               ) ;

        /// @brief              Output stream operator
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anEnvironment An environment
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Environment&                anEnvironment                               ) ;

        /// @brief              Check if environment is defined
        ///
        /// @return             True if environment is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Returns true if environment contains objects with a given name
        ///
        /// @param              [in] aName An object name
        /// @return             True if environment contains objects with a given name

        bool                    hasObjectWithName                           (   const   String&                     aName                                       ) const ;

        /// @brief              Returns true if a given geometry intersects any of the environment objects
        ///
        /// @param              [in] aGeometry A geometry
        /// @return             True if a given geometry intersects any of the environment objects

        bool                    intersects                                  (   const   Object::Geometry&           aGeometry                                   ) const ;

        /// @brief              Access objects
        ///
        /// @return             Reference to array of shared pointers to objects

        Array<Shared<const Object>> accessObjects                           ( ) const ;

        /// @brief              Access object with a given name
        ///
        /// @param              [in] aName An object name
        /// @return             Reference to shared pointer to object
        
        Shared<const Object>    accessObjectWithName                        (   const   String&                     aName                                       ) const ;

        /// @brief              Access celestial object with a given name
        ///
        /// @param              [in] aName A celestial object name
        /// @return             Reference to shared pointer to celestial object
        
        Shared<const Celestial> accessCelestialObjectWithName               (   const   String&                     aName                                       ) const ;

        /// @brief              Get instant
        ///
        /// @return             Instant

        Instant                 getInstant                                  ( ) const ;

        /// @brief              Get names of objects
        ///
        /// @return             Array of objects names

        Array<String>           getObjectNames                              ( ) const ;

        /// @brief              Set instant
        ///
        /// @param              [in] anInstant An instant

        void                    setInstant                                  (   const   Instant&                    anInstant                                   ) ;

        /// @brief              Constructs an undefined environment
        ///
        /// @code
        ///                     Environment environment = Environment::Undefined() ;
        ///                     environment.isDefined() ; // False
        /// @endcode
        ///
        /// @return             Undefined environment

        static Environment      Undefined                                   ( ) ;

        /// @brief              Constructs a default environment
        ///
        ///                     Contains Earth, Sun and Moon, with SPICE-based ephemeris.
        ///
        /// @code
        ///                     Environment environment = Environment::Default() ;
        /// @endcode
        ///
        /// @return             Undefined environment

        static Environment      Default                                     ( ) ;

    private:

        Instant                 instant_ ;
        Array<Shared<Object>>   objects_ ;

        void                    updateObjects                               ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////