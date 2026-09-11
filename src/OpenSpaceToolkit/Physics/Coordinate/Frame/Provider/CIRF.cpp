/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/CIRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

#define DAS2R (4.848136811095359935899141e-6)
#define DMAS2R (DAS2R / 1e3)

namespace
{

using ostk::mathematics::object::Vector2d;

using ostk::physics::time::Instant;
using IersManager = ostk::physics::coordinate::frame::provider::iers::Manager;

/// Observed celestial pole offsets (dX, dY) [mas] at the given instant: the IERS corrections to the IAU 2006/2000A
/// precession-nutation model (mostly the Free Core Nutation, which the model does not predict). Zero when the IERS
/// data does not provide them (no data available, instant outside the data span, or offsets not filled in for that
/// date): the model is then used as is.
Vector2d celestialPoleOffsetsAt(const Instant& anInstant)
{
    try
    {
        const Vector2d celestialPoleOffsets_mas = IersManager::Get().getCelestialPoleOffsetsAt(anInstant);

        if (celestialPoleOffsets_mas.isDefined())
        {
            return celestialPoleOffsets_mas;
        }
    }
    catch (const ostk::core::error::RuntimeError&)
    {
        // No IERS data covering the instant
    }

    return Vector2d(0.0, 0.0);
}

}  // namespace

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{

CIRF::CIRF() {}

CIRF::~CIRF() {}

CIRF* CIRF::clone() const
{
    return new CIRF(*this);
}

bool CIRF::isDefined() const
{
    return true;
}

Transform CIRF::getTransformAt(const Instant& anInstant) const
{
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("CIRF");
    }

    // http://www.iausofa.org/2018_0130_C/sofa/sofa_pn_c.pdf

    // Time (TT)

    static const Real djmjd0 = 2400000.5;
    const Real tt = anInstant.getModifiedJulianDate(Scale::TT);

    // CIP and CIO, IAU 2006/2000A

    double x;
    double y;
    double s;

    iauXys06a(djmjd0, tt, &x, &y, &s);

    // Celestial pole offsets wrt IAU 2006/2000A: observed dX, dY from the IERS (mas -> radians)

    const Vector2d celestialPoleOffsets_mas = celestialPoleOffsetsAt(anInstant);

    const double dx = celestialPoleOffsets_mas.x() * DMAS2R;
    const double dy = celestialPoleOffsets_mas.y() * DMAS2R;

    // Add CIP corrections. The CIO locator series actually provides s + XY / 2 (IERS Conventions 2010, Section
    // 5.5.6), so s is re-derived from the corrected X, Y to keep it consistent (a ~1e-12 rad effect).

    const double sPlusHalfXY = s + 0.5 * x * y;

    x += dx;
    y += dy;

    s = sPlusHalfXY - 0.5 * x * y;

    // GCRS to CIRS matrix

    double rc2i[3][3];  // dcm_CIRS_GCRS

    iauC2ixys(x, y, s, rc2i);

    const Vector3d GCRF_x_CIRF = Vector3d(rc2i[0][0], rc2i[1][0], rc2i[2][0]).normalized();
    const Vector3d GCRF_y_CIRF = Vector3d(rc2i[0][1], rc2i[1][1], rc2i[2][1]).normalized();
    const Vector3d GCRF_z_CIRF = Vector3d(rc2i[0][2], rc2i[1][2], rc2i[2][2]).normalized();

    const RotationMatrix dcm_CIRF_GCRF = RotationMatrix::Columns(GCRF_x_CIRF, GCRF_y_CIRF, GCRF_z_CIRF);

    // Output

    const Vector3d x_CIRF_GCRF = {0.0, 0.0, 0.0};
    const Vector3d v_CIRF_GCRF = {0.0, 0.0, 0.0};

    const Quaternion q_CIRF_GCRF = Quaternion::RotationMatrix(dcm_CIRF_GCRF).rectify();
    const Vector3d w_CIRF_GCRF_in_CIRF = {0.0, 0.0, 0.0};

    return Transform::Passive(anInstant, x_CIRF_GCRF, v_CIRF_GCRF, q_CIRF_GCRF, w_CIRF_GCRF_in_CIRF);
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
