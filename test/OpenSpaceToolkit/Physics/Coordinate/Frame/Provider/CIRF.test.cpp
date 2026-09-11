/// Apache License 2.0

#include <algorithm>
#include <cmath>
#include <thread>
#include <vector>

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

namespace ostk::physics::coordinate::frame::provider
{

/// Test-only access to CIRF::ComputeCIPCoordinates, which is private in production (declared friend in CIRF.hpp).
class CIRFTestAccessor
{
   public:
    static void ComputeCIPCoordinates(
        const Real& aModifiedJulianDate_TT, double& x, double& y, double& s, const bool interpolate
    )
    {
        CIRF::ComputeCIPCoordinates(aModifiedJulianDate_TT, x, y, s, interpolate);
    }
};

}  // namespace ostk::physics::coordinate::frame::provider

using ostk::physics::coordinate::frame::provider::CIRFTestAccessor;

// 1 arcsecond in radians (SOFA DAS2R)
static const double ARCSEC_IN_RAD = 4.848136811095359935899141e-6;

// Verifies that the production X, Y, s interpolation (CIRF::ComputeCIPCoordinates with interpolation enabled)
// reproduces the direct iauXys06a evaluation to the double-precision floor, orders of magnitude below both the ~0.2 mas
// CIP corrections applied downstream and the accuracy of the IAU 2006/2000A model itself. Both paths go through the
// same private entry point that CIRF::getTransformAt uses, so a bug in the interpolation grid would be caught here.
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
        CIRFTestAccessor::ComputeCIPCoordinates(tt, xDirect, yDirect, sDirect, false);

        double xInterp, yInterp, sInterp;
        CIRFTestAccessor::ComputeCIPCoordinates(tt, xInterp, yInterp, sInterp, true);

        maxErrorX = std::max(maxErrorX, std::abs(xInterp - xDirect));
        maxErrorY = std::max(maxErrorY, std::abs(yInterp - yDirect));
        maxErrorS = std::max(maxErrorS, std::abs(sInterp - sDirect));
    }

    // With the centered 8-point Lagrange polynomial on the 0.25-day grid, the interpolation error sits at the
    // double-precision floor (observed max ~1.2e-10 arcsec, i.e. ~1e-4 micro-arcsec, over 1980-2060). The tolerance
    // leaves roughly an order of magnitude of margin for platform rounding differences (e.g. FMA contraction) while
    // still catching a regression to a lower-order polynomial (4-point: ~1e-6 arcsec).
    const double toleranceRad = 1.0e-9 * ARCSEC_IN_RAD;  // 1e-3 micro-arcseconds

    EXPECT_LT(maxErrorX, toleranceRad) << "max X error: " << (maxErrorX / ARCSEC_IN_RAD) << " arcsec";
    EXPECT_LT(maxErrorY, toleranceRad) << "max Y error: " << (maxErrorY / ARCSEC_IN_RAD) << " arcsec";
    EXPECT_LT(maxErrorS, toleranceRad) << "max s error: " << (maxErrorS / ARCSEC_IN_RAD) << " arcsec";
}

// Verifies that interpolated evaluations can run concurrently from several threads, and that the result depends
// neither on the evaluation order nor on which thread populated the shared node cache: grid nodes sit at fixed absolute
// epochs and are deterministic functions of the series, so a concurrent evaluation starting from an empty cache must
// match a single-threaded one, and both must match the direct evaluation.
TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, ComputeCIPCoordinatesInterpolationThreadSafety)
{
    const std::size_t threadCount = 8;
    const std::size_t sampleCount = 400;

    const Instant startInstant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::TT);

    // Each thread walks ~20 days at a 73-minute step (not a divisor of the 0.25-day grid spacing). Thread spans start
    // 15 days apart, so threads populate distinct parts of the shared cache concurrently and also race on the nodes of
    // the ~5 days they share with their neighbor.
    const auto modifiedJulianDateAt =
        [&startInstant](const std::size_t aThreadIndex, const std::size_t aSampleIndex) -> Real
    {
        return (startInstant + Duration::Days(15.0 * static_cast<double>(aThreadIndex)) +
                Duration::Minutes(73.0 * static_cast<double>(aSampleIndex)))
            .getModifiedJulianDate(Scale::TT);
    };

    struct Coordinates
    {
        double x;
        double y;
        double s;
    };

    // Concurrent interpolated evaluation, starting from an empty shared cache

    CIRF::ClearXysCache();

    std::vector<std::vector<Coordinates>> concurrentResults(threadCount, std::vector<Coordinates>(sampleCount));

    {
        std::vector<std::thread> threads;

        for (std::size_t threadIndex = 0; threadIndex < threadCount; ++threadIndex)
        {
            threads.emplace_back(
                [&modifiedJulianDateAt, &concurrentResults, threadIndex, sampleCount]()
                {
                    for (std::size_t sampleIndex = 0; sampleIndex < sampleCount; ++sampleIndex)
                    {
                        Coordinates& coordinates = concurrentResults[threadIndex][sampleIndex];

                        CIRFTestAccessor::ComputeCIPCoordinates(
                            modifiedJulianDateAt(threadIndex, sampleIndex),
                            coordinates.x,
                            coordinates.y,
                            coordinates.s,
                            true
                        );
                    }
                }
            );
        }

        for (std::thread& thread : threads)
        {
            thread.join();
        }
    }

    // Compare against a single-threaded interpolated evaluation and against the direct evaluation

    const double toleranceRad = 1.0e-9 * ARCSEC_IN_RAD;  // 1e-3 micro-arcseconds, as in the accuracy test

    for (std::size_t threadIndex = 0; threadIndex < threadCount; ++threadIndex)
    {
        for (std::size_t sampleIndex = 0; sampleIndex < sampleCount; ++sampleIndex)
        {
            const Real tt = modifiedJulianDateAt(threadIndex, sampleIndex);
            const Coordinates& concurrent = concurrentResults[threadIndex][sampleIndex];

            double xInterp, yInterp, sInterp;
            CIRFTestAccessor::ComputeCIPCoordinates(tt, xInterp, yInterp, sInterp, true);

            EXPECT_DOUBLE_EQ(concurrent.x, xInterp) << "thread " << threadIndex << ", sample " << sampleIndex;
            EXPECT_DOUBLE_EQ(concurrent.y, yInterp) << "thread " << threadIndex << ", sample " << sampleIndex;
            EXPECT_DOUBLE_EQ(concurrent.s, sInterp) << "thread " << threadIndex << ", sample " << sampleIndex;

            double xDirect, yDirect, sDirect;
            CIRFTestAccessor::ComputeCIPCoordinates(tt, xDirect, yDirect, sDirect, false);

            EXPECT_NEAR(concurrent.x, xDirect, toleranceRad) << "thread " << threadIndex << ", sample " << sampleIndex;
            EXPECT_NEAR(concurrent.y, yDirect, toleranceRad) << "thread " << threadIndex << ", sample " << sampleIndex;
            EXPECT_NEAR(concurrent.s, sDirect, toleranceRad) << "thread " << threadIndex << ", sample " << sampleIndex;
        }
    }
}

// Verifies that clearing the cached X, Y, s interpolation grid is transparent: the interpolated output for a given
// instant is unchanged (the grid nodes are recomputed deterministically from the same series), and that clearing an
// already-empty cache is a no-op.
TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, ClearXysCache)
{
    const Instant instant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::TT);
    const Real tt = instant.getModifiedJulianDate(Scale::TT);

    double xBefore, yBefore, sBefore;
    CIRFTestAccessor::ComputeCIPCoordinates(tt, xBefore, yBefore, sBefore, true);

    EXPECT_NO_THROW(CIRF::ClearXysCache());

    double xAfter, yAfter, sAfter;
    CIRFTestAccessor::ComputeCIPCoordinates(tt, xAfter, yAfter, sAfter, true);

    EXPECT_DOUBLE_EQ(xBefore, xAfter);
    EXPECT_DOUBLE_EQ(yBefore, yAfter);
    EXPECT_DOUBLE_EQ(sBefore, sAfter);

    // Clearing an empty cache, repeatedly, is harmless.

    CIRF::ClearXysCache();

    EXPECT_NO_THROW(CIRF::ClearXysCache());
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
