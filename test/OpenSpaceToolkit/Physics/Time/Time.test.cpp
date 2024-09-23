/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Time.hpp>

#include <Global.test.hpp>

using ostk::physics::time::Time;

TEST(OpenSpaceToolkit_Physics_Time_Time, Constructor)
{
    {
        EXPECT_NO_THROW(Time(0, 0, 0, 0, 0, 0));

        EXPECT_NO_THROW(Time(23, 0, 0, 0, 0, 0));
        EXPECT_NO_THROW(Time(0, 59, 0, 0, 0, 0));
        EXPECT_NO_THROW(Time(0, 0, 59, 0, 0, 0));
        EXPECT_NO_THROW(Time(0, 0, 60, 0, 0, 0));
        EXPECT_NO_THROW(Time(0, 0, 0, 999, 0, 0));
        EXPECT_NO_THROW(Time(0, 0, 0, 0, 999, 0));
        EXPECT_NO_THROW(Time(0, 0, 0, 0, 0, 999));

        EXPECT_NO_THROW(Time(23, 59, 59, 999, 999, 999));
        EXPECT_NO_THROW(Time(23, 59, 60, 999, 999, 999));
    }

    {
        EXPECT_ANY_THROW(Time(24, 0, 0));
        EXPECT_ANY_THROW(Time(0, 60, 0));
        EXPECT_ANY_THROW(Time(0, 0, 61));
        EXPECT_ANY_THROW(Time(0, 0, 0, 1000));
        EXPECT_ANY_THROW(Time(0, 0, 0, 0, 1000));
        EXPECT_ANY_THROW(Time(0, 0, 0, 0, 0, 1000));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, EqualToOperator)
{
    {
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0) == Time(0, 0, 0, 0, 0, 0));
        EXPECT_TRUE(Time(23, 59, 60, 999, 999, 999) == Time(23, 59, 60, 999, 999, 999));
    }

    {
        EXPECT_FALSE(Time(0, 0, 0, 0, 0, 0) == Time(1, 0, 0, 0, 0, 0));
        EXPECT_FALSE(Time(0, 0, 0, 0, 0, 0) == Time(0, 1, 0, 0, 0, 0));
        EXPECT_FALSE(Time(0, 0, 0, 0, 0, 0) == Time(0, 0, 1, 0, 0, 0));
        EXPECT_FALSE(Time(0, 0, 0, 0, 0, 0) == Time(0, 0, 0, 1, 0, 0));
        EXPECT_FALSE(Time(0, 0, 0, 0, 0, 0) == Time(0, 0, 0, 0, 1, 0));
        EXPECT_FALSE(Time(0, 0, 0, 0, 0, 0) == Time(0, 0, 0, 0, 0, 1));
    }

    {
        EXPECT_FALSE(Time::Undefined() == Time::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, NotEqualToOperator)
{
    {
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0) != Time(1, 0, 0, 0, 0, 0));
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0) != Time(0, 1, 0, 0, 0, 0));
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0) != Time(0, 0, 1, 0, 0, 0));
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0) != Time(0, 0, 0, 1, 0, 0));
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0) != Time(0, 0, 0, 0, 1, 0));
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0) != Time(0, 0, 0, 0, 0, 1));
    }

    {
        EXPECT_FALSE(Time(0, 0, 0, 0, 0, 0) != Time(0, 0, 0, 0, 0, 0));
        EXPECT_FALSE(Time(23, 59, 60, 999, 999, 999) != Time(23, 59, 60, 999, 999, 999));
    }

    {
        EXPECT_TRUE(Time::Undefined() != Time::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Time(23, 59, 60, 999, 999, 999) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, IsDefined)
{
    {
        EXPECT_TRUE(Time(0, 0, 0, 0, 0, 0).isDefined());
        EXPECT_TRUE(Time(1, 2, 3, 4, 5, 6).isDefined());
        EXPECT_TRUE(Time(23, 59, 60, 999, 999, 999).isDefined());
    }

    {
        EXPECT_FALSE(Time::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetHour)
{
    {
        EXPECT_EQ(1, Time(1, 2, 3, 4, 5, 6).getHour());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getHour());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetMinute)
{
    {
        EXPECT_EQ(2, Time(1, 2, 3, 4, 5, 6).getMinute());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getMinute());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetSecond)
{
    {
        EXPECT_EQ(3, Time(1, 2, 3, 4, 5, 6).getSecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getSecond());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetMillisecond)
{
    {
        EXPECT_EQ(4, Time(1, 2, 3, 4, 5, 6).getMillisecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getMillisecond());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetMicrosecond)
{
    {
        EXPECT_EQ(5, Time(1, 2, 3, 4, 5, 6).getMicrosecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getMicrosecond());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetNanosecond)
{
    {
        EXPECT_EQ(6, Time(1, 2, 3, 4, 5, 6).getNanosecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getNanosecond());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetFloatingSeconds)
{
    {
        EXPECT_NEAR(6.0, Time(0, 0, 6, 0, 0, 0).getFloatingSeconds(), 1e-15);
        EXPECT_NEAR(6.0, Time(4, 5, 6, 0, 0, 0).getFloatingSeconds(), 1e-15);

        EXPECT_NEAR(6.001002003, Time(4, 5, 6, 1, 2, 3).getFloatingSeconds(), 1e-15);
        EXPECT_NEAR(6.100200300, Time(4, 5, 6, 100, 200, 300).getFloatingSeconds(), 1e-15);
        EXPECT_NEAR(6.999999999, Time(4, 5, 6, 999, 999, 999).getFloatingSeconds(), 1e-15);
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getFloatingSeconds());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetTotalFloatingSeconds)
{
    {
        EXPECT_NEAR(6.0, Time(0, 0, 6, 0, 0, 0).getTotalFloatingSeconds(), 1e-15);
        EXPECT_NEAR(14706.0, Time(4, 5, 6, 0, 0, 0).getTotalFloatingSeconds(), 1e-15);

        EXPECT_NEAR(14706.001002003, Time(4, 5, 6, 1, 2, 3).getTotalFloatingSeconds(), 1e-15);
        EXPECT_NEAR(14706.100200300, Time(4, 5, 6, 100, 200, 300).getTotalFloatingSeconds(), 1e-15);
        EXPECT_NEAR(14706.999999999, Time(4, 5, 6, 999, 999, 999).getTotalFloatingSeconds(), 1e-15);
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getTotalFloatingSeconds());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, GetTotalFloatingHours)
{
    {
        EXPECT_NEAR(0.0016666666666666668, Time(0, 0, 6, 0, 0, 0).getTotalFloatingHours(), 1e-15);
        EXPECT_NEAR(4.085, Time(4, 5, 6, 0, 0, 0).getTotalFloatingHours(), 1e-15);

        EXPECT_NEAR(4.085000278334166, Time(4, 5, 6, 1, 2, 3).getTotalFloatingHours(), 1e-15);
        EXPECT_NEAR(4.0850278334166665, Time(4, 5, 6, 100, 200, 300).getTotalFloatingHours(), 1e-15);
        EXPECT_NEAR(4.0852777777775, Time(4, 5, 6, 999, 999, 999).getTotalFloatingHours(), 1e-15);
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().getTotalFloatingHours());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, ToString)
{
    {
        EXPECT_EQ("01:02:03.004.005.006", Time(1, 2, 3, 4, 5, 6).toString());
        EXPECT_EQ("23:59:60.999.999.999", Time(23, 59, 60, 999, 999, 999).toString());
    }

    {
        EXPECT_EQ("00:00:00", Time(0, 0, 0, 0, 0, 0).toString(Time::Format::Standard));
        EXPECT_EQ("01:02:03", Time(1, 2, 3).toString(Time::Format::Standard));
        EXPECT_EQ("01:02:03.004", Time(1, 2, 3, 4).toString(Time::Format::Standard));
        EXPECT_EQ("01:02:03.004.005", Time(1, 2, 3, 4, 5).toString(Time::Format::Standard));
        EXPECT_EQ("01:02:03.004.005.006", Time(1, 2, 3, 4, 5, 6).toString(Time::Format::Standard));
        EXPECT_EQ("23:59:60.999.999.999", Time(23, 59, 60, 999, 999, 999).toString(Time::Format::Standard));
    }

    {
        EXPECT_EQ("00:00:00", Time(0, 0, 0, 0, 0, 0).toString(Time::Format::ISO8601));
        EXPECT_EQ("01:02:03", Time(1, 2, 3).toString(Time::Format::ISO8601));
        EXPECT_EQ("01:02:03.004", Time(1, 2, 3, 4).toString(Time::Format::ISO8601));
        EXPECT_EQ("01:02:03.004005", Time(1, 2, 3, 4, 5).toString(Time::Format::ISO8601));
        EXPECT_EQ("01:02:03.004005006", Time(1, 2, 3, 4, 5, 6).toString(Time::Format::ISO8601));
        EXPECT_EQ("23:59:60.999999999", Time(23, 59, 60, 999, 999, 999).toString(Time::Format::ISO8601));
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, SetHour)
{
    {
        Time time(1, 2, 3, 4, 5, 6);

        EXPECT_EQ(1, time.getHour());

        EXPECT_NO_THROW(time.setHour(2));

        EXPECT_EQ(2, time.getHour());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().setHour(24));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, SetMinute)
{
    {
        Time time(1, 2, 3, 4, 5, 6);

        EXPECT_EQ(2, time.getMinute());

        EXPECT_NO_THROW(time.setMinute(3));

        EXPECT_EQ(3, time.getMinute());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().setMinute(1));

        EXPECT_ANY_THROW(Time(1, 2, 3, 4, 5, 6).setMinute(60));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, SetSecond)
{
    {
        Time time(1, 2, 3, 4, 5, 6);

        EXPECT_EQ(3, time.getSecond());

        EXPECT_NO_THROW(time.setSecond(4));

        EXPECT_EQ(4, time.getSecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().setSecond(1));

        EXPECT_ANY_THROW(Time(1, 2, 3, 4, 5, 6).setSecond(61));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, SetMillisecond)
{
    {
        Time time(1, 2, 3, 4, 5, 6);

        EXPECT_EQ(4, time.getMillisecond());

        EXPECT_NO_THROW(time.setMillisecond(5));

        EXPECT_EQ(5, time.getMillisecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().setMillisecond(1));

        EXPECT_ANY_THROW(Time(1, 2, 3, 4, 5, 6).setMillisecond(1000));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, SetMicrosecond)
{
    {
        Time time(1, 2, 3, 4, 5, 6);

        EXPECT_EQ(5, time.getMicrosecond());

        EXPECT_NO_THROW(time.setMicrosecond(6));

        EXPECT_EQ(6, time.getMicrosecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().setMicrosecond(1));

        EXPECT_ANY_THROW(Time(1, 2, 3, 4, 5, 6).setMicrosecond(1000));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, SetNanosecond)
{
    {
        Time time(1, 2, 3, 4, 5, 6);

        EXPECT_EQ(6, time.getNanosecond());

        EXPECT_NO_THROW(time.setNanosecond(7));

        EXPECT_EQ(7, time.getNanosecond());
    }

    {
        EXPECT_ANY_THROW(Time::Undefined().setNanosecond(1));

        EXPECT_ANY_THROW(Time(1, 2, 3, 4, 5, 6).setNanosecond(1000));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, Undefined)
{
    {
        EXPECT_NO_THROW(Time::Undefined());

        EXPECT_FALSE(Time::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, Midnight)
{
    {
        EXPECT_EQ(Time(0, 0, 0), Time::Midnight());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, Noon)
{
    {
        EXPECT_EQ(Time(12, 0, 0), Time::Noon());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, Parse)
{
    // Undefined (automatic format detection)

    {
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 789), Time::Parse("12:34:56.123.456.789"));
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 789), Time::Parse("12:34:56.123456789"));
    }

    // Standard

    {
        EXPECT_EQ(Time(12, 34, 56), Time::Parse("12:34:56", Time::Format::Standard));

        EXPECT_EQ(Time(12, 34, 56, 100), Time::Parse("12:34:56.1", Time::Format::Standard));
        EXPECT_EQ(Time(12, 34, 56, 120), Time::Parse("12:34:56.12", Time::Format::Standard));
        EXPECT_EQ(Time(12, 34, 56, 123), Time::Parse("12:34:56.123", Time::Format::Standard));

        EXPECT_EQ(Time(12, 34, 56, 123, 400), Time::Parse("12:34:56.123.4", Time::Format::Standard));
        EXPECT_EQ(Time(12, 34, 56, 123, 450), Time::Parse("12:34:56.123.45", Time::Format::Standard));
        EXPECT_EQ(Time(12, 34, 56, 123, 456), Time::Parse("12:34:56.123.456", Time::Format::Standard));

        EXPECT_EQ(Time(12, 34, 56, 123, 456, 700), Time::Parse("12:34:56.123.456.7", Time::Format::Standard));
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 780), Time::Parse("12:34:56.123.456.78", Time::Format::Standard));
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 789), Time::Parse("12:34:56.123.456.789", Time::Format::Standard));
    }

    {
        EXPECT_ANY_THROW(Time::Parse("", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("abc", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("1:34:56", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("12:3:56", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("12:34:5", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("24:34:56", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("12:60:56", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("12:34:61", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("12:34:61.", Time::Format::Standard));
        EXPECT_ANY_THROW(Time::Parse("-12:34:56", Time::Format::Standard));
    }

    // ISO 8601

    {
        EXPECT_EQ(Time(12, 34, 56), Time::Parse("12:34:56", Time::Format::ISO8601));

        EXPECT_EQ(Time(12, 34, 56, 100), Time::Parse("12:34:56.1", Time::Format::ISO8601));
        EXPECT_EQ(Time(12, 34, 56, 120), Time::Parse("12:34:56.12", Time::Format::ISO8601));
        EXPECT_EQ(Time(12, 34, 56, 123), Time::Parse("12:34:56.123", Time::Format::ISO8601));

        EXPECT_EQ(Time(12, 34, 56, 123, 400), Time::Parse("12:34:56.1234", Time::Format::ISO8601));
        EXPECT_EQ(Time(12, 34, 56, 123, 450), Time::Parse("12:34:56.12345", Time::Format::ISO8601));
        EXPECT_EQ(Time(12, 34, 56, 123, 456), Time::Parse("12:34:56.123456", Time::Format::ISO8601));

        EXPECT_EQ(Time(12, 34, 56, 123, 456, 700), Time::Parse("12:34:56.1234567", Time::Format::ISO8601));
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 780), Time::Parse("12:34:56.12345678", Time::Format::ISO8601));
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 789), Time::Parse("12:34:56.123456789", Time::Format::ISO8601));
    }

    {
        EXPECT_ANY_THROW(Time::Parse("", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("abc", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("1:34:56", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("12:3:56", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("12:34:5", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("24:34:56", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("12:60:56", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("12:34:61", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("12:34:61.", Time::Format::ISO8601));
        EXPECT_ANY_THROW(Time::Parse("-12:34:56", Time::Format::ISO8601));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, Seconds)
{
    {
        EXPECT_EQ(Time(12, 30, 15, 234, 456, 678), Time::Seconds(45015.234456678001));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_Time, Hours)
{
    {
        EXPECT_EQ(Time(12, 30, 15, 234, 456, 678), Time::Hours(12.504231793521667));
    }
}
