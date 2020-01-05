////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Position.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Position__
#define __OpenSpaceToolkit_Physics_Coordinate_Position__

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Shared ;
using ostk::core::types::Integer ;
using ostk::core::types::String ;

using ostk::math::geom::d3::objects::Point ;
using ostk::math::obj::Vector3d ;

using ostk::physics::units::Length ;
using ostk::physics::time::Instant ;

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

        Position&               operator =                                  (   const   Position&                   aPosition                                   ) ;

        bool                    operator ==                                 (   const   Position&                   aPosition                                   ) const ;

        bool                    operator !=                                 (   const   Position&                   aPosition                                   ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Position&                   aPosition                                   ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isNear                                      (   const   Position&                   aPosition,
                                                                                const   Length&                     aLength                                     ) const ;

        const Vector3d&         accessCoordinates                           ( ) const ;

        Shared<const Frame>     accessFrame                                 ( ) const ;

        Vector3d                getCoordinates                              ( ) const ;

        Position::Unit          getUnit                                     ( ) const ;

        Position                inUnit                                      (   const   Position::Unit&             aUnit                                       ) const ;

        Position                inMeters                                    ( ) const ;

        Position                inFrame                                     (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const ;

        String                  toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const ;

        static Position         Undefined                                   ( ) ;

        static Position         Meters                                      (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

    private:

        Vector3d                coordinates_ ;
        Position::Unit          unit_ ;
        Shared<const Frame>     frameSPtr_ ; // [TBR] With Transform instead, as Frame is a function of time...

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
