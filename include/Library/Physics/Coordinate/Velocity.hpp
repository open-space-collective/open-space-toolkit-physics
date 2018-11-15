////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Velocity.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Velocity__
#define __Library_Physics_Coordinate_Velocity__

#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Units/Derived.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>
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
using library::core::types::Integer ;
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
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

        bool                    operator ==                                 (   const   Velocity&                   aVelocity                                   ) const ;
        
        bool                    operator !=                                 (   const   Velocity&                   aVelocity                                   ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Velocity&                   aVelocity                                   ) ;

        bool                    isDefined                                   ( ) const ;

        const Vector3d&         accessCoordinates                           ( ) const ;

        Shared<const Frame>     accessFrame                                 ( ) const ;

        Vector3d                getCoordinates                              ( ) const ;

        Velocity::Unit          getUnit                                     ( ) const ;

        Velocity                inUnit                                      (   const   Velocity::Unit&             aUnit                                       ) const ;

        Velocity                inFrame                                     (   const   Position&                   aPosition,
                                                                                const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const ;

        String                  toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const ;

        static Velocity         Undefined                                   ( ) ;

        static Velocity         MetersPerSecond                             (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

        static String           StringFromUnit                              (   const   Velocity::Unit&             aUnit                                       ) ;

    private:

        Vector3d                coordinates_ ;
        Velocity::Unit          unit_ ;
        Shared<const Frame>     frameSPtr_ ; // [TBR] With Transform instead, as Frame is a function of time...

        static Derived::Unit    DerivedUnitFromVelocityUnit                 (   const   Velocity::Unit&             aUnit                                       ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////