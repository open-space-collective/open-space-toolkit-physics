/// Apache License 2.0

#include <sofa/sofa.h>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/ITRF.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DAS2R (4.848136811095359935899141e-6)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using IersManager = ostk::physics::coord::frame::provider::iers::Manager;
using ostk::physics::coord::frame::provider::iers::BulletinA;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ITRF::ITRF() {}

ITRF::~ITRF() {}

ITRF* ITRF::clone() const
{
    return new ITRF(*this);
}

bool ITRF::isDefined() const
{
    return true;
}

Transform ITRF::getTransformAt(const Instant& anInstant) const
{
    using ostk::math::obj::Vector2d;
    using ostk::math::geom::d3::trf::rot::RotationMatrix;

    using ostk::physics::time::Scale;
    using ostk::physics::time::DateTime;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("ITRF");
    }

    // Time (TT)

    static const Real djmjd0 = 2400000.5;
    const Real tt = anInstant.getDateTime(Scale::TT).getModifiedJulianDate();

    // The polar motion xp,yp can be obtained from IERS bulletins.  The
    // values are the coordinates (in radians) of the Celestial
    // Intermediate Pole with respect to the International Terrestrial
    // Reference System (see IERS Conventions 2003), measured along the
    // meridians 0 and 90 deg west respectively.  For many applications,
    // xp and yp can be set to zero.

    // Polar motion

    const Vector2d polarMotion = IersManager::Get().getPolarMotionAt(anInstant);  // [asec]

    const Real xp = polarMotion.x() * DAS2R;  // [rad]
    const Real yp = polarMotion.y() * DAS2R;  // [rad]

    // TIO locator s', in radians, which positions the Terrestrial Intermediate Origin on the equator.
    // It is obtained from polar motion observations by numerical integration, and so is in essence unpredictable.
    // However, it is dominated by a secular drift of about 47 microarcseconds per century, and so can be taken into
    // account by using s' = -47*t, where t is centuries since J2000.0.

    const Real sp = iauSp00(djmjd0, tt);

    // Polar motion matrix (TIRS -> ITRS, IERS 2003)
    // The matrix operates in the sense V(TRS) = rpom * V(CIP), meaning
    // that it is the final rotation when computing the pointing direction to a celestial source.

    double rpom[3][3];

    iauPom00(xp, yp, sp, rpom);

    const Vector3d TIRF_x_ITRF = Vector3d(rpom[0][0], rpom[1][0], rpom[2][0]).normalized();
    const Vector3d TIRF_y_ITRF = Vector3d(rpom[0][1], rpom[1][1], rpom[2][1]).normalized();
    const Vector3d TIRF_z_ITRF = Vector3d(rpom[0][2], rpom[1][2], rpom[2][2]).normalized();

    const RotationMatrix dcm_ITRF_TIRF = RotationMatrix::Columns(TIRF_x_ITRF, TIRF_y_ITRF, TIRF_z_ITRF);

    // Output

    const Vector3d x_ITRF_TIRF = {0.0, 0.0, 0.0};
    const Vector3d v_ITRF_TIRF = {0.0, 0.0, 0.0};

    const Quaternion q_ITRF_TIRF = Quaternion::RotationMatrix(dcm_ITRF_TIRF).rectify();
    // const Quaternion q_ITRF_TIRF = Quaternion::RotationMatrix(dcm_ITRF_TIRF).conjugate().rectify() ; // TBC ANGULAR
    // VELOCITY WORKS IF CONJUGATED
    const Vector3d w_ITRF_TIRF_in_ITRF = {0.0, 0.0, 0.0};

    return Transform::Passive(anInstant, x_ITRF_TIRF, v_ITRF_TIRF, q_ITRF_TIRF, w_ITRF_TIRF_in_ITRF);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
