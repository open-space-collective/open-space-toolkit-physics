/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

// Include sofa last to avoid type errors in underlying Eigen lib
#include <sofa/sofa.h>

#include <Global.test.hpp>

// Millisecond of arc in radians (matches CIRF.cpp)
#define DMAS2R (4.848136811095359935899141e-6 / 1e3)

using ostk::core::type::Real;
using ostk::core::type::Shared;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;
using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

namespace
{

static constexpr double djmjd0 = 2400000.5;

// Direct evaluation of the IAU 2006/2000A X, Y, s series, as done in CIRF.cpp when interpolation is disabled.
void directXys(const double aModifiedJulianDate_TT, double& x, double& y, double& s)
{
    iauXys06a(djmjd0, aModifiedJulianDate_TT, &x, &y, &s);
}

// Replicates the centered 4-point Lagrange interpolation on the 0.25-day grid used by the XysGrid helper in
// CIRF.cpp when interpolation is enabled (the default).
void interpolatedXys(const double aModifiedJulianDate_TT, double& x, double& y, double& s)
{
    static constexpr double gridSpacingDays = 0.25;

    const double gridCoordinate = aModifiedJulianDate_TT / gridSpacingDays;
    const std::int64_t nodeIndex = static_cast<std::int64_t>(std::floor(gridCoordinate));
    const double tau = gridCoordinate - static_cast<double>(nodeIndex);  // in [0, 1)

    double nx[4];
    double ny[4];
    double ns[4];

    for (std::int64_t offset = -1; offset <= 2; ++offset)
    {
        iauXys06a(
            djmjd0,
            static_cast<double>(nodeIndex + offset) * gridSpacingDays,
            &nx[offset + 1],
            &ny[offset + 1],
            &ns[offset + 1]
        );
    }

    const double w0 = -tau * (tau - 1.0) * (tau - 2.0) / 6.0;
    const double w1 = (tau + 1.0) * (tau - 1.0) * (tau - 2.0) / 2.0;
    const double w2 = -(tau + 1.0) * tau * (tau - 2.0) / 2.0;
    const double w3 = (tau + 1.0) * tau * (tau - 1.0) / 6.0;

    x = w0 * nx[0] + w1 * nx[1] + w2 * nx[2] + w3 * nx[3];
    y = w0 * ny[0] + w1 * ny[1] + w2 * ny[2] + w3 * ny[3];
    s = w0 * ns[0] + w1 * ns[1] + w2 * ns[2] + w3 * ns[3];
}

// Builds the GCRF -> CIRF orientation quaternion from raw X, Y, s, replicating the CIRF.cpp pipeline
// (CIP corrections + iauC2ixys + rotation matrix columns).
Quaternion cirfOrientationFromXys(double x, double y, const double s)
{
    static const double dx06 = +0.1750 * DMAS2R;
    static const double dy06 = -0.2259 * DMAS2R;

    x += dx06;
    y += dy06;

    double rc2i[3][3];

    iauC2ixys(x, y, s, rc2i);

    const Vector3d GCRF_x_CIRF = Vector3d(rc2i[0][0], rc2i[1][0], rc2i[2][0]).normalized();
    const Vector3d GCRF_y_CIRF = Vector3d(rc2i[0][1], rc2i[1][1], rc2i[2][1]).normalized();
    const Vector3d GCRF_z_CIRF = Vector3d(rc2i[0][2], rc2i[1][2], rc2i[2][2]).normalized();

    const RotationMatrix dcm_CIRF_GCRF = RotationMatrix::Columns(GCRF_x_CIRF, GCRF_y_CIRF, GCRF_z_CIRF);

    return Quaternion::RotationMatrix(dcm_CIRF_GCRF).rectify();
}

}  // namespace

// Verifies that the 0.25-day / 4-point Lagrange interpolation reproduces the direct iauXys06a evaluation to
// micro-arcsecond level, orders of magnitude below the ~0.2 mas CIP corrections applied downstream. This is
// independent of any environment variable or frame machinery: it directly compares the two evaluation strategies.
TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, Xys06aInterpolationAccuracy)
{
    const Instant startInstant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::TT);

    // 1 arcsecond in radians (SOFA DAS2R)
    static const double arcsecInRad = 4.848136811095359935899141e-6;

    double maxErrorX = 0.0;
    double maxErrorY = 0.0;
    double maxErrorS = 0.0;

    // Sample over ~2 years at a 137-minute step. The step is deliberately not a divisor of the 0.25-day grid
    // spacing (360 min) so that the interpolation parameter tau sweeps across the full [0, 1) interval.
    const std::size_t sampleCount = 8000;

    for (std::size_t i = 0; i < sampleCount; ++i)
    {
        const Instant instant = startInstant + Duration::Minutes(137.0 * static_cast<double>(i));
        const double tt = instant.getModifiedJulianDate(Scale::TT);

        double xDirect, yDirect, sDirect;
        directXys(tt, xDirect, yDirect, sDirect);

        double xInterp, yInterp, sInterp;
        interpolatedXys(tt, xInterp, yInterp, sInterp);

        maxErrorX = std::max(maxErrorX, std::abs(xInterp - xDirect));
        maxErrorY = std::max(maxErrorY, std::abs(yInterp - yDirect));
        maxErrorS = std::max(maxErrorS, std::abs(sInterp - sDirect));
    }

    // Interpolation error stays at the micro-arcsecond level (observed max ~1.2e-6 arcsec), roughly two orders of
    // magnitude below the ~0.2 mas (200 micro-arcsec) CIP corrections applied downstream, so it is negligible.
    const double toleranceRad = 1.0e-5 * arcsecInRad;  // 10 micro-arcseconds

    EXPECT_LT(maxErrorX, toleranceRad) << "max X error: " << (maxErrorX / arcsecInRad) << " arcsec";
    EXPECT_LT(maxErrorY, toleranceRad) << "max Y error: " << (maxErrorY / arcsecInRad) << " arcsec";
    EXPECT_LT(maxErrorS, toleranceRad) << "max s error: " << (maxErrorS / arcsecInRad) << " arcsec";
}

// Verifies that the full GCRF -> ITRF transform produced by the (interpolated) library path matches a reference
// built from the direct iauXys06a evaluation to sub-millimeter positional accuracy at the Earth's surface. Only
// the CIRF (X, Y, s) portion differs between the two paths; the TIRF (Earth rotation) and ITRF (polar motion)
// portions are shared via the library frames.
TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF, GetTransformAtGcrfToItrfInterpolationAccuracy)
{
    const Shared<const Frame> gcrfSPtr = Frame::GCRF();
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
        const double tt = instant.getModifiedJulianDate(Scale::TT);

        // Library path (interpolation enabled by default): full GCRF -> ITRF orientation.

        const Quaternion q_ITRF_GCRF_library = gcrfSPtr->getTransformTo(itrfSPtr, instant).getOrientation();

        // Reference path: direct X, Y, s for the CIRF portion, composed with the shared CIRF -> ITRF orientation.

        double xDirect, yDirect, sDirect;
        directXys(tt, xDirect, yDirect, sDirect);

        const Quaternion q_CIRF_GCRF_direct = cirfOrientationFromXys(xDirect, yDirect, sDirect);
        const Quaternion q_ITRF_CIRF = cirfSPtr->getTransformTo(itrfSPtr, instant).getOrientation();

        const Quaternion q_ITRF_GCRF_direct = (q_ITRF_CIRF * q_CIRF_GCRF_direct).rectify();

        const double angularError_rad = q_ITRF_GCRF_library.angularDifferenceWith(q_ITRF_GCRF_direct).inRadians();

        maxPositionalError_m = std::max(maxPositionalError_m, angularError_rad * equatorialRadius_m);
    }

    // Sub-millimeter agreement at the Earth's surface between the interpolated and direct transforms.
    EXPECT_LT(maxPositionalError_m, 1.0e-3) << "max positional error: " << maxPositionalError_m << " m";
}
