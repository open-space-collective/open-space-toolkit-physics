/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{

using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using ostk::physics::unit::Mass;
using ostk::physics::unit::Time;

Spherical::Spherical(const Model::Parameters& aParameterSet)
    : Model(aParameterSet),
      gravitationalParameter_SI_(aParameterSet.gravitationalParameter_.in(GravitationalParameterSIUnit))
{
    if (!gravitationalParameter_SI_.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Gravitational parameter");
    }
}

Spherical* Spherical::clone() const
{
    return new Spherical(*this);
}

bool Spherical::isDefined() const
{
    return gravitationalParameter_SI_.isDefined();
}

Vector3d Spherical::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    (void)anInstant;  // Temporal invariance

    const Real r = aPosition.norm();
    const Vector3d fieldDirection = aPosition.normalized();

    const Vector3d field = (-gravitationalParameter_SI_) / (r * r) * fieldDirection;

    return field;
}

}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk
