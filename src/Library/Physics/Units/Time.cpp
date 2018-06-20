////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Time.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Time.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Time::Time                                  (   const   Real&                       aValue,
                                                                                const   Time::Unit&                 aUnit                                       )
                                :   units::Unit(units::Unit::Type::Time, aValue),
                                    unit_(aUnit)
{

}

bool                            Time::isDefined                             ( ) const
{
    return units::Unit::isDefined() && (unit_ != Time::Unit::Undefined) ;
}

String                          Time::getString                             ( ) const
{

    if (!this->isDefined())
    {
        return "Undef" ;
    }

    return this->accessValue().getString() + " [" + Time::SymbolFromUnit(unit_) + "]" ;

}

Time                            Time::Undefined                             ( )
{
    return Time(Real::Undefined(), Time::Unit::Undefined) ;
}

String                          Time::StringFromUnit                        (   const   Time::Unit&                 aUnit                                       )
{

    switch (aUnit)
    {

        case Time::Unit::Undefined:
            return "Undefined" ;
            
        case Time::Unit::Second:
            return "Second" ;
            
        case Time::Unit::Minute:
            return "Minute" ;
            
        case Time::Unit::Hour:
            return "Hour" ;
            
        case Time::Unit::Day:
            return "Day" ;
            
        case Time::Unit::Week:
            return "Week" ;
            
        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return String::Empty() ;

}

String                          Time::SymbolFromUnit                        (   const   Time::Unit&                 aUnit                                       )
{

    switch (aUnit)
    {

        case Time::Unit::Second:
            return "s" ;
            
        case Time::Unit::Minute:
            return "min" ;
            
        case Time::Unit::Hour:
            return "hr" ;
            
        case Time::Unit::Day:
            return "day" ;
            
        case Time::Unit::Week:
            return "week" ;
            
        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////