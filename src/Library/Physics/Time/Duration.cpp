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
    return (*this) ;
}

Duration                        Duration::operator -                        ( ) const
{
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
    return this->isDefined() && (count_ == 0) ;
}

bool                            Duration::isPositive                        ( ) const
{
    return this->isDefined() && (count_ >= 0) ;
}

bool                            Duration::isStrictlyPositive                ( ) const
{
    return this->isDefined() && (count_ > 0) ;
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

    switch (aFormat)
    {

        case Duration::Format::Undefined:
            break ;

        case Duration::Format::ISO8601:
            break ;

        default:
            break ;

    }

    throw library::core::error::runtime::ToBeImplemented("Duration::getString") ;

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