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
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather/SW-Last5Years.test.csv")
        );
        this->CSSISpaceWeather_ = CSSISpaceWeather::Load(file);
    }

    CSSISpaceWeather CSSISpaceWeather_ = CSSISpaceWeather::Undefined();
};

/*
TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << CSSISpaceWeather_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}
*/
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
    SUCCEED();  // See: GetObservationInterval
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, AccessPredictionInterval)
{
    SUCCEED();  // See: GetPredictionInterval
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, GetObservationInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-01-01 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2023-06-19 00:00:00"), Scale::UTC)
            ),
            CSSISpaceWeather_.getObservationInterval()
        );
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().getObservationInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, GetObservationAt)
{
    {
        const CSSISpaceWeather::Observation firstObservation =
            CSSISpaceWeather_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-01-01 12:00:00"), Scale::UTC));

        EXPECT_EQ(Date::Parse("2018-01-01", Date::Format::Standard), firstObservation.date);

        EXPECT_EQ(2515, firstObservation.BSRN);
        EXPECT_EQ(177, firstObservation.KP_SUM);
        EXPECT_EQ(10, firstObservation.AP_AVG);
        EXPECT_EQ("OBS", firstObservation.F107_DATA_TYPE);

        EXPECT_NEAR(69.1, firstObservation.F107_OBS, 1e-15);
        EXPECT_NEAR(71.4, firstObservation.F107_OBS_CENTER81, 1e-15);
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().getObservationAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, GetDailyPredictionInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2023-06-20 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2023-08-03 00:00:00"), Scale::UTC)
            ),
            CSSISpaceWeather_.getDailyPredictionInterval()
        );
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().getDailyPredictionInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, GetDailyPredictionAt)
{
    {
        const CSSISpaceWeather::DailyPrediction firstDailyPrediction =
            CSSISpaceWeather_.getDailyPredictionAt(Instant::DateTime(DateTime::Parse("2023-06-20 12:00:00"), Scale::UTC));

        EXPECT_EQ(Date::Parse("2023-06-20", Date::Format::Standard), firstDailyPrediction.date);

        EXPECT_EQ(2589, firstDailyPrediction.BSRN);
        EXPECT_EQ(167, firstDailyPrediction.KP_SUM);
        EXPECT_EQ(9, firstDailyPrediction.AP_AVG);
        EXPECT_EQ("PRD", firstDailyPrediction.F107_DATA_TYPE);

        EXPECT_NEAR(164.6, firstDailyPrediction.F107_OBS, 1e-15);
        EXPECT_NEAR(160.2, firstDailyPrediction.F107_OBS_CENTER81, 1e-15);
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().getDailyPredictionAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, GetMonthlyPredictionInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2023-09-01 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2029-01-01 00:00:00"), Scale::UTC)
            ),
            CSSISpaceWeather_.getMonthlyPredictionInterval()
        );
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().getMonthlyPredictionInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, GetMonthlyPredictionAt)
{
    {
        const CSSISpaceWeather::MonthlyPrediction firstMonthlyPrediction =
            CSSISpaceWeather_.getMonthlyPredictionAt(Instant::DateTime(DateTime::Parse("2023-09-15 12:00:00"), Scale::UTC));

        EXPECT_EQ(Date::Parse("2023-09-01", Date::Format::Standard), firstMonthlyPrediction.date);

        EXPECT_EQ(11, firstMonthlyPrediction.ND);
        EXPECT_EQ("PRM", firstMonthlyPrediction.F107_DATA_TYPE);

        EXPECT_NEAR(151.3, firstMonthlyPrediction.F107_OBS, 1e-15);
        EXPECT_NEAR(154.2, firstMonthlyPrediction.F107_OBS_CENTER81, 1e-15);
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Undefined().getMonthlyPredictionAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_CSSISpaceWeather, Load)
{
    {
        
        EXPECT_TRUE(CSSISpaceWeather_.isDefined());
        
        /*
        {
            const CSSISpaceWeather::Observation firstObservation =
                CSSISpaceWeather_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC));

            EXPECT_EQ(2018, firstObservation.year);
            EXPECT_EQ(6, firstObservation.month);
            EXPECT_EQ(22, firstObservation.day);
            EXPECT_NEAR(58291.0, firstObservation.mjd, 1e-1);
            EXPECT_NEAR(0.14461, firstObservation.x, 1e-5);
            EXPECT_NEAR(0.00009, firstObservation.xError, 1e-5);
            EXPECT_NEAR(0.43734, firstObservation.y, 1e-5);
            EXPECT_NEAR(0.00009, firstObservation.yError, 1e-5);
            EXPECT_NEAR(0.067056, firstObservation.ut1MinusUtc, 1e-6);
            EXPECT_NEAR(0.000031, firstObservation.ut1MinusUtcError, 1e-6);
        }

        {
            const CSSISpaceWeather::Observation lastObservation =
                CSSISpaceWeather_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC));

            EXPECT_EQ(2018, lastObservation.year);
            EXPECT_EQ(6, lastObservation.month);
            EXPECT_EQ(28, lastObservation.day);
            EXPECT_NEAR(58297.0, lastObservation.mjd, 1e11);
            EXPECT_NEAR(0.15609, lastObservation.x, 1e-5);
            EXPECT_NEAR(0.00009, lastObservation.xError, 1e-5);
            EXPECT_NEAR(0.43164, lastObservation.y, 1e-5);
            EXPECT_NEAR(0.00009, lastObservation.yError, 1e-5);
            EXPECT_NEAR(0.068744, lastObservation.ut1MinusUtc, 1e-6);
            EXPECT_NEAR(0.000018, lastObservation.ut1MinusUtcError, 1e-6);
        }

        {
            const CSSISpaceWeather::Observation interpolatedObservation =
                CSSISpaceWeather_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 12:00:00"), Scale::UTC));

            EXPECT_EQ(2018, interpolatedObservation.year);
            EXPECT_EQ(6, interpolatedObservation.month);
            EXPECT_EQ(22, interpolatedObservation.day);
            EXPECT_NEAR(58291.5, interpolatedObservation.mjd, 1e-1);
            EXPECT_NEAR(0.14461 + (0.14665 - 0.14461) / 2.0, interpolatedObservation.x, 1e-5);
            EXPECT_NEAR(0.00009 + (0.00009 - 0.00009) / 2.0, interpolatedObservation.xError, 1e-5);
            EXPECT_NEAR(0.43734 + (0.43659 - 0.43734) / 2.0, interpolatedObservation.y, 1e-5);
            EXPECT_NEAR(0.00009 + (0.00009 - 0.00009) / 2.0, interpolatedObservation.yError, 1e-5);
            EXPECT_NEAR(0.067056 + (0.066865 - 0.067056) / 2.0, interpolatedObservation.ut1MinusUtc, 1e-6);
            EXPECT_NEAR(0.000031 + (0.000030 - 0.000031) / 2.0, interpolatedObservation.ut1MinusUtcError, 1e-6);
        }
        */

        /*
        {
            const CSSISpaceWeather::Prediction firstPrediction =
                CSSISpaceWeather_.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC));

            EXPECT_EQ(2018, firstPrediction.year);
            EXPECT_EQ(6, firstPrediction.month);
            EXPECT_EQ(29, firstPrediction.day);
            EXPECT_NEAR(58298.0, firstPrediction.mjd, 1e-1);
            EXPECT_NEAR(0.1580, firstPrediction.x, 1e-5);
            EXPECT_NEAR(0.4308, firstPrediction.y, 1e-5);
            EXPECT_NEAR(0.06934, firstPrediction.ut1MinusUtc, 1e-6);
        }

        {
            const CSSISpaceWeather::Prediction lastPrediction =
                CSSISpaceWeather_.getPredictionAt(Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC));

            EXPECT_EQ(2019, lastPrediction.year);
            EXPECT_EQ(6, lastPrediction.month);
            EXPECT_EQ(28, lastPrediction.day);
            EXPECT_NEAR(58662.0, lastPrediction.mjd, 1e11);
            EXPECT_NEAR(0.1741, lastPrediction.x, 1e-5);
            EXPECT_NEAR(0.4422, lastPrediction.y, 1e-5);
            EXPECT_NEAR(-0.19681, lastPrediction.ut1MinusUtc, 1e-6);
        }

        {
            const CSSISpaceWeather::Prediction interpolatedPrediction =
                CSSISpaceWeather_.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 12:00:00"), Scale::UTC));

            EXPECT_EQ(2018, interpolatedPrediction.year);
            EXPECT_EQ(6, interpolatedPrediction.month);
            EXPECT_EQ(29, interpolatedPrediction.day);
            EXPECT_NEAR(58298.5, interpolatedPrediction.mjd, 1e-1);
            EXPECT_NEAR(0.1580 + (0.1599 - 0.1580) / 2.0, interpolatedPrediction.x, 1e-5);
            EXPECT_NEAR(0.4308 + (0.4301 - 0.4308) / 2.0, interpolatedPrediction.y, 1e-5);
            EXPECT_NEAR(0.06934 + (0.06994 - 0.06934) / 2.0, interpolatedPrediction.ut1MinusUtc, 1e-6);
        }
        */
    }

    {
        EXPECT_ANY_THROW(CSSISpaceWeather::Load(File::Undefined()));
        EXPECT_ANY_THROW(CSSISpaceWeather::Load(File::Path(Path::Parse("/does/not/exist"))));
    }
}

