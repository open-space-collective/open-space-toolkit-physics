/// Apache License 2.0

#include <cmath>
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

bool Mass::operator==(const Mass& aMass) const
{
    if (unit_ == aMass.unit_)
    {
        return this->getValue() == aMass.getValue();
    }

    // Convert both operands to a common unit so the result does not depend on operand order
    return this->inKilograms() == aMass.inKilograms();
}

bool Mass::operator!=(const Mass& aMass) const
{
    return !((*this) == aMass);
}

bool Mass::operator<(const Mass& aMass) const
{
    if (unit_ == aMass.unit_)
    {
        return this->getValue() < aMass.getValue();
    }

    // Convert both operands to a common unit so the result does not depend on operand order
    return this->inKilograms() < aMass.inKilograms();
}

bool Mass::operator<=(const Mass& aMass) const
{
    if (unit_ == aMass.unit_)
    {
        return this->getValue() <= aMass.getValue();
    }

    // Convert both operands to a common unit so the result does not depend on operand order
    return this->inKilograms() <= aMass.inKilograms();
}

bool Mass::operator>(const Mass& aMass) const
{
    if (unit_ == aMass.unit_)
    {
        return this->getValue() > aMass.getValue();
    }

    // Convert both operands to a common unit so the result does not depend on operand order
    return this->inKilograms() > aMass.inKilograms();
}

bool Mass::operator>=(const Mass& aMass) const
{
    if (unit_ == aMass.unit_)
    {
        return this->getValue() >= aMass.getValue();
    }

    // Convert both operands to a common unit so the result does not depend on operand order
    return this->inKilograms() >= aMass.inKilograms();
}

Mass Mass::operator+(const Mass& aMass) const
{
    return {(this->getValue() + ((unit_ == aMass.unit_) ? aMass.getValue() : aMass.in(unit_))), unit_};
}

Mass Mass::operator-(const Mass& aMass) const
{
    return {(this->getValue() - ((unit_ == aMass.unit_) ? aMass.getValue() : aMass.in(unit_))), unit_};
}

Mass Mass::operator*(double aReal) const
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return {(this->getValue() * aReal), unit_};
}

Mass Mass::operator/(double aReal) const
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal == 0.0)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    return {(this->getValue() / aReal), unit_};
}

Mass& Mass::operator+=(const Mass& aMass)
{
    this->accessValue() += ((unit_ == aMass.unit_) ? aMass.getValue() : aMass.in(unit_));

    return *this;
}

Mass& Mass::operator-=(const Mass& aMass)
{
    this->accessValue() -= ((unit_ == aMass.unit_) ? aMass.getValue() : aMass.in(unit_));

    return *this;
}

Mass& Mass::operator*=(double aReal)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    this->accessValue() *= aReal;

    return *this;
}

Mass& Mass::operator/=(double aReal)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal == 0.0)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    this->accessValue() /= aReal;

    return *this;
}

Mass operator*(double aReal, const Mass& aMass)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return {(aMass.getValue() * aReal), aMass.unit_};
}

Mass Mass::operator+() const
{
    return Mass(this->getValue(), unit_);
}

Mass Mass::operator-() const
{
    return Mass(-this->getValue(), unit_);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Mass& aMass)
{
    ostk::core::utils::Print::Header(anOutputStream, "Mass");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << aMass.getValue();
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << Mass::StringFromUnit(aMass.unit_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
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
            return 0.45359237;  // International avoirdupois pound (exact)
        case Mass::Unit::Tonne:
            return 1000.0;  // Metric tonne

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }
}
}  // namespace unit
}  // namespace physics
}  // namespace ostk
