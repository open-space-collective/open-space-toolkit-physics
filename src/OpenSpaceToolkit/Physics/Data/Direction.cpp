/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Data/Direction.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::physics::Unit;

Direction::Direction(const Vector3d& aValue, const Shared<const Frame>& aFrameSPtr)
    : Vector(aValue.normalized(), Unit::None(), aFrameSPtr)
{
    if (std::abs(aValue.norm() - 1.0) > 1e-15)
    {
        throw ostk::core::error::RuntimeError("Direction vector is not unitary [{}].", aValue.norm());
    }
}

std::ostream& operator<<(std::ostream& anOutputStream, const Direction& aDirection)
{
    ostk::core::utils::Print::Header(anOutputStream, "Direction");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Value:" << (aDirection.getValue().isDefined() ? aDirection.getValue().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Frame:" << aDirection.getFrame()->getName();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

}  // namespace data
}  // namespace physics
}  // namespace ostk
