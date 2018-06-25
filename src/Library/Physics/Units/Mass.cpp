////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Mass.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Mass.hpp>
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

                                Mass::Mass                                  (   const   Real&                       aValue,
                                                                                const   Mass::Unit&                 aUnit                                       )
                                :   units::Unit(units::Unit::Type::Mass, aValue),
                                    unit_(aUnit)
{

}

bool                            Mass::isDefined                             ( ) const
{
    return units::Unit::isDefined() && (unit_ != Mass::Unit::Undefined) ;
}

String                          Mass::getString                             ( ) const
{

    if (!this->isDefined())
    {
        return "Undef" ;
    }

    return this->accessValue().getString() + " [" + Mass::SymbolFromUnit(unit_) + "]" ;

}

Mass                            Mass::Undefined                             ( )
{
    return Mass(Real::Undefined(), Mass::Unit::Undefined) ;
}

String                          Mass::StringFromUnit                        (   const   Mass::Unit&                 aUnit                                       )
{

    switch (aUnit)
    {

        case Mass::Unit::Undefined:
            return "Undefined" ;
            
        case Mass::Unit::Kilogram:
            return "Kilogram" ;
            
        case Mass::Unit::Tonne:
            return "Tonne" ;
            
        case Mass::Unit::Pound:
            return "Pound" ;
            
        default:
            break ;

    }

    throw library::core::error::runtime::Wrong("Unit") ;

    return String::Empty() ;

}

String                          Mass::SymbolFromUnit                        (   const   Mass::Unit&                 aUnit                                       )
{

    switch (aUnit)
    {

        case Mass::Unit::Kilogram:
            return "kg" ;
            
        case Mass::Unit::Tonne:
            return "t" ;
            
        case Mass::Unit::Pound:
            return "lb" ;
            
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