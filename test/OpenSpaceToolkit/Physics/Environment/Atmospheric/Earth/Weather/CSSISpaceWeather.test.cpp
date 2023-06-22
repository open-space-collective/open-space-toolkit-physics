/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather.hpp>

#include <Global.test.hpp>

using ostk::core::fs::Path;
using ostk::core::fs::File;

using ostk::physics::time::Date;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Interval;
using ostk::physics::time::Duration;
using ostk::physics::environment::atmospheric::earth::weather::CSSISpaceWeather;

class OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/"
                                   "CSSISpaceWeather/SW-Last5Years.test.csv"));
        this->CSSISpaceWeather_ = CSSISpaceWeather::Load(file);
    }

    CSSISpaceWeather CSSISpaceWeather_ = CSSISpaceWeather::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << CSSISpaceWeather_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, IsDefined)
{
    {
        EXPECT_TRUE(CSSISpaceWeather_.isDefined());
    }

    {
        EXPECT_FALSE(CSSISpaceWeather::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, AccessObservationInterval)
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
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().accessObservationInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, AccessObservationAt)
{
    {
        const CSSISpaceWeather::Observation firstObservation =
            CSSISpaceWeather_.accessObservationAt(Instant::DateTime(DateTime::Parse("2018-01-01 12:00:00"), Scale::UTC));

        EXPECT_EQ(Date::Parse("2018-01-01", Date::Format::Standard), firstObservation.date);

        EXPECT_EQ(2515, firstObservation.BSRN);
        EXPECT_EQ(177, firstObservation.KP_SUM);
        EXPECT_EQ(10, firstObservation.AP_AVG);
        EXPECT_EQ("OBS", firstObservation.F107_DATA_TYPE);

        EXPECT_NEAR(69.1, firstObservation.F107_OBS, 1e-15);
        EXPECT_NEAR(71.4, firstObservation.F107_OBS_CENTER81, 1e-15);
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().accessObservationAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, AccessDailyPredictionInterval)
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

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, AccessDailyPredictionAt)
{
    {
        const CSSISpaceWeather::DailyPrediction firstDailyPrediction =
            CSSISpaceWeather_.accessDailyPredictionAt(Instant::DateTime(DateTime::Parse("2023-06-20 12:00:00"), Scale::UTC)
            );

        EXPECT_EQ(Date::Parse("2023-06-20", Date::Format::Standard), firstDailyPrediction.date);

        EXPECT_EQ(2589, firstDailyPrediction.BSRN);
        EXPECT_EQ(167, firstDailyPrediction.KP_SUM);
        EXPECT_EQ(9, firstDailyPrediction.AP_AVG);
        EXPECT_EQ("PRD", firstDailyPrediction.F107_DATA_TYPE);

        EXPECT_NEAR(164.6, firstDailyPrediction.F107_OBS, 1e-15);
        EXPECT_NEAR(160.2, firstDailyPrediction.F107_OBS_CENTER81, 1e-15);
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().accessDailyPredictionAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, AccessMonthlyPredictionInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2023-09-01 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2029-01-01 00:00:00"), Scale::UTC)
            ),
            CSSISpaceWeather_.accessMonthlyPredictionInterval()
        );
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().accessMonthlyPredictionInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, AccessMonthlyPredictionAt)
{
    {
        const CSSISpaceWeather::MonthlyPrediction firstMonthlyPrediction = CSSISpaceWeather_.accessMonthlyPredictionAt(
            Instant::DateTime(DateTime::Parse("2023-09-15 12:00:00"), Scale::UTC)
        );

        EXPECT_EQ(Date::Parse("2023-09-01", Date::Format::Standard), firstMonthlyPrediction.date);

        EXPECT_EQ(11, firstMonthlyPrediction.ND);
        EXPECT_EQ("PRM", firstMonthlyPrediction.F107_DATA_TYPE);

        EXPECT_NEAR(151.3, firstMonthlyPrediction.F107_OBS, 1e-15);
        EXPECT_NEAR(154.2, firstMonthlyPrediction.F107_OBS_CENTER81, 1e-15);
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().accessMonthlyPredictionAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, Load)
{
    {
        EXPECT_TRUE(CSSISpaceWeather_.isDefined());
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Load(File::Undefined()));
        EXPECT_ANY_THROW(CSSISpaceWeather::Load(File::Path(Path::Parse("/does/not/exist"))));
    }
}
