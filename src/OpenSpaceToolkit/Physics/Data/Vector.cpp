/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Data/Vector.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

Vector::Vector(const Vector3d& aValue, const Unit& aUnit, const Shared<const Frame>& aFrameSPtr)
    : value_(aValue),
      unit_(aUnit),
      frameSPtr_(aFrameSPtr)
{
    if (aFrameSPtr == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }
}

bool Vector::operator==(const Vector& aVector) const
{
    return (value_ == aVector.value_) && (unit_ == aVector.unit_) && ((*frameSPtr_) == (*aVector.frameSPtr_));
}

bool Vector::operator!=(const Vector& aVector) const
{
    return !((*this) == aVector);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Vector& aVector)
{
    ostk::core::utils::Print::Header(anOutputStream, "Vector");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Value:" << (aVector.value_.isDefined() ? aVector.value_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << aVector.unit_.toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Frame:" << aVector.frameSPtr_->getName();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

const Vector3d& Vector::getValue() const
{
    return value_;
}

const Unit& Vector::getUnit() const
{
    return unit_;
}

const Shared<const Frame>& Vector::getFrame() const
{
    return frameSPtr_;
}

Vector Vector::inUnit(const Unit& aUnit) const
{
    return {value_ * unit_.ratioTo(aUnit), aUnit, frameSPtr_};
}

Vector Vector::inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    return {frameSPtr_->getTransformTo(aFrameSPtr, anInstant).applyToVector(value_), unit_, aFrameSPtr};
}

String Vector::toString(int aPrecision) const
{
    return String::Format("{} [{}] @ {}", value_.toString(aPrecision), unit_.toString(), frameSPtr_->getName());
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
