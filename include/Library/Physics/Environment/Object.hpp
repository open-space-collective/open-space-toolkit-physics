////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Object__
#define __Library_Physics_Environment_Object__

#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Axes.hpp>
#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Geometry/3D/Object.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Unique.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::Weak ;
using library::core::types::String ;

using library::physics::time::Instant ;
using library::physics::coord::Position ;
using library::physics::coord::Axes ;
using library::physics::coord::Frame ;
using library::physics::coord::Transform ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Object
{

    public:
    
        typedef library::math::geom::d3::Object Geometry ;

                                Object                                      (   const   String&                     aName,
                                                                                const   Instant&                    anInstant                                   ) ;

                                Object                                      (   const   String&                     aName,
                                                                                const   Instant&                    anInstant,
                                                                                const   Object::Geometry&           aGeometry                                   ) ;

                                Object                                      (   const   Object&                     anObject                                    ) ;

        virtual                 ~Object                                     ( ) = 0 ;

        virtual Object*         clone                                       ( ) const = 0 ;

        Object&                 operator =                                  (   const   Object&                     anObject                                    ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Object&                     anObject                                    ) ;

        virtual bool            isDefined                                   ( ) const ;

        const String&           accessName                                  ( ) const ;

        const Instant&          accessInstant                               ( ) const ;

        virtual Weak<const Frame> accessFrame                               ( ) const = 0 ;

        virtual const Object::Geometry& accessGeometry                      ( ) const ;

        Frame                   getFrame                                    ( ) const ;

        virtual Position        getPositionIn                               (   const   Frame&                      aFrame                                      ) const = 0 ;

        virtual Transform       getTransformTo                              (   const   Frame&                      aFrame                                      ) const = 0 ;

        virtual Axes            getAxesIn                                   (   const   Frame&                      aFrame                                      ) const = 0 ;

        void                    setInstant                                  (   const   Instant&                    anInstant                                   ) ;

    private:

        String                  name_ ;
        Instant                 instant_ ;

        Unique<Object::Geometry> geometryUPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////