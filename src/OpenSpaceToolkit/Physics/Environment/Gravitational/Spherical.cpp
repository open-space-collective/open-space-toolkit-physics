/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>

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

static const Derived::Unit GravitationParameterSIUnit =
    Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second);

Spherical::Spherical(const Derived& aGravitationalParameter)
    : Model(),
      gravitationalParameter_SI_(aGravitationalParameter.in(GravitationParameterSIUnit))
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
