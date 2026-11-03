/// Apache License 2.0

#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit/ElectricCurrent.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

using ostk::physics::utility::DoubleToString;

ElectricCurrent::ElectricCurrent(double aValue, const ElectricCurrent::Unit& aUnit)
    : unit::Unit(unit::Unit::Type::ElectricCurrent, aValue),
      unit_(aUnit)
{
}

ElectricCurrent* ElectricCurrent::clone() const
{
    return new ElectricCurrent(*this);
}

bool ElectricCurrent::isDefined() const
{
    return unit::Unit::isDefined() && (unit_ != ElectricCurrent::Unit::Undefined);
}

ElectricCurrent::Unit ElectricCurrent::getUnit() const
{
    return unit_;
}

double ElectricCurrent::in(const ElectricCurrent::Unit& aUnit) const
{
    if (!this->isDefined())
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    if (unit_ == aUnit)
    {
        return this->accessValue();
    }

    return this->accessValue() * ElectricCurrent::SIRatio(unit_) / ElectricCurrent::SIRatio(aUnit);
}

double ElectricCurrent::inAmperes() const
{
    return this->in(ElectricCurrent::Unit::Ampere);
}

String ElectricCurrent::toString(int aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Electric current");
    }

    return DoubleToString(this->accessValue(), aPrecision) + " [" + ElectricCurrent::SymbolFromUnit(unit_) + "]";
}

ElectricCurrent ElectricCurrent::Undefined()
{
    return {std::numeric_limits<double>::quiet_NaN(), ElectricCurrent::Unit::Undefined};
}

ElectricCurrent ElectricCurrent::Amperes(double aValue)
{
    return {aValue, ElectricCurrent::Unit::Ampere};
}

// ElectricCurrent                 ElectricCurrent::Parse                      (   const   String& aString )
// {

// }

String ElectricCurrent::StringFromUnit(const ElectricCurrent::Unit& aUnit)
{
    switch (aUnit)
    {
        case ElectricCurrent::Unit::Undefined:
            return "Undefined";

        case ElectricCurrent::Unit::Ampere:
            return "Ampere";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

String ElectricCurrent::SymbolFromUnit(const ElectricCurrent::Unit& aUnit)
{
    switch (aUnit)
    {
        case ElectricCurrent::Unit::Ampere:
            return "A";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

double ElectricCurrent::SIRatio(const ElectricCurrent::Unit& aUnit)
{
    switch (aUnit)
    {
        case ElectricCurrent::Unit::Ampere:
            return 1.0;

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

}  // namespace unit
}  // namespace physics
}  // namespace ostk
