////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Units/ElectricCurrent.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Units/ElectricCurrent.hpp>
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

                                ElectricCurrent::ElectricCurrent            (   const   Real&                       aValue,
                                                                                const   ElectricCurrent::Unit&      aUnit                                       )
                                :   units::Unit(units::Unit::Type::ElectricCurrent, aValue),
                                    unit_(aUnit)
{

}

ElectricCurrent*                ElectricCurrent::clone                      ( ) const
{
    return new ElectricCurrent(*this) ;
}

bool                            ElectricCurrent::isDefined                  ( ) const
{
    return units::Unit::isDefined() && (unit_ != ElectricCurrent::Unit::Undefined) ;
}

ElectricCurrent::Unit           ElectricCurrent::getUnit                    ( ) const
{
    return unit_ ;
}

Real                            ElectricCurrent::in                         (   const   ElectricCurrent::Unit&      aUnit                                       ) const
{

    if (!this->isDefined())
    {
        return Real::Undefined() ;
    }

    if (unit_ == aUnit)
    {
        return this->accessValue() ;
    }

    return this->accessValue() * ElectricCurrent::SIRatio(unit_) / ElectricCurrent::SIRatio(aUnit) ;

}

Real                            ElectricCurrent::inAmperes                  ( ) const
{
    return this->in(ElectricCurrent::Unit::Ampere) ;
}

String                          ElectricCurrent::toString                   (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Electric current") ;
    }

    return this->accessValue().toString(aPrecision) + " [" + ElectricCurrent::SymbolFromUnit(unit_) + "]" ;

}

ElectricCurrent                 ElectricCurrent::Undefined                  ( )
{
    return { Real::Undefined(), ElectricCurrent::Unit::Undefined } ;
}

ElectricCurrent                 ElectricCurrent::Amperes                    (   const   Real&                       aValue                                      )
{
    return { aValue, ElectricCurrent::Unit::Ampere } ;
}

// ElectricCurrent                 ElectricCurrent::Parse                      (   const   String&                     aString                                     )
// {

// }

String                          ElectricCurrent::StringFromUnit             (   const   ElectricCurrent::Unit&      aUnit                                       )
{

    switch (aUnit)
    {

        case ElectricCurrent::Unit::Undefined:
            return "Undefined" ;

        case ElectricCurrent::Unit::Ampere:
            return "Ampere" ;

        default:
            throw ostk::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return String::Empty() ;

}

String                          ElectricCurrent::SymbolFromUnit             (   const   ElectricCurrent::Unit&      aUnit                                       )
{

    switch (aUnit)
    {

        case ElectricCurrent::Unit::Ampere:
            return "A" ;

        default:
            throw ostk::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Real                            ElectricCurrent::SIRatio                    (   const   ElectricCurrent::Unit&      aUnit                                       )
{

    switch (aUnit)
    {

        case ElectricCurrent::Unit::Ampere:
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
