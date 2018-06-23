////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/DateTime.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/DateTime.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/regex.hpp>

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

                                DateTime::DateTime                          (           Uint16                      aYear,
                                                                                        Uint8                       aMonth,
                                                                                        Uint8                       aDay,
                                                                                        Uint8                       anHour,
                                                                                        Uint8                       aMinute,
                                                                                        Uint8                       aSecond,
                                                                                        Uint16                      aMillisecond,
                                                                                        Uint16                      aMicrosecond,
                                                                                        Uint16                      aNanosecond                                 )
                                :   date_({aYear, aMonth, aDay}),
                                    time_({anHour, aMinute, aSecond, aMillisecond, aMicrosecond, aNanosecond})
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

const Date&                     DateTime::accessDate                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("DateTime") ;
    }

    return date_ ;

}

const Time&                     DateTime::accessTime                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("DateTime") ;
    }

    return time_ ;

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

DateTime                        DateTime::ModifiedJulianDate                ( )
{
    return DateTime(Date::ModifiedJulianDate(), Time::Midnight()) ;
}

DateTime                        DateTime::Parse                             (   const   String&                     aString,
                                                                                const   DateTime::Format&           aFormat                                     )
{

    if (aString.isEmpty())
    {
        throw library::core::error::runtime::Undefined("String") ;
    }

    switch (aFormat)
    {

        case DateTime::Format::Undefined: // Automatic format detection
        {

            if (aString.match(std::regex("^([-]?[0-9]+-[0-9]{2}-[0-9]{2})T([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,9})?)$")))
            {
                return DateTime::Parse(aString, DateTime::Format::ISO8601) ;
            }
            
            return DateTime::Parse(aString, DateTime::Format::Standard) ;

        }

        case DateTime::Format::Standard:
        {

            boost::smatch match ;

            if (boost::regex_match(aString, match, boost::regex("^([-]?[0-9]+-[0-9]{2}-[0-9]{2}) ([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,3})?(?:\\.[0-9]{1,3})?(?:\\.[0-9]{1,3})?)$")))
            {
                return DateTime(Date::Parse(String(match[1])), Time::Parse(String(match[2]), Time::Format::Standard)) ;
            }
            else
            {
                throw library::core::error::RuntimeError("Cannot parse [Standard] date-time string [{}].", aString) ;
            }

        }

        case DateTime::Format::ISO8601:
        {

            boost::smatch match ;

            if (boost::regex_match(aString, match, boost::regex("^([-]?[0-9]+-[0-9]{2}-[0-9]{2})T([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,9})?)$")))
            {
                return DateTime(Date::Parse(String(match[1])), Time::Parse(String(match[2]), Time::Format::ISO8601)) ;
            }
            else
            {
                throw library::core::error::RuntimeError("Cannot parse [ISO 8601] date-time string [{}].", aString) ;
            }

        }

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return DateTime::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////