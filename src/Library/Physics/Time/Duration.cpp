////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Duration.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <iostream>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Duration::Duration                          (           Int64                       aNanosecondCount                            )
                                :   defined_(true),
                                    count_(aNanosecondCount)
{

}

bool                            Duration::operator ==                       (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        return false ;
    }

    return count_ == aDuration.count_ ;

}
        
bool                            Duration::operator !=                       (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        return true ;
    }

    return count_ != aDuration.count_ ;

}

bool                            Duration::operator <                        (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return count_ < aDuration.count_ ;

}
        
bool                            Duration::operator <=                       (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return count_ <= aDuration.count_ ;

}
        
bool                            Duration::operator >                        (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return count_ > aDuration.count_ ;

}
        
bool                            Duration::operator >=                       (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return count_ >= aDuration.count_ ;

}

Duration                        Duration::operator +                        (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Duration(count_ + aDuration.count_) ;

}

Duration                        Duration::operator -                        (   const   Duration&                   aDuration                                   ) const
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Duration(count_ - aDuration.count_) ;

}

Duration                        Duration::operator *                        (   const   Real&                       aMultiplier                                 ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    if (!aMultiplier.isDefined())
    {
        throw library::core::error::runtime::Undefined("Multiplier") ;
    }

    return Duration(count_ * static_cast<double>(aMultiplier)) ;

}

Duration                        Duration::operator /                        (   const   Real&                       aDivider                                    ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    if (!aDivider.isDefined())
    {
        throw library::core::error::runtime::Undefined("Divider") ;
    }

    if (aDivider.isZero())
    {
        throw library::core::error::RuntimeError("Cannot divide by zero.") ;
    }

    return Duration(count_ / static_cast<double>(aDivider)) ;

}

Duration                        Duration::operator +                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    return (*this) ;

}

Duration                        Duration::operator -                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    return Duration(-count_) ;

}

Duration&                       Duration::operator +=                       (   const   Duration&                   aDuration                                   )
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    count_ += aDuration.count_ ;

    return (*this) ;

}

Duration&                       Duration::operator -=                       (   const   Duration&                   aDuration                                   )
{

    if ((!this->isDefined()) || (!aDuration.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    count_ -= aDuration.count_ ;

    return (*this) ;

}

Duration&                       Duration::operator *=                       (   const   Real&                       aMultiplier                                 )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    if (!aMultiplier.isDefined())
    {
        throw library::core::error::runtime::Undefined("Multiplier") ;
    }

    count_ *= aMultiplier ;

    return (*this) ;

}

Duration&                       Duration::operator /=                       (   const   Real&                       aDivider                                    )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    if (!aDivider.isDefined())
    {
        throw library::core::error::runtime::Undefined("Divider") ;
    }

    if (aDivider.isZero())
    {
        throw library::core::error::RuntimeError("Cannot divide by zero.") ;
    }

    count_ /= aDivider ;

    return (*this) ;

}

Duration                        operator *                                  (           double                      aMultiplier,
                                                                                const   Duration&                   aDuration                                   )
{

    if (!aDuration.isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    return Duration(aMultiplier * aDuration.count_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Duration&                   aDuration                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Duration") ;

    library::core::utils::Print::Line(anOutputStream) << (aDuration.isDefined() ? aDuration.getString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Duration::isDefined                         ( ) const
{
    return defined_ ;
}

bool                            Duration::isZero                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return count_ == 0 ;
}

bool                            Duration::isPositive                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    return count_ >= 0 ;

}

bool                            Duration::isStrictlyPositive                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    return count_ > 0 ;

}

Integer                         Duration::getNanoseconds                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64(std::abs(count_) % 1000) ;

}

Integer                         Duration::getMicroseconds                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64((std::abs(count_) / 1000) % 1000) ;

}

Integer                         Duration::getMilliseconds                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64((std::abs(count_) / 1000000) % 1000) ;

}

Integer                         Duration::getSeconds                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64((std::abs(count_) / 1000000000) % 60) ;

}

Integer                         Duration::getMinutes                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64((std::abs(count_) / 60000000000) % 60) ;

}

Integer                         Duration::getHours                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64((std::abs(count_) / 3600000000000) % 24) ;

}

Integer                         Duration::getDays                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64(std::abs(count_) / 86400000000000) ;

}

Integer                         Duration::getWeeks                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Integer::Int64(std::abs(count_) / 604800000000000) ;

}

Real                            Duration::inNanoseconds                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_) ;

}

Real                            Duration::inMicroseconds                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_ / 1e3) ;

}

Real                            Duration::inMilliseconds                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_ / 1e6) ;

}

Real                            Duration::inSeconds                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_ / 1e9) ;

}

Real                            Duration::inMinutes                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_ / 60000000000.0) ;

}

Real                            Duration::inHours                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_ / 3600000000000.0) ;

}

Real                            Duration::inDays                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_ / 86400000000000.0) ;

}

Real                            Duration::inWeeks                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    return Real(count_ / 604800000000000.0) ;

}

Real                            Duration::in                                (   const   units::Time::Unit&          aTimeUnit                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    switch (aTimeUnit)
    {

        case units::Time::Unit::Nanosecond:
            return Real(count_) ;

        case units::Time::Unit::Microsecond:
            return Real(count_ / 1e3) ;

        case units::Time::Unit::Millisecond:
            return Real(count_ / 1e6) ;

        case units::Time::Unit::Second:
            return Real(count_ / 1e9) ;

        case units::Time::Unit::Minute:
            return Real(count_ / 60000000000.0) ;

        case units::Time::Unit::Hour:
            return Real(count_ / 3600000000000.0) ;

        case units::Time::Unit::Day:
            return Real(count_ / 86400000000000.0) ;

        case units::Time::Unit::Week:
            return Real(count_ / 604800000000000.0) ;
        
        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return Real::Undefined() ;

}

Duration                        Duration::getAbsolute                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }
    
    return Duration(std::abs(count_)) ;

}

String                          Duration::getString                         (   const   Duration::Format&           aFormat                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    const Integer nanoseconds = this->getNanoseconds() ;
    const Integer microseconds = this->getMicroseconds() ;
    const Integer milliseconds = this->getMilliseconds() ;
    const Integer seconds = this->getSeconds() ;
    const Integer minutes = this->getMinutes() ;
    const Integer hours = this->getHours() ;
    const Integer days = this->getDays() ;

    switch (aFormat)
    {

        case Duration::Format::Standard:
        {

            if (days > 0)
            {
                return String::Format("{0}{1:d} {2:02d}:{3:02d}:{4:02d}.{5:03d}.{6:03d}.{7:03d}", ((count_ < 0) ? "-" : ""), days, hours, minutes, seconds, milliseconds, microseconds, nanoseconds) ;
            }

            if (hours > 0)
            {
                return String::Format("{0}{1:02d}:{2:02d}:{3:02d}.{4:03d}.{5:03d}.{6:03d}", ((count_ < 0) ? "-" : ""), hours, minutes, seconds, milliseconds, microseconds, nanoseconds) ;
            }

            if (minutes > 0)
            {
                return String::Format("{0}{1:02d}:{2:02d}.{3:03d}.{4:03d}.{5:03d}", ((count_ < 0) ? "-" : ""), minutes, seconds, milliseconds, microseconds, nanoseconds) ;
            }

            return String::Format("{0}{1:02d}.{2:03d}.{3:03d}.{4:03d}", ((count_ < 0) ? "-" : ""), seconds, milliseconds, microseconds, nanoseconds) ;

        }

        case Duration::Format::ISO8601:
        {

            if (this->isZero())
            {
                return "PT0H0M0S" ;
            }

            String dayString = String::Empty() ;

            if (days > 0)
            {
                dayString = String::Format("{:d}D", days) ;
            }

            String timeString = String::Empty() ;

            if ((milliseconds > 0) || (microseconds > 0) || (nanoseconds > 0)) // Floating seconds
            {

                const Real floatingSeconds = Real::Integer(seconds)
                                           + (Real::Integer(milliseconds) / 1000.0)
                                           + (Real::Integer(microseconds) / 1000000.0)
                                           + (Real::Integer(nanoseconds) / 1000000000.0) ;

                // Pretty ugly implementation, couldn't quickly find a better way... feel free to improve!

                if (nanoseconds == 100)
                {
                    timeString = String::Format("{:.7f}S", floatingSeconds) ;
                }
                else if (nanoseconds == 10)
                {
                    timeString = String::Format("{:.8f}S", floatingSeconds) ;
                }
                else if (nanoseconds > 0)
                {
                    timeString = String::Format("{:.9f}S", floatingSeconds) ;
                }
                else if (microseconds == 100)
                {
                    timeString = String::Format("{:.4f}S", floatingSeconds) ;
                }
                else if (microseconds == 10)
                {
                    timeString = String::Format("{:.5f}S", floatingSeconds) ;
                }
                else if (microseconds > 0)
                {
                    timeString = String::Format("{:.6f}S", floatingSeconds) ;
                }
                else if (milliseconds == 100)
                {
                    timeString = String::Format("{:.1f}S", floatingSeconds) ;
                }
                else if (milliseconds == 10)
                {
                    timeString = String::Format("{:.2f}S", floatingSeconds) ;
                }
                else
                {
                    timeString = String::Format("{:.3f}S", floatingSeconds) ;
                }

            }
            else if (seconds > 0)
            {
                timeString = String::Format("{:d}S", seconds) ;
            }

            if (minutes > 0)
            {
                timeString = String::Format("{:d}M", minutes) + timeString ;
            }

            if (hours > 0)
            {
                timeString = String::Format("{:d}H", hours) + timeString ;
            }

            return ((count_ < 0) ? "-P" : "P") + dayString + ((!timeString.isEmpty()) ? ("T" + timeString) : "") ;

        }

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return String::Empty() ;

}

Duration                        Duration::Undefined                         ( )
{
    return Duration() ;   
}

Duration                        Duration::Zero                              ( )
{
    return Duration(0) ;
}

Duration                        Duration::Nanoseconds                       (   const   Real&                       aNanosecondCount                            )
{
    return Duration(static_cast<Int64>(aNanosecondCount)) ;
}

Duration                        Duration::Microseconds                      (   const   Real&                       aMicrosecondCount                           )
{
    return Duration(static_cast<Int64>(aMicrosecondCount * 1e3)) ;
}

Duration                        Duration::Milliseconds                      (   const   Real&                       aMillisecondCount                           )
{
    return Duration(static_cast<Int64>(aMillisecondCount * 1e6)) ;
}

Duration                        Duration::Seconds                           (   const   Real&                       aSecondCount                                )
{
    return Duration(static_cast<Int64>(aSecondCount * 1e9)) ;
}

Duration                        Duration::Minutes                           (   const   Real&                       aMinuteCount                                )
{
    return Duration(static_cast<Int64>(aMinuteCount * 60000000000.0)) ;
}

Duration                        Duration::Hours                             (   const   Real&                       anHourCount                                 )
{
    return Duration(static_cast<Int64>(anHourCount * 3600000000000.0)) ;
}

Duration                        Duration::Days                              (   const   Real&                       aDayCount                                   )
{
    return Duration(static_cast<Int64>(aDayCount * 86400000000000.0)) ;
}

Duration                        Duration::Weeks                             (   const   Real&                       aWeekCount                                  )
{
    return Duration(static_cast<Int64>(aWeekCount * 604800000000000.0)) ;
}

Duration                        Duration::Between                           (   const   Instant&                    aFirstInstant,
                                                                                const   Instant&                    aSecondInstant                              )
{
    return aSecondInstant - aFirstInstant ;
}

// Duration                        Duration::Parse                             (   const   String&                     aString                                     )
// {

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Duration::Duration                          ( )
                                :   defined_(false),
                                    count_(0)
{
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////