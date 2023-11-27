/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/J2000.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

#define DAS2R (4.848136811095359935899141e-6)

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

J2000::J2000(const iau::Theory& aTheory)
    : theory_(aTheory)
{
}

J2000::~J2000() {}

J2000* J2000::clone() const
{
    return new J2000(*this);
}

bool J2000::isDefined() const
{
    return true;
}

iau::Theory J2000::getTheory() const
{
    return this->theory_;
}

Transform J2000::getTransformAt(const Instant& anInstant) const
{
    using ostk::math::geometry::d3::transformation::rotation::RotationMatrix;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("J2000");
    }

    double rb[3][3];

    switch (this->theory_)
    {
        case iau::Theory::IAU_2000A:
        {
            const double EPS0 = 84381.448 * DAS2R;

            double dpsibi, depsbi, dra0, rbw[3][3];

            iauBi00(&dpsibi, &depsbi, &dra0);

            iauIr(rbw);
            iauRz(dra0, rbw);
            iauRy(dpsibi * sin(EPS0), rbw);
            iauRx(-depsbi, rbw);
            iauCr(rbw, rb);

            break;
        }

        case iau::Theory::IAU_2006:
        {
            double gamb, phib, psib, epsa;

            iauPfw06(DJM0, DJM00, &gamb, &phib, &psib, &epsa);
            iauFw2m(gamb, phib, psib, epsa, rb);

            break;
        }

        default:
            throw ostk::core::error::runtime::Wrong("Theory");
            break;
    }

    const Vector3d GCRF_x_J2000 = Vector3d(rb[0][0], rb[1][0], rb[2][0]).normalized();
    const Vector3d GCRF_y_J2000 = Vector3d(rb[0][1], rb[1][1], rb[2][1]).normalized();
    const Vector3d GCRF_z_J2000 = Vector3d(rb[0][2], rb[1][2], rb[2][2]).normalized();

    const RotationMatrix dcm_J2000_GCRF = RotationMatrix::Columns(GCRF_x_J2000, GCRF_y_J2000, GCRF_z_J2000);

    const Vector3d x_J2000_GCRF = {0.0, 0.0, 0.0};
    const Vector3d v_J2000_GCRF = {0.0, 0.0, 0.0};

    const Quaternion q_J2000_GCRF = Quaternion::RotationMatrix(dcm_J2000_GCRF).normalize().rectify();
    const Vector3d w_J2000_GCRF_in_J2000 = {0.0, 0.0, 0.0};

    return Transform::Passive(anInstant, x_J2000_GCRF, v_J2000_GCRF, q_J2000_GCRF, w_J2000_GCRF_in_J2000);
}

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
