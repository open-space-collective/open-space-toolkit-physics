////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Date.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Date.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Date::Date                                  (           Int16                       aYear,
                                                                                        Uint8                       aMonth,
                                                                                        Uint8                       aDay                                        )
                                :   defined_(true),
                                    year_(aYear),
                                    month_(aMonth),
                                    day_(aDay)
{

}

bool                            Date::operator ==                           (   const   Date&                       aDate                                       ) const
{

    if ((!this->isDefined()) || (!aDate.isDefined()))
    {
        return false ;
    }

    return (year_ == aDate.year_) && (month_ == aDate.month_) && (day_ == aDate.day_) ;

}

bool                            Date::operator !=                           (   const   Date&                       aDate                                       ) const
{

    if ((!this->isDefined()) || (!aDate.isDefined()))
    {
        return true ;
    }

    return (year_ != aDate.year_) || (month_ != aDate.month_) || (day_ != aDate.day_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Date&                       aDate                                       )
{

    library::core::utils::Print::Header(anOutputStream, "Date") ;

    library::core::utils::Print::Line(anOutputStream) << "Year:" << (aDate.isDefined() ? String::Format("{:d}", aDate.year_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Month:" << (aDate.isDefined() ? String::Format("{:d}", aDate.month_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Day:" << (aDate.isDefined() ? String::Format("{:d}", aDate.day_) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Date::isDefined                             ( ) const
{
    return defined_ ;
}

Int16                           Date::getYear                               ( ) const
{
    return year_ ;
}

Uint8                           Date::getMonth                              ( ) const
{
    return month_ ;
}

Uint8                           Date::getDay                                ( ) const
{
    return day_ ;
}

String                          Date::getString                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Date") ;
    }
    
    return String::Format("{0:d}-{1:02d}-{2:02d}", year_, month_, day_) ;

}

void                            Date::setYear                               (           Int16                       aYear                                       )
{
    year_ = aYear ;
}

void                            Date::setMonth                              (           Uint8                       aMonth                                      )
{
    month_ = aMonth ;
}

void                            Date::setDay                                (           Uint8                       aDay                                        )
{
    day_ = aDay ;
}

Date                            Date::Undefined                             ( )
{
    return Date() ;
}

Date                            Date::J2000                                 ( )
{
    return Date(2000, 1, 1) ;
}

Date                            Date::GPS                                   ( )
{
    return Date(1980, 1, 6) ;
}

Date                            Date::Unix                                  ( )
{
    return Date(1970, 1, 1) ;
}

Date                            Date::JulianDate                            ( )
{
    return Date(-4712, 1, 1) ;
}

Date                            Date::ModifiedJulianDate                    ( )
{
    return Date(1858, 11, 17) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Date::Date                                  ( )
                                :   defined_(false),
                                    year_(0),
                                    month_(0),
                                    day_(0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////