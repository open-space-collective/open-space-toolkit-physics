/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Direction.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::Shared;

using ostk::mathematics::object::Vector3d;

using ostk::physics::data::Direction;
using ostk::physics::coordinate::Frame;

class OpenSpaceToolkit_Physics_Data_Direction : public ::testing::Test
{
   protected:
    const Vector3d value_ = {1.0, 0.0, 0.0};
    const Shared<const Frame> frameSPtr_ = Frame::GCRF();
    const Direction direction_ = {
        value_,
        frameSPtr_,
    };
};

TEST_F(OpenSpaceToolkit_Physics_Data_Direction, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << direction_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Direction, Undefined)
{
    {
        EXPECT_FALSE(Direction::Undefined().isDefined());
    }
}

