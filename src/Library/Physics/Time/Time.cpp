////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Time.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Time.hpp>

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

                                Time::Time                                  (           Uint8                       anHour,
                                                                                        Uint8                       aMinute,
                                                                                        Uint8                       aSecond,
                                                                                        Uint8                       aMillisecond,
                                                                                        Uint8                       aMicrosecond,
                                                                                        Uint8                       aNanosecond                                 )
                                :   defined_(true),
                                    hour_(anHour),
                                    minute_(aMinute),
                                    second_(aSecond),
                                    millisecond_(aMillisecond),
                                    microsecond_(aMicrosecond),
                                    nanosecond_(aNanosecond)
{

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
    return hour_ ;
}

Uint8                           Time::getMinute                             ( ) const
{
    return minute_ ;
}

Uint8                           Time::getSecond                             ( ) const
{
    return second_ ;
}

Uint8                           Time::getMillisecond                        ( ) const
{
    return millisecond_ ;
}

Uint8                           Time::getMicrosecond                        ( ) const
{
    return microsecond_ ;
}

Uint8                           Time::getNanosecond                         ( ) const
{
    return nanosecond_ ;
}

String                          Time::getString                             (   const   Time::Format&               aFormat                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Time") ;
    }

    switch (aFormat)
    {

        case Time::Format::Standard:
            return String::Format("{0:d}:{1:02d}:{2:02d}.{3:03d}.{4:03d}.{5:03d}", hour_, minute_, second_, millisecond_, microsecond_, nanosecond_) ;

        case Time::Format::ISO8601:
            return String::Format("{0:d}:{1:02d}:{2:02d}{3:03d}{4:03d}{5:03d}", hour_, minute_, second_, millisecond_, microsecond_, nanosecond_) ;

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }
    
    return String::Empty() ;

}

void                            Time::setHour                               (           Uint8                       anHour                                      )
{
    hour_ = anHour ;
}

void                            Time::setMinute                             (           Uint8                       aMinute                                     )
{
    minute_ = aMinute ;
}

void                            Time::setSecond                             (           Uint8                       aSecond                                     )
{
    second_ = aSecond ;
}

void                            Time::setMillisecond                        (           Uint8                       aMillisecond                                )
{
    millisecond_ = aMillisecond ;
}

void                            Time::setMicrosecond                        (           Uint8                       aMicrosecond                                )
{
    microsecond_ = aMicrosecond ;
}

void                            Time::setNanosecond                         (           Uint8                       aNanosecond                                 )
{
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////