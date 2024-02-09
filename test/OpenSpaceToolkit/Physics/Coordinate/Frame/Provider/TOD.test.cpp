/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Triple.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/GCRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/TOD.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::container::Triple;
using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::filesystem::Path;
using ostk::core::filesystem::File;

using ostk::mathematics::object::Vector3d;
using ostk::mathematics::object::Vector4d;
using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

using ostk::physics::unit::Angle;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::frame::Transform;
using ostk::physics::coordinate::frame::provider::TOD;
using ostk::physics::coordinate::frame::provider::iau::Theory;
using ostk::physics::environment::object::celestial::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TOD, GetTransformAt)
{
    {
        const Instant instant = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

        const Transform transform_TOD_GCRF = TOD(instant, Theory::IAU_2000A).getTransformAt(instant);

        EXPECT_EQ(instant, transform_TOD_GCRF.getInstant());

        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_TOD_GCRF.getTranslation());
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_TOD_GCRF.getVelocity());
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), transform_TOD_GCRF.getAngularVelocity());
    }

    {
        const Instant instant = Instant::DateTime(DateTime(2023, 1, 1, 0, 0, 0), Scale::UTC);

        const Quaternion ref_q_J2000_TOD =
            Quaternion::XYZS(1.58621719623e-05, -1.10716940847e-03, 2.54801869031e-03, 9.99996140755e-01)
                .toNormalized();

        const Quaternion q_J2000_TOD_IAU_2000 = Frame::TOD(instant, Theory::IAU_2000B)
                                                    ->getTransformTo(Frame::J2000(Theory::IAU_2000A), instant)
                                                    .getOrientation();
        const Quaternion q_J2000_TOD_IAU_2006 = Frame::TOD(instant, Theory::IAU_2006)
                                                    ->getTransformTo(Frame::J2000(Theory::IAU_2006), instant)
                                                    .getOrientation();

        EXPECT_GT(
            1.0,
            q_J2000_TOD_IAU_2000.angularDifferenceWith(ref_q_J2000_TOD).inRadians() *
                EarthGravitationalModel::EGM2008.equatorialRadius_.inMeters()
        );
        EXPECT_GT(
            1.0,
            q_J2000_TOD_IAU_2006.angularDifferenceWith(ref_q_J2000_TOD).inRadians() *
                EarthGravitationalModel::EGM2008.equatorialRadius_.inMeters()
        );
    }
}
