/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

namespace iau = ostk::physics::coord::frame::providers::iau;

using ostk::core::types::Shared;
using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::ctnr::Tuple;
using ostk::core::ctnr::Array;
using ostk::core::ctnr::Table;
using ostk::core::fs::Path;
using ostk::core::fs::File;

using ostk::math::obj::Vector3d;
using ostk::math::geom::d3::trf::rot::Quaternion;
using ostk::math::geom::d3::trf::rot::RotationVector;
using ostk::math::geom::d3::trf::rot::RotationMatrix;

using ostk::physics::units::Length;
using ostk::physics::units::Angle;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coord::Transform;
using ostk::physics::coord::Frame;
using ostk::physics::env::obj::celest::Earth;

// This will test transformation translation, relative velocity, oreintation and
// angular velocity against 3rd party generated files. The files can be found in
// the folder 'Transforms', together with a README.md containing context.
TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_Transform, Validation)
{
    {
        const Array<Tuple<File, String, String, Real, Real, Real, Real>> referenceScenarios = {

            // GCRF <> TIRF (Orekit)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_TIRF_orekit.csv"
             )),
             "TIRF",
             "",
             0.0,    // Translation tolerance [m]
             0.0,    // Relative velocity tolerance [m/s]
             50.0,   // Orientation tolerance at Earth Surface [m]
             1e-6},  // Angular velocity tolerance [rad/s]

            // GCRF <> CIRF (Orekit)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_CIRF_orekit.csv"
             )),
             "CIRF",
             "",
             0.0,     // Translation tolerance [m]
             0.0,     // Relative velocity tolerance [m/s]
             1e-1,    // Orientation tolerance at Earth Surface [m]
             1e-11},  // Angular velocity tolerance [rad/s]

            // GCRF <> MOD (STK)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_MOD_stk.csv"
             )),
             "MOD",
             "",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             2.0,   // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> MOD (Orekit)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_MOD_orekit.csv"
             )),
             "MOD",
             "",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             3.0,   // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> J2000 IAU 2000A (STK)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_J2000_stk.csv"
             )),
             "J2000",
             "IAU 2000A",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             1.5,   // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> J2000 IAU 2000A (Orekit)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_J2000_orekit.csv"
             )),
             "J2000",
             "IAU 2000A",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             1e-5,  // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> J2000 IAU 2006 (STK)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_J2000_stk.csv"
             )),
             "J2000",
             "IAU 2006",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             1.5,   // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> J2000 IAU 2006 (Orekit)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_J2000_orekit.csv"
             )),
             "J2000",
             "IAU 2006",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             1e-4,  // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> TOD IAU 2000A (STK)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_TOD_stk.csv"
             )),
             "TOD",
             "IAU 2000A",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             3.0,   // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> TOD IAU 2000A (Orekit)
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                    "GCRF_TOD_orekit.csv")),
             "TOD",
             "IAU 2000A",
             0.0,     // Translation tolerance [m]
             0.0,     // Relative velocity tolerance [m/s]
             3.0,     // Orientation tolerance at Earth Surface [m]
             1e-10},  // Angular velocity tolerance [rad/s]

            // GCRF <> TOD IAU 2000B (STK)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_TOD_stk.csv"
             )),
             "TOD",
             "IAU 2000B",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             3.0,   // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> TOD IAU 2000B (Orekit)
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                    "GCRF_TOD_orekit.csv")),
             "TOD",
             "IAU 2000B",
             0.0,     // Translation tolerance [m]
             0.0,     // Relative velocity tolerance [m/s]
             3.0,     // Orientation tolerance at Earth Surface [m]
             1e-10},  // Angular velocity tolerance [rad/s]

            // GCRF <> TOD IAU 2006 (STK)
            {File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_TOD_stk.csv"
             )),
             "TOD",
             "IAU 2006",
             0.0,   // Translation tolerance [m]
             0.0,   // Relative velocity tolerance [m/s]
             3.0,   // Orientation tolerance at Earth Surface [m]
             0.0},  // Angular velocity tolerance [rad/s]

            // GCRF <> TOD IAU 2006 (Orekit)
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                    "GCRF_TOD_orekit.csv")),
             "TOD",
             "IAU 2006",
             0.0,     // Translation tolerance [m]
             0.0,     // Relative velocity tolerance [m/s]
             3.0,     // Orientation tolerance at Earth Surface [m]
             1e-10},  // Angular velocity tolerance [rad/s]

            // GCRF <> TEME (STK)
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                    "GCRF_TEME_stk.csv")),
             "TEME",
             "",
             0.0,     // Translation tolerance [m]
             0.0,     // Relative velocity tolerance [m/s]
             1.0,     // Orientation tolerance at Earth Surface [m]
             1e-11},  // Angular velocity tolerance [rad/s]

            // GCRF <> TEME (Orekit)
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                    "GCRF_TEME_orekit.csv")),
             "TEME",
             "",
             0.0,     // Translation tolerance [m]
             0.0,     // Relative velocity tolerance [m/s]
             2.0,     // Orientation tolerance at Earth Surface [m]
             1e-11},  // Angular velocity tolerance [rad/s]

            // GCRF <> ITRF (STK)
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                    "GCRF_ITRF_stk.csv")),
             "ITRF",
             "",
             0.0,    // Translation tolerance [m]
             0.0,    // Relative velocity tolerance [m/s]
             50.0,   // Orientation tolerance at Earth Surface [m]
             1e-6},  // Angular velocity tolerance [rad/s]

            // GCRF <> ITRF (Orekit)
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                    "GCRF_ITRF_orekit.csv")),
             "ITRF",
             "",
             0.0,    // Translation tolerance [m]
             0.0,    // Relative velocity tolerance [m/s]
             25.0,   // Orientation tolerance at Earth Surface [m]
             1e-6},  // Angular velocity tolerance [rad/s]
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario);
            const String frame2Str = std::get<1>(referenceScenario);
            const String otherStr = std::get<2>(referenceScenario);
            const Real translationTolerance = std::get<3>(referenceScenario);
            const Real velocityTolerance = std::get<4>(referenceScenario);
            const Real orientationToleranceAtEarthSurface = std::get<5>(referenceScenario);
            const Real angularVelocityTolerance = std::get<6>(referenceScenario);

            const double earthRadius = 6370000;
            const Vector3d earthSurfaceX = earthRadius * Vector3d::X();
            const Vector3d earthSurfaceY = earthRadius * Vector3d::Y();
            const Vector3d earthSurfaceZ = earthRadius * Vector3d::Z();

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Comparison test scenario
            const String scenario =
                String::Format("Frame: {} ({}) | File: {}\n", frame2Str, otherStr, referenceDataFile.toString());

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI);
                Shared<const Frame> frame1 = Frame::GCRF();
                Shared<const Frame> frame2 = Frame::GCRF();

                if (frame2Str == "TOD")
                {
                    frame2 = Frame::TOD(instant, iau::TheoryFromString(otherStr));
                }
                else if (frame2Str == "TEME")
                {
                    frame2 = Frame::TEME();
                }
                else if (frame2Str == "ITRF")
                {
                    frame2 = Frame::ITRF();
                }
                else if (frame2Str == "J2000")
                {
                    frame2 = Frame::J2000(iau::TheoryFromString(otherStr));
                }
                else if (frame2Str == "MOD")
                {
                    frame2 = Frame::MOD(instant);
                }
                else if (frame2Str == "CIRF")
                {
                    frame2 = Frame::CIRF();
                }
                else if (frame2Str == "TIRF")
                {
                    frame2 = Frame::TIRF();
                }

                const Transform transformToFrame1 = frame2->getTransformTo(frame1, instant);
                const Transform transformToFrame2 = frame1->getTransformTo(frame2, instant);

                // Instant

                {
                    EXPECT_EQ(instant, transformToFrame1.getInstant());
                    EXPECT_EQ(instant, transformToFrame2.getInstant());
                }

                // Translation

                {
                    const Vector3d referenceToFrame2 = {
                        referenceRow[1].accessReal(), referenceRow[2].accessReal(), referenceRow[3].accessReal()};
                    const Vector3d referenceToFrame1 = -1 * referenceToFrame2;

                    const Vector3d toFrame2 = transformToFrame2.getTranslation();
                    const Vector3d toFrame1 = transformToFrame1.getTranslation();

                    ASSERT_TRUE(referenceToFrame2.isNear(toFrame2, translationTolerance)) << String::Format(
                        "{} @ {} Translation: {} [m] vs. {} [m] above {} [m] tolerance",
                        scenario,
                        instant.toString(Scale::TAI),
                        referenceToFrame2.toString(),
                        toFrame2.toString(),
                        translationTolerance.toString()
                    );

                    ASSERT_TRUE(referenceToFrame1.isNear(toFrame1, translationTolerance)) << String::Format(
                        "{} @ {} Translation: {} [m] vs. {} [m] above {} [m] tolerance",
                        scenario,
                        instant.toString(Scale::TAI),
                        referenceToFrame1.toString(),
                        toFrame1.toString(),
                        translationTolerance.toString()
                    );
                }

                // Relative velocity

                {
                    const Vector3d referenceToFrame2 = {
                        referenceRow[4].accessReal(), referenceRow[5].accessReal(), referenceRow[6].accessReal()};
                    const Vector3d referenceToFrame1 = -1 * referenceToFrame2;

                    const Vector3d toFrame2 = transformToFrame2.getVelocity();
                    const Vector3d toFrame1 = transformToFrame1.getVelocity();

                    ASSERT_TRUE(referenceToFrame2.isNear(toFrame2, velocityTolerance)) << String::Format(
                        "{} @ {} Velocity: {} [m/s] vs. {} [m/s] above {} [m/s] tolerance",
                        scenario,
                        instant.toString(Scale::TAI),
                        referenceToFrame2.toString(),
                        toFrame2.toString(),
                        velocityTolerance.toString()
                    );

                    ASSERT_TRUE(referenceToFrame1.isNear(toFrame1, velocityTolerance)) << String::Format(
                        "{} @ {} Velocity: {} [m/s] vs. {} [m/s] above {} [m/s] tolerance",
                        scenario,
                        instant.toString(Scale::TAI),
                        referenceToFrame1.toString(),
                        toFrame1.toString(),
                        velocityTolerance.toString()
                    );
                }

                // Relative orientation

                {
                    const Quaternion referenceOrientationToFrame2 = Quaternion::XYZS(
                                                                        referenceRow[7].accessReal(),
                                                                        referenceRow[8].accessReal(),
                                                                        referenceRow[9].accessReal(),
                                                                        referenceRow[10].accessReal()
                    )
                                                                        .normalize();

                    // Orientation to Frame 2
                    const Vector3d referenceToFrame2X = referenceOrientationToFrame2 * earthSurfaceX;
                    const Vector3d toFrame2X = transformToFrame2.applyToVector(earthSurfaceX);
                    const Vector3d referenceToFrame2Y = referenceOrientationToFrame2 * earthSurfaceY;
                    const Vector3d toFrame2Y = transformToFrame2.applyToVector(earthSurfaceY);
                    const Vector3d referenceToFrame2Z = referenceOrientationToFrame2 * earthSurfaceZ;
                    const Vector3d toFrame2Z = transformToFrame2.applyToVector(earthSurfaceZ);

                    ASSERT_TRUE(referenceToFrame2X.isNear(toFrame2X, orientationToleranceAtEarthSurface))
                        << String::Format(
                               "{} @ {} Orientation at Earth Surface +X: {} [m] vs. {} [m] above {} [m] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame2X.toString(),
                               toFrame2X.toString(),
                               orientationToleranceAtEarthSurface.toString()
                           );

                    ASSERT_TRUE(referenceToFrame2Y.isNear(toFrame2Y, orientationToleranceAtEarthSurface))
                        << String::Format(
                               "{} @ {} Orientation at Earth Surface +Y: {} [m] vs. {} [m] above {} [m] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame2Y.toString(),
                               toFrame2Y.toString(),
                               orientationToleranceAtEarthSurface.toString()
                           );

                    ASSERT_TRUE(referenceToFrame2Z.isNear(toFrame2Z, orientationToleranceAtEarthSurface))
                        << String::Format(
                               "{} @ {} Orientation at Earth Surface +Z: {} [m] vs. {} [m] above {} [m] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame2Z.toString(),
                               toFrame2Z.toString(),
                               orientationToleranceAtEarthSurface.toString()
                           );

                    // Orientation to Frame 1
                    const Quaternion referenceOrientationToFrame1 = referenceOrientationToFrame2.toConjugate();

                    const Vector3d referenceToFrame1X = referenceOrientationToFrame1 * earthSurfaceX;
                    const Vector3d toFrame1X = transformToFrame1.applyToVector(earthSurfaceX);
                    const Vector3d referenceToFrame1Y = referenceOrientationToFrame1 * earthSurfaceY;
                    const Vector3d toFrame1Y = transformToFrame1.applyToVector(earthSurfaceY);
                    const Vector3d referenceToFrame1Z = referenceOrientationToFrame1 * earthSurfaceZ;
                    const Vector3d toFrame1Z = transformToFrame1.applyToVector(earthSurfaceZ);

                    ASSERT_TRUE(referenceToFrame1X.isNear(toFrame1X, orientationToleranceAtEarthSurface))
                        << String::Format(
                               "{} @ {} Orientation at Earth Surface +X: {} [m] vs. {} [m] above {} [m] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame1X.toString(),
                               toFrame1X.toString(),
                               orientationToleranceAtEarthSurface.toString()
                           );

                    ASSERT_TRUE(referenceToFrame1Y.isNear(toFrame1Y, orientationToleranceAtEarthSurface))
                        << String::Format(
                               "{} @ {} Orientation at Earth Surface +Y: {} [m] vs. {} [m] above {} [m] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame1Y.toString(),
                               toFrame1Y.toString(),
                               orientationToleranceAtEarthSurface.toString()
                           );

                    ASSERT_TRUE(referenceToFrame1Z.isNear(toFrame1Z, orientationToleranceAtEarthSurface))
                        << String::Format(
                               "{} @ {} Orientation at Earth Surface +Z: {} [m] vs. {} [m] above {} [m] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame1Z.toString(),
                               toFrame1Z.toString(),
                               orientationToleranceAtEarthSurface.toString()
                           );
                }

                // Relative angular velocity

                {
                    const Vector3d referenceToFrame2 = {
                        referenceRow[11].accessReal(), referenceRow[12].accessReal(), referenceRow[13].accessReal()};
                    const Vector3d referenceToFrame1 = -1 * referenceToFrame2;

                    const Vector3d toFrame2 = transformToFrame2.getAngularVelocity();
                    const Vector3d toFrame1 = transformToFrame1.getAngularVelocity();

                    ASSERT_TRUE(referenceToFrame2.isNear(toFrame2, angularVelocityTolerance)) << String::Format(
                        "{} @ {} Angular Velocity: {} [rad/s] vs. {} [rad/s] above {} [rad/s] tolerance",
                        scenario,
                        instant.toString(Scale::TAI),
                        referenceToFrame2.toString(),
                        toFrame2.toString(),
                        angularVelocityTolerance.toString()
                    );

                    ASSERT_TRUE(referenceToFrame1.isNear(toFrame1, angularVelocityTolerance)) << String::Format(
                        "{} @ {} Angular Velocity: {} [rad/s] vs. {} [rad/s] above {} [rad/s] tolerance",
                        scenario,
                        instant.toString(Scale::TAI),
                        referenceToFrame1.toString(),
                        toFrame1.toString(),
                        angularVelocityTolerance.toString()
                    );
                }
            }
        }
    }
}
