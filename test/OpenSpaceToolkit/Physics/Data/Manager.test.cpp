/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::fs::File;
using ostk::core::fs::Path;
using ostk::core::fs::Directory;
using ostk::core::ctnr::Array;

using ostk::io::URL;

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
        manifest_ = Manifest::Load(manifestFile_);
        manager_.loadManifest(manifest_);

        manager_.setRemoteUrl(
            URL::Parse("https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data")
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

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";

    char* localRepositoryPath;
    char* fullDataPath_;
};

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, GetLastUpdateTimestampFor)
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

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, GetRemoteUrl)
{
    {
        EXPECT_EQ(
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data",
            manager_.getRemoteUrl().toString()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, setRemoteUrl)
{
    {
        EXPECT_EQ(
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data",
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
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data/",
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
            URL::Parse("https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data/environment/"
                       "gravitational/earth/egm2008.egm")
        );
        EXPECT_EQ(
            urls[1],
            URL::Parse("https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data/environment/"
                       "gravitational/earth/egm2008.egm.cof")
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, GetManifestRepository)
{
    {
        EXPECT_EQ("data", manager_.getManifestRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, SetManifestRepository)
{
    {
        EXPECT_EQ("data", manager_.getManifestRepository().getName());

        manager_.setManifestRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager_.getManifestRepository().getName());

        manager_.setManifestRepository(Directory::Path(Path::Parse("./.open-space-toolkit/physics/data")));

        EXPECT_EQ("data", manager_.getManifestRepository().getName());

        EXPECT_ANY_THROW(manager_.setManifestRepository(Directory::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, DefaultManifestRepository)
{
    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        EXPECT_EQ(
            Manager::DefaultManifestRepository(), Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/"))
        );
    }

    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        setenv(fullDataVarName_, "/tmp", true);

        EXPECT_EQ(Manager::DefaultManifestRepository(), Directory::Path(Path::Parse("/tmp")));
    }

    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        setenv(fullDataVarName_, "/tmp", true);
        setenv(localRepositoryVarName_, "/local_override", true);

        EXPECT_EQ(Manager::DefaultManifestRepository(), Directory::Path(Path::Parse("/local_override")));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Data_Manager, loadManifest_)
{
    {
        manager_.reset();

        EXPECT_FALSE(manager_.getManifest().isDefined());

        manager_.loadManifest(manifest_);

        EXPECT_TRUE(manager_.getManifest().isDefined());

        EXPECT_ANY_THROW(manager_.loadManifest(Manifest::Undefined()));
    }
}
