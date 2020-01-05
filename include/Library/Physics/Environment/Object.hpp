////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Object.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Object__
#define __Library_Physics_Environment_Object__

#include <Library/Physics/Environment/Object/Geometry.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Axes.hpp>
#include <Library/Physics/Coordinate/Velocity.hpp>
#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Geometry/3D/Object.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Shared.hpp>
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
using library::core::types::Shared ;
using library::core::types::String ;

using library::physics::time::Instant ;
using library::physics::coord::Position ;
using library::physics::coord::Velocity ;
using library::physics::coord::Axes ;
using library::physics::coord::Frame ;
using library::physics::coord::Transform ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Object
{

    public:

        typedef object::Geometry Geometry ;

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

        virtual Shared<const Frame> accessFrame                             ( ) const = 0 ;

        const Object::Geometry& accessGeometry                              ( ) const ;

        String                  getName                                     ( ) const ;

        Instant                 getInstant                                  ( ) const ;

        Object::Geometry        getGeometry                                 ( ) const ;

        virtual Position        getPositionIn                               (   const   Shared<const Frame>&        aFrameSPtr                                  ) const = 0 ;

        virtual Velocity        getVelocityIn                               (   const   Shared<const Frame>&        aFrameSPtr                                  ) const = 0 ;

        virtual Transform       getTransformTo                              (   const   Shared<const Frame>&        aFrameSPtr                                  ) const = 0 ;

        virtual Axes            getAxesIn                                   (   const   Shared<const Frame>&        aFrameSPtr                                  ) const = 0 ;

        Object::Geometry        getGeometryIn                               (   const   Shared<const Frame>&        aFrameSPtr                                  ) const ;

        void                    setInstant                                  (   const   Instant&                    anInstant                                   ) ;

    private:

        String                  name_ ;
        Instant                 instant_ ;

        Object::Geometry        geometry_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
