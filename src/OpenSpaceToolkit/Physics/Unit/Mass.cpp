/// Apache License 2.0

#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{
using ostk::physics::utility::DoubleToString;

Mass::Mass(double aValue, const Mass::Unit& aUnit)
    : unit::Unit(unit::Unit::Type::Mass, aValue),
      unit_(aUnit)
{
}

Mass* Mass::clone() const
{
    return new Mass(*this);
}

Mass::Unit Mass::getUnit() const
{
    return unit_;
}

double Mass::in(const Mass::Unit& aUnit) const
{
    if (unit_ == aUnit)
    {
        return this->getValue();
    }

    return this->getValue() * Mass::SIRatio(unit_) / Mass::SIRatio(aUnit);
}

double Mass::inKilograms() const
{
    return this->in(Mass::Unit::Kilogram);
}

String Mass::toString(int aPrecision) const
{
    return DoubleToString(this->getValue(), aPrecision) + " [" + Mass::SymbolFromUnit(unit_) + "]";
}

Mass Mass::Kilograms(double aValue)
{
    return {aValue, Mass::Unit::Kilogram};
}

Mass Mass::Parse(const String& aString)
{
    (void)aString;

    throw ostk::core::error::runtime::ToBeImplemented("Mass :: Parse");
}

String Mass::StringFromUnit(const Mass::Unit& aUnit)
{
    switch (aUnit)
    {
        case Mass::Unit::Kilogram:
            return "Kilogram";

        case Mass::Unit::Tonne:
            return "Tonne";

        case Mass::Unit::Pound:
            return "Pound";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

String Mass::SymbolFromUnit(const Mass::Unit& aUnit)
{
    switch (aUnit)
    {
        case Mass::Unit::Kilogram:
            return "kg";

        case Mass::Unit::Tonne:
            return "t";

        case Mass::Unit::Pound:
            return "lb";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

double Mass::SIRatio(const Mass::Unit& aUnit)
{
    switch (aUnit)
    {
        case Mass::Unit::Kilogram:
            return 1.0;
        case Mass::Unit::Pound:
            return 2.20462;
        case Mass::Unit::Tonne:
            return 1016.047;

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }
}
}  // namespace unit
}  // namespace physics
}  // namespace ostk
