/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/TIRF.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

#define DAYSEC (86400.0)

using IersManager = ostk::physics::coordinate::frame::provider::iers::Manager;

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

TIRF::TIRF() {}

TIRF::~TIRF() {}

TIRF* TIRF::clone() const
{
    return new TIRF(*this);
}

Transform TIRF::getTransformAt(const Instant& anInstant) const
{
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Scale;

    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    // http://www.iausofa.org/2018_0130_C/sofa/sofa_pn_c.pdf

    // Time (UTC)

    static const double djmjd0 = 2400000.5;
    const double utc = anInstant.getModifiedJulianDate(Scale::UTC);

    const double date = std::floor(utc);
    const double time = utc - date;

    // UT1 - UTC (s)

    const std::optional<double> dut1 = IersManager::Get().getUt1MinusUtcAt(anInstant);  // [s]

    if (!dut1.has_value())
    {
        throw ostk::core::error::RuntimeError("Cannot obtain UT1 - UTC at [{}].", anInstant.toString());
    }

    const double tut = time + *dut1 / DAYSEC;

    // Earth rotation angle, IAU 2000 [rad]

    const double era = iauEra00(djmjd0 + date, tut);

    // CIRS to TIRF matrix

    const double cosEra = std::cos(era);
    const double sinEra = std::sin(era);

    const RotationMatrix dcm_TIRF_CIRF =
        RotationMatrix::Rows({+cosEra, +sinEra, 0.0}, {-sinEra, +cosEra, 0.0}, {0.0, 0.0, 1.0});

    // Angular velocity

    // [TBI] Fail in strict mode if LOD is not available
    const double lod_ms = IersManager::Get().getLodAt(anInstant).value_or(0.0);  // [ms]

    const double w_TIRF_CIRF = (72921151.467064 - 0.843994809 * lod_ms) *
                               1e-12;  // [rad/s] https://www.iers.org/IERS/EN/Science/EarthRotation/UT1LOD.html

    // Output

    const Vector3d x_TIRF_CIRF = {0.0, 0.0, 0.0};
    const Vector3d v_TIRF_CIRF = {0.0, 0.0, 0.0};

    const Quaternion q_TIRF_CIRF = Quaternion::RotationMatrix(dcm_TIRF_CIRF).rectify();
    const Vector3d w_TIRF_CIRF_in_TIRF = Vector3d::Z() * w_TIRF_CIRF;

    return Transform::Passive(anInstant, x_TIRF_CIRF, v_TIRF_CIRF, q_TIRF_CIRF, w_TIRF_CIRF_in_TIRF);
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
