/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::physics::time::Date;
using ostk::physics::time::DateTime;
using ostk::physics::time::Time;

TEST(OpenSpaceToolkit_Physics_Time_DateTime, Constructor)
{
    {
        EXPECT_NO_THROW(DateTime(Date(2018, 1, 1), Time(1, 2, 3)));

        EXPECT_NO_THROW(DateTime(Date(1400, 1, 1), Time(1, 2, 3, 123, 456, 789)));
        EXPECT_NO_THROW(DateTime(Date(9999, 1, 1), Time(1, 2, 3, 123, 456, 789)));
    }

    {
        EXPECT_ANY_THROW(DateTime(Date(2018, 2, 29), Time(0, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(0, 1, 1), Time(0, 0, 0)));
        EXPECT_ANY_THROW(DateTime(Date(1399, 12, 31), Time(0, 0, 0)));
        EXPECT_ANY_THROW(DateTime(Date(10000, 1, 1), Time(0, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 0, 1), Time(0, 0, 0)));
        EXPECT_ANY_THROW(DateTime(Date(2018, 13, 1), Time(0, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 0), Time(0, 0, 0)));
        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 32), Time(0, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(24, 0, 0, 0, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 60, 0, 0, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 61, 0, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 0, 1000, 0, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 0, 0, 1000, 0)));

        EXPECT_ANY_THROW(DateTime(Date(2018, 1, 1), Time(0, 0, 0, 0, 0, 1000)));
    }

    {
        EXPECT_NO_THROW(DateTime(2018, 1, 1, 1, 2, 3));

        EXPECT_NO_THROW(DateTime(1400, 1, 1, 1, 2, 3, 123, 456, 789));
        EXPECT_NO_THROW(DateTime(9999, 1, 1, 1, 2, 3, 123, 456, 789));
    }

    {
        EXPECT_ANY_THROW(DateTime(2018, 2, 29, 0, 0, 0));

        EXPECT_ANY_THROW(DateTime(0, 1, 1, 0, 0, 0));
        EXPECT_ANY_THROW(DateTime(1399, 12, 31, 0, 0, 0));
        EXPECT_ANY_THROW(DateTime(10000, 1, 1, 0, 0, 0));

        EXPECT_ANY_THROW(DateTime(2018, 0, 1, 0, 0, 0));
        EXPECT_ANY_THROW(DateTime(2018, 13, 1, 0, 0, 0));

        EXPECT_ANY_THROW(DateTime(2018, 1, 0, 0, 0, 0));
        EXPECT_ANY_THROW(DateTime(2018, 1, 32, 0, 0, 0));

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 24, 0, 0, 0, 0, 0));

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 60, 0, 0, 0, 0));

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 61, 0, 0, 0));

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 0, 1000, 0, 0));

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 0, 0, 1000, 0));

        EXPECT_ANY_THROW(DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 1000));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, EqualToOperator)
{
    {
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789));

        EXPECT_TRUE(DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789));
        EXPECT_TRUE(DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789));
    }

    {
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2019, 1, 2, 12, 34, 56, 123, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 2, 2, 12, 34, 56, 123, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 3, 12, 34, 56, 123, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 13, 34, 56, 123, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 35, 56, 123, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 57, 123, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 124, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 123, 457, 789)
        );
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) == DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 790)
        );
    }

    {
        EXPECT_FALSE(DateTime::Undefined() == DateTime::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, NotEqualToOperator)
{
    {
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2019, 1, 2, 12, 34, 56, 123, 456, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 2, 2, 12, 34, 56, 123, 456, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 3, 12, 34, 56, 123, 456, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 13, 34, 56, 123, 456, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 35, 56, 123, 456, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 57, 123, 456, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 124, 456, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 123, 457, 789));
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 790));
    }

    {
        EXPECT_FALSE(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789)
        );

        EXPECT_FALSE(
            DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789)
        );
        EXPECT_FALSE(
            DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789) != DateTime(9999, 1, 2, 12, 34, 56, 123, 456, 789)
        );
    }

    {
        EXPECT_TRUE(DateTime::Undefined() != DateTime::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, IsDefined)
{
    {
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56).isDefined());
        EXPECT_TRUE(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).isDefined());
    }

    {
        EXPECT_FALSE(DateTime::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, AccessDate)
{
    {
        EXPECT_EQ(Date(2018, 1, 2), DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).accessDate());
    }

    {
        EXPECT_ANY_THROW(DateTime::Undefined().accessDate());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, AccessTime)
{
    {
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 789), DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).accessTime());
    }

    {
        EXPECT_ANY_THROW(DateTime::Undefined().accessTime());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, GetDate)
{
    {
        EXPECT_EQ(Date(2018, 1, 2), DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).getDate());
    }

    {
        EXPECT_ANY_THROW(DateTime::Undefined().getDate());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, GetTime)
{
    {
        EXPECT_EQ(Time(12, 34, 56, 123, 456, 789), DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).getTime());
    }

    {
        EXPECT_ANY_THROW(DateTime::Undefined().getTime());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, GetJulianDate)
{
    {
        EXPECT_EQ(2451545.0, DateTime(2000, 1, 1, 12, 0, 0).getJulianDate());
        EXPECT_EQ(2451545.25, DateTime(2000, 1, 1, 18, 0, 0).getJulianDate());
        EXPECT_EQ(2451545.50, DateTime(2000, 1, 2, 0, 0, 0).getJulianDate());
        EXPECT_EQ(2451545.75, DateTime(2000, 1, 2, 6, 0, 0).getJulianDate());
        EXPECT_EQ(2451546.0, DateTime(2000, 1, 2, 12, 0, 0).getJulianDate());
    }

    {
        EXPECT_ANY_THROW(DateTime::Undefined().getJulianDate());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, GetModifiedJulianDate)
{
    {
        EXPECT_EQ(0.0, DateTime(1858, 11, 17, 0, 0, 0).getModifiedJulianDate());
        EXPECT_EQ(54000.0, DateTime(2006, 9, 22, 0, 0, 0).getModifiedJulianDate());
        EXPECT_EQ(88069.0, DateTime(2100, 1, 1, 0, 0, 0).getModifiedJulianDate());
    }

    {
        EXPECT_ANY_THROW(DateTime::Undefined().getModifiedJulianDate());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, ToString)
{
    {
        EXPECT_EQ("2018-01-02 12:34:56.123.456.789", DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).toString());

        EXPECT_EQ("1400-01-02 12:34:56.123.456.789", DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789).toString());
        EXPECT_EQ("9999-12-31 12:34:56.123.456.789", DateTime(9999, 12, 31, 12, 34, 56, 123, 456, 789).toString());
    }

    {
        EXPECT_EQ(
            "2018-01-02 12:34:56", DateTime(2018, 1, 2, 12, 34, 56, 0, 0, 0).toString(DateTime::Format::Standard)
        );
        EXPECT_EQ(
            "2018-01-02 12:34:56.123", DateTime(2018, 1, 2, 12, 34, 56, 123, 0, 0).toString(DateTime::Format::Standard)
        );
        EXPECT_EQ(
            "2018-01-02 12:34:56.123.456",
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 0).toString(DateTime::Format::Standard)
        );
        EXPECT_EQ(
            "2018-01-02 12:34:56.123.456.789",
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::Standard)
        );

        EXPECT_EQ(
            "1400-01-02 12:34:56.123.456.789",
            DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::Standard)
        );
        EXPECT_EQ(
            "9999-12-31 12:34:56.123.456.789",
            DateTime(9999, 12, 31, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::Standard)
        );
    }

    {
        EXPECT_EQ("2018-01-02T12:34:56", DateTime(2018, 1, 2, 12, 34, 56, 0, 0, 0).toString(DateTime::Format::ISO8601));
        EXPECT_EQ(
            "2018-01-02T12:34:56.123", DateTime(2018, 1, 2, 12, 34, 56, 123, 0, 0).toString(DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            "2018-01-02T12:34:56.123456",
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 0).toString(DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            "2018-01-02T12:34:56.123456789",
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::ISO8601)
        );

        EXPECT_EQ(
            "1400-01-02T12:34:56.123456789",
            DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            "9999-12-31T12:34:56.123456789",
            DateTime(9999, 12, 31, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::ISO8601)
        );
    }

    {
        EXPECT_EQ("2 Jan 2018 12:34:56", DateTime(2018, 1, 2, 12, 34, 56, 0, 0, 0).toString(DateTime::Format::STK));
        EXPECT_EQ(
            "2 Jan 2018 12:34:56.123", DateTime(2018, 1, 2, 12, 34, 56, 123, 0, 0).toString(DateTime::Format::STK)
        );
        EXPECT_EQ(
            "2 Jan 2018 12:34:56.123456", DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 0).toString(DateTime::Format::STK)
        );
        EXPECT_EQ(
            "2 Jan 2018 12:34:56.123456789",
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::STK)
        );

        EXPECT_EQ(
            "2 Jan 1400 12:34:56.123456789",
            DateTime(1400, 1, 2, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::STK)
        );
        EXPECT_EQ(
            "31 Dec 9999 12:34:56.123456789",
            DateTime(9999, 12, 31, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::STK)
        );
    }

    {
        EXPECT_ANY_THROW(DateTime::Undefined().toString());
        EXPECT_ANY_THROW(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789).toString(DateTime::Format::Undefined));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, Undefined)
{
    {
        EXPECT_NO_THROW(DateTime::Undefined());

        EXPECT_FALSE(DateTime::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, J2000)
{
    {
        EXPECT_EQ(DateTime(2000, 1, 1, 12, 0, 0), DateTime::J2000());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, GPSEpoch)
{
    {
        EXPECT_EQ(DateTime(1980, 1, 6, 0, 0, 0), DateTime::GPSEpoch());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, UnixEpoch)
{
    {
        EXPECT_EQ(DateTime(1970, 1, 1, 0, 0, 0), DateTime::UnixEpoch());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, ModifiedJulianDateEpoch)
{
    {
        EXPECT_EQ(DateTime(1858, 11, 17, 0, 0, 0), DateTime::ModifiedJulianDateEpoch());
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, JulianDate)
{
    {
        EXPECT_EQ(DateTime(2000, 1, 1, 12, 0, 0), DateTime::JulianDate(2451545.0));
        EXPECT_EQ(DateTime(2000, 1, 1, 18, 0, 0), DateTime::JulianDate(2451545.25));
        EXPECT_EQ(DateTime(2000, 1, 2, 0, 0, 0), DateTime::JulianDate(2451545.50));
        EXPECT_EQ(DateTime(2000, 1, 2, 6, 0, 0), DateTime::JulianDate(2451545.75));
        EXPECT_EQ(DateTime(2000, 1, 2, 12, 0, 0), DateTime::JulianDate(2451546.0));

        EXPECT_EQ(DateTime(2004, 4, 5, 12, 0, 0), DateTime::JulianDate(2453101.0));
        EXPECT_EQ(DateTime(2004, 4, 6, 7, 52, 19, 200, 18, 346), DateTime::JulianDate(2453101.828));
        EXPECT_EQ(DateTime(2004, 4, 6, 7, 52, 27, 840, 4), DateTime::JulianDate(2453101.8281));
        EXPECT_EQ(DateTime(2004, 4, 6, 7, 52, 32, 160, 0), DateTime::JulianDate(2453101.82815));
        EXPECT_EQ(DateTime(2004, 4, 6, 7, 52, 32, 506, 0), DateTime::JulianDate(2453101.828154));
        EXPECT_EQ(DateTime(2004, 4, 6, 7, 52, 32, 566, 69, 364), DateTime::JulianDate(2453101.8281547));
        EXPECT_EQ(DateTime(2004, 4, 6, 7, 52, 32, 570, 0, 0), DateTime::JulianDate(2453101.82815474));
        EXPECT_EQ(DateTime(2004, 4, 6, 7, 52, 32, 570, 0, 0), DateTime::JulianDate(2453101.828154745));
    }

    {
        EXPECT_ANY_THROW(DateTime::JulianDate(Real::Undefined()));
        EXPECT_ANY_THROW(DateTime::JulianDate(0.0));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, ModifiedJulianDate)
{
    {
        EXPECT_EQ(DateTime(1858, 11, 17, 0, 0, 0), DateTime::ModifiedJulianDate(0.0));

        EXPECT_EQ(DateTime(2006, 9, 22, 0, 0, 0), DateTime::ModifiedJulianDate(54000.0));

        EXPECT_EQ(DateTime(2100, 1, 1, 0, 0, 0), DateTime::ModifiedJulianDate(88069.0));
    }

    {
        EXPECT_ANY_THROW(DateTime::ModifiedJulianDate(Real::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Physics_Time_DateTime, Parse)
{
    // Undefined (automatic format detection)

    {
        // Standard
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02 12:34:56.123.456.789"));
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02T12:34:56.123456789+0000")
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02 12:34:56.123.456.789+0000")
        );

        // ISO8601
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02T12:34:56.123456789"));
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02T12:34:56.123456789Z"));
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2018-01-02 12:34:56.123.456.789Z"));

        // STK
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789), DateTime::Parse("2 Jan 2018 12:34:56.123456789"));
    }

    // Standard

    {
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56), DateTime::Parse("2018-01-02 12:34:56", DateTime::Format::Standard));

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 100), DateTime::Parse("2018-01-02 12:34:56.1", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 120), DateTime::Parse("2018-01-02 12:34:56.12", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123),
            DateTime::Parse("2018-01-02 12:34:56.123", DateTime::Format::Standard)
        );

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 400),
            DateTime::Parse("2018-01-02 12:34:56.123.4", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 450),
            DateTime::Parse("2018-01-02 12:34:56.123.45", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456),
            DateTime::Parse("2018-01-02 12:34:56.123.456", DateTime::Format::Standard)
        );

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 700),
            DateTime::Parse("2018-01-02 12:34:56.123.456.7", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 780),
            DateTime::Parse("2018-01-02 12:34:56.123.456.78", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789),
            DateTime::Parse("2018-01-02 12:34:56.123.456.789", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789),
            DateTime::Parse("2018-01-02 12:34:56.123.456.789+0000", DateTime::Format::Standard)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789),
            DateTime::Parse("2018-01-02 12:34:56.123.456.789Z", DateTime::Format::Standard)
        );

        EXPECT_EQ(DateTime(1400, 1, 1, 0, 0, 0), DateTime::Parse("1400-01-01 00:00:00", DateTime::Format::Standard));
        EXPECT_EQ(
            DateTime(9999, 12, 31, 23, 59, 59), DateTime::Parse("9999-12-31 23:59:59", DateTime::Format::Standard)
        );
    }

    {
        EXPECT_ANY_THROW(DateTime::Parse("", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("abc", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 01", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 1:34", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 1:34:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:3:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:34:5", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-00-01 24:34:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-13-01 24:34:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-00 24:34:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-32 24:34:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 24:34:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:60:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:34:61", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 12:34:61.", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02 -12:34:56", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("1399-12-31 23:59:59", DateTime::Format::Standard));
        EXPECT_ANY_THROW(DateTime::Parse("10000-01-01 00:00:00", DateTime::Format::Standard));
    }

    // ISO 8601

    {
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56), DateTime::Parse("2018-01-02T12:34:56", DateTime::Format::ISO8601));

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 100), DateTime::Parse("2018-01-02T12:34:56.1", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 120), DateTime::Parse("2018-01-02T12:34:56.12", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123), DateTime::Parse("2018-01-02T12:34:56.123", DateTime::Format::ISO8601)
        );

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 400),
            DateTime::Parse("2018-01-02T12:34:56.1234", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 450),
            DateTime::Parse("2018-01-02T12:34:56.12345", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456),
            DateTime::Parse("2018-01-02T12:34:56.123456", DateTime::Format::ISO8601)
        );

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 700),
            DateTime::Parse("2018-01-02T12:34:56.1234567", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 780),
            DateTime::Parse("2018-01-02T12:34:56.12345678", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789),
            DateTime::Parse("2018-01-02T12:34:56.123456789", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789),
            DateTime::Parse("2018-01-02T12:34:56.123456789+0000", DateTime::Format::ISO8601)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789),
            DateTime::Parse("2018-01-02T12:34:56.123456789Z", DateTime::Format::ISO8601)
        );

        EXPECT_EQ(DateTime(1400, 1, 1, 0, 0, 0), DateTime::Parse("1400-01-01T00:00:00", DateTime::Format::ISO8601));
        EXPECT_EQ(
            DateTime(9999, 12, 31, 23, 59, 59), DateTime::Parse("9999-12-31T23:59:59", DateTime::Format::ISO8601)
        );
    }

    // STK

    {
        EXPECT_EQ(DateTime(2018, 1, 2, 12, 34, 56), DateTime::Parse("2 Jan 2018 12:34:56", DateTime::Format::STK));

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 100), DateTime::Parse("2 Jan 2018 12:34:56.1", DateTime::Format::STK)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 120), DateTime::Parse("2 Jan 2018 12:34:56.12", DateTime::Format::STK)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123), DateTime::Parse("2 Jan 2018 12:34:56.123", DateTime::Format::STK)
        );

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 400),
            DateTime::Parse("2 Jan 2018 12:34:56.1234", DateTime::Format::STK)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 450),
            DateTime::Parse("2 Jan 2018 12:34:56.12345", DateTime::Format::STK)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456),
            DateTime::Parse("2 Jan 2018 12:34:56.123456", DateTime::Format::STK)
        );

        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 700),
            DateTime::Parse("2 Jan 2018 12:34:56.1234567", DateTime::Format::STK)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 780),
            DateTime::Parse("2 Jan 2018 12:34:56.12345678", DateTime::Format::STK)
        );
        EXPECT_EQ(
            DateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789),
            DateTime::Parse("2 Jan 2018 12:34:56.123456789", DateTime::Format::STK)
        );

        EXPECT_EQ(DateTime(1400, 1, 1, 0, 0, 0), DateTime::Parse("1 Jan 1400 00:00:00", DateTime::Format::STK));
        EXPECT_EQ(DateTime(9999, 12, 31, 23, 59, 59), DateTime::Parse("31 Dec 9999 23:59:59", DateTime::Format::STK));
    }

    {
        EXPECT_ANY_THROW(DateTime::Parse(""));
        EXPECT_ANY_THROW(DateTime::Parse("abc"));
        EXPECT_ANY_THROW(DateTime::Parse("2018"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T01"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T1:34"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T1:34:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:3:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:5"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-00-01T24:34:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-13-01T24:34:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-00T24:34:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-32T24:34:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T24:34:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:60:56"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:61"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:61."));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T-12:34:56"));
        EXPECT_ANY_THROW(DateTime::Parse("1399-12-31T23:59:59"));
        EXPECT_ANY_THROW(DateTime::Parse("10000-01-01T00:00:00"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:56.123.456"));
        EXPECT_ANY_THROW(DateTime::Parse("2018-01-02T12:34:56.123.456.789"));
    }
}
