/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

#include <Global.test.hpp>

using ostk::core::fs::Path;
using ostk::core::fs::File;

using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;

using ostk::physics::data::Manifest;

class OpenSpaceToolkit_Physics_Data_Manifest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        const File manifestFile =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Data/Manifest/manifest.json"));

        this->manifest_ = Manifest::Load(manifestFile);
    }

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
            Instant::DateTime(DateTime::Parse("2023-07-24T00:00:00.000", DateTime::Format::ISO8601), Scale::UTC),
            manifest_.getLastUpdateTimestampFor("space_weather_CSSI")
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manifest, Load)
{
    {
        const File manifestFile =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Data/Manifest/manifest.json"));
        EXPECT_NO_THROW(Manifest::Load(manifestFile));
    }
}
