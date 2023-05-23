/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <boost/regex.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
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
                                :   date_({ aYear, aMonth, aDay }),
                                    time_({ anHour, aMinute, aSecond, aMillisecond, aMicrosecond, aNanosecond })
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

    ostk::core::utils::Print::Header(anOutputStream, "DateTime") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Year:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.date_.getYear()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Month:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.date_.getMonth()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Day:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.date_.getDay()) : "Undefined") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Hour:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getHour()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Minute:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getMinute()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Second:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getSecond()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Millisecond:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getMillisecond()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Microsecond:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getMicrosecond()) : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Nanosecond:" << (aDateTime.isDefined() ? String::Format("{:d}", aDateTime.time_.getNanosecond()) : "Undefined") ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

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
        throw ostk::core::error::runtime::Undefined("DateTime") ;
    }

    return date_ ;

}

Time                            DateTime::getTime                           ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("DateTime") ;
    }

    return time_ ;

}

Date                            DateTime::getDate                           ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("DateTime") ;
    }

    return date_ ;

}

const Time&                     DateTime::accessTime                        ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("DateTime") ;
    }

    return time_ ;

}

Real                            DateTime::getJulianDate                     ( ) const
{

    using ostk::core::types::Int16 ;
    using ostk::core::types::Int32 ;

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("DateTime") ;
    }

    const Uint16 year = date_.getYear() ;
    const Uint8 month = date_.getMonth() ;
    const Uint8 day = date_.getDay() ;

    const Int32 julianDate = day
                           + 1461 * (year + 4800 + (month - 14) / 12) / 4
                           + 367 * (month - 2 - (month - 14) / 12 * 12) / 12
                           - 3 * ((year + 4900 + (month - 14) / 12) / 100) / 4
                           - 32075 ;

    const Int16 hour = time_.getHour() ;
    const Int16 minute = time_.getMinute() ;
    const Int16 second = time_.getSecond() ;
    const Uint16 millisecond = time_.getMillisecond() ;
    const Uint16 microsecond = time_.getMicrosecond() ;
    const Uint16 nanosecond = time_.getNanosecond() ;

    const Real fractionalDay = ((hour - 12.0) + (minute / 60.0) + (second / 3600.0) + ((millisecond / 1e3) + (microsecond / 1e6) + (nanosecond / 1e9)) / 3600.0) / 24.0 ;

    return Real(julianDate) + fractionalDay ;

}

Real                            DateTime::getModifiedJulianDate             ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("DateTime") ;
    }

    return DateTime::ModifiedJulianDateFromJulianDate(this->getJulianDate()) ;

}

String                          DateTime::toString                         (   const   DateTime::Format&           aFormat                                     ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("DateTime") ;
    }

    switch (aFormat)
    {

        case DateTime::Format::Standard:
            return date_.toString(Date::Format::Standard) + " " + time_.toString(Time::Format::Standard) ;

        case DateTime::Format::ISO8601:
            return date_.toString(Date::Format::Standard) + "T" + time_.toString(Time::Format::ISO8601) ;

        case DateTime::Format::STK:
            return date_.toString(Date::Format::STK) + " " + time_.toString(Time::Format::ISO8601) ;

        default:
            throw ostk::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return String::Empty() ;

}

DateTime                        DateTime::Undefined                         ( )
{
    return { Date::Undefined(), Time::Undefined() } ;
}

DateTime                        DateTime::J2000                             ( )
{
    return { Date::J2000(), Time::Noon() } ;
}

DateTime                        DateTime::GPSEpoch                          ( )
{
    return { Date::GPSEpoch(), Time::Midnight() } ;
}

DateTime                        DateTime::UnixEpoch                         ( )
{
    return { Date::UnixEpoch(), Time::Midnight() } ;
}

DateTime                        DateTime::ModifiedJulianDateEpoch           ( )
{
    return { Date::ModifiedJulianDateEpoch(), Time::Midnight() } ;
}

DateTime                        DateTime::JulianDate                        (   const   Real&                       aJulianDate                                 )
{

    using ostk::core::types::Int32 ;
    using ostk::core::types::Int64 ;
    using ostk::core::types::Uint32 ;
    using ostk::core::types::Uint64 ;

    if (!aJulianDate.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Julian Date") ;
    }

    if (aJulianDate < 0.0)
    {
        throw ostk::core::error::RuntimeError("Julian Date [{}] is negative.", aJulianDate) ;
    }

    // const Int32 J = std::floor(aJulianDate) ;

    // const Int32 y = 4716 ;
    // const Int32 v = 3 ;
    // const Int32 j = 1401 ;
    // const Int32 u = 5 ;
    // const Int32 m = 2 ;
    // const Int32 s = 153 ;
    // const Int32 n = 12 ;
    // const Int32 w = 2 ;
    // const Int32 r = 4 ;
    // const Int32 B = 274277 ;
    // const Int32 p = 1461 ;
    // const Int32 C = -38 ;

    // const Int32 f = J + j + (((4 * J + B) / 146097) * 3) / 4 + C ;
    // const Int32 e = r * f + v ;
    // const Int32 g = (e % p) / r ;
    // const Int32 h = u * g + w ;

    // const Int32 D = (h % s) / u + 1 ;
    // const Int32 M = ((h / s + m) % n) + 1 ;
    // const Int32 Y = (e / p) - y + (n + m - M) / n ;

    // Uint32 year = static_cast<Uint32>(Y) ;
    // Uint32 month = static_cast<Uint32>(M) ;
    // Uint32 day = static_cast<Uint32>(D) ;

    const Int64 integerJulianDate = std::floor(aJulianDate + 0.5) ;
    const double fractionalJulianDate = static_cast<double>(aJulianDate) - integerJulianDate + 0.5 ;

    const Int32 a = integerJulianDate + 32044 ;
    const Int32 b = std::floor((4 * a + 3) / 146097) ;
    const Int32 c = a - std::floor((b * 146097) / 4) ;

    const Int32 d = std::floor((4 * c + 3) / 1461) ;
    const Int32 e = c - std::floor((1461 * d) / 4) ;
    const Int32 m = std::floor((5 * e + 2) / 153) ;

    Uint32 year = static_cast<Uint32>(b * 100 + d - 4800 + std::floor(m / 10)) ;
    Uint32 month = static_cast<Uint32>(m + 3 - 12 * std::floor(m / 10)) ;
    Uint32 day = static_cast<Uint32>(e - std::floor((153 * m + 2) / 5) + 1) ;

    Uint64 nanosecondCountOfDay = Uint64(fractionalJulianDate * 86400.0 * 1e9) ;

    Uint32 hours = static_cast<Uint32>(std::floor(nanosecondCountOfDay / (3600.0 * 1e9))) ;

    if (nanosecondCountOfDay > Uint64(hours * 3600 * 1e9))
    {
        nanosecondCountOfDay -= Uint64(hours * 3600 * 1e9) ;
    }
    else
    {
        nanosecondCountOfDay = 0 ;
    }

    Uint32 minute = static_cast<Uint32>(std::floor(nanosecondCountOfDay / (60.0 * 1e9))) ;

    if (nanosecondCountOfDay > Uint64(minute * 60 * 1e9))
    {
        nanosecondCountOfDay -= Uint64(minute * 60 * 1e9) ;
    }
    else
    {
        nanosecondCountOfDay = 0 ;
    }

    Uint32 second = static_cast<Uint32>(std::floor(nanosecondCountOfDay / 1e9)) ;

    if (nanosecondCountOfDay > Uint64(second * 1e9))
    {
        nanosecondCountOfDay -= Uint64(second * 1e9) ;
    }
    else
    {
        nanosecondCountOfDay = 0 ;
    }

    Uint32 millisecond = static_cast<Uint32>(std::round(nanosecondCountOfDay / 1e6)) ;

    if (nanosecondCountOfDay > Uint64(millisecond * 1e6))
    {
        nanosecondCountOfDay -= Uint64(millisecond * 1e6) ;
    }
    else
    {
        nanosecondCountOfDay = 0 ;
    }

    Uint32 microsecond = static_cast<Uint32>(std::round(nanosecondCountOfDay / 1e3)) ;

    if (nanosecondCountOfDay > Uint64(microsecond * 1e3))
    {
        nanosecondCountOfDay -= Uint64(microsecond * 1e3) ;
    }
    else
    {
        nanosecondCountOfDay = 0 ;
    }

    Uint32 nanosecond = nanosecondCountOfDay ;

    if (millisecond == 1000)
    {
        second++ ;
        millisecond = 0 ;
    }

    if (second == 60)
    {
        minute++ ;
        second = 0 ;
    }

    if (minute == 60)
    {
        hours++ ;
        minute = 0 ;
    }

    if (hours == 24)
    {

        day++ ;
        hours = 0 ;

        if (day > 28)
        {
            throw ostk::core::error::RuntimeError("Implementation error.") ;
        }

    }

    return DateTime(year, month, day, hours, minute, second, millisecond, microsecond, nanosecond) ;

}

DateTime                        DateTime::ModifiedJulianDate                (   const   Real&                       aModifiedJulianDate                         )
{

    if (!aModifiedJulianDate.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Modified Julian Date") ;
    }

    if (aModifiedJulianDate < 0.0)
    {
        throw ostk::core::error::RuntimeError("Modified Julian Date [{}] is negative.", aModifiedJulianDate) ;
    }

    return DateTime::JulianDate(DateTime::JulianDateFromModifiedJulianDate(aModifiedJulianDate)) ;

}

DateTime                        DateTime::Parse                             (   const   String&                     aString,
                                                                                const   DateTime::Format&           aFormat                                     )
{

    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String") ;
    }

    switch (aFormat)
    {

        case DateTime::Format::Undefined: // Automatic format detection
        {

            if (aString.match(std::regex("^([-]?[0-9]+-[0-9]{2}-[0-9]{2})T([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,9})?)$")))
            {
                return DateTime::Parse(aString, DateTime::Format::ISO8601) ;
            }

            if (aString.match(std::regex("^([\\d]{1,2} [\\w]{3} [\\d]{4}) ([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,9})?)$")))
            {
                return DateTime::Parse(aString, DateTime::Format::STK) ;
            }

            return DateTime::Parse(aString, DateTime::Format::Standard) ;

        }

        case DateTime::Format::Standard:
        {

            boost::smatch match ;

            if (boost::regex_match(aString, match, boost::regex("^([-]?[0-9]+-[0-9]{2}-[0-9]{2}) ([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,3})?(?:\\.[0-9]{1,3})?(?:\\.[0-9]{1,3})?)$")))
            {
                return DateTime(Date::Parse(String(match[1]), Date::Format::Standard), Time::Parse(String(match[2]), Time::Format::Standard)) ;
            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot parse [Standard] date-time string [{}].", aString) ;
            }

        }

        case DateTime::Format::ISO8601:
        {

            boost::smatch match ;

            if (boost::regex_match(aString, match, boost::regex("^([-]?[0-9]+-[0-9]{2}-[0-9]{2})T([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,9})?)$")))
            {
                return DateTime(Date::Parse(String(match[1]), Date::Format::Standard), Time::Parse(String(match[2]), Time::Format::ISO8601)) ;
            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot parse [ISO 8601] date-time string [{}].", aString) ;
            }

        }

        case DateTime::Format::STK:
        {

            boost::smatch match ;

            if (boost::regex_match(aString, match, boost::regex("^([\\d]{1,2} [\\w]{3} [\\d]{4}) ([0-9]{2}:[0-9]{2}:[0-9]{2}(?:\\.[0-9]{1,9})?)$")))
            {
                return DateTime(Date::Parse(String(match[1]), Date::Format::STK), Time::Parse(String(match[2]), Time::Format::ISO8601)) ;
            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot parse [STK] date-time string [{}].", aString) ;
            }

        }

        default:
            throw ostk::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return DateTime::Undefined() ;

}

Real                            DateTime::ModifiedJulianDateFromJulianDate  (   const   Real&                       aJulianDate                                 )
{
    return aJulianDate - 2400000.5 ; // MJD = JD - 2400000.5 [day]
}

Real                            DateTime::JulianDateFromModifiedJulianDate  (   const   Real&                       aModifiedJulianDate                         )
{
    return aModifiedJulianDate + 2400000.5 ; // JD = MJD + 2400000.5 [day]
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
