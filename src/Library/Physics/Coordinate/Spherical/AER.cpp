////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Spherical/AER.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Spherical/AER.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

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

                                AER::AER                                    (   const   Angle&                      anAzimuth,
                                                                                const   Angle&                      anElevation,
                                                                                const   Length&                     aRange                                      )
                                :   azimuth_(anAzimuth),
                                    elevation_(anElevation),
                                    range_(aRange)
{

}

bool                            AER::operator ==                            (   const   AER&                        anAER                                       ) const
{

    if ((!this->isDefined()) || (!anAER.isDefined()))
    {
        return false ;
    }

    return (azimuth_ == anAER.azimuth_) && (elevation_ == anAER.elevation_) && (range_ == anAER.range_) ;

}

bool                            AER::operator !=                            (   const   AER&                        anAER                                       ) const
{
    return !((*this) == anAER) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   AER&                        anAER                                       )
{

    library::core::utils::Print::Header(anOutputStream, "AER") ;

    library::core::utils::Print::Line(anOutputStream) << "Azimuth:"             << (anAER.azimuth_.isDefined() ? anAER.azimuth_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Elevation:"           << (anAER.elevation_.isDefined() ? anAER.elevation_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Range:"               << (anAER.range_.isDefined() ? anAER.range_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            AER::isDefined                              ( ) const
{
    return azimuth_.isDefined() && elevation_.isDefined() && range_.isDefined() ;
}

Angle                           AER::getAzimuth                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("AER") ;
    }
    
    return azimuth_ ;

}

Angle                           AER::getElevation                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("AER") ;
    }
    
    return elevation_ ;

}

Length                          AER::getRange                               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("AER") ;
    }
    
    return range_ ;

}

Vector3d                        AER::toVector                               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("AER") ;
    }
    
    return Vector3d(azimuth_.inDegrees(), elevation_.inDegrees(), range_.inMeters()) ;

}

// Vector3d                        AER::toCartesian                            ( ) const
// {

//     if (!this->isDefined())
//     {
//         throw library::core::error::runtime::Undefined("AER") ;
//     }



// }

String                          AER::toString                               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("AER") ;
    }
    
    return String::Format("[{}, {}, {}]", azimuth_.toString(), elevation_.toString(), range_.toString()) ;

}

AER                             AER::Undefined                              ( )
{
    return AER(Angle::Undefined(), Angle::Undefined(), Length::Undefined()) ;
}

AER                             AER::Vector                                 (   const   Vector3d&                   aVector                                     )
{

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }
    
    return AER(Angle::Degrees(aVector.x()), Angle::Degrees(aVector.y()), Length::Meters(aVector.z())) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////