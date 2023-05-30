/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Coordinate_Frames_TOD, NoCaching)
{
    namespace iau = ostk::physics::coord::frame::providers::iau;

    using ostk::math::geom::d3::trf::rot::Quaternion;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::Frame;

    {
        const auto GCRF = Frame::GCRF();

        const Instant epoch_1 = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);
        const Instant epoch_2 = Instant::DateTime(DateTime(2022, 1, 1, 0, 0, 0), Scale::UTC);

        const auto TOD_1 = Frame::TOD(epoch_1, iau::Theory::IAU_2006);
        const auto TOD_2 = Frame::TOD(epoch_2, iau::Theory::IAU_2006);

        const Quaternion q_GCRF_TOD_1 = TOD_1->getTransformTo(GCRF, epoch_1).getOrientation();
        const Quaternion q_GCRF_TOD_2 = TOD_2->getTransformTo(GCRF, epoch_2).getOrientation();

        EXPECT_NE(q_GCRF_TOD_1, q_GCRF_TOD_2);
    }

    {
        const auto GCRF = Frame::GCRF();

        const Instant epoch = Instant::DateTime(DateTime(2020, 1, 1, 0, 0, 0), Scale::UTC);

        const auto TOD_1 = Frame::TOD(epoch, iau::Theory::IAU_2000B);
        const auto TOD_2 = Frame::TOD(epoch, iau::Theory::IAU_2006);

        const Quaternion q_GCRF_TOD_1 = TOD_1->getTransformTo(GCRF, epoch).getOrientation();
        const Quaternion q_GCRF_TOD_2 = TOD_2->getTransformTo(GCRF, epoch).getOrientation();

        EXPECT_NE(q_GCRF_TOD_1, q_GCRF_TOD_2);
    }
}
