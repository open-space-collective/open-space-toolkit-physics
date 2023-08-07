/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::fs::File;
using ostk::core::fs::Path;

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;

using ostk::physics::data::Manager;
using ostk::physics::data::Manifest;

class OpenSpaceToolkit_Physics_Data_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        const File manifestFile =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Data/Manifest/manifest.json"));

        manifest_ = Manifest::Load(manifestFile);
    }

    Manifest manifest_ = Manifest::Undefined();

    Manager& manager_ = Manager::Get();
};

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, getLastUpdateTimestampFor)
{
    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2023-08-04T12:02:17.028701"), Scale::UTC),
            manager_.getLastUpdateTimestampFor("bulletin-A")
        );
    }

    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2023-08-03T00:03:15.288325"), Scale::UTC),
            manager_.getLastUpdateTimestampFor("finals-2000A")
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, getRemoteUrl)
{
    {
        EXPECT_EQ(
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data/",
            manager_.getRemoteUrl().toString()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, loadManifest_)
{
    {
        manager_.reset();

        EXPECT_FALSE(manager_.getManifest().isDefined());

        manager_.loadManifest(manifest_);

        EXPECT_TRUE(manager_.getManifest().isDefined());
    }
}
