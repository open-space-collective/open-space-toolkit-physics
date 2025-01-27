/// Apache License 2.0

#include <gmock/gmock.h>

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;

using ostk::io::URL;

using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

using ostk::physics::data::Manager;
using ostk::physics::data::Manifest;

class TestManager : public Manager
{
    // Create a manager with no I/O so that we can force usage of the local testing manifest
   public:
    MOCK_METHOD(File, fetchLatestManifestFile_, (), (const));
};

class OpenSpaceToolkit_Physics_Data_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        manifest_ = Manifest::Load(manifestFile_);
        manager_.loadManifest(manifest_);
        managerNoIO_.loadManifest(manifest_);

        manager_.setRemoteUrl(
            URL::Parse("https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data")
        );

        // cache current directory environment variables
        localRepositoryPath = std::getenv(localRepositoryVarName_);
        fullDataPath_ = std::getenv(fullDataVarName_);
    }

    void TearDown() override
    {
        // reset cached environment variables
        if (fullDataPath_)
        {
            setenv(fullDataVarName_, fullDataPath_, true);
        }
        else
        {
            unsetenv(fullDataVarName_);
        }

        if (localRepositoryPath)
        {
            setenv(localRepositoryVarName_, localRepositoryPath, true);
        }
        else
        {
            unsetenv(localRepositoryVarName_);
        }

        // reset repository so other test suites do not use the test manifest
        // in /app/test/OpenSpaceToolkit/Physics/Data/Manifest/
        manager_.reset();
    }

    const File manifestFile_ =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Data/Manifest/manifest.json"));

    Manifest manifest_ = Manifest::Undefined();

    Manager& manager_ = Manager::Get();
    TestManager managerNoIO_ = TestManager();

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";

    char* localRepositoryPath;
    char* fullDataPath_;
};

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, GetLastUpdateTimestampFor)
{
    // Mock the fetching function to do nothing and just return the test file
    EXPECT_CALL(managerNoIO_, fetchLatestManifestFile_()).WillRepeatedly(testing::Return(manifestFile_));

    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2023-08-04T12:02:17.028701"), Scale::UTC),
            managerNoIO_.getLastUpdateTimestampFor("bulletin-A")
        );
    }

    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2023-08-03T00:03:15.288325"), Scale::UTC),
            managerNoIO_.getLastUpdateTimestampFor("finals-2000A")
        );
    }

    // Manual mode
    {
        // no manifest file loaded or existing
        {
            managerNoIO_.reset();
            managerNoIO_.setMode(Manager::Mode::Manual);
            EXPECT_FALSE(managerNoIO_.getManifest().isDefined());

            Directory tempDirectory =
                Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Data/Manifest/Test"));
            managerNoIO_.setLocalRepository(tempDirectory);

            EXPECT_THROW(
                {
                    try
                    {
                        managerNoIO_.getLastUpdateTimestampFor("bulletin-A");
                    }
                    catch (const ostk::core::error::RuntimeError& e)
                    {
                        EXPECT_EQ(
                            "No manifest file loaded and no manifest file found in local repository. Manager mode is "
                            "Manual.",
                            e.getMessage()
                        );
                        throw;
                    }
                },
                ostk::core::error::RuntimeError
            );

            tempDirectory.remove();
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, GetLastUpdateTimestampFor_Skipped)
{
    GTEST_SKIP() << "Skipping test as in the CI the file is modified when copied and so the while the test passes "
                    "locally it does not in CI.";

    // Mock the fetching function to do nothing and just return the test file
    EXPECT_CALL(managerNoIO_, fetchLatestManifestFile_()).WillRepeatedly(testing::Return(manifestFile_));

    // manifest exists but is old
    {
        managerNoIO_.loadManifest(manifest_);
        managerNoIO_.setMode(Manager::Mode::Manual);
        EXPECT_TRUE(managerNoIO_.getManifest().isDefined());

        Directory tempDirectory = Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Data/Manifest/Test"));
        managerNoIO_.setLocalRepository(tempDirectory);

        EXPECT_THROW(
            {
                try
                {
                    managerNoIO_.getLastUpdateTimestampFor("bulletin-A");
                }
                catch (const ostk::core::error::RuntimeError& e)
                {
                    EXPECT_EQ("Manifest file is old. Cannot fetch as manager mode is Manual.", e.getMessage());
                    throw;
                }
            },
            ostk::core::error::RuntimeError
        );

        tempDirectory.remove();
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, GetRemoteUrl)
{
    {
        EXPECT_EQ(
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data",
            manager_.getRemoteUrl().toString()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, SetRemoteUrl)
{
    {
        EXPECT_EQ(
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data",
            manager_.getRemoteUrl().toString()
        );

        manager_.setRemoteUrl(URL::Parse("http://fake.com"));

        EXPECT_EQ("http://fake.com", manager_.getRemoteUrl().toString());

        EXPECT_ANY_THROW(manager_.setRemoteUrl(URL::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, DefaultRemoteUrl)
{
    {
        EXPECT_EQ(
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data/",
            Manager::DefaultRemoteUrl().toString()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, FindRemoteDataUrls)
{
    {
        Array<URL> urls = manager_.findRemoteDataUrls(".*EGM2008");

        EXPECT_EQ(
            urls[0],
            URL::Parse(
                "https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data/environment/"
                "gravitational/earth/egm2008.egm"
            )
        );
        EXPECT_EQ(
            urls[1],
            URL::Parse(
                "https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data/environment/"
                "gravitational/earth/egm2008.egm.cof"
            )
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, LoadManifest)
{
    {
        manager_.reset();

        EXPECT_FALSE(manager_.getManifest().isDefined());

        manager_.loadManifest(manifest_);

        EXPECT_TRUE(manager_.getManifest().isDefined());

        EXPECT_ANY_THROW(manager_.loadManifest(Manifest::Undefined()));
    }
}
