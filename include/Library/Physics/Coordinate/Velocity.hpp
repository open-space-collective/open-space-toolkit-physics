////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Velocity.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Velocity__
#define __Library_Physics_Coordinate_Velocity__

#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Units/Derived.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;
using library::core::types::Weak ;
using library::core::types::String ;

using library::math::obj::Vector3d ;

using library::physics::units::Derived ;
using library::physics::time::Instant ;
using library::physics::coord::Position ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Frame ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Velocity

class Velocity
{

    public:

        enum class Unit
        {

            Undefined,
            MeterPerSecond

        } ;

                                Velocity                                    (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Velocity::Unit&             aUnit,
                                                                                const   Shared<const Frame>&        aFrame                                      ) ;

        bool                    operator ==                                 (   const   Velocity&                   aVelocity                                   ) const ;
        
        bool                    operator !=                                 (   const   Velocity&                   aVelocity                                   ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Velocity&                   aVelocity                                   ) ;

        bool                    isDefined                                   ( ) const ;

        const Vector3d&         accessCoordinates                           ( ) const ;

        Shared<const Frame>     accessFrame                                 ( ) const ;

        Velocity::Unit          getUnit                                     ( ) const ;

        Velocity                inUnit                                      (   const   Velocity::Unit&             aUnit                                       ) const ;

        Velocity                inFrame                                     (   const   Position&                   aPosition,
                                                                                const   Shared<const Frame>&        aFrame,
                                                                                const   Instant&                    anInstant                                   ) const ;

        String                  toString                                    ( ) const ;

        static Velocity         Undefined                                   ( ) ;

        static Velocity         MetersPerSecond                             (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrame                                      ) ;

        static String           StringFromUnit                              (   const   Velocity::Unit&             aUnit                                       ) ;

    private:

        Vector3d                coordinates_ ;
        Velocity::Unit          unit_ ;
        Weak<const Frame>       frameWPtr_ ; // [TBR] With Transform instead, as Frame is a function of time...

        static Derived::Unit    DerivedUnitFromVelocityUnit                 (   const   Velocity::Unit&             aUnit                                       ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////