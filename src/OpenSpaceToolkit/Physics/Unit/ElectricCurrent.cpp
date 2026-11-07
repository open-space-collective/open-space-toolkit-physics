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

ElectricCurrent::Unit ElectricCurrent::getUnit() const
{
    return unit_;
}

double ElectricCurrent::in(const ElectricCurrent::Unit& aUnit) const
{
    if (unit_ == aUnit)
    {
        return this->getValue();
    }

    return this->getValue() * ElectricCurrent::SIRatio(unit_) / ElectricCurrent::SIRatio(aUnit);
}

double ElectricCurrent::inAmperes() const
{
    return this->in(ElectricCurrent::Unit::Ampere);
}

String ElectricCurrent::toString(int aPrecision) const
{
    return DoubleToString(this->getValue(), aPrecision) + " [" + ElectricCurrent::SymbolFromUnit(unit_) + "]";
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
}
}  // namespace unit
}  // namespace physics
}  // namespace ostk
