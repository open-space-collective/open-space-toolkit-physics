////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Spherical/LLA.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Spherical_LLA__
#define __Library_Physics_Coordinate_Spherical_LLA__

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Latitude - Longitude - Altitude (LLA)
///
/// @ref                        https://en.wikipedia.org/wiki/Latitude#Geodetic_and_geocentric_latitudes

class LLA
{

    public:
    
        enum class Type
        {

            Undefined,
            Geocentric,
            Geodetic

        } ;

                                LLA                                         (   const   LLA::Type&                  aType,
                                                                                const   Angle&                      aLatitude,
                                                                                const   Angle&                      aLongitude,
                                                                                const   Length&                     anAltitude                                  ) ;

        bool                    operator ==                                 (   const   LLA&                        aLLA                                        ) const ;
        
        bool                    operator !=                                 (   const   LLA&                        aLLA                                        ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   LLA&                        aLLA                                        ) ;

        bool                    isDefined                                   ( ) const ;

        LLA::Type               getType                                     ( ) const ;

        Angle                   getLatitude                                 ( ) const ;

        Angle                   getLongitude                                ( ) const ;

        Length                  getAltitude                                 ( ) const ;

        Vector3d                toCartesian                                 ( ) const ;
        
        Vector3d                toCartesian                                 (   const   Length&                     anEllipsoidEquatorialRadius,
                                                                                const   Real&                       anEllipsoidFlattening                       ) const ;

        String                  toString                                    ( ) const ;

        static LLA              Undefined                                   ( ) ;

        static LLA              Geocentric                                  (   const   Angle&                      aLatitude,
                                                                                const   Angle&                      aLongitude,
                                                                                const   Length&                     anAltitude                                  ) ;

        static LLA              Geodetic                                    (   const   Angle&                      aLatitude,
                                                                                const   Angle&                      aLongitude,
                                                                                const   Length&                     anAltitude                                  ) ;

        static LLA              GeocentricFromCartesian                     (   const   Vector3d&                   aCartesianCoordinateSet                     ) ;

        static LLA              GeodeticFromCartesian                       (   const   Vector3d&                   aCartesianCoordinateSet,
                                                                                const   Length&                     anEllipsoidEquatorialRadius,
                                                                                const   Real&                       anEllipsoidFlattening                       ) ;

    private:

        LLA::Type               type_ ;

        Angle                   latitude_ ;
        Angle                   longitude_ ;
        Length                  altitude_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////