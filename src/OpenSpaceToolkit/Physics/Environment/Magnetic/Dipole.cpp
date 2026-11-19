/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{

using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using ostk::physics::unit::Mass;
using ostk::physics::unit::Time;

Dipole::Dipole(const Vector3d& aMagneticMoment)
    : Model(),
      magneticMoment_SI_(aMagneticMoment)
{
}

Dipole* Dipole::clone() const
{
    return new Dipole(*this);
}

Vector3d Dipole::getFieldValueAt(const Vector3d& aPosition, const Instant& anInstant) const
{
    (void)anInstant;  // Temporal invariance

    const double r = aPosition.norm();  // [m]

    const Vector3d magneticField =
        1e-7 * (3.0 * (magneticMoment_SI_.dot(aPosition)) * aPosition - std::pow(r, 2.0) * magneticMoment_SI_) /
        std::pow(r, 5.0);  // [T]
    // const Vector3d magneticField = (3.0 * (magneticMoment_SI_.dot(aPosition)) * aPosition - std::pow(r, 2.0) *
    // magneticMoment_SI_) / std::pow(r, 5.0) ; // [T]

    return magneticField;
}

}  // namespace magnetic
}  // namespace environment
}  // namespace physics
}  // namespace ostk
