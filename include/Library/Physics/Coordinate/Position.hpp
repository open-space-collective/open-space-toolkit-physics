////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Position.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Position__
#define __Library_Physics_Coordinate_Position__

#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
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
using library::core::types::Weak ;
using library::core::types::Integer ;
using library::core::types::String ;

using library::math::obj::Vector3d ;

using library::physics::units::Length ;
using library::physics::time::Instant ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Frame ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Position

class Position
{

    public:

        typedef                 Length::Unit                                    Unit ;

                                Position                                    (   const   Vector3d&                   aCoordinateSet, // [TBI] Replace w/ Point
                                                                                const   Position::Unit&             aUnit,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

                                Position                                    (   const   Position&                   aPosition                                   ) ;

        Position&               operator =                                  (   const   Position&                   Position                                    ) = delete ;

        bool                    operator ==                                 (   const   Position&                   aPosition                                   ) const ;
        
        bool                    operator !=                                 (   const   Position&                   aPosition                                   ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Position&                   aPosition                                   ) ;

        bool                    isDefined                                   ( ) const ;

        const Vector3d&         accessCoordinates                           ( ) const ;

        Shared<const Frame>     accessFrame                                 ( ) const ;

        Vector3d                getCoordinates                              ( ) const ;

        Position::Unit          getUnit                                     ( ) const ;

        Position                inUnit                                      (   const   Position::Unit&             aUnit                                       ) const ;

        Position                inFrame                                     (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const ;

        String                  toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const ;

        static Position         Undefined                                   ( ) ;

        static Position         Meters                                      (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

    private:

        Vector3d                coordinates_ ;
        Position::Unit          unit_ ;
        Weak<const Frame>       frameWPtr_ ; // [TBR] With Transform instead, as Frame is a function of time...

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////