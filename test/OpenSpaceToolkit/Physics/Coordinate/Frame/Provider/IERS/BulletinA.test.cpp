/// Apache License 2.0

#include <fstream>
#include <sstream>
#include <string>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/BulletinA.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Size;
using ostk::core::type::String;

using ostk::physics::coordinate::frame::provider::iers::BulletinA;
using ostk::physics::time::Date;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Interval;
using ostk::physics::time::Scale;

class OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/bulletin-A/ser7.dat")
        );
        this->bulletinA_ = BulletinA::Load(file);
    }

    BulletinA bulletinA_ = BulletinA::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << bulletinA_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, IsDefined)
{
    {
        EXPECT_TRUE(bulletinA_.isDefined());
    }

    {
        EXPECT_FALSE(BulletinA::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, AccessReleaseDate)
{
    SUCCEED();  // See: GetReleaseDate
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, AccessTAIMinusUTC)
{
    SUCCEED();  // See: GetTAIMinusUTC
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, AccessTAIMinusUTCEpoch)
{
    SUCCEED();  // See: GetTAIMinusUTCEpoch
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, AccessObservationInterval)
{
    SUCCEED();  // See: GetObservationInterval
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, AccessPredictionInterval)
{
    SUCCEED();  // See: GetPredictionInterval
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, GetReleaseDate)
{
    {
        EXPECT_EQ(Date(2018, 6, 28), bulletinA_.getReleaseDate());
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getReleaseDate());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, GetTAIMinusUTC)
{
    {
        EXPECT_EQ(Duration::Seconds(37.0), bulletinA_.getTAIMinusUTC());
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getTAIMinusUTC());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, GetTAIMinusUTCEpoch)
{
    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2017-01-01 00:00:00"), Scale::UTC), bulletinA_.getTAIMinusUTCEpoch()
        );
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getTAIMinusUTCEpoch());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, GetObservationInterval)
{
    {
        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC),
                Interval::Type::HalfOpenRight
            ),
            bulletinA_.getObservationInterval()
        );
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getObservationInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, IntervalOverlap)
{
    const Interval observationInterval = bulletinA_.getObservationInterval();
    const Interval predictionInterval = bulletinA_.getPredictionInterval();

    {
        EXPECT_EQ(observationInterval.accessEnd(), predictionInterval.accessStart());
    }

    {
        EXPECT_FALSE(observationInterval.contains(predictionInterval.accessStart()));
    }

    {
        EXPECT_TRUE(predictionInterval.contains(observationInterval.accessEnd()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, GetObservationAt)
{
    {
        const BulletinA::Observation firstObservation =
            bulletinA_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC));

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
        EXPECT_NO_THROW(
            bulletinA_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-28 12:00:00"), Scale::UTC))
        );
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getObservationAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, GetPredictionInterval)
{
    {
        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC)
            ),
            bulletinA_.getPredictionInterval()
        );
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getPredictionInterval());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, GetPredictionAt)
{
    {
        const BulletinA::Prediction firstPrediction =
            bulletinA_.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC));

        EXPECT_EQ(2018, firstPrediction.year);
        EXPECT_EQ(6, firstPrediction.month);
        EXPECT_EQ(29, firstPrediction.day);
        EXPECT_NEAR(58298.0, firstPrediction.mjd, 1e-1);
        EXPECT_NEAR(0.1580, firstPrediction.x, 1e-5);
        EXPECT_NEAR(0.4308, firstPrediction.y, 1e-5);
        EXPECT_NEAR(0.06934, firstPrediction.ut1MinusUtc, 1e-6);
    }

    {
        EXPECT_ANY_THROW(BulletinA::Undefined().getPredictionAt(
            Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC)
        ));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, Load_AbbreviatedMonthNames)
{
    // Some bulletins abbreviate month names, e.g. "Beginning 1 Jan 2017:" in Vol. XXX No. 001 (5 January 2017).
    // Write copies of the test bulletin with abbreviated month names and check they load.

    const File file =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/bulletin-A/ser7.dat")
        );

    std::string content;

    {
        std::ifstream fileStream {std::string(file.getPath().toString())};
        std::stringstream contentStream;
        contentStream << fileStream.rdbuf();
        content = contentStream.str();
    }

    const auto replace = [](std::string aString, const std::string& aSubstring, const std::string& aReplacement
                         ) -> std::string
    {
        const std::size_t position = aString.find(aSubstring);

        EXPECT_NE(std::string::npos, position) << aSubstring;

        return (position != std::string::npos) ? aString.replace(position, aSubstring.size(), aReplacement) : aString;
    };

    Directory temporaryDirectory = Directory::Path(Path::Parse("/tmp/ostk-physics-test-bulletin-a"));

    if (temporaryDirectory.exists())
    {
        temporaryDirectory.remove();
    }

    temporaryDirectory.create();

    const File abbreviatedFile = File::Path(temporaryDirectory.getPath() + Path::Parse("ser7.dat"));

    const auto loadWith = [&](const std::string& aContent) -> BulletinA
    {
        {
            std::ofstream fileStream {std::string(abbreviatedFile.getPath().toString())};
            fileStream << aContent;
        }

        return BulletinA::Load(abbreviatedFile);
    };

    {
        const Array<String> monthAbbreviations = {
            "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
        };

        for (Size monthIndex = 0; monthIndex < monthAbbreviations.getSize(); ++monthIndex)
        {
            const std::string beginningLine = "Beginning 1 " + std::string(monthAbbreviations[monthIndex]) + " 2017:";

            const BulletinA bulletinA = loadWith(replace(content, "Beginning 1 January 2017:", beginningLine));

            EXPECT_EQ(
                Instant::DateTime(DateTime(2017, monthIndex + 1, 1, 0, 0, 0), Scale::UTC),
                bulletinA.getTAIMinusUTCEpoch()
            ) << beginningLine;
        }
    }

    {
        const BulletinA bulletinA = loadWith(replace(content, "28 June 2018 ", "28 Jun 2018  "));

        EXPECT_EQ(Date(2018, 6, 28), bulletinA.getReleaseDate());
    }

    {
        EXPECT_ANY_THROW(loadWith(replace(content, "Beginning 1 January 2017:", "Beginning 1 Janvier 2017:")));
    }

    temporaryDirectory.remove();
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_BulletinA, Load)
{
    {
        EXPECT_TRUE(bulletinA_.isDefined());

        EXPECT_EQ(Date(2018, 6, 28), bulletinA_.getReleaseDate());

        EXPECT_EQ(Duration::Seconds(37.0), bulletinA_.getTAIMinusUTC());
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2017-01-01 00:00:00"), Scale::UTC), bulletinA_.getTAIMinusUTCEpoch()
        );

        EXPECT_EQ(
            Interval(
                Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC),
                Interval::Type::HalfOpenRight
            ),
            bulletinA_.getObservationInterval()
        );

        {
            const BulletinA::Observation firstObservation =
                bulletinA_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 00:00:00"), Scale::UTC));

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
                bulletinA_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-28 00:00:00"), Scale::UTC));

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
                bulletinA_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-22 12:00:00"), Scale::UTC));

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

        {
            const BulletinA::Observation extrapolatedObservation =
                bulletinA_.getObservationAt(Instant::DateTime(DateTime::Parse("2018-06-28 12:00:00"), Scale::UTC));

            EXPECT_EQ(2018, extrapolatedObservation.year);
            EXPECT_EQ(6, extrapolatedObservation.month);
            EXPECT_EQ(28, extrapolatedObservation.day);
            EXPECT_NEAR(58297.5, extrapolatedObservation.mjd, 1e-1);
            EXPECT_NEAR(0.15407 + (0.15609 - 0.15407) * 1.5, extrapolatedObservation.x, 1e-5);
            EXPECT_NEAR(0.00009 + (0.00009 - 0.00009) * 1.5, extrapolatedObservation.xError, 1e-5);
            EXPECT_NEAR(0.43267 + (0.43164 - 0.43267) * 1.5, extrapolatedObservation.y, 1e-5);
            EXPECT_NEAR(0.00009 + (0.00009 - 0.00009) * 1.5, extrapolatedObservation.yError, 1e-5);
            EXPECT_NEAR(0.068107 + (0.068744 - 0.068107) * 1.5, extrapolatedObservation.ut1MinusUtc, 1e-6);
            EXPECT_NEAR(0.000019 + (0.000018 - 0.000019) * 1.5, extrapolatedObservation.ut1MinusUtcError, 1e-6);
        }

        EXPECT_EQ(
            Interval::Closed(
                Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC),
                Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC)
            ),
            bulletinA_.getPredictionInterval()
        );

        {
            const BulletinA::Prediction firstPrediction =
                bulletinA_.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 00:00:00"), Scale::UTC));

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
                bulletinA_.getPredictionAt(Instant::DateTime(DateTime::Parse("2019-06-28 00:00:00"), Scale::UTC));

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
                bulletinA_.getPredictionAt(Instant::DateTime(DateTime::Parse("2018-06-29 12:00:00"), Scale::UTC));

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
