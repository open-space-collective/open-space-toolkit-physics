/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Undefined.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace atmospheric
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

Real Undefined::getDensityAt(const Position& aPosition, const Instant& anInstant) const
{
    throw ostk::core::error::runtime::Undefined("Atmospheric Model") ;
}

}  // namespace atmospheric
}  // namespace environment
}  // namespace physics
}  // namespace ostk
