/// Apache License 2.0

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

double Scalar::getValue() const
{
    return value_;
}

const Unit& Scalar::getUnit() const
{
    return unit_;
}

Scalar Scalar::inUnit(const Unit& aUnit) const
{
    return {value_ * unit_.ratioTo(aUnit), aUnit};
}

String Scalar::toString(int aPrecision) const
{
    return String::Format("{} [{}]", DoubleToString(value_, aPrecision), unit_.toString());
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
