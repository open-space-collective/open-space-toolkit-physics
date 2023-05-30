/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{

Axes::Axes(
    const Vector3d& aXAxis, const Vector3d& aYAxis, const Vector3d& aZAxis, const Shared<const Frame>& aFrameSPtr
)
    : x_(aXAxis),
      y_(aYAxis),
      z_(aZAxis),
      frameSPtr_(aFrameSPtr)
{
}

bool Axes::operator==(const Axes& anAxes) const
{
    if ((!this->isDefined()) || (!anAxes.isDefined()))
    {
        return false;
    }

    return (x_ == anAxes.x_) && (y_ == anAxes.y_) && (z_ == anAxes.z_) && ((*frameSPtr_) == (*anAxes.frameSPtr_));
}

bool Axes::operator!=(const Axes& anAxes) const
{
    return !((*this) == anAxes);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Axes& anAxes)
{
    ostk::core::utils::Print::Header(anOutputStream, "Axes");

    ostk::core::utils::Print::Line(anOutputStream)
        << "X:" << (anAxes.isDefined() ? anAxes.x().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Y:" << (anAxes.isDefined() ? anAxes.y().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Z:" << (anAxes.isDefined() ? anAxes.z().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Frame:" << (anAxes.isDefined() ? anAxes.frameSPtr_->getName() : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Axes::isDefined() const
{
    return x_.isDefined() && y_.isDefined() && z_.isDefined() && (frameSPtr_ != nullptr) && frameSPtr_->isDefined();
}

const Vector3d& Axes::x() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Axes");
    }

    return x_;
}

const Vector3d& Axes::y() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Axes");
    }

    return y_;
}

const Vector3d& Axes::z() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Axes");
    }

    return z_;
}

Shared<const Frame> Axes::getFrame() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Axes");
    }

    return frameSPtr_;
}

Axes Axes::inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    using ostk::physics::coord::Transform;

    if ((aFrameSPtr == nullptr) && (!aFrameSPtr->isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Axes");
    }

    const Transform transform = frameSPtr_->getTransformTo(aFrameSPtr, anInstant);

    return {
        transform.applyToVector(x_).normalized(),
        transform.applyToVector(y_).normalized(),
        transform.applyToVector(z_).normalized(),
        aFrameSPtr};
}

Axes Axes::Undefined()
{
    return {Vector3d::Undefined(), Vector3d::Undefined(), Vector3d::Undefined(), nullptr};
}

}  // namespace coord
}  // namespace physics
}  // namespace ostk
