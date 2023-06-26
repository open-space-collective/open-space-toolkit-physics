/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>

#include <Global.test.hpp>

using ostk::core::fs::Path;
using ostk::core::fs::File;

using ostk::physics::time::Date;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Interval;
using ostk::physics::time::Duration;
using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;

class OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/"
                                   "CSSISpaceWeather/SW-Last5Years.test.csv"));
        this->CSSISpaceWeather_ = CSSISpaceWeather::Load(file);
    }

    CSSISpaceWeather CSSISpaceWeather_ = CSSISpaceWeather::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << CSSISpaceWeather_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, IsDefined)
{
    {
        EXPECT_TRUE(CSSISpaceWeather_.isDefined());
    }

    {
        EXPECT_FALSE(CSSISpaceWeather::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, AccessLastObservationDate)
{
    {
        EXPECT_EQ(Date::Parse("2023-06-19", Date::Format::Standard), CSSISpaceWeather_.accessLastObservationDate());
    }

    {
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessLastObservationDate(), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, AccessObservationInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-01-01 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2023-06-19 00:00:00"), Scale::UTC)
            ),
            CSSISpaceWeather_.accessObservationInterval()
        );
    }

    {
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessObservationInterval(), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, AccessObservationAt)
{
    {
        const CSSISpaceWeather::Reading firstObservation =
            CSSISpaceWeather_.accessObservationAt(Instant::DateTime(DateTime::Parse("2018-01-01 12:00:00"), Scale::UTC)
            );

        EXPECT_EQ(Date::Parse("2018-01-01", Date::Format::Standard), firstObservation.date);

        EXPECT_EQ(2515, firstObservation.BSRN);
        EXPECT_EQ(177, firstObservation.KpSum);
        EXPECT_EQ(10, firstObservation.ApAvg);
        EXPECT_EQ("OBS", firstObservation.F107DataType);

        EXPECT_NEAR(69.1, firstObservation.F107Obs, 1e-15);
        EXPECT_NEAR(71.4, firstObservation.F107ObsCenter81, 1e-15);
    }

    {
        // calling Undefined Space Weather
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessObservationAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ),
        ostk::core::error::runtime::Undefined);
    }

    {
        // calling Space Weather with Undefined Instant
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessObservationAt(
            Instant::Undefined()
        ),
        ostk::core::error::runtime::Undefined);
    }

    {
        // access reading outside of interval
        EXPECT_THROW(CSSISpaceWeather_.accessObservationAt(Instant::DateTime(DateTime::Parse("2000-01-01 00:00:00"), Scale::UTC)),
        ostk::core::error::RuntimeError);
    }

    {
        // access reading inside of interval, but with no data present
        EXPECT_THROW(CSSISpaceWeather_.accessObservationAt(Instant::DateTime(DateTime::Parse("2019-01-01 00:00:00"), Scale::UTC)),
        ostk::core::error::RuntimeError);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, AccessDailyPredictionInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2023-06-20 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2023-08-03 00:00:00"), Scale::UTC)
            ),
            CSSISpaceWeather_.accessDailyPredictionInterval()
        );
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().accessDailyPredictionInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, AccessDailyPredictionAt)
{
    {
        const CSSISpaceWeather::Reading firstDailyPrediction = CSSISpaceWeather_.accessDailyPredictionAt(
            Instant::DateTime(DateTime::Parse("2023-06-20 12:00:00"), Scale::UTC)
        );

        EXPECT_EQ(Date::Parse("2023-06-20", Date::Format::Standard), firstDailyPrediction.date);

        EXPECT_EQ(2589, firstDailyPrediction.BSRN);
        EXPECT_EQ(167, firstDailyPrediction.KpSum);
        EXPECT_EQ(9, firstDailyPrediction.ApAvg);
        EXPECT_EQ("PRD", firstDailyPrediction.F107DataType);

        EXPECT_NEAR(164.6, firstDailyPrediction.F107Obs, 1e-15);
        EXPECT_NEAR(160.2, firstDailyPrediction.F107ObsCenter81, 1e-15);
    }

    {
        // calling Undefined Space Weather
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessDailyPredictionAt(
            Instant::DateTime(DateTime::Parse("2023-06-29 00:00:00"), Scale::UTC)
        ),
        ostk::core::error::runtime::Undefined);
    }

    {
        // calling Space Weather with Undefined Instant
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessDailyPredictionAt(
            Instant::Undefined()
        ),
        ostk::core::error::runtime::Undefined);
    }

    {
        // access reading outside of interval
        EXPECT_THROW(CSSISpaceWeather_.accessDailyPredictionAt(Instant::DateTime(DateTime::Parse("2020-07-15 00:00:00"), Scale::UTC)),
        ostk::core::error::RuntimeError);
    }

    {
        // access reading inside of interval, but with no data present
        EXPECT_THROW(CSSISpaceWeather_.accessDailyPredictionAt(Instant::DateTime(DateTime::Parse("2023-07-15 00:00:00"), Scale::UTC)),
        ostk::core::error::RuntimeError);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, AccessMonthlyPredictionInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2023-08-01 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2029-01-01 00:00:00"), Scale::UTC)
            ),
            CSSISpaceWeather_.accessMonthlyPredictionInterval()
        );
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().accessMonthlyPredictionInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, AccessMonthlyPredictionAt)
{
    {
        const CSSISpaceWeather::Reading firstMonthlyPrediction = CSSISpaceWeather_.accessMonthlyPredictionAt(
            Instant::DateTime(DateTime::Parse("2023-09-15 12:00:00"), Scale::UTC)
        );

        EXPECT_EQ(Date::Parse("2023-09-01", Date::Format::Standard), firstMonthlyPrediction.date);

        EXPECT_EQ(11, firstMonthlyPrediction.ND);
        EXPECT_EQ("PRM", firstMonthlyPrediction.F107DataType);

        EXPECT_NEAR(151.3, firstMonthlyPrediction.F107Obs, 1e-15);
        EXPECT_NEAR(154.2, firstMonthlyPrediction.F107ObsCenter81, 1e-15);
    }

    {
        // calling Undefined Space Weather
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessMonthlyPredictionAt(
            Instant::DateTime(DateTime::Parse("2023-06-29 00:00:00"), Scale::UTC)
        ),
        ostk::core::error::runtime::Undefined);
    }

    {
        // calling Space Weather with Undefined Instant
        EXPECT_THROW(CSSISpaceWeather::Undefined().accessMonthlyPredictionAt(
            Instant::Undefined()
        ),
        ostk::core::error::runtime::Undefined);
    }

    {
        // access reading outside of interval
        EXPECT_THROW(CSSISpaceWeather_.accessMonthlyPredictionAt(Instant::DateTime(DateTime::Parse("2020-07-15 00:00:00"), Scale::UTC)),
        ostk::core::error::RuntimeError);
    }

    {
        // access reading inside of interval, but with no data present
        EXPECT_THROW(CSSISpaceWeather_.accessMonthlyPredictionAt(Instant::DateTime(DateTime::Parse("2025-07-15 00:00:00"), Scale::UTC)),
        ostk::core::error::RuntimeError);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_CSSISpaceWeather, Load)
{
    {
        EXPECT_TRUE(CSSISpaceWeather_.isDefined());
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Load(File::Undefined()));
        EXPECT_ANY_THROW(CSSISpaceWeather::Load(File::Path(Path::Parse("/does/not/exist"))));
    }
}
