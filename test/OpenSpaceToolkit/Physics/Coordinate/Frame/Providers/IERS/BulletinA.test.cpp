/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, StreamOperator)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << bulletinA << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, IsDefined)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        EXPECT_TRUE(bulletinA.isDefined());
    }

    {
        EXPECT_FALSE(BulletinA::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessReleaseDate)
{
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    SUCCEED();  // See: GetReleaseDate
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessTAIMinusUTC)
{
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    SUCCEED();  // See: GetTAIMinusUTC
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessTAIMinusUTCEpoch)
{
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    SUCCEED();  // See: GetTAIMinusUTCEpoch
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessObservationInterval)
{
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    SUCCEED();  // See: GetObservationInterval
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, AccessPredictionInterval)
{
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    SUCCEED();  // See: GetPredictionInterval
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetReleaseDate)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Date;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        EXPECT_EQ(Date(2018, 6, 28), bulletinA.getReleaseDate());
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getReleaseDate());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetTAIMinusUTC)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Duration;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        EXPECT_EQ(Duration::Seconds(37.0), bulletinA.getTAIMinusUTC());
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getTAIMinusUTC());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetTAIMinusUTCEpoch)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2017-01-01 00:00:00"), Scale::UTC), bulletinA.getTAIMinusUTCEpoch()
        );
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getTAIMinusUTCEpoch());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetObservationInterval)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC)
            ),
            bulletinA.getObservationInterval()
        );
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getObservationInterval());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetObservationAt)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        {
            const BulletinA::Observation firstObservation =
                bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC));

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
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getObservationAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetPredictionInterval)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC)
            ),
            bulletinA.getPredictionInterval()
        );
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getPredictionInterval());
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, GetPredictionAt)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        {
            const BulletinA::Prediction firstPrediction =
                bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC));

            EXPECT_EQ(2018, firstPrediction.year);
            EXPECT_EQ(6, firstPrediction.month);
            EXPECT_EQ(29, firstPrediction.day);
            EXPECT_NEAR(58298.0, firstPrediction.mjd, 1e-1);
            EXPECT_NEAR(0.1580, firstPrediction.x, 1e-5);
            EXPECT_NEAR(0.4308, firstPrediction.y, 1e-5);
            EXPECT_NEAR(0.06934, firstPrediction.ut1MinusUtc, 1e-6);
        }
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getPredictionAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_BulletinA, Load)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Date;
    using ostk::physics::time::DateTime;
    using ostk::physics::coord::frame::provider::iers::BulletinA;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")
        );

        const BulletinA bulletinA = BulletinA::Load(file);

        EXPECT_TRUE(bulletinA.isDefined());

        EXPECT_EQ(Date(2018, 6, 28), bulletinA.getReleaseDate());

        EXPECT_EQ(Duration::Seconds(37.0), bulletinA.getTAIMinusUTC());
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2017-01-01 00:00:00"), Scale::UTC), bulletinA.getTAIMinusUTCEpoch()
        );

        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC)
            ),
            bulletinA.getObservationInterval()
        );

        {
            const BulletinA::Observation firstObservation =
                bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC));

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
            const BulletinA::Observation lastObservation =
                bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC));

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
            const BulletinA::Observation interpolatedObservation =
                bulletinA.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 12:00:00"), Scale::UTC));

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

        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC)
            ),
            bulletinA.getPredictionInterval()
        );

        {
            const BulletinA::Prediction firstPrediction =
                bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC));

            EXPECT_EQ(2018, firstPrediction.year);
            EXPECT_EQ(6, firstPrediction.month);
            EXPECT_EQ(29, firstPrediction.day);
            EXPECT_NEAR(58298.0, firstPrediction.mjd, 1e-1);
            EXPECT_NEAR(0.1580, firstPrediction.x, 1e-5);
            EXPECT_NEAR(0.4308, firstPrediction.y, 1e-5);
            EXPECT_NEAR(0.06934, firstPrediction.ut1MinusUtc, 1e-6);
        }

        {
            const BulletinA::Prediction lastPrediction =
                bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC));

            EXPECT_EQ(2019, lastPrediction.year);
            EXPECT_EQ(6, lastPrediction.month);
            EXPECT_EQ(28, lastPrediction.day);
            EXPECT_NEAR(58662.0, lastPrediction.mjd, 1e11);
            EXPECT_NEAR(0.1741, lastPrediction.x, 1e-5);
            EXPECT_NEAR(0.4422, lastPrediction.y, 1e-5);
            EXPECT_NEAR(-0.19681, lastPrediction.ut1MinusUtc, 1e-6);
        }

        {
            const BulletinA::Prediction interpolatedPrediction =
                bulletinA.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 12:00:00"), Scale::UTC));

            EXPECT_EQ(2018, interpolatedPrediction.year);
            EXPECT_EQ(6, interpolatedPrediction.month);
            EXPECT_EQ(29, interpolatedPrediction.day);
            EXPECT_NEAR(58298.5, interpolatedPrediction.mjd, 1e-1);
            EXPECT_NEAR(0.1580 + (0.1599 - 0.1580) / 2.0, interpolatedPrediction.x, 1e-5);
            EXPECT_NEAR(0.4308 + (0.4301 - 0.4308) / 2.0, interpolatedPrediction.y, 1e-5);
            EXPECT_NEAR(0.06934 + (0.06994 - 0.06934) / 2.0, interpolatedPrediction.ut1MinusUtc, 1e-6);
        }
    }

    {
        EXPECT_ANY_THROW(BulletinA::Load(File::Undefined()));
        EXPECT_ANY_THROW(BulletinA::Load(File::Path(Path::Parse("/does/not/exist"))));
    }
}
