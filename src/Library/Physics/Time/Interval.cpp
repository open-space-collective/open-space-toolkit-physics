////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Time/Interval.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Interval.hpp>

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

                                Interval::Interval                          (   const   Instant&                    aLowerBound,
                                                                                const   Instant&                    anUpperBound,
                                                                                const   Interval::Type&             anIntervalType                              )
                                :   math::obj::Interval<Instant>(aLowerBound, anUpperBound, anIntervalType)
{

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Interval&                   anInterval                                  )
{

    library::core::utils::Print::Header(anOutputStream, "Interval") ;

    library::core::utils::Print::Line(anOutputStream) << "Start:" << (anInterval.isDefined() ? anInterval.accessStart().toString(Scale::UTC) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "End:" << (anInterval.isDefined() ? anInterval.accessEnd().toString(Scale::UTC) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Interval::isDefined                         ( ) const
{
    return math::obj::Interval<Instant>::isDefined() && (this->getType() != Interval::Type::Undefined) ;
}

const Instant&                  Interval::accessStart                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return this->accessLowerBound() ;

}

const Instant&                  Interval::accessEnd                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return this->accessUpperBound() ;

}

Instant                         Interval::getStart                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return this->accessLowerBound() ;

}

Instant                         Interval::getEnd                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return this->accessUpperBound() ;

}

Duration                        Interval::getDuration                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return Duration::Between(this->accessLowerBound(), this->accessUpperBound()) ;

}

Instant                         Interval::getCenter                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return this->accessLowerBound() + this->getDuration() / 2.0 ;

}

String                          Interval::toString                         (   const   Scale&                      aTimeScale                                  ) const
{

    using library::physics::time::DateTime ;

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    switch (this->getType())
    {

        case Interval::Type::Closed:
            return String::Format("[{0} - {1}] [{2}]", this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), StringFromScale(aTimeScale)) ;

        case Interval::Type::Open:
            return String::Format("]{0} - {1}[ [{2}]", this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), StringFromScale(aTimeScale)) ;

        case Interval::Type::HalfOpenLeft:
            return String::Format("]{0} - {1}] [{2}]", this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), StringFromScale(aTimeScale)) ;

        case Interval::Type::HalfOpenRight:
            return String::Format("[{0} - {1}[ [{2}]", this->accessLowerBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), this->accessUpperBound().getDateTime(aTimeScale).toString(DateTime::Format::Standard), StringFromScale(aTimeScale)) ;

        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Interval type") ;

    return String::Empty() ;

}

Array<Instant>                  Interval::generateGrid                      (   const   Duration&                   aTimeStep                                   ) const
{

    return this->generateArrayWithStep(aTimeStep) ;

    // using library::core::types::Index ;
    // using library::core::types::Size ;

    // if (!this->isDefined())
    // {
    //     throw library::core::error::runtime::Undefined("Interval") ;
    // }

    // if (!aTimeStep.isDefined())
    // {
    //     throw library::core::error::runtime::Undefined("Time step") ;
    // }

    // if (aTimeStep.isZero())
    // {
    //     throw library::core::error::RuntimeError("Time step is zero.") ;
    // }

    // Array<Instant> grid = Array<Instant>::Empty() ;

    // if (aTimeStep.isPositive())
    // {

    //     Instant instant = this->accessLowerBound() ;

    //     while (instant <= this->accessUpperBound())
    //     {

    //         grid.add(instant) ;

    //         instant += aTimeStep ;

    //     }

    //     if (grid.accessLast() < this->accessUpperBound())
    //     {
    //         grid.add(this->accessUpperBound()) ;
    //     }

    // }
    // else
    // {

    //     Instant instant = this->accessUpperBound() ;

    //     while (instant >= this->accessLowerBound())
    //     {

    //         grid.add(instant) ;

    //         instant += aTimeStep ;

    //     }

    //     if (grid.accessLast() > this->accessLowerBound())
    //     {
    //         grid.add(this->accessLowerBound()) ;
    //     }

    // }

    // return grid ;

}

Interval                        Interval::Undefined                         ( )
{
    return Interval(Instant::Undefined(), Instant::Undefined(), Interval::Type::Undefined) ;
}

Interval                        Interval::Closed                            (   const   Instant&                    aLowerBound,
                                                                                const   Instant&                    anUpperBound                                )
{

    if (!aLowerBound.isDefined())
    {
        throw library::core::error::runtime::Undefined("Lower bound") ;
    }

    if (!anUpperBound.isDefined())
    {
        throw library::core::error::runtime::Undefined("Upper bound") ;
    }

    return Interval(aLowerBound, anUpperBound, Interval::Type::Closed) ;

}

Interval                        Interval::Centered                          (   const   Instant&                    aCentralInstant,
                                                                                const   Duration&                   aDuration,
                                                                                const   Interval::Type&             anIntervalType                              )
{

    if (!aCentralInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Central instant") ;
    }

    if (!aDuration.isDefined())
    {
        throw library::core::error::runtime::Undefined("Duration") ;
    }

    if (!aDuration.isPositive())
    {
        throw library::core::error::RuntimeError("Duration is negative.") ;
    }

    if (anIntervalType == Interval::Type::Undefined)
    {
        throw library::core::error::runtime::Undefined("Interval type") ;
    }

    return Interval((aCentralInstant - aDuration / 2.0), (aCentralInstant + aDuration / 2.0), anIntervalType) ;

}

Interval                        Interval::Parse                             (   const   String&                     aString                                     )
{

    using library::physics::time::DateTime ;

    if (aString.isEmpty())
    {
        throw library::core::error::runtime::Undefined("String") ;
    }

    boost::smatch match ;

    if (boost::regex_match(aString, match, boost::regex("^([\\[\\]])([\\d]{4}-[\\d]{2}-[\\d]{2} [\\d]{2}:[\\d]{2}:[\\d]{2}) - ([\\d]{4}-[\\d]{2}-[\\d]{2} [\\d]{2}:[\\d]{2}:[\\d]{2})([\\[\\]]) \\[([\\w]+)\\]$")))
    {

        const String openingBracket = String(match[1]) ;
        const String startInstantString = String(match[2]) ;
        const String endInstantString = String(match[3]) ;
        const String closingBracket = String(match[4]) ;
        const String timeScaleString = String(match[5]) ;

        const Scale timeScale = ScaleFromString(timeScaleString) ;

        const Instant startInstant = Instant::DateTime(DateTime::Parse(startInstantString, DateTime::Format::Standard), timeScale) ;
        const Instant endInstant = Instant::DateTime(DateTime::Parse(endInstantString, DateTime::Format::Standard), timeScale) ;

        Interval::Type type = Interval::Type::Undefined ;

        if ((openingBracket == "[") && (closingBracket == "]"))
        {
            type = Interval::Type::Closed ;
        }
        else if ((openingBracket == "]") && (closingBracket == "["))
        {
            type = Interval::Type::Open ;
        }
        else if ((openingBracket == "]") && (closingBracket == "]"))
        {
            type = Interval::Type::HalfOpenLeft ;
        }
        else if ((openingBracket == "[") && (closingBracket == "["))
        {
            type = Interval::Type::HalfOpenRight ;
        }
        else
        {
            throw library::core::error::runtime::Wrong("Brackets") ;
        }

        return Interval(startInstant, endInstant, type) ;

    }
    else
    {
        throw library::core::error::RuntimeError("Cannot parse interval string [{}].", aString) ;
    }

    return Interval::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
