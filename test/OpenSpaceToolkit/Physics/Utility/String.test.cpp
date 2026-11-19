/// Apache License 2.0

#include <limits>

#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

#include <Global.test.hpp>

using ostk::physics::utility::DoubleToString;
using ostk::physics::utility::ParseDouble;
using ostk::physics::utility::ParseInt;

TEST(OpenSpaceToolkit_Physics_Utility_String, DoubleToString)
{
    {
        EXPECT_EQ("1.0", DoubleToString(1.0));
        EXPECT_EQ("0.5", DoubleToString(0.5));
        EXPECT_EQ("0.500", DoubleToString(0.5, 3));
        EXPECT_EQ("+Inf", DoubleToString(std::numeric_limits<double>::infinity()));
        EXPECT_EQ("-Inf", DoubleToString(-std::numeric_limits<double>::infinity()));
    }

    {
        // NaN is printed as such: there is no undefined double
        EXPECT_EQ("NaN", DoubleToString(std::numeric_limits<double>::quiet_NaN()));
        EXPECT_EQ("NaN", DoubleToString(std::numeric_limits<double>::quiet_NaN(), 3));
    }
}

TEST(OpenSpaceToolkit_Physics_Utility_String, ParseDouble)
{
    {
        EXPECT_EQ(1.5, ParseDouble("1.5"));
        EXPECT_EQ(-2.0, ParseDouble("-2"));
        EXPECT_EQ(std::numeric_limits<double>::infinity(), ParseDouble("Inf"));
        EXPECT_EQ(std::numeric_limits<double>::infinity(), ParseDouble("+Inf"));
        EXPECT_EQ(-std::numeric_limits<double>::infinity(), ParseDouble("-Inf"));
    }

    {
        // A parsed value is never undefined
        EXPECT_ANY_THROW(ParseDouble(""));
        EXPECT_ANY_THROW(ParseDouble("Undefined"));
        EXPECT_ANY_THROW(ParseDouble("NaN"));
        EXPECT_ANY_THROW(ParseDouble("nan"));
        EXPECT_ANY_THROW(ParseDouble("abc"));
    }
}

TEST(OpenSpaceToolkit_Physics_Utility_String, ParseInt)
{
    {
        EXPECT_EQ(42, ParseInt("42"));
        EXPECT_EQ(-7, ParseInt("-7"));
    }

    {
        EXPECT_ANY_THROW(ParseInt(""));
        EXPECT_ANY_THROW(ParseInt("abc"));
    }
}
