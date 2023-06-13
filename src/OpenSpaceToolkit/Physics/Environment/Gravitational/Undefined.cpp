/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Undefined.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::physics::units::Length;
using ostk::physics::units::Mass;
using ostk::physics::units::Time;
using ostk::physics::units::Angle;

Undefined::Undefined()
    : Model()
{
}

Undefined* Undefined::clone() const
{
    return new Undefined(*this);
}

bool Undefined::isDefined() const
{
    return false;
}

Vector3d Undefined::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    throw ostk::core::error::runtime::Undefined("Gravitational Model") ;
}

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk
