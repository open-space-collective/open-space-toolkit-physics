/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

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

using ostk::physics::time::Scale;

TOD::TOD(const Instant& anEpoch, const iau::Theory& aTheory)
    : epoch_(anEpoch),
      theory_(aTheory)
{
}

TOD::~TOD() {}

TOD* TOD::clone() const
{
    return new TOD(*this);
}

bool TOD::isDefined() const
{
    return this->epoch_.isDefined();
}

Instant TOD::getEpoch() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("TOD");
    }

    return this->epoch_;
}

iau::Theory TOD::getTheory() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("TOD");
    }

    return this->theory_;
}

Transform TOD::getTransformAt(const Instant& anInstant) const
{
    using ostk::math::geometry::d3::transformation::rotation::RotationMatrix;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("TOD");
    }

    const double date1 = 2400000.5;
    const double date2 = this->epoch_.getModifiedJulianDate(Scale::TT);

    double rbpn[3][3];

    switch (this->theory_)
    {
        case iau::Theory::IAU_2000A:
            // Matrix of precession−nutation for a given date (including frame bias), equinox based, IAU 2000A model.
            iauPnm00a(date1, date2, rbpn);
            break;

        case iau::Theory::IAU_2000B:
            // Matrix of precession−nutation for a given date (including frame bias), equinox−based, IAU 2000B model.
            iauPnm00b(date1, date2, rbpn);
            break;

        case iau::Theory::IAU_2006:
            // Matrix of precession−nutation for a given date (including frame bias), equinox based, IAU 2006 precession
            // and IAU 2000A nutation models.
            iauPnm06a(date1, date2, rbpn);
            break;

        default:
            throw ostk::core::error::runtime::Wrong("Theory");
            break;
    }

    const Vector3d TOD_x_GCRF = Vector3d(rbpn[0][0], rbpn[1][0], rbpn[2][0]).normalized();
    const Vector3d TOD_y_GCRF = Vector3d(rbpn[0][1], rbpn[1][1], rbpn[2][1]).normalized();
    const Vector3d TOD_z_GCRF = Vector3d(rbpn[0][2], rbpn[1][2], rbpn[2][2]).normalized();

    const RotationMatrix dcm_TOD_GCRF =
        RotationMatrix::Columns(TOD_x_GCRF, TOD_y_GCRF, TOD_z_GCRF);  // Change variable name?

    const Vector3d x_TOD_GCRF = {0.0, 0.0, 0.0};
    const Vector3d v_TOD_GCRF = {0.0, 0.0, 0.0};

    const Quaternion q_TOD_GCRF = Quaternion::RotationMatrix(dcm_TOD_GCRF).normalize().rectify();
    const Vector3d w_TOD_GCRF_in_TOD = {0.0, 0.0, 0.0};

    return Transform::Passive(anInstant, x_TOD_GCRF, v_TOD_GCRF, q_TOD_GCRF, w_TOD_GCRF_in_TOD);
}

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
