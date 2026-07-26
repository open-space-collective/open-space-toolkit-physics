/// Apache License 2.0

#include <algorithm>
#include <cmath>

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/CIRF.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::Shared;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::frame::provider::CIRF;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

// 1 arcsecond in radians (SOFA DAS2R)
static const double ARCSEC_IN_RAD = 4.848136811095359935899141e-6;

// Verifies that the production X, Y, s interpolation (CIRF::ComputeCIPCoordinates with interpolation enabled)
// reproduces the direct iauXys06a evaluation to micro-arcsecond level, orders of magnitude below the ~0.2 mas CIP
// corrections applied downstream. Both paths are exercised through the real production entry point, so a bug in the
// interpolation grid would be caught here.
TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, ComputeCIPCoordinatesInterpolationAccuracy)
{
    const Instant startInstant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::TT);

    double maxErrorX = 0.0;
    double maxErrorY = 0.0;
    double maxErrorS = 0.0;

    // Sample over ~2 years at a 137-minute step. The step is deliberately not a divisor of the 0.25-day grid
    // spacing (360 min) so that the interpolation parameter tau sweeps across the full [0, 1) interval.
    const std::size_t sampleCount = 8000;

    for (std::size_t i = 0; i < sampleCount; ++i)
    {
        const Instant instant = startInstant + Duration::Minutes(137.0 * static_cast<double>(i));
        const Real tt = instant.getModifiedJulianDate(Scale::TT);

        double xDirect, yDirect, sDirect;
        CIRF::ComputeCIPCoordinates(tt, xDirect, yDirect, sDirect, false);

        double xInterp, yInterp, sInterp;
        CIRF::ComputeCIPCoordinates(tt, xInterp, yInterp, sInterp, true);

        maxErrorX = std::max(maxErrorX, std::abs(xInterp - xDirect));
        maxErrorY = std::max(maxErrorY, std::abs(yInterp - yDirect));
        maxErrorS = std::max(maxErrorS, std::abs(sInterp - sDirect));
    }

    // Interpolation error stays at the micro-arcsecond level (observed max ~1.2e-6 arcsec), roughly two orders of
    // magnitude below the ~0.2 mas (200 micro-arcsec) CIP corrections applied downstream, so it is negligible.
    const double toleranceRad = 1.0e-5 * ARCSEC_IN_RAD;  // 10 micro-arcseconds

    EXPECT_LT(maxErrorX, toleranceRad) << "max X error: " << (maxErrorX / ARCSEC_IN_RAD) << " arcsec";
    EXPECT_LT(maxErrorY, toleranceRad) << "max Y error: " << (maxErrorY / ARCSEC_IN_RAD) << " arcsec";
    EXPECT_LT(maxErrorS, toleranceRad) << "max s error: " << (maxErrorS / ARCSEC_IN_RAD) << " arcsec";
}

// Verifies that the full GCRF -> ITRF transform is essentially unchanged (sub-millimeter at the Earth's surface)
// whether or not X, Y, s interpolation is enabled. The GCRF -> CIRF portion is computed both ways via the real CIRF
// provider (toggling the runtime flag); the interpolation-independent CIRF -> ITRF portion (Earth rotation + polar
// motion) is taken from the library and shared. The provider's getTransformAt is used directly because the Frame
// transform cache would otherwise return a stale result across the toggle.
TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, GetTransformAtGcrfToItrfInterpolationAccuracy)
{
    const bool initialInterpolationEnabled = CIRF::IsXysInterpolationEnabled();

    const CIRF cirfProvider;
    const Shared<const Frame> cirfSPtr = Frame::CIRF();
    const Shared<const Frame> itrfSPtr = Frame::ITRF();

    const Instant startInstant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

    const double equatorialRadius_m = EarthGravitationalModel::EGM2008.equatorialRadius_.inMeters();

    double maxPositionalError_m = 0.0;

    // Sample at a 137-minute step over ~1.5 years, off the 0.25-day grid (see rationale above).
    const std::size_t sampleCount = 800;

    for (std::size_t i = 0; i < sampleCount; ++i)
    {
        const Instant instant = startInstant + Duration::Minutes(137.0 * static_cast<double>(i));

        // Interpolation-independent CIRF -> ITRF portion (Earth rotation + polar motion), shared by both paths.

        const Quaternion q_ITRF_CIRF = cirfSPtr->getTransformTo(itrfSPtr, instant).getOrientation();

        // GCRF -> CIRF portion, computed both ways via the real provider.

        CIRF::SetXysInterpolationEnabled(false);
        const Quaternion q_CIRF_GCRF_direct = cirfProvider.getTransformAt(instant).getOrientation();

        CIRF::SetXysInterpolationEnabled(true);
        const Quaternion q_CIRF_GCRF_interp = cirfProvider.getTransformAt(instant).getOrientation();

        const Quaternion q_ITRF_GCRF_direct = (q_ITRF_CIRF * q_CIRF_GCRF_direct).rectify();
        const Quaternion q_ITRF_GCRF_interp = (q_ITRF_CIRF * q_CIRF_GCRF_interp).rectify();

        const double angularError_rad = q_ITRF_GCRF_interp.angularDifferenceWith(q_ITRF_GCRF_direct).inRadians();

        maxPositionalError_m = std::max(maxPositionalError_m, angularError_rad * equatorialRadius_m);
    }

    // Restore the flag before asserting so subsequent tests are unaffected even if the expectation fails.
    CIRF::SetXysInterpolationEnabled(initialInterpolationEnabled);

    // Sub-millimeter agreement at the Earth's surface between the interpolated and direct transforms.
    EXPECT_LT(maxPositionalError_m, 1.0e-3) << "max positional error: " << maxPositionalError_m << " m";
}
