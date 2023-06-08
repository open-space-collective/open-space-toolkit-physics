/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/GCRF.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/TOD.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::types::Real;
using ostk::core::ctnr::Triple;
using ostk::core::ctnr::Array;
using ostk::core::ctnr::Table;
using ostk::core::fs::Path;
using ostk::core::fs::File;

using ostk::math::obj::Vector3d;
using ostk::math::obj::Vector4d;
using ostk::math::geom::d3::trf::rot::Quaternion;
using ostk::math::geom::d3::trf::rot::RotationVector;

using ostk::physics::units::Angle;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coord::Frame;
using ostk::physics::coord::frame::Transform;
using ostk::physics::coord::frame::provider::TOD;
using ostk::physics::coord::frame::providers::iau::Theory;
using ostk::physics::env::obj::celest::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_TOD, GetTransformAt)
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
                EarthGravitationalModel::EGM2008Parameters.equatorialRadius_.inMeters()
        );
        EXPECT_GT(
            1.0,
            q_J2000_TOD_IAU_2006.angularDifferenceWith(ref_q_J2000_TOD).inRadians() *
                EarthGravitationalModel::EGM2008Parameters.equatorialRadius_.inMeters()
        );
    }
}
