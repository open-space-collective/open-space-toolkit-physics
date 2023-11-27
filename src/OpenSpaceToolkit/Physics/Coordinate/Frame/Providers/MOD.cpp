/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/MOD.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{

using ostk::core::ctnr::Triple;

using ostk::physics::units::Angle;
using ostk::physics::time::Scale;

Triple<Angle, Angle, Angle> computeFK5Precession(const Instant& anInstant)
{
    // Compute the angles related to the precession movement using the theory IAU-76/FK5.
    // Ref.: Vallado, D. A (2013). Fundamentals of Astrodynamics and Applications. Microcosm Press, Hawthorn, CA, USA.

    // Compute the Julian Centuries.

    const double JD_TT = anInstant.getJulianDate(Scale::TT);
    const double JD_J2000 = 2451545.0;
    const double T_TT = (JD_TT - JD_J2000) / 36525.0;

    // Compute the angles [arcsec].

    const double zeta = (+2306.2181 * T_TT) + (+0.30188 * T_TT * T_TT) + (+0.017998 * T_TT * T_TT * T_TT);
    const double theta = (+2004.3109 * T_TT) + (-0.42665 * T_TT * T_TT) + (-0.041833 * T_TT * T_TT * T_TT);
    const double z = (+2306.2181 * T_TT) + (+1.09468 * T_TT * T_TT) + (+0.018203 * T_TT * T_TT * T_TT);

    // Normalize the angles in the interval [0, 86400]s and convert to radians.

    const double s2r = M_PI / 648000.0;

    return {Angle::Radians(zeta * s2r), Angle::Radians(theta * s2r), Angle::Radians(z * s2r)};
}

MOD::MOD(const Instant& anEpoch)
    : epoch_(anEpoch)
{
}

MOD::~MOD() {}

MOD* MOD::clone() const
{
    return new MOD(*this);
}

bool MOD::isDefined() const
{
    return true;
}

Instant MOD::getEpoch() const
{
    return epoch_;
}

Transform MOD::getTransformAt(const Instant& anInstant) const
{
    using ostk::math::object::Vector2d;
    using ostk::math::geometry::d3::transformation::rotation::RotationMatrix;

    using ostk::physics::time::Scale;
    using ostk::physics::time::DateTime;
    using ostk::physics::units::Angle;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("MOD");
    }

    const auto& [zeta, theta, z] = computeFK5Precession(epoch_);

    const RotationMatrix dcm_GCRF_MOD = RotationMatrix::RZ(zeta) * RotationMatrix::RY(-theta) * RotationMatrix::RZ(z);

    const Vector3d x_MOD_GCRF = {0.0, 0.0, 0.0};
    const Vector3d v_MOD_GCRF = {0.0, 0.0, 0.0};

    const Quaternion q_MOD_GCRF = Quaternion::RotationMatrix(dcm_GCRF_MOD).conjugate().normalize().rectify();
    const Vector3d w_MOD_GCRF_in_MOD = {0.0, 0.0, 0.0};

    return Transform::Passive(anInstant, x_MOD_GCRF, v_MOD_GCRF, q_MOD_GCRF, w_MOD_GCRF_in_MOD);
}

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
