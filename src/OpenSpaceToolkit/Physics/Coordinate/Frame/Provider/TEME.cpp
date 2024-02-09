/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/TEME.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

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

#define DAYSEC (86400.0)
#define DJC (36525.0)
#define DAS2R (4.848136811095359935899141e-6)
#define DS2R (7.272205216643039903848712e-5)

using IersManager = ostk::physics::coordinate::frame::provider::iers::Manager;

TEME::TEME() {}

TEME::~TEME() {}

TEME* TEME::clone() const
{
    return new TEME(*this);
}

bool TEME::isDefined() const
{
    return true;
}

Transform TEME::getTransformAt(const Instant& anInstant) const
{
    // https://geodesy.geology.ohio-state.edu/course/refpapers/AIAA4025.pdf
    // https://celestrak.com/publications/AIAA/2006-6753/faq.php
    // http://www.dtic.mil/dtic/tr/fulltext/u2/a637370.pdf p.18

    using ostk::mathematics::object::Vector2d;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    using ostk::physics::time::Scale;
    using ostk::physics::time::DateTime;
    using ostk::physics::unit::Angle;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("TEME");
    }

    // Time (UTC)

    static const Real djmjd0 = 2400000.5;
    const Real utc = anInstant.getDateTime(Scale::UTC).getModifiedJulianDate();

    const Real date = std::floor(utc);
    const Real time = utc - date;

    // UT1 - UTC (s)

    const Real dut1 = IersManager::Get().getUt1MinusUtcAt(anInstant);  // [s]
    const Real tut = time + dut1 / DAYSEC;

    // UT1 as a 2-part Julian Date

    const Real uta = djmjd0 + date;
    const Real utb = tut;

    // Julian centuries since fundamental epoch

    static const Real dj00 = 2451545.0;
    const Real t = (uta + (utb - dj00)) / DJC;

    // Greenwich apparent sidereal time (consistent with IAU 1982/94 resolutions)

    static const Real a = 24110.54841 - DAYSEC / 2.0;
    static const Real b = 8640184.812866;
    static const Real c = 0.093104;
    static const Real d = -6.2e-6;

    const Real f = DAYSEC * (fmod(uta, 1.0) + fmod(utb, 1.0));

    const Real gmst_1982 = ((a + (b * t) + (c * t * t) + (d * t * t * t)) + f) * DS2R;
    const Real dgmst_1982 = ((b + (2.0 * c * t) + (3.0 * d * t * t)) / (DAYSEC * DJC) + 1.0) * DS2R;

    const RotationMatrix R_3 = RotationMatrix::RZ(Angle::Radians(gmst_1982));  // dcm_PEF_TEME

    // Polar motion matrix using the IAU 1980 model

    const Vector2d polarMotion = IersManager::Get().getPolarMotionAt(anInstant);  // [asec]

    const Real xp = polarMotion.x() * DAS2R;  // [rad]
    const Real yp = polarMotion.y() * DAS2R;  // [rad]

    const Real cos_xp = std::cos(xp);
    const Real sin_xp = std::sin(xp);

    const Real cos_yp = std::cos(yp);
    const Real sin_yp = std::sin(yp);

    const RotationMatrix W_1980 = RotationMatrix::Rows(
        {+cos_xp, +sin_xp * sin_yp, +sin_xp * cos_yp},
        {0.0, +cos_yp, -sin_yp},
        {-sin_xp, +cos_xp * sin_yp, +cos_xp * cos_yp}
    );  // dcm_ITRF_PEF

    const RotationMatrix dcm_ITRF_TEME = W_1980 * R_3;

    // Output

    const Vector3d x_TEME_ITRF = {0.0, 0.0, 0.0};
    const Vector3d v_TEME_ITRF = {0.0, 0.0, 0.0};

    const Quaternion q_TEME_ITRF = Quaternion::RotationMatrix(dcm_ITRF_TEME).conjugate().rectify();
    const Vector3d w_TEME_ITRF_in_TEME = {0.0, 0.0, -dgmst_1982};

    return Transform::Passive(anInstant, x_TEME_ITRF, v_TEME_ITRF, q_TEME_ITRF, w_TEME_ITRF_in_TEME);
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
