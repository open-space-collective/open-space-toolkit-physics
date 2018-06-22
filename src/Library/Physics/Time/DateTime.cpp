////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/DateTime.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/DateTime.hpp>

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

                                DateTime::DateTime                          (   const   Date&                       aDate,
                                                                                const   Time&                       aTime                                       )
                                :   date_(aDate),
                                    time_(aTime)
{

}

bool                            DateTime::operator ==                       (   const   DateTime&                   aDateTime                                   ) const
{

    if ((!this->isDefined()) || (!aDateTime.isDefined()))
    {
        return false ;
    }

    return (date_ == aDateTime.date_) && (time_ == aDateTime.time_) ;

}
        
bool                            DateTime::operator !=                       (   const   DateTime&                   aDateTime                                   ) const
{

    if ((!this->isDefined()) || (!aDateTime.isDefined()))
    {
        return true ;
    }

    return (date_ != aDateTime.date_) || (time_ != aDateTime.time_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   DateTime&                   aDateTime                                   )
{

    library::core::utils::Print::Header(anOutputStream, "DateTime") ;

    library::core::utils::Print::Line(anOutputStream) << "Year:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.date_.getYear()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Month:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.date_.getMonth()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Day:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.date_.getDay()) : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "Hour:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getHour()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Minute:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getMinute()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Second:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getSecond()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Millisecond:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getMillisecond()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Microsecond:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getMicrosecond()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Nanosecond:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getNanosecond()) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            DateTime::isDefined                         ( ) const
{
    return date_.isDefined() && time_.isDefined() ;
}

String                          DateTime::getString                         (   const   DateTime::Format&           aFormat                                     ) const
{
    
    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("DateTime") ;
    }

    switch (aFormat)
    {

        case DateTime::Format::Standard:
            return date_.getString() + " " + time_.getString(Time::Format::Standard) ;

        case DateTime::Format::ISO8601:
            return date_.getString() + "T" + time_.getString(Time::Format::ISO8601) ;

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return String::Empty() ;

}

DateTime                        DateTime::Undefined                         ( )
{
    return DateTime(Date::Undefined(), Time::Undefined()) ;
}

DateTime                        DateTime::J2000                             ( )
{
    return DateTime(Date::J2000(), Time::Noon()) ;
}

DateTime                        DateTime::GPS                               ( )
{
    return DateTime(Date::GPS(), Time::Midnight()) ;
}

DateTime                        DateTime::Unix                              ( )
{
    return DateTime(Date::Unix(), Time::Midnight()) ;
}

DateTime                        DateTime::JulianDate                        ( )
{
    return DateTime(Date::JulianDate(), Time::Noon()) ;
}

DateTime                        DateTime::ModifiedJulianDate                ( )
{
    return DateTime(Date::ModifiedJulianDate(), Time::Midnight()) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////