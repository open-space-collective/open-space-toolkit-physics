/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <Global.test.hpp>

using ostk::math::geometry::d3::transformation::rotation::Quaternion;

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coord::Frame;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frames_MOD, NoCaching)
{
    const auto GCRF = Frame::GCRF();

    const Instant epoch_1 = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);
    const Instant epoch_2 = Instant::DateTime(DateTime(2022, 1, 1, 0, 0, 0), Scale::UTC);

    const auto MOD_1 = Frame::MOD(epoch_1);
    const auto MOD_2 = Frame::MOD(epoch_2);

    const Quaternion q_GCRF_MOD_1 = MOD_1->getTransformTo(GCRF, epoch_1).getOrientation();
    const Quaternion q_GCRF_MOD_2 = MOD_2->getTransformTo(GCRF, epoch_2).getOrientation();

    EXPECT_NE(q_GCRF_MOD_1, q_GCRF_MOD_2);
}
