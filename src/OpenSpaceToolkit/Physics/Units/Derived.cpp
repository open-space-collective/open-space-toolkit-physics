/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
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
        throw ostk::core::error::runtime::Wrong("Denominator") ;
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

Int16                           Derived::Order::getNumerator                ( ) const
{
    return numerator_ ;
}

Int16                           Derived::Order::getDenominator              ( ) const
{
    return denominator_ ;
}

Real                            Derived::Order::getValue                    ( ) const
{

    using ostk::core::types::Integer ;

    return Real::Integer(Integer::Int16(numerator_)) / Real::Integer(Integer::Int16(denominator_)) ;

}

String                          Derived::Order::toString                    ( ) const
{

    using ostk::core::types::Integer ;

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
    return { 0, 1 } ;
}

Derived::Order                  Derived::Order::One                         ( )
{
    return { 1, 1 } ;
}

Derived::Order                  Derived::Order::Two                         ( )
{
    return { 2, 1 } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Derived::Unit::Unit                         (   const   Length::Unit&               aLengthUnit,
                                                                                const   Order&                      aLengthOrder,
                                                                                const   Mass::Unit&                 aMassUnit,
                                                                                const   Order&                      aMassOrder,
                                                                                const   Time::Unit&                 aTimeUnit,
                                                                                const   Order&                      aTimeOrder,
                                                                                const   ElectricCurrent::Unit&      anElectricCurrentUnit,
                                                                                const   Order&                      anElectricCurrentOrder,
                                                                                const   Angle::Unit&                anAngleUnit,
                                                                                const   Order&                      anAngleOrder                                )
                                :   lengthUnit_(aLengthUnit),
                                    lengthOrder_(aLengthOrder),
                                    massUnit_(aMassUnit),
                                    massOrder_(aMassOrder),
                                    timeUnit_(aTimeUnit),
                                    timeOrder_(aTimeOrder),
                                    electricCurrentUnit_(anElectricCurrentUnit),
                                    electricCurrentOrder_(anElectricCurrentOrder),
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
        && (electricCurrentUnit_ == aUnit.electricCurrentUnit_) && (electricCurrentOrder_ == aUnit.electricCurrentOrder_)
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
        || (electricCurrentUnit_ != ElectricCurrent::Unit::Undefined)
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
        && (electricCurrentOrder_ == aUnit.electricCurrentOrder_)
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

const ElectricCurrent::Unit&    Derived::Unit::accessElectricCurrentUnit    ( ) const
{
    return electricCurrentUnit_ ;
}

const Derived::Order&           Derived::Unit::accessElectricCurrentOrder   ( ) const
{
    return electricCurrentOrder_ ;
}

const Angle::Unit&              Derived::Unit::accessAngleUnit              ( ) const
{
    return angleUnit_ ;
}

const Derived::Order&           Derived::Unit::accessAngleOrder             ( ) const
{
    return angleOrder_ ;
}

String                          Derived::Unit::toString                     ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Unit") ;
    }

    String symbol = "" ;

    if ((lengthUnit_ != Length::Unit::Undefined) && (!lengthOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Length::StringFromUnit(lengthUnit_) + ((!lengthOrder_.isUnity()) ? ("^" + lengthOrder_.toString()) : "") ;
    }

    if ((massUnit_ != Mass::Unit::Undefined) && (!massOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Mass::StringFromUnit(massUnit_) + ((!massOrder_.isUnity()) ? ("^" + massOrder_.toString()) : "") ;
    }

    if ((electricCurrentUnit_ != ElectricCurrent::Unit::Undefined) && (!electricCurrentOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + ElectricCurrent::StringFromUnit(electricCurrentUnit_) + ((!electricCurrentOrder_.isUnity()) ? ("^" + electricCurrentOrder_.toString()) : "") ;
    }

    if ((angleUnit_ != Angle::Unit::Undefined) && (!angleOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Angle::StringFromUnit(angleUnit_) + ((!angleOrder_.isUnity()) ? ("^" + angleOrder_.toString()) : "") ;
    }

    if ((timeUnit_ != Time::Unit::Undefined) && (!timeOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Time::StringFromUnit(timeUnit_) + ((!timeOrder_.isUnity()) ? ("^" + timeOrder_.toString()) : "") ;
    }

    return symbol ;

}

String                          Derived::Unit::getSymbol                    ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Unit") ;
    }

    String symbol = "" ;

    if ((lengthUnit_ != Length::Unit::Undefined) && (!lengthOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Length::SymbolFromUnit(lengthUnit_) + ((!lengthOrder_.isUnity()) ? ("^" + lengthOrder_.toString()) : "") ;
    }

    if ((massUnit_ != Mass::Unit::Undefined) && (!massOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Mass::SymbolFromUnit(massUnit_) + ((!massOrder_.isUnity()) ? ("^" + massOrder_.toString()) : "") ;
    }

    if ((electricCurrentUnit_ != ElectricCurrent::Unit::Undefined) && (!electricCurrentOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + ElectricCurrent::SymbolFromUnit(electricCurrentUnit_) + ((!electricCurrentOrder_.isUnity()) ? ("^" + electricCurrentOrder_.toString()) : "") ;
    }

    if ((angleUnit_ != Angle::Unit::Undefined) && (!angleOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Angle::SymbolFromUnit(angleUnit_) + ((!angleOrder_.isUnity()) ? ("^" + angleOrder_.toString()) : "") ;
    }

    if ((timeUnit_ != Time::Unit::Undefined) && (!timeOrder_.isZero()))
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
    return { Length::Unit::Undefined, { 0 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Undefined, { 0 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::SquareMeter                  ( )
{
    return { Length::Unit::Meter, { 2 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Undefined, { 0 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::CubicMeter                   ( )
{
    return { Length::Unit::Meter, { 3 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Undefined, { 0 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::Hertz                        ( )
{
    return { Length::Unit::Undefined, { 0 }, Mass::Unit::Undefined, { 0 }, Time::Unit::Second, { -1 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::Watt                         ( )
{
    return { Length::Unit::Meter, { 2 }, Mass::Unit::Kilogram, { 1 }, Time::Unit::Second, { -3 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::Tesla                        ( )
{
    return { Length::Unit::Undefined, { 0 }, Mass::Unit::Kilogram, { 1 }, Time::Unit::Second, { -2 }, ElectricCurrent::Unit::Ampere, { -1 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::Velocity                     (   const   Length::Unit&               aLengthUnit,
                                                                                const   Time::Unit&                 aTimeUnit                                   )
{
    return { aLengthUnit, { 1 }, Mass::Unit::Undefined, { 0 }, aTimeUnit, { -1 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::Acceleration                 (   const   Length::Unit&               aLengthUnit,
                                                                                const   Time::Unit&                 aTimeUnit                                   )
{
    return { aLengthUnit, { 1 }, Mass::Unit::Undefined, { 0 }, aTimeUnit, { -2 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::GravitationalParameter       (   const   Length::Unit&               aLengthUnit,
                                                                                const   Time::Unit&                 aTimeUnit                                   )
{
    return { aLengthUnit, { 3 }, Mass::Unit::Undefined, { 0 }, aTimeUnit, { -2 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
}

Derived::Unit                   Derived::Unit::AngularVelocity              (   const   Angle::Unit&                anAngleUnit,
                                                                                const   Time::Unit&                 aTimeUnit                                   )
{
    return { Length::Unit::Undefined, { 0 }, Mass::Unit::Undefined, { 0 }, aTimeUnit, { -1 }, ElectricCurrent::Unit::Undefined, { 0 }, anAngleUnit, { 1 } } ;
}

Derived::Unit                   Derived::Unit::MassDensity                  (   const   Mass::Unit&                 aMassUnit,
                                                                                const   Length::Unit&               aLengthUnit                                 )
{
    return { aLengthUnit, { -3 }, aMassUnit, { 1 }, Time::Unit::Undefined, { 0 }, ElectricCurrent::Unit::Undefined, { 0 }, Angle::Unit::Undefined, { 0 } } ;
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

Derived*                        Derived::clone                              ( ) const
{
    return new Derived(*this) ;
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

    ostk::core::utils::Print::Header(anOutputStream, "Derived") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << aDerivedUnit.accessValue() ;
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << aDerivedUnit.unit_.toString() ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

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
        throw ostk::core::error::RuntimeError("Cannot convert unit [" + unit_.toString() + "] to [" + aUnit.toString() + "].") ;
    }

    return this->accessValue() * Derived::SIRatio(unit_) / Derived::SIRatio(aUnit) ;

}

String                          Derived::toString                           (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Derived") ;
    }

    return this->accessValue().toString(aPrecision) + " [" + unit_.getSymbol() + "]" ;

}

Derived                         Derived::Undefined                          ( )
{
    return { Real::Undefined(), Derived::Unit::Undefined() } ;
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
        ratio *= std::pow(Mass(1.0, aUnit.accessMassUnit()).in(Mass::Unit::Kilogram), aUnit.accessMassOrder().getValue()) ;
    }

    if (!aUnit.accessTimeOrder().isZero())
    {
        ratio *= std::pow(Time(1.0, aUnit.accessTimeUnit()).in(Time::Unit::Second), aUnit.accessTimeOrder().getValue()) ;
    }

    if (!aUnit.accessElectricCurrentOrder().isZero())
    {
        ratio *= std::pow(ElectricCurrent(1.0, aUnit.accessElectricCurrentUnit()).in(ElectricCurrent::Unit::Ampere), aUnit.accessElectricCurrentOrder().getValue()) ;
    }

    if (!aUnit.accessAngleOrder().isZero())
    {
        ratio *= std::pow(Angle(1.0, aUnit.accessAngleUnit()).in(Angle::Unit::Radian), aUnit.accessAngleOrder().getValue()) ;
    }

    return ratio ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
