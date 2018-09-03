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
#include <Library/Core/Types/Weak.hpp>
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
using library::core::types::Weak ;
using library::core::types::String ;
using library::core::ctnr::Array ;

using GeometricalObject = library::math::geom::d3::Object ;

using library::physics::time::Instant ;
using library::physics::env::Object ;
using library::physics::env::obj::Celestial ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Environment
{

    public:

                                Environment                                 (   const   Instant&                    anInstant,
                                                                                const   Array<Shared<Object>>&      anObjectArray                               ) ;

                                Environment                                 (   const   Environment&                anEnvironment                               ) ;

        Environment&            operator =                                  (   const   Environment&                anEnvironment                               ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Environment&                anEnvironment                               ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    hasObjectWithName                           (   const   String&                     aName                                       ) const ;

        Array<Shared<const Object>> accessObjects                           ( ) const ;
        
        Shared<const Object>    accessObjectWithName                        (   const   String&                     aName                                       ) const ;
        
        Shared<const Celestial> accessCelestialObjectWithName               (   const   String&                     aName                                       ) const ;

        Instant                 getInstant                                  ( ) const ;

        Array<String>           getObjectNames                              ( ) const ;

        void                    setInstant                                  (   const   Instant&                    anInstant                                   ) ;

        bool                    intersects                                  (   const   Object::Geometry&           aGeometry                                   ) const ;

        static Environment      Undefined                                   ( ) ;

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