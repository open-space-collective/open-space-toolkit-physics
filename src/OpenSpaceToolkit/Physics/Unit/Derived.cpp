/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::physics::utility::DoubleToString;

Derived::Order::Order(Int16 aNumerator)
    : numerator_(aNumerator),
      denominator_(1)
{
}

Derived::Order::Order(Int16 aNumerator, Int16 aDenominator)
    : numerator_(aNumerator),
      denominator_(aDenominator)
{
    if (denominator_ == 0)
    {
        throw ostk::core::error::runtime::Wrong("Denominator");
    }
}

bool Derived::Order::operator==(const Derived::Order& anOrder) const
{
    return (numerator_ == anOrder.numerator_) && (denominator_ == anOrder.denominator_);
}

bool Derived::Order::operator!=(const Derived::Order& anOrder) const
{
    return (numerator_ != anOrder.numerator_) || (denominator_ != anOrder.denominator_);
}

bool Derived::Order::isZero() const
{
    return numerator_ == 0;
}

bool Derived::Order::isUnity() const
{
    return (numerator_ == 1) && (denominator_ == 1);
}

Int16 Derived::Order::getNumerator() const
{
    return numerator_;
}

Int16 Derived::Order::getDenominator() const
{
    return denominator_;
}

double Derived::Order::getValue() const
{
    return static_cast<double>(numerator_) / static_cast<double>(denominator_);
}

String Derived::Order::toString() const
{
    if (denominator_ == 1)
    {
        return std::to_string(numerator_);
    }

    if (numerator_ == 1)
    {
        return "-" + std::to_string(denominator_);
    }

    return std::to_string(numerator_) + "/" + std::to_string(denominator_);
}

Derived::Order Derived::Order::Zero()
{
    return {0, 1};
}

Derived::Order Derived::Order::One()
{
    return {1, 1};
}

Derived::Order Derived::Order::Two()
{
    return {2, 1};
}

Derived::Unit::Unit(
    const std::optional<Length::Unit>& aLengthUnit,
    const Order& aLengthOrder,
    const std::optional<Mass::Unit>& aMassUnit,
    const Order& aMassOrder,
    const std::optional<Time::Unit>& aTimeUnit,
    const Order& aTimeOrder,
    const std::optional<ElectricCurrent::Unit>& anElectricCurrentUnit,
    const Order& anElectricCurrentOrder,
    const std::optional<Angle::Unit>& anAngleUnit,
    const Order& anAngleOrder
)
    : lengthUnit_(aLengthUnit),
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
    // A dimension that is present in the unit (non-zero order) needs a unit

    if ((!lengthUnit_.has_value()) && (!lengthOrder_.isZero()))
    {
        throw ostk::core::error::runtime::Wrong("Length unit");
    }

    if ((!massUnit_.has_value()) && (!massOrder_.isZero()))
    {
        throw ostk::core::error::runtime::Wrong("Mass unit");
    }

    if ((!timeUnit_.has_value()) && (!timeOrder_.isZero()))
    {
        throw ostk::core::error::runtime::Wrong("Time unit");
    }

    if ((!electricCurrentUnit_.has_value()) && (!electricCurrentOrder_.isZero()))
    {
        throw ostk::core::error::runtime::Wrong("Electric current unit");
    }

    if ((!angleUnit_.has_value()) && (!angleOrder_.isZero()))
    {
        throw ostk::core::error::runtime::Wrong("Angle unit");
    }
}

bool Derived::Unit::operator==(const Derived::Unit& aUnit) const
{
    return (lengthUnit_ == aUnit.lengthUnit_) && (lengthOrder_ == aUnit.lengthOrder_) &&
           (massUnit_ == aUnit.massUnit_) && (massOrder_ == aUnit.massOrder_) && (timeUnit_ == aUnit.timeUnit_) &&
           (timeOrder_ == aUnit.timeOrder_) && (electricCurrentUnit_ == aUnit.electricCurrentUnit_) &&
           (electricCurrentOrder_ == aUnit.electricCurrentOrder_) && (angleUnit_ == aUnit.angleUnit_) &&
           (angleOrder_ == aUnit.angleOrder_);
}

bool Derived::Unit::operator!=(const Derived::Unit& aUnit) const
{
    return !((*this) == aUnit);
}

bool Derived::Unit::isCompatibleWith(const Unit& aUnit) const
{
    return (lengthOrder_ == aUnit.lengthOrder_) && (massOrder_ == aUnit.massOrder_) &&
           (timeOrder_ == aUnit.timeOrder_) && (electricCurrentOrder_ == aUnit.electricCurrentOrder_) &&
           (angleOrder_ == aUnit.angleOrder_);
}

const std::optional<Length::Unit>& Derived::Unit::accessLengthUnit() const
{
    return lengthUnit_;
}

const Derived::Order& Derived::Unit::accessLengthOrder() const
{
    return lengthOrder_;
}

const std::optional<Mass::Unit>& Derived::Unit::accessMassUnit() const
{
    return massUnit_;
}

const Derived::Order& Derived::Unit::accessMassOrder() const
{
    return massOrder_;
}

const std::optional<Time::Unit>& Derived::Unit::accessTimeUnit() const
{
    return timeUnit_;
}

const Derived::Order& Derived::Unit::accessTimeOrder() const
{
    return timeOrder_;
}

const std::optional<ElectricCurrent::Unit>& Derived::Unit::accessElectricCurrentUnit() const
{
    return electricCurrentUnit_;
}

const Derived::Order& Derived::Unit::accessElectricCurrentOrder() const
{
    return electricCurrentOrder_;
}

const std::optional<Angle::Unit>& Derived::Unit::accessAngleUnit() const
{
    return angleUnit_;
}

const Derived::Order& Derived::Unit::accessAngleOrder() const
{
    return angleOrder_;
}

String Derived::Unit::toString() const
{
    String symbol = "";

    if (lengthUnit_.has_value() && (!lengthOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Length::StringFromUnit(*lengthUnit_) +
                  ((!lengthOrder_.isUnity()) ? ("^" + lengthOrder_.toString()) : "");
    }

    if (massUnit_.has_value() && (!massOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Mass::StringFromUnit(*massUnit_) +
                  ((!massOrder_.isUnity()) ? ("^" + massOrder_.toString()) : "");
    }

    if (electricCurrentUnit_.has_value() && (!electricCurrentOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + ElectricCurrent::StringFromUnit(*electricCurrentUnit_) +
                  ((!electricCurrentOrder_.isUnity()) ? ("^" + electricCurrentOrder_.toString()) : "");
    }

    if (angleUnit_.has_value() && (!angleOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Angle::StringFromUnit(*angleUnit_) +
                  ((!angleOrder_.isUnity()) ? ("^" + angleOrder_.toString()) : "");
    }

    if (timeUnit_.has_value() && (!timeOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Time::StringFromUnit(*timeUnit_) +
                  ((!timeOrder_.isUnity()) ? ("^" + timeOrder_.toString()) : "");
    }

    return symbol;
}

String Derived::Unit::getSymbol() const
{
    String symbol = "";

    if (lengthUnit_.has_value() && (!lengthOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Length::SymbolFromUnit(*lengthUnit_) +
                  ((!lengthOrder_.isUnity()) ? ("^" + lengthOrder_.toString()) : "");
    }

    if (massUnit_.has_value() && (!massOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Mass::SymbolFromUnit(*massUnit_) +
                  ((!massOrder_.isUnity()) ? ("^" + massOrder_.toString()) : "");
    }

    if (electricCurrentUnit_.has_value() && (!electricCurrentOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + ElectricCurrent::SymbolFromUnit(*electricCurrentUnit_) +
                  ((!electricCurrentOrder_.isUnity()) ? ("^" + electricCurrentOrder_.toString()) : "");
    }

    if (angleUnit_.has_value() && (!angleOrder_.isZero()))
    {
        symbol += ((!symbol.isEmpty()) ? "." : "") + Angle::SymbolFromUnit(*angleUnit_) +
                  ((!angleOrder_.isUnity()) ? ("^" + angleOrder_.toString()) : "");
    }

    if (timeUnit_.has_value() && (!timeOrder_.isZero()))
    {
        if (timeOrder_.getValue() == -1.0)  // Special case to support / time format
        {
            symbol += ((!symbol.isEmpty()) ? "/" : "") + Time::SymbolFromUnit(*timeUnit_);
        }
        else
        {
            symbol += ((!symbol.isEmpty()) ? "." : "") + Time::SymbolFromUnit(*timeUnit_) +
                      ((!timeOrder_.isUnity()) ? ("^" + timeOrder_.toString()) : "");
        }
    }

    return symbol;
}

Derived::Unit Derived::Unit::SquareMeter()
{
    return {Length::Unit::Meter, {2}, std::nullopt, {0}, std::nullopt, {0}, std::nullopt, {0}, std::nullopt, {0}};
}

Derived::Unit Derived::Unit::CubicMeter()
{
    return {Length::Unit::Meter, {3}, std::nullopt, {0}, std::nullopt, {0}, std::nullopt, {0}, std::nullopt, {0}};
}

Derived::Unit Derived::Unit::Hertz()
{
    return {std::nullopt, {0}, std::nullopt, {0}, Time::Unit::Second, {-1}, std::nullopt, {0}, std::nullopt, {0}};
}

Derived::Unit Derived::Unit::Watt()
{
    return {
        Length::Unit::Meter,
        {2},
        Mass::Unit::Kilogram,
        {1},
        Time::Unit::Second,
        {-3},
        std::nullopt,
        {0},
        std::nullopt,
        {0}
    };
}

Derived::Unit Derived::Unit::Tesla()
{
    return {
        std::nullopt,
        {0},
        Mass::Unit::Kilogram,
        {1},
        Time::Unit::Second,
        {-2},
        ElectricCurrent::Unit::Ampere,
        {-1},
        std::nullopt,
        {0}
    };
}

Derived::Unit Derived::Unit::Newton()
{
    return {
        Length::Unit::Meter,
        {1},
        Mass::Unit::Kilogram,
        {1},
        Time::Unit::Second,
        {-2},
        std::nullopt,
        {0},
        std::nullopt,
        {0},
    };
}

Derived::Unit Derived::Unit::KilogramPerSecond()
{
    return {
        std::nullopt,
        {0},
        Mass::Unit::Kilogram,
        {1},
        Time::Unit::Second,
        {-1},
        std::nullopt,
        {0},
        std::nullopt,
        {0},
    };
}

Derived::Unit Derived::Unit::MeterPerSecond()
{
    return {
        Length::Unit::Meter, {1}, std::nullopt, {0}, Time::Unit::Second, {-1}, std::nullopt, {0}, std::nullopt, {0}
    };
}

Derived::Unit Derived::Unit::MeterPerSecondSquared()
{
    return {
        Length::Unit::Meter, {1}, std::nullopt, {0}, Time::Unit::Second, {-2}, std::nullopt, {0}, std::nullopt, {0}
    };
}

Derived::Unit Derived::Unit::MeterCubedPerSecondSquared()
{
    return {
        Length::Unit::Meter, {3}, std::nullopt, {0}, Time::Unit::Second, {-2}, std::nullopt, {0}, std::nullopt, {0}
    };
}

Derived::Unit Derived::Unit::RadianPerSecond()
{
    return {
        std::nullopt, {0}, std::nullopt, {0}, Time::Unit::Second, {-1}, std::nullopt, {0}, Angle::Unit::Radian, {1}
    };
}

Derived::Unit Derived::Unit::RevolutionPerDay()
{
    return {
        std::nullopt, {0}, std::nullopt, {0}, Time::Unit::Day, {-1}, std::nullopt, {0}, Angle::Unit::Revolution, {1}
    };
}

Derived::Unit Derived::Unit::Velocity(const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit)
{
    return {aLengthUnit, {1}, std::nullopt, {0}, aTimeUnit, {-1}, std::nullopt, {0}, std::nullopt, {0}};
}

Derived::Unit Derived::Unit::Acceleration(const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit)
{
    return {aLengthUnit, {1}, std::nullopt, {0}, aTimeUnit, {-2}, std::nullopt, {0}, std::nullopt, {0}};
}

Derived::Unit Derived::Unit::GravitationalParameter(const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit)
{
    return {aLengthUnit, {3}, std::nullopt, {0}, aTimeUnit, {-2}, std::nullopt, {0}, std::nullopt, {0}};
}

Derived::Unit Derived::Unit::AngularVelocity(const Angle::Unit& anAngleUnit, const Time::Unit& aTimeUnit)
{
    return {std::nullopt, {0}, std::nullopt, {0}, aTimeUnit, {-1}, std::nullopt, {0}, anAngleUnit, {1}};
}

Derived::Unit Derived::Unit::Force(
    const Mass::Unit& aMassUnit, const Length::Unit& aLengthUnit, const Time::Unit& aTimeUnit
)
{
    return {
        aLengthUnit,
        {1},
        aMassUnit,
        {1},
        aTimeUnit,
        {-2},
        std::nullopt,
        {0},
        std::nullopt,
        {0},
    };
}

Derived::Unit Derived::Unit::MassFlowRate(const Mass::Unit& aMassUnit, const Time::Unit& aTimeUnit)
{
    return {
        std::nullopt,
        {0},
        aMassUnit,
        {1},
        aTimeUnit,
        {-1},
        std::nullopt,
        {0},
        std::nullopt,
        {0},
    };
}

Derived::Unit Derived::Unit::MassDensity(const Mass::Unit& aMassUnit, const Length::Unit& aLengthUnit)
{
    return {aLengthUnit, {-3}, aMassUnit, {1}, std::nullopt, {0}, std::nullopt, {0}, std::nullopt, {0}};
}

// Derived::Unit                   Derived::Unit::Parse                        (   const   String& aString )
// {

// }

Derived::Derived(double aValue, const Derived::Unit& aUnit)
    : unit::Unit(unit::Unit::Type::Derived, aValue),
      unit_(aUnit)
{
}

Derived* Derived::clone() const
{
    return new Derived(*this);
}

bool Derived::operator==(const Derived& aDerivedUnit) const
{
    return this->accessValue() == ((unit_ == aDerivedUnit.unit_) ? aDerivedUnit.accessValue() : aDerivedUnit.in(unit_));
}

bool Derived::operator!=(const Derived& aDerivedUnit) const
{
    return !((*this) == aDerivedUnit);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Derived& aDerivedUnit)
{
    ostk::core::utils::Print::Header(anOutputStream, "Derived");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << aDerivedUnit.accessValue();
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << aDerivedUnit.unit_.toString();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

Derived::Unit Derived::getUnit() const
{
    return unit_;
}

double Derived::in(const Derived::Unit& aUnit) const
{
    if (unit_ == aUnit)
    {
        return this->accessValue();
    }

    if (!unit_.isCompatibleWith(aUnit))
    {
        throw ostk::core::error::RuntimeError(
            "Cannot convert unit [" + unit_.toString() + "] to [" + aUnit.toString() + "]."
        );
    }

    return this->accessValue() * Derived::SIRatio(unit_) / Derived::SIRatio(aUnit);
}

String Derived::toString(int aPrecision) const
{
    return DoubleToString(this->accessValue(), aPrecision) + " [" + unit_.getSymbol() + "]";
}

// Derived                         Derived::Parse                               (   const   String& aString )
// {

// }

String Derived::StringFromUnit(const Derived::Unit& aUnit)
{
    return aUnit.toString();
}

String Derived::SymbolFromUnit(const Derived::Unit& aUnit)
{
    return aUnit.getSymbol();
}

double Derived::SIRatio(const Derived::Unit& aUnit)
{
    double ratio = 1.0;

    if (!aUnit.accessLengthOrder().isZero())
    {
        ratio *= std::pow(
            Length(1.0, aUnit.accessLengthUnit().value()).in(Length::Unit::Meter), aUnit.accessLengthOrder().getValue()
        );
    }

    if (!aUnit.accessMassOrder().isZero())
    {
        ratio *= std::pow(
            Mass(1.0, aUnit.accessMassUnit().value()).in(Mass::Unit::Kilogram), aUnit.accessMassOrder().getValue()
        );
    }

    if (!aUnit.accessTimeOrder().isZero())
    {
        ratio *= std::pow(
            Time(1.0, aUnit.accessTimeUnit().value()).in(Time::Unit::Second), aUnit.accessTimeOrder().getValue()
        );
    }

    if (!aUnit.accessElectricCurrentOrder().isZero())
    {
        ratio *= std::pow(
            ElectricCurrent(1.0, aUnit.accessElectricCurrentUnit().value()).in(ElectricCurrent::Unit::Ampere),
            aUnit.accessElectricCurrentOrder().getValue()
        );
    }

    if (!aUnit.accessAngleOrder().isZero())
    {
        ratio *= std::pow(
            Angle(1.0, aUnit.accessAngleUnit().value()).in(Angle::Unit::Radian), aUnit.accessAngleOrder().getValue()
        );
    }

    return ratio;
}

}  // namespace unit
}  // namespace physics
}  // namespace ostk
