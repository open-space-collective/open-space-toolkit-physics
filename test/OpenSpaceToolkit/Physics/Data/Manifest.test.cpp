/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::filesystem::Path;
using ostk::core::filesystem::File;
using ostk::core::container::Array;

using ostk::io::URL;

using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;

using ostk::physics::data::Manifest;

class OpenSpaceToolkit_Physics_Data_Manifest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        file_ = File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Data/Manifest/manifest.json"));

        this->manifest_ = Manifest::Load(file_);
    }

    File file_ = File::Undefined();
    Manifest manifest_ = Manifest::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Data_Manifest, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << manifest_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manifest, IsDefined)
{
    {
        EXPECT_FALSE(Manifest::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manifest, GetLastUpdateTimestampFor)
{
    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2023-08-03T00:03:15.288325", DateTime::Format::ISO8601), Scale::UTC),
            manifest_.getLastUpdateTimestampFor("finals-2000A")
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manifest, FindRemoteDataUrls)
{
    const URL baseUrl = URL::Parse("https://fake.com/data");

    {
        Array<URL> expectedUrls = {
            URL::Parse("https://fake.com/data/coordinate/frame/provider/iers/finals-2000A/finals2000A.data"),
        };

        EXPECT_EQ(expectedUrls, manifest_.findRemoteDataUrls(baseUrl, "finals-2000A"));
    }

    {
        Array<URL> expectedUrls = {
            URL::Parse("https://fake.com/data/coordinate/frame/provider/iers/finals-2000A/finals2000A.data"),
        };

        EXPECT_EQ(expectedUrls, manifest_.findRemoteDataUrls(baseUrl, "f.*A"));
    }

    {
        Array<URL> expectedUrls = {
            URL::Parse("https://fake.com/data/coordinate/frame/provider/iers/bulletin-A/ser7.dat"),
        };

        EXPECT_EQ(expectedUrls, manifest_.findRemoteDataUrls(baseUrl, "bulletin-A"));
    }

    {
        Array<URL> expectedUrls = {
            URL::Parse("https://fake.com/data/environment/gravitational/earth/egm2008.egm"),
            URL::Parse("https://fake.com/data/environment/gravitational/earth/egm2008.egm.cof")
        };

        EXPECT_EQ(expectedUrls, manifest_.findRemoteDataUrls(baseUrl, "earth-gravity-EGM2008"));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manifest, Load)
{
    {
        EXPECT_NO_THROW(Manifest::Load(file_));
    }

    {
        EXPECT_ANY_THROW(Manifest::Load(File::Path(Path::Parse("/does/not/exist.json"))));
    }
}
