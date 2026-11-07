/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

Axes::Axes(
    const Vector3d& aXAxis, const Vector3d& aYAxis, const Vector3d& aZAxis, const Shared<const Frame>& aFrameSPtr
)
    : x_(aXAxis),
      y_(aYAxis),
      z_(aZAxis),
      frameSPtr_(aFrameSPtr)
{
    if (aFrameSPtr == nullptr)
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }
}

bool Axes::operator==(const Axes& anAxes) const
{
    return (x_ == anAxes.x_) && (y_ == anAxes.y_) && (z_ == anAxes.z_) && ((*frameSPtr_) == (*anAxes.frameSPtr_));
}

bool Axes::operator!=(const Axes& anAxes) const
{
    return !((*this) == anAxes);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Axes& anAxes)
{
    ostk::core::utils::Print::Header(anOutputStream, "Axes");

    ostk::core::utils::Print::Line(anOutputStream) << "X:" << anAxes.x().toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Y:" << anAxes.y().toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Z:" << anAxes.z().toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Frame:" << anAxes.frameSPtr_->getName();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

const Vector3d& Axes::x() const
{
    return x_;
}

const Vector3d& Axes::y() const
{
    return y_;
}

const Vector3d& Axes::z() const
{
    return z_;
}

const Shared<const Frame>& Axes::getFrame() const
{
    return frameSPtr_;
}

Axes Axes::inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    using ostk::physics::coordinate::Transform;

    if ((aFrameSPtr == nullptr))
    {
        throw ostk::core::error::runtime::Undefined("Frame");
    }

    const Transform transform = frameSPtr_->getTransformTo(aFrameSPtr, anInstant);

    return {
        transform.applyToVector(x_).normalized(),
        transform.applyToVector(y_).normalized(),
        transform.applyToVector(z_).normalized(),
        aFrameSPtr
    };
}

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
