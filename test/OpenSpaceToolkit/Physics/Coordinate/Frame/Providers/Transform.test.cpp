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

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_Transform, Test)
{
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

    {
        const Array<Tuple<File, Shared<const Frame>, Shared<const Frame>, Real, Real, Real, Real, Real>>
            referenceScenarios = {

                // GCRF <> J2000

                {File::Path(Path::Parse(
                     "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_J2000_orekit.csv"
                 )),
                 Frame::GCRF(),
                 Frame::J2000(iau::Theory::IAU_2006),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-3,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 0.0},  // Angular velocity tolerance [rad/s]

                // GCRF <> ITRF

                {File::Path(Path::Parse(
                     "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_ITRF_IERS_2010_orekit.csv"
                 )),
                 Frame::GCRF(),
                 Frame::ITRF(),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-3,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 1e-6},  // Angular velocity tolerance [rad/s]


                // GCRF <> TEME

                {File::Path(Path::Parse(
                     "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/GCRF_TEME_orekit.csv"
                 )),
                 Frame::GCRF(),
                 Frame::TEME(),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-3,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 1e-6},  // Angular velocity tolerance [rad/s]

                // GCRF <> TOD IAU_2000A @2020-01-01T00:00:00.000 TAI

                {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                        "GCRF_TOD_IERS_2010@2020-01-01T00:00:00.000TAI_orekit.csv")),
                 Frame::GCRF(),
                 Frame::TOD(Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::TAI), iau::Theory::IAU_2000A),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-6,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 0.0},  // Angular velocity tolerance [rad/s]

                // GCRF <> TOD IAU_2000B @2020-01-01T00:00:00.000 TAI

                {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                        "GCRF_TOD_IERS_2010@2020-01-01T00:00:00.000TAI_orekit.csv")),
                 Frame::GCRF(),
                 Frame::TOD(Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::TAI), iau::Theory::IAU_2000B),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-6,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 0.0},  // Angular velocity tolerance [rad/s]

                // GCRF <> TOD IAU_2006 @2020-01-01T00:00:00.000 TAI

                {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                        "GCRF_TOD_IERS_2010@2020-01-01T00:00:00.000TAI_orekit.csv")),
                 Frame::GCRF(),
                 Frame::TOD(Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::TAI), iau::Theory::IAU_2006),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-6,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 0.0},  // Angular velocity tolerance [rad/s]

                // GCRF <> TOD IAU_2000A @2030-01-01T00:00:00.000 TAI

                {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                        "GCRF_TOD_IERS_2010@2030-01-01T00:00:00.000TAI_orekit.csv")),
                 Frame::GCRF(),
                 Frame::TOD(Instant::DateTime(DateTime(2030, 1, 1, 0, 0, 0), Scale::TAI), iau::Theory::IAU_2000A),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-6,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 0.0},  // Angular velocity tolerance [rad/s]

                // GCRF <> TOD IAU_2000B @2030-01-01T00:00:00.000 TAI

                {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                        "GCRF_TOD_IERS_2010@2030-01-01T00:00:00.000TAI_orekit.csv")),
                 Frame::GCRF(),
                 Frame::TOD(Instant::DateTime(DateTime(2030, 1, 1, 0, 0, 0), Scale::TAI), iau::Theory::IAU_2000B),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-6,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 0.0},  // Angular velocity tolerance [rad/s]

                // GCRF <> TOD IAU_2006 @2030-01-01T00:00:00.000 TAI

                {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Transforms/"
                                        "GCRF_TOD_IERS_2010@2030-01-01T00:00:00.000TAI_orekit.csv")),
                 Frame::GCRF(),
                 Frame::TOD(Instant::DateTime(DateTime(2030, 1, 1, 0, 0, 0), Scale::TAI), iau::Theory::IAU_2006),
                 0.0,   // Position tolerance [m]
                 0.0,   // Velocity tolerance [m/s]
                 1e-6,  // Orientation axis tolerance []
                 1e-6,  // Orientation angle tolerance [rad]
                 0.0},  // Angular velocity tolerance [rad/s]
            };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario);
            const Shared<const Frame> frame1SPtr = std::get<1>(referenceScenario);
            const Shared<const Frame> frame2SPtr = std::get<2>(referenceScenario);
            const Real translationTolerance = std::get<3>(referenceScenario);
            const Real velocityTolerance = std::get<4>(referenceScenario);
            const Real orientationAxisTolerance = std::get<5>(referenceScenario);
            const Real orientationAngleTolerance = std::get<6>(referenceScenario);
            const Real angularVelocityTolerance = std::get<7>(referenceScenario);

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Test
            const String scenario =
                String::Format("Frame 1: {} - Frame 2: {}", frame1SPtr->getName(), frame2SPtr->getName());

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI);

                const Transform transformToFrame1 = frame2SPtr->getTransformTo(frame1SPtr, instant);
                const Transform transformToFrame2 = frame1SPtr->getTransformTo(frame2SPtr, instant);

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

                // Velocity

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

                // Orientation

                {
                    const Quaternion referenceQuaterion = Quaternion::XYZS(
                                                              referenceRow[7].accessReal(),
                                                              referenceRow[8].accessReal(),
                                                              referenceRow[9].accessReal(),
                                                              referenceRow[10].accessReal()
                    )
                                                              .normalize();

                    const RotationVector referenceToFrame2 = RotationVector::Quaternion(referenceQuaterion);
                    const RotationVector referenceToFrame1 =
                        RotationVector::Quaternion(referenceQuaterion.toConjugate());\

                    const RotationVector toFrame2 = RotationVector::Quaternion(transformToFrame2.getOrientation());
                    const RotationVector toFrame1 = RotationVector::Quaternion(transformToFrame1.getOrientation());


                    // Angle

                    ASSERT_GT(
                        orientationAngleTolerance,
                        std::abs((referenceToFrame2.getAngle() - toFrame2.getAngle()).inRadians())
                    )
                        << String::Format(
                               "{} @ {} Rotation Angle: {} [rad] vs. {} [rad] above {} [rad] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame2.getAngle().inRadians().toString(),
                               toFrame2.getAngle().inRadians().toString(),
                               orientationAngleTolerance.toString()
                           );

                    ASSERT_GT(
                        orientationAngleTolerance,
                        std::abs((referenceToFrame1.getAngle() - toFrame1.getAngle()).inRadians())
                    )
                        << String::Format(
                               "{} @ {} Rotation Angle: {} [rad] vs. {} [rad] above {} [rad] tolerance",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame1.getAngle().inRadians().toString(),
                               toFrame1.getAngle().inRadians().toString(),
                               orientationAngleTolerance.toString()
                           );

                    // Axis

                    ASSERT_TRUE(referenceToFrame2.getAxis().isNear(toFrame2.getAxis(), orientationAxisTolerance))
                        << String::Format(
                               "{} @ {} Rotation Axis: {} [] vs. {} [] above {} [] tolerance | Rotation Angle: {} [rad] vs {} [rad]",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame2.getAxis().toString(),
                               toFrame2.getAxis().toString(),
                               orientationAxisTolerance.toString(),
                               referenceToFrame2.getAngle().inRadians(),
                               toFrame2.getAngle().inRadians()
                           );

                    ASSERT_TRUE(referenceToFrame1.getAxis().isNear(toFrame1.getAxis(), orientationAxisTolerance))
                        << String::Format(
                               "{} @ {} Rotation Axis: {} [] vs. {} [] above {} [] tolerance | Rotation Angle: {} [rad] vs {} [rad]",
                               scenario,
                               instant.toString(Scale::TAI),
                               referenceToFrame1.getAxis().toString(),
                               toFrame1.getAxis().toString(),
                               orientationAxisTolerance.toString(),
                               referenceToFrame1.getAngle().inRadians(),
                               toFrame1.getAngle().inRadians()
                           );
                }

                // Angular velocity

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
