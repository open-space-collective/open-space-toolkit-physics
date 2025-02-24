/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/GCRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/J2000.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>

#include <Global.test.hpp>

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::frame::provider::iau::Theory;
using ostk::physics::coordinate::frame::provider::J2000;
using ostk::physics::coordinate::frame::Transform;
using ostk::physics::environment::object::celestial::Earth;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_J2000, GetTransformAt)
{
    // IAU 2000A

    {
        const Instant instant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

        const Transform transform_J2000_GCRF = J2000(Theory::IAU_2000A).getTransformAt(instant);

        EXPECT_EQ(instant, transform_J2000_GCRF.getInstant());

        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_J2000_GCRF.getTranslation());
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_J2000_GCRF.getVelocity());
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_J2000_GCRF.getAngularVelocity());

        const Quaternion q_J2000_GCRF = transform_J2000_GCRF.getOrientation();

        EXPECT_TRUE(
            q_J2000_GCRF.toVector(Quaternion::Format::XYZS)
                .isNear({1.65302058455067e-08, -4.02810863199078e-08, -3.53913980551414e-08, 0.999999999999998}, 1e-12)
        );
    }

    {
        const Instant instant_1 = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);
        const Instant instant_2 = Instant::DateTime(DateTime(2022, 1, 1, 0, 0, 0), Scale::UTC);

        EXPECT_EQ(
            J2000(Theory::IAU_2000A).getTransformAt(instant_1).getOrientation(),
            J2000(Theory::IAU_2000A).getTransformAt(instant_2).getOrientation()
        );
    }

    // IAU 2006

    {
        const Instant instant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

        const Transform transform_J2000_GCRF = J2000(Theory::IAU_2006).getTransformAt(instant);

        EXPECT_EQ(instant, transform_J2000_GCRF.getInstant());

        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_J2000_GCRF.getTranslation());
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_J2000_GCRF.getVelocity());
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_J2000_GCRF.getAngularVelocity());

        const Quaternion q_J2000_GCRF = transform_J2000_GCRF.getOrientation();

        EXPECT_TRUE(
            q_J2000_GCRF.toVector(Quaternion::Format::XYZS)
                .isNear({1.65297172616264e-08, -4.02810704730832e-08, -3.53918441390231e-08, 0.999999999999998}, 1e-12)
        );
    }

    {
        const Instant instant_1 = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);
        const Instant instant_2 = Instant::DateTime(DateTime(2022, 1, 1, 0, 0, 0), Scale::UTC);

        EXPECT_EQ(
            J2000(Theory::IAU_2006).getTransformAt(instant_1).getOrientation(),
            J2000(Theory::IAU_2006).getTransformAt(instant_2).getOrientation()
        );
    }

    {
        // https://github.com/CS-SI/Orekit/blob/develop/src/test/java/org/orekit/frames/EME2000ProviderTest.java#L35

        const Instant instant = Instant::DateTime(DateTime(2004, 4, 6, 7, 51, 28, 386, 9), Scale::UTC);

        const Quaternion q_J2000_GCRF_IAU_2000A = J2000(Theory::IAU_2000A).getTransformAt(instant).getOrientation();
        const Quaternion q_J2000_GCRF_IAU_2006 = J2000(Theory::IAU_2006).getTransformAt(instant).getOrientation();

        // LEO

        EXPECT_TRUE(q_J2000_GCRF_IAU_2000A.rotateVector({5102508.9579, 6123011.4038, 6378136.9252})
                        .isNear({5102509.0383, 6123011.9758, 6378136.3118}, 1e-3));
        EXPECT_TRUE(q_J2000_GCRF_IAU_2006.rotateVector({5102508.9579, 6123011.4038, 6378136.9252})
                        .isNear({5102509.0383, 6123011.9758, 6378136.3118}, 1e-3));

        EXPECT_TRUE(q_J2000_GCRF_IAU_2000A.rotateVector({5102508.9579, 6123011.4012, 6378136.9277})
                        .isNear({5102509.0383, 6123011.9733, 6378136.3142}, 1e-3));
        EXPECT_TRUE(q_J2000_GCRF_IAU_2006.rotateVector({5102508.9579, 6123011.4012, 6378136.9277})
                        .isNear({5102509.0383, 6123011.9733, 6378136.3142}, 1e-3));

        // GEO

        EXPECT_TRUE(q_J2000_GCRF_IAU_2000A.rotateVector({-40588150.3617, -11462167.0397, 27143.1974})
                        .isNear({-40588149.5482, -11462169.9118, 27146.8462}, 1e-3));
        EXPECT_TRUE(q_J2000_GCRF_IAU_2006.rotateVector({-40588150.3617, -11462167.0397, 27143.1974})
                        .isNear({-40588149.5482, -11462169.9118, 27146.8462}, 1e-3));

        EXPECT_TRUE(q_J2000_GCRF_IAU_2000A.rotateVector({-40588150.3617, -11462167.0397, 27143.2125})
                        .isNear({-40588149.5481, -11462169.9118, 27146.8613}, 1e-3));
        EXPECT_TRUE(q_J2000_GCRF_IAU_2006.rotateVector({-40588150.3617, -11462167.0397, 27143.2125})
                        .isNear({-40588149.5481, -11462169.9118, 27146.8613}, 1e-3));
    }

    // Verify that the J2000 / GCRF frame difference doesn't introduce a positional delta on the surface greater
    // than 1.0 [m].

    {
        const Instant instant = Instant::DateTime(DateTime(2004, 4, 6, 7, 51, 28, 386, 9), Scale::UTC);

        EXPECT_GT(
            1.0,
            RotationVector::Quaternion(J2000(Theory::IAU_2000A).getTransformAt(instant).getOrientation())
                    .getAngle()
                    .inRadians() *
                EarthGravitationalModel::EGM2008.equatorialRadius_.inMeters()
        );
        EXPECT_GT(
            1.0,
            RotationVector::Quaternion(J2000(Theory::IAU_2006).getTransformAt(instant).getOrientation())
                    .getAngle()
                    .inRadians() *
                EarthGravitationalModel::EGM2008.equatorialRadius_.inMeters()
        );
    }
}
