////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment__
#define __Library_Physics_Environment__

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Environment
{

    public:

                                Environment                                 (   const   Instant&                    anInstant,
                                                                                const   Array<Shared<Object>>&      anObjectArray                               ) ;

                                Environment                                 (   const   Environment&                anEnvironment                               ) ;

        Environment&            operator =                                  (   const   Environment&                anEnvironment                               ) ;

        bool                    isDefined                                   ( ) const ;

        Weak<const Object>      accessObjectWithName                        (   const   String&                     aName                                       ) const ;

        Instant                 getInstant                                  ( ) const ;

        void                    setInstant                                  (   const   Instant&                    anInstant                                   ) ;

        bool                    intersects                                  (   const   GeometricalObject&          aGeometricalObject                          ) const ;

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