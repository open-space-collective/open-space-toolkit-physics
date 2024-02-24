/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Scalar.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::physics::data::Scalar;
using ostk::physics::Unit;
using ostk::physics::unit::Length;

class OpenSpaceToolkit_Physics_Data_Scalar : public ::testing::Test
{
   protected:
    const Unit unit_ = Unit::Length(Length::Unit::Meter);
    const Real value_ = 5.0;
    const Scalar scalar_ = {value_, unit_};
};

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, EqualToOperator)
{
    {
        EXPECT_TRUE(scalar_ == scalar_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, NotEqualToOperator)
{
    {
        EXPECT_FALSE(scalar_ != scalar_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << scalar_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, IsDefined)
{
    {
        EXPECT_FALSE(Scalar::Undefined().isDefined());
    }

    {
        EXPECT_TRUE(scalar_.isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, GetValue)
{
    {
        EXPECT_EQ(scalar_.getValue(), value_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, GetUnit)
{
    {
        EXPECT_EQ(scalar_.getUnit(), unit_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, InUnit)
{
    {
        EXPECT_TRUE(scalar_.inUnit(Unit::Length(Length::Unit::Foot)).isDefined());

        EXPECT_DOUBLE_EQ(value_, scalar_.inUnit(Unit::Length(Length::Unit::Meter)).getValue());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, ToString)
{
    {
        EXPECT_EQ(scalar_.toString(), "5.0 [m]");
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Scalar, Undefined)
{
    {
        EXPECT_FALSE(Scalar::Undefined().isDefined());
    }
}
