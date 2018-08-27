////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Spherical/AER.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Spherical_AER__
#define __Library_Physics_Coordinate_Spherical_AER__

#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Units/Derived/Angle.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Core/Types/String.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{
namespace spherical
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::String ;

using library::math::obj::Vector3d ;

using library::physics::units::Angle ;
using library::physics::units::Length ;
using library::physics::coord::Position ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Azimuth - Elevation - Range (AER)

class AER
{

    public:

                                AER                                         (   const   Angle&                      anAzimuth,
                                                                                const   Angle&                      anElevation,
                                                                                const   Length&                     aRange                                      ) ;

        bool                    operator ==                                 (   const   AER&                        anAER                                       ) const ;
        
        bool                    operator !=                                 (   const   AER&                        anAER                                       ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   AER&                        anAER                                       ) ;

        bool                    isDefined                                   ( ) const ;

        Angle                   getAzimuth                                  ( ) const ;

        Angle                   getElevation                                ( ) const ;

        Length                  getRange                                    ( ) const ;

        Vector3d                toVector                                    ( ) const ;
        
        Vector3d                toCartesian                                 ( ) const ; // [TBI]

        String                  toString                                    ( ) const ;

        static AER              Undefined                                   ( ) ;

        static AER              Vector                                      (   const   Vector3d&                   aVector                                     ) ;

        static AER              FromPositionToPosition                      (   const   Position&                   aFromPosition,
                                                                                const   Position&                   aToPosition                                 ) ;

    private:

        Angle                   azimuth_ ;
        Angle                   elevation_ ;
        Length                  range_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////