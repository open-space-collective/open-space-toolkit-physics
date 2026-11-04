/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Data/Scalar.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::physics::utility::DoubleToString;

Scalar::Scalar(double aValue, const Unit& aUnit)
    : value_(aValue),
      unit_(aUnit)
{
}

bool Scalar::operator==(const Scalar& aScalar) const
{
    if ((!this->isDefined()) || (!aScalar.isDefined()))
    {
        return false;
    }

    return (value_ == aScalar.value_) && (unit_ == aScalar.unit_);
}

bool Scalar::operator!=(const Scalar& aScalar) const
{
    return !((*this) == aScalar);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Scalar& aScalar)
{
    ostk::core::utils::Print::Header(anOutputStream, "Scalar");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << DoubleToString(aScalar.value_);
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << aScalar.unit_.toString();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Scalar::isDefined() const
{
    return !std::isnan(value_);
}

double Scalar::getValue() const
{
    return value_;
}

Unit Scalar::getUnit() const
{
    return unit_;
}

Scalar Scalar::inUnit(const Unit& aUnit) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Scalar");
    }

    return {value_ * unit_.ratioTo(aUnit), aUnit};
}

String Scalar::toString(int aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Scalar");
    }

    return String::Format("{} [{}]", DoubleToString(value_, aPrecision), unit_.toString());
}

Scalar Scalar::Undefined()
{
    return {std::numeric_limits<double>::quiet_NaN(), Unit::None()};
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
