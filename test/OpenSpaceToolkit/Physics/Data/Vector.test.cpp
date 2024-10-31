/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::Shared;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::data::Vector;
using ostk::physics::time::Instant;
using ostk::physics::Unit;
using ostk::physics::unit::Length;

class OpenSpaceToolkit_Physics_Data_Vector : public ::testing::Test
{
   protected:
    const Unit unit_ = Unit::Length(Length::Unit::Meter);
    const Vector3d value_ = {1.0, 2.0, 3.0};
    const Shared<const Frame> frameSPtr_ = Frame::GCRF();
    const Vector vector_ = {
        value_,
        unit_,
        frameSPtr_,
    };
};

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, EqualToOperator)
{
    {
        EXPECT_TRUE(vector_ == vector_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, NotEqualToOperator)
{
    {
        EXPECT_FALSE(vector_ != vector_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << vector_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, IsDefined)
{
    {
        EXPECT_FALSE(Vector::Undefined().isDefined());
    }

    {
        EXPECT_TRUE(vector_.isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, GetValue)
{
    {
        EXPECT_EQ(vector_.getValue(), value_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, GetUnit)
{
    {
        EXPECT_EQ(vector_.getUnit(), unit_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, GetFrame)
{
    {
        EXPECT_EQ(vector_.getFrame(), frameSPtr_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, InUnit)
{
    {
        EXPECT_TRUE(vector_.inUnit(Unit::Length(Length::Unit::Foot)).isDefined());

        EXPECT_DOUBLE_EQ(value_.norm(), vector_.inUnit(Unit::Length(Length::Unit::Meter)).getValue().norm());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, InFrame)
{
    {
        EXPECT_EQ(vector_.inFrame(frameSPtr_, Instant::J2000()), vector_);
        EXPECT_NE(vector_.inFrame(frameSPtr_, Instant::J2000()), vector_.inFrame(Frame::ITRF(), Instant::J2000()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, ToString)
{
    {
        EXPECT_EQ(vector_.toString(1), "[1.0, 2.0, 3.0] [m] @ GCRF");
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Vector, Undefined)
{
    {
        EXPECT_FALSE(Vector::Undefined().isDefined());
    }
}
