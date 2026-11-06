/// Apache License 2.0

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Unit/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace unit
{

Unit::Unit(const Unit::Type& aType, double aValue)
    : type_(aType),
      value_(aValue)
{
}

Unit::~Unit() {}

bool Unit::operator==(const Unit& aUnit) const
{
    return (type_ == aUnit.type_) && (value_ == aUnit.value_);
}

bool Unit::operator!=(const Unit& aUnit) const
{
    return (type_ != aUnit.type_) || (value_ != aUnit.value_);
}

bool Unit::isZero() const
{
    return value_ == 0.0;
}

const double& Unit::accessValue() const
{
    return value_;
}

Unit::Type Unit::getType() const
{
    return type_;
}

double Unit::getValue() const
{
    return value_;
}

double& Unit::accessValue()
{
    return value_;
}

void Unit::setValue(double aValue)
{
    value_ = aValue;
}

Pair<double, String> Unit::ParseString(const String& aString)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    boost::smatch match;

    if (boost::regex_match(aString, match, boost::regex("^([-+\\de.]+) \\[([\\w\\/^\\.]+)\\]$")))
    {
        const double value = boost::lexical_cast<double>(match[1]);
        const String unit = String(match[2]);

        return {value, unit};
    }
    else
    {
        throw ostk::core::error::RuntimeError("Cannot parse unit string [{}].", aString);
    }
}

}  // namespace unit
}  // namespace physics
}  // namespace ostk
