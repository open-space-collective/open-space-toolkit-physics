////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Units/Mass.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Units/Mass.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
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

Mass*                           Mass::clone                                 ( ) const
{
    return new Mass(*this) ;
}

bool                            Mass::isDefined                             ( ) const
{
    return units::Unit::isDefined() && (unit_ != Mass::Unit::Undefined) ;
}

Mass::Unit                      Mass::getUnit                               ( ) const
{
    return unit_ ;
}

Real                            Mass::in                                    (   const   Mass::Unit&                 aUnit                                       ) const
{

    if (!this->isDefined())
    {
        return Real::Undefined() ;
    }

    if (unit_ == aUnit)
    {
        return this->accessValue() ;
    }

    return this->accessValue() * Mass::SIRatio(unit_) / Mass::SIRatio(aUnit) ;

}

Real                            Mass::inKilograms                           ( ) const
{
    return this->in(Mass::Unit::Kilogram) ;
}

String                          Mass::toString                              (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Mass") ;
    }

    return this->accessValue().toString(aPrecision) + " [" + Mass::SymbolFromUnit(unit_) + "]" ;

}

Mass                            Mass::Undefined                             ( )
{
    return { Real::Undefined(), Mass::Unit::Undefined } ;
}

Mass                            Mass::Kilograms                             (   const   Real&                       aValue                                      )
{
    return { aValue, Mass::Unit::Kilogram } ;
}

// Mass                            Mass::Parse                                 (   const   String&                     aString                                     )
// {

// }

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
            throw ostk::core::error::runtime::Wrong("Unit") ;
            break ;

    }

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
            throw ostk::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Real                            Mass::SIRatio                               (   const   Mass::Unit&                 aUnit                                       )
{

    switch (aUnit)
    {

        case Mass::Unit::Kilogram:
            return 1.0 ;

        default:
            throw ostk::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return Real::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
