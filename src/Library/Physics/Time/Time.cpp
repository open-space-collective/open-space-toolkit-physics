////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Time.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Time.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Time::Time                                  (           Uint8                       anHour,
                                                                                        Uint8                       aMinute,
                                                                                        Uint8                       aSecond,
                                                                                        Uint16                      aMillisecond,
                                                                                        Uint16                      aMicrosecond,
                                                                                        Uint16                      aNanosecond                                 )
                                :   defined_(true),
                                    hour_(anHour),
                                    minute_(aMinute),
                                    second_(aSecond),
                                    millisecond_(aMillisecond),
                                    microsecond_(aMicrosecond),
                                    nanosecond_(aNanosecond)
{

    Time::ValidateHour(hour_) ;
    Time::ValidateMinute(minute_) ;
    Time::ValidateSecond(second_) ;
    Time::ValidateMillisecond(millisecond_) ;
    Time::ValidateMicrosecond(microsecond_) ;
    Time::ValidateNanosecond(nanosecond_) ;

}

bool                            Time::operator ==                           (   const   Time&                       aTime                                       ) const
{

    if ((!this->isDefined()) || (!aTime.isDefined()))
    {
        return false ;
    }

    return (hour_ == aTime.hour_)
        && (minute_ == aTime.minute_)
        && (second_ == aTime.second_)
        && (millisecond_ == aTime.millisecond_)
        && (microsecond_ == aTime.microsecond_)
        && (nanosecond_ == aTime.nanosecond_) ;

}

bool                            Time::operator !=                           (   const   Time&                       aTime                                       ) const
{

    if ((!this->isDefined()) || (!aTime.isDefined()))
    {
        return true ;
    }

    return (hour_ != aTime.hour_)
        || (minute_ != aTime.minute_)
        || (second_ != aTime.second_)
        || (millisecond_ != aTime.millisecond_)
        || (microsecond_ != aTime.microsecond_)
        || (nanosecond_ != aTime.nanosecond_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Time&                       aTime                                       )
{

    library::core::utils::Print::Header(anOutputStream, "Time") ;

    library::core::utils::Print::Line(anOutputStream) << "Hour:" << (aTime.isDefined() ? String::Format("{:d}", aTime.hour_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Minute:" << (aTime.isDefined() ? String::Format("{:d}", aTime.minute_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Second:" << (aTime.isDefined() ? String::Format("{:d}", aTime.second_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Millisecond:" << (aTime.isDefined() ? String::Format("{:d}", aTime.millisecond_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Microsecond:" << (aTime.isDefined() ? String::Format("{:d}", aTime.microsecond_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Nanosecond:" << (aTime.isDefined() ? String::Format("{:d}", aTime.nanosecond_) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Time::isDefined                             ( ) const
{
    return defined_ ;
}

Uint8                           Time::getHour                               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }
    
    return hour_ ;

}

Uint8                           Time::getMinute                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }
    
    return minute_ ;

}

Uint8                           Time::getSecond                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }
    
    return second_ ;

}

Uint16                          Time::getMillisecond                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }
    
    return millisecond_ ;

}

Uint16                          Time::getMicrosecond                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }
    
    return microsecond_ ;

}

Uint16                          Time::getNanosecond                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }
    
    return nanosecond_ ;

}

String                          Time::toString                             (   const   Time::Format&               aFormat                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    switch (aFormat)
    {

        case Time::Format::Standard:
        {

            if (nanosecond_ == 0)
            {

                if (microsecond_ == 0)
                {

                    if (millisecond_ == 0)
                    {
                        return String::Format("{0:02d}:{1:02d}:{2:02d}", hour_, minute_, second_) ;
                    }

                    return String::Format("{0:02d}:{1:02d}:{2:02d}.{3:03d}", hour_, minute_, second_, millisecond_) ;

                }

                return String::Format("{0:02d}:{1:02d}:{2:02d}.{3:03d}.{4:03d}", hour_, minute_, second_, millisecond_, microsecond_) ;

            }

            return String::Format("{0:02d}:{1:02d}:{2:02d}.{3:03d}.{4:03d}.{5:03d}", hour_, minute_, second_, millisecond_, microsecond_, nanosecond_) ;

        }

        case Time::Format::ISO8601:
        {

            if (nanosecond_ == 0)
            {

                if (microsecond_ == 0)
                {

                    if (millisecond_ == 0)
                    {
                        return String::Format("{0:02d}:{1:02d}:{2:02d}", hour_, minute_, second_) ;
                    }

                    return String::Format("{0:02d}:{1:02d}:{2:02d}.{3:03d}", hour_, minute_, second_, millisecond_) ;

                }

                return String::Format("{0:02d}:{1:02d}:{2:02d}.{3:03d}{4:03d}", hour_, minute_, second_, millisecond_, microsecond_) ;

            }

            return String::Format("{0:02d}:{1:02d}:{2:02d}.{3:03d}{4:03d}{5:03d}", hour_, minute_, second_, millisecond_, microsecond_, nanosecond_) ;

        }

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }
    
    return String::Empty() ;

}

void                            Time::setHour                               (           Uint8                       anHour                                      )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    Time::ValidateHour(anHour) ;

    hour_ = anHour ;

}

void                            Time::setMinute                             (           Uint8                       aMinute                                     )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    Time::ValidateMinute(aMinute) ;

    minute_ = aMinute ;

}

void                            Time::setSecond                             (           Uint8                       aSecond                                     )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    Time::ValidateSecond(aSecond) ;

    second_ = aSecond ;

}

void                            Time::setMillisecond                        (           Uint16                      aMillisecond                                )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    Time::ValidateMillisecond(aMillisecond) ;

    millisecond_ = aMillisecond ;

}

void                            Time::setMicrosecond                        (           Uint16                      aMicrosecond                                )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    Time::ValidateMicrosecond(aMicrosecond) ;

    microsecond_ = aMicrosecond ;

}

void                            Time::setNanosecond                         (           Uint16                      aNanosecond                                 )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    Time::ValidateNanosecond(aNanosecond) ;

    nanosecond_ = aNanosecond ;

}

Time                            Time::Undefined                             ( )
{
    return Time() ;
}

Time                            Time::Midnight                              ( )
{
    return Time(0, 0, 0, 0, 0, 0) ;
}

Time                            Time::Noon                                  ( )
{
    return Time(12, 0, 0, 0, 0, 0) ;
}

Time                            Time::Parse                                 (   const   String&                     aString,
                                                                                const   Time::Format&               aFormat                                     )
{

    if (aString.isEmpty())
    {
        throw library::core::error::runtime::Undefined("String") ;
    }

    switch (aFormat)
    {

        case Time::Format::Undefined: // Automatic format detection
        {

            if (aString.match(std::regex("^([0-9]{2}).([0-9]{2}).([0-9]{2})(?:.([0-9]{1,9}))?$")))
            {
                return Time::Parse(aString, Time::Format::ISO8601) ;
            }
            
            return Time::Parse(aString, Time::Format::Standard) ;

        }

        case Time::Format::Standard:
        {

            boost::smatch match ;

            if (boost::regex_match(aString, match, boost::regex("^([0-9]{2}).([0-9]{2}).([0-9]{2})(?:.([0-9]{1,3}))?(?:.([0-9]{1,3}))?(?:.([0-9]{1,3}))?$")))
            {

                try
                {

                    // https://stackoverflow.com/questions/9601919/converting-from-stdstring-to-uint8

                    const Uint8 hour = static_cast<Uint8>(boost::lexical_cast<int>(match[1])) ;
                    const Uint8 minute = static_cast<Uint8>(boost::lexical_cast<int>(match[2])) ;
                    const Uint8 second = static_cast<Uint8>(boost::lexical_cast<int>(match[3])) ;

                    auto parseFractionalString =
                    [ ] (const String& aFractionalString) -> Uint16
                    {

                        switch (aFractionalString.getLength())
                        {

                            case 1:
                                return boost::lexical_cast<Uint16>(aFractionalString) * 100 ;

                            case 2:
                                return boost::lexical_cast<Uint16>(aFractionalString) * 10 ;

                            case 3:
                                return boost::lexical_cast<Uint16>(aFractionalString) ;

                            default:
                                throw library::core::error::RuntimeError("Cannot parse fractional string [" + aFractionalString + "].") ;
                                break ;

                        }

                        return 0 ;

                    } ;

                    const Uint16 millisecond = (match[4] != "") ? parseFractionalString(String(match[4])) : 0 ;
                    const Uint16 microsecond = (match[5] != "") ? parseFractionalString(String(match[5])) : 0 ;
                    const Uint16 nanosecond = (match[6] != "") ? parseFractionalString(String(match[6])) : 0 ;

                    return Time(hour, minute, second, millisecond, microsecond, nanosecond) ;

                }
                catch (const boost::bad_lexical_cast& e)
                {

                    throw library::core::error::RuntimeError(String::Format("Cannot parse time string [{0}] ({1}).", aString, e.what())) ;

                }

            }
            else
            {
                throw library::core::error::RuntimeError("Cannot parse time string [" + aString + "].") ;
            }

        }

        case Time::Format::ISO8601:
        {

            boost::smatch match ;

            if (boost::regex_match(aString, match, boost::regex("^([0-9]{2}).([0-9]{2}).([0-9]{2})(?:.([0-9]{1,9}))?$")))
            {

                try
                {

                    const Uint8 hour = static_cast<Uint8>(boost::lexical_cast<int>(match[1])) ;
                    const Uint8 minute = static_cast<Uint8>(boost::lexical_cast<int>(match[2])) ;
                    const Uint8 second = static_cast<Uint8>(boost::lexical_cast<int>(match[3])) ;

                    Uint16 millisecond = 0 ;
                    Uint16 microsecond = 0 ;
                    Uint16 nanosecond = 0 ;

                    if (match[4] != "")
                    {

                        const String floatingPartString(match[4]) ;

                        switch (floatingPartString.getLength())
                        {

                            case 1:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString) * 100 ;
                                break ;

                            case 2:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString) * 10 ;
                                break ;

                            case 3:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString) ;
                                break ;

                            case 4:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(0, 3)) ;
                                microsecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(3, 1)) * 100 ;
                                break ;

                            case 5:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(0, 3)) ;
                                microsecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(3, 2)) * 10 ;
                                break ;

                            case 6:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(0, 3)) ;
                                microsecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(3, 3)) ;
                                break ;

                            case 7:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(0, 3)) ;
                                microsecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(3, 3)) ;
                                nanosecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(6, 1)) * 100 ;
                                break ;

                            case 8:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(0, 3)) ;
                                microsecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(3, 3)) ;
                                nanosecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(6, 2)) * 10 ;
                                break ;

                            case 9:
                                millisecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(0, 3)) ;
                                microsecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(3, 3)) ;
                                nanosecond = boost::lexical_cast<Uint16>(floatingPartString.getSubstring(6, 3)) ;
                                break ;

                            default:
                                break ;

                        }

                    }

                    return Time(hour, minute, second, millisecond, microsecond, nanosecond) ;

                }
                catch (const boost::bad_lexical_cast& e)
                {
                    throw library::core::error::RuntimeError(String::Format("Cannot parse time string [{0}] ({1}).", aString, e.what())) ;
                }

            }
            else
            {
                throw library::core::error::RuntimeError("Cannot parse time string [{}].", aString) ;
            }

        }

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return Time::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Time::Time                                  ( )
                                :   defined_(false),
                                    hour_(0),
                                    minute_(0),
                                    second_(0),
                                    millisecond_(0),
                                    microsecond_(0),
                                    nanosecond_(0)
{

}

void                            Time::ValidateHour                          (           Uint8                       anHour                                      )
{

    if (anHour > 23)
    {
        throw library::core::error::RuntimeError(String::Format("Hour [{}] out of range [0 - 23].", anHour)) ;
    }

}

void                            Time::ValidateMinute                        (           Uint8                       aMinute                                     )
{

    if (aMinute > 59)
    {
        throw library::core::error::RuntimeError(String::Format("Minute [{}] out of range [0 - 59].", aMinute)) ;
    }

}

void                            Time::ValidateSecond                        (           Uint8                       aSecond                                     )
{

    

    if (aSecond > 60)
    {
        throw library::core::error::RuntimeError(String::Format("Second [{}] out of range [0 - 60].", aSecond)) ;
    }

}

void                            Time::ValidateMillisecond                   (           Uint16                      aMillisecond                                )
{

    

    if (aMillisecond > 999)
    {
        throw library::core::error::RuntimeError(String::Format("Millisecond [{}] out of range [0 - 999].", aMillisecond)) ;
    }

}

void                            Time::ValidateMicrosecond                   (           Uint16                      aMicrosecond                                )
{

    

    if (aMicrosecond > 999)
    {
        throw library::core::error::RuntimeError(String::Format("Microsecond [{}] out of range [0 - 999].", aMicrosecond)) ;
    }

}

void                            Time::ValidateNanosecond                    (           Uint16                      aNanosecond                                 )
{

    if (aNanosecond > 999)
    {
        throw library::core::error::RuntimeError(String::Format("Nanosecond [{}] out of range [0 - 999].", aNanosecond)) ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////