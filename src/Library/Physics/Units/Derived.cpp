////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Derived.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Derived.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <iostream>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Derived::Order::Order                       (           Int16                       aNumerator                                  )
                                :   numerator_(aNumerator),
                                    denominator_(1)
{

}

                                Derived::Order::Order                       (           Int16                       aNumerator,
                                                                                        Int16                       aDenominator                                )
                                :   numerator_(aNumerator),
                                    denominator_(aDenominator)
{

    if (denominator_ == 0)
    {
        throw library::core::error::runtime::Wrong("Denominator") ;
    }

}

bool                            Derived::Order::operator ==                 (   const   Derived::Order&             anOrder                                     ) const
{
    return (numerator_ == anOrder.numerator_) && (denominator_ == anOrder.denominator_) ;
}

bool                            Derived::Order::operator !=                 (   const   Derived::Order&             anOrder                                     ) const
{
    return (numerator_ != anOrder.numerator_) || (denominator_ != anOrder.denominator_) ;
}

bool                            Derived::Order::isZero                      ( ) const
{
    return numerator_ == 0 ;
}

bool                            Derived::Order::isUnity                     ( ) const
{
    return (numerator_ == 1) && (denominator_ == 1) ;
}

const Int16&                    Derived::Order::accessNumerator             ( ) const
{
    return numerator_ ;
}

const Int16&                    Derived::Order::accessDenominator           ( ) const
{
    return denominator_ ;
}

Real                            Derived::Order::getValue                    ( ) const
{

    using library::core::types::Integer ;

    return Real::Integer(Integer::Int16(numerator_)) / Real::Integer(Integer::Int16(denominator_)) ;

}

String                          Derived::Order::toString                   ( ) const
{

    using library::core::types::Integer ;

    if (denominator_ == 1)
    {
        return Integer::Int16(numerator_).toString() ;
    }

    if (numerator_ == 1)
    {
        return "-" + Integer::Int16(denominator_).toString() ;
    }
    
    return Integer::Int16(numerator_).toString() + "/" + Integer::Int16(denominator_).toString() ;

}

Derived::Order                  Derived::Order::Zero                        ( )
{
    return Derived::Order(0, 1) ;
}
                
Derived::Order                  Derived::Order::One                         ( )
{
    return Derived::Order(1, 1) ;
}

Derived::Order                  Derived::Order::Two                         ( )
{
    return Derived::Order(2, 1) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Derived::Unit::Unit                         (   const   Length::Unit&               aLengthUnit,
                                                                                const   Order&                      aLengthOrder,
                                                                                const   Mass::Unit&                 aMassUnit,
                                                                                const   Order&                      aMassOrder,
                                                                                const   Time::Unit&                 aTimeUnit,
                                                                                const   Order&                      aTimeOrder,
                                                                                const   Angle::Unit&                anAngleUnit,
                                                                                const   Order&                      anAngleOrder                                )
                                :   lengthUnit_(aLengthUnit),
                                    lengthOrder_(aLengthOrder),
                                    massUnit_(aMassUnit),
                                    massOrder_(aMassOrder),
                                    timeUnit_(aTimeUnit),
                                    timeOrder_(aTimeOrder),
                                    angleUnit_(anAngleUnit),
                                    angleOrder_(anAngleOrder)
{

}

bool                            Derived::Unit::operator ==                  (   const   Derived::Unit&              aUnit                                       ) const
{

    if ((!this->isDefined()) || (!aUnit.isDefined()))
    {
        return false ;
    }
    
    return (lengthUnit_ == aUnit.lengthUnit_) && (lengthOrder_ == aUnit.lengthOrder_)
        && (massUnit_ == aUnit.massUnit_) && (massOrder_ == aUnit.massOrder_)
        && (timeUnit_ == aUnit.timeUnit_) && (timeOrder_ == aUnit.timeOrder_)
        && (angleUnit_ == aUnit.angleUnit_) && (angleOrder_ == aUnit.angleOrder_) ;
    
}

bool                            Derived::Unit::operator !=                  (   const   Derived::Unit&              aUnit                                       ) const
{
    return !((*this) == aUnit) ;
}

bool                            Derived::Unit::isDefined                    ( ) const
{
    return (lengthUnit_ != Length::Unit::Undefined)
        || (massUnit_ != Mass::Unit::Undefined)
        || (timeUnit_ != Time::Unit::Undefined)
        || (angleUnit_ != Angle::Unit::Undefined) ;
}

bool                            Derived::Unit::isCompatibleWith             (   const   Unit&                       aUnit                                       ) const
{

    if ((!this->isDefined()) || (!aUnit.isDefined()))
    {
        return false ;
    }

    return (lengthOrder_ == aUnit.lengthOrder_)
        && (massOrder_ == aUnit.massOrder_)
        && (timeOrder_ == aUnit.timeOrder_)
        && (angleOrder_ == aUnit.angleOrder_) ;

}

const Length::Unit&             Derived::Unit::accessLengthUnit             ( ) const
{
    return lengthUnit_ ;
}

const Derived::Order&           Derived::Unit::accessLengthOrder            ( ) const
{
    return lengthOrder_ ;
}

const Mass::Unit&               Derived::Unit::accessMassUnit               ( ) const
{
    return massUnit_ ;
}

const Derived::Order&           Derived::Unit::accessMassOrder              ( ) const
{
    return massOrder_ ;
}

const Time::Unit&               Derived::Unit::accessTimeUnit               ( ) const
{
    return timeUnit_ ;
}

const Derived::Order&           Derived::Unit::accessTimeOrder              ( ) const
{
    return timeOrder_ ;
}

const Angle::Unit&              Derived::Unit::accessAngleUnit              ( ) const
{
    return angleUnit_ ;
}

const Derived::Order&           Derived::Unit::accessAngleOrder             ( ) const
{
    return angleOrder_ ;
}

String                          Derived::Unit::toString                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Unit") ;
    }

    String symbol = "" ;

    if (lengthUnit_ != Length::Unit::Undefined)
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Length::StringFromUnit(lengthUnit_) + ((!lengthOrder_.isUnity()) ? ("^" + lengthOrder_.toString()) : "") ;
    }

    if (massUnit_ != Mass::Unit::Undefined)
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Mass::StringFromUnit(massUnit_) + ((!massOrder_.isUnity()) ? ("^" + massOrder_.toString()) : "") ;
    }

    if (angleUnit_ != Angle::Unit::Undefined)
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Angle::StringFromUnit(angleUnit_) + ((!angleOrder_.isUnity()) ? ("^" + angleOrder_.toString()) : "") ;
    }

    if (timeUnit_ != Time::Unit::Undefined)
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Time::StringFromUnit(timeUnit_) + ((!timeOrder_.isUnity()) ? ("^" + timeOrder_.toString()) : "") ;
    }

    return symbol ;

}

String                          Derived::Unit::getSymbol                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Unit") ;
    }

    String symbol = "" ;

    if (lengthUnit_ != Length::Unit::Undefined)
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Length::SymbolFromUnit(lengthUnit_) + ((!lengthOrder_.isUnity()) ? ("^" + lengthOrder_.toString()) : "") ;
    }

    if (massUnit_ != Mass::Unit::Undefined)
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Mass::SymbolFromUnit(massUnit_) + ((!massOrder_.isUnity()) ? ("^" + massOrder_.toString()) : "") ;
    }

    if (angleUnit_ != Angle::Unit::Undefined)
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Angle::SymbolFromUnit(angleUnit_) + ((!angleOrder_.isUnity()) ? ("^" + angleOrder_.toString()) : "") ;
    }

    if (timeUnit_ != Time::Unit::Undefined)
    {

        if (timeOrder_.getValue() == -1.0) // Special case to support / time format
        {
            symbol += ((!symbol.isEmpty()) ? "/" : "") + Time::SymbolFromUnit(timeUnit_) ;
        }
        else
        {
            symbol += ((!symbol.isEmpty()) ? "." : "") + Time::SymbolFromUnit(timeUnit_) + ((!timeOrder_.isUnity()) ? ("^" + timeOrder_.toString()) : "") ;
        }
        
    }

    return symbol ;

}

Derived::Unit                   Derived::Unit::Undefined                    ( )
{
    return Derived::Unit(Length::Unit::Undefined, { 0 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 }) ;
}

Derived::Unit                   Derived::Unit::SquareMeter                  ( )
{
    return Derived::Unit(Length::Unit::Meter, { 2 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 }) ;
}

Derived::Unit                   Derived::Unit::CubicMeter                   ( )
{
    return Derived::Unit(Length::Unit::Meter, { 3 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 }) ;
}

Derived::Unit                   Derived::Unit::Hertz                        ( )
{
    return Derived::Unit(Length::Unit::Undefined, { 0 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Second, { -1 }, Angle::Unit::Undefined, { 0 }) ;
}
                
Derived::Unit                   Derived::Unit::Watt                         ( )
{
    return Derived::Unit(Length::Unit::Meter, { 2 }, Mass::Unit::Kilogram, { 1 }, Time::Unit::Second, { -3 }, Angle::Unit::Undefined, { 0 }) ;
}

Derived::Unit                   Derived::Unit::AngularVelocity              (   const   Angle::Unit&                anAngleUnit,
                                                                                const   Time::Unit&                 aTimeUnit                                   )
{
    return Derived::Unit(Length::Unit::Undefined, { 0 }, Mass::Unit::Undefined, { 0 }, aTimeUnit, { -1 }, anAngleUnit, { 1 }) ;
}

// Derived::Unit                   Derived::Unit::Parse                        (   const   String&                     aString                                     )
// {

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Derived::Derived                            (   const   Real&                       aValue,
                                                                                const   Derived::Unit&              aUnit                                       )
                                :   units::Unit(units::Unit::Type::Derived, aValue),
                                    unit_(aUnit)
{

}

bool                            Derived::operator ==                        (   const   Derived&                    aDerivedUnit                                ) const
{

    if ((!unit_.isDefined()) || (!aDerivedUnit.unit_.isDefined()))
    {
        return false ;
    }

    return this->accessValue() == ((unit_ == aDerivedUnit.unit_) ? aDerivedUnit.accessValue() : aDerivedUnit.in(unit_)) ;

}

bool                            Derived::operator !=                        (   const   Derived&                    aDerivedUnit                                ) const
{
    return !((*this) == aDerivedUnit) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Derived&                     aDerivedUnit                                     )
{

    library::core::utils::Print::Header(anOutputStream, "Derived") ;

    library::core::utils::Print::Line(anOutputStream) << "Value:" << aDerivedUnit.accessValue() ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:" << aDerivedUnit.unit_.toString() ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Derived::isDefined                          ( ) const
{
    return units::Unit::isDefined() && unit_.isDefined() ;
}

Derived::Unit                   Derived::getUnit                            ( ) const
{
    return unit_ ;
}

Real                            Derived::in                                 (   const   Derived::Unit&              aUnit                                       ) const
{

    if (!this->isDefined())
    {
        return Real::Undefined() ;
    }

    if (unit_ == aUnit)
    {
        return this->accessValue() ;
    }

    if (!unit_.isCompatibleWith(aUnit))
    {
        throw library::core::error::RuntimeError("Cannot convert unit [" + unit_.toString() + "] to [" + aUnit.toString() + "].") ;
    }

    return this->accessValue() * Derived::SIRatio(unit_) / Derived::SIRatio(aUnit) ;

}

String                          Derived::toString                          ( ) const
{

    if (!this->isDefined())
    {
        return "Undef" ;
    }

    return this->accessValue().toString() + " [" + unit_.getSymbol() + "]" ;

}

Derived                         Derived::Undefined                          ( )
{
    return Derived(Real::Undefined(), Derived::Unit::Undefined()) ;
}

// Derived                         Derived::Parse                               (   const   String&                     aString                                     )
// {

// }

String                          Derived::StringFromUnit                     (   const   Derived::Unit&              aUnit                                       )
{
    return aUnit.toString() ;
}

String                          Derived::SymbolFromUnit                     (   const   Derived::Unit&              aUnit                                       )
{
    return aUnit.getSymbol() ;
}

Real                            Derived::SIRatio                            (   const   Derived::Unit&              aUnit                                       )
{

    Real ratio = 1.0 ;
    
    if (!aUnit.accessLengthOrder().isZero())
    {
        ratio *= std::pow(Length(1.0, aUnit.accessLengthUnit()).in(Length::Unit::Meter), aUnit.accessLengthOrder().getValue()) ;
    }

    if (!aUnit.accessMassOrder().isZero())
    {
        throw library::core::error::runtime::ToBeImplemented("Mass::in(Mass::Unit)") ;
        // ratio *= std::pow(Mass(1.0, aUnit.accessMassUnit()).in(Mass::Unit::Kilogram), aUnit.accessMassOrder().getValue()) ;
    }

    if (!aUnit.accessTimeOrder().isZero())
    {
        throw library::core::error::runtime::ToBeImplemented("Time::in(Time::Unit)") ;
        // ratio *= std::pow(Time(1.0, aUnit.accessTimeUnit()).in(Time::Unit::Second), aUnit.accessTimeOrder().getValue()) ;
    }
    
    return ratio ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////