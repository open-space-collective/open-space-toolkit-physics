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

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

                                Object                                      (   const   String&                     aName,
                                                                                const   Instant&                    anInstant                                   ) ;

        virtual                 ~Object                                     ( ) = 0 ;

        virtual Object*         clone                                       ( ) const = 0 ;

        virtual bool            isDefined                                   ( ) const ;

        const String&           accessName                                  ( ) const ;

        const Instant&          accessInstant                               ( ) const ;

        virtual Weak<const Frame> accessFrame                               ( ) const = 0 ;

        virtual Position        getPositionIn                               (   const   Frame&                      aFrame                                      ) const = 0 ;

        virtual Transform       getTransformTo                              (   const   Frame&                      aFrame                                      ) const = 0 ;

        virtual Axes            getAxesIn                                   (   const   Frame&                      aFrame                                      ) const = 0 ;

        void                    setInstant                                  (   const   Instant&                    anInstant                                   ) ;

    private:

        String                  name_ ;
        Instant                 instant_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////