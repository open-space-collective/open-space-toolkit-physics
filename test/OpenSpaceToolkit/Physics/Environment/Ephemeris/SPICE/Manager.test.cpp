/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Tuple;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::io::URL;

using ostk::physics::environment::ephemeris::spice::Engine;
using ostk::physics::environment::ephemeris::spice::Kernel;
using ostk::physics::environment::ephemeris::spice::Manager;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

class OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        manager_.setLocalRepository(
            Directory::Path(Path::Parse("test/OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/"))
        );

        // cache current directory environment variables
        localRepositoryPath = std::getenv(localRepositoryVarName_);
        fullDataPath_ = std::getenv(fullDataVarName_);
        modeValue_ = std::getenv(modeVarName_);
    }

    virtual void TearDown()
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

        if (modeValue_)
        {
            setenv(modeVarName_, modeValue_, true);
        }
        else
        {
            unsetenv(modeVarName_);
        }

        // reset repository so other test suites do not use the test data
        manager_.reset();
    }

    Manager& manager_ = Manager::Get();

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";
    const char* modeVarName_ = "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_ENGINE_MODE";

    char* localRepositoryPath;
    char* fullDataPath_;
    char* modeValue_;
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager, FetchKernel)
{
    // make subdir for test
    manager_.setLocalRepository(Directory::Path(
        Path::Parse("/app/.open-space-toolkit/physics/environment/ephemeris/spice/") + Path::Parse("FetchKernelTest/")
    ));

    {
        File kernelFile = File::Path(manager_.getLocalRepository().getPath() + Path::Parse("latest_leapseconds.tls"));

        EXPECT_FALSE(kernelFile.exists());

        Kernel kernel = Kernel(Kernel::Type::LSK, kernelFile);

        EXPECT_NO_THROW(manager_.fetchKernel(kernel));

        EXPECT_TRUE(kernelFile.exists());

        // already exists
        EXPECT_THROW(manager_.fetchKernel(kernel), ostk::core::error::RuntimeError);
    }

    manager_.getLocalRepository().remove();
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager, FetchMatchingKernels)
{
    // make subdir for test
    manager_.setLocalRepository(Directory::Path(
        Path::Parse("/app/.open-space-toolkit/physics/environment/ephemeris/spice/") +
        Path::Parse("FetchMatchingKernelsTest/")
    ));
    if (manager_.getLocalRepository().exists())
    {
        manager_.getLocalRepository().remove();
    }
    manager_.getLocalRepository().create();

    {
        File expectedKernelFile =
            File::Path(manager_.getLocalRepository().getPath() + Path::Parse("latest_leapseconds.tls"));

        EXPECT_FALSE(expectedKernelFile.exists());

        EXPECT_NO_THROW(manager_.fetchMatchingKernels(".*leapseconds.*"));

        EXPECT_TRUE(expectedKernelFile.exists());
    }

    manager_.getLocalRepository().remove();
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager, FindKernel)
{
    // make subdir for test
    manager_.setLocalRepository(Directory::Path(
        Path::Parse("/app/.open-space-toolkit/physics/environment/ephemeris/spice/") + Path::Parse("FindKernelTest/")
    ));

    if (manager_.getLocalRepository().exists())
    {
        manager_.getLocalRepository().remove();
    }
    manager_.getLocalRepository().create();

    {
        File expectedKernelFile =
            File::Path(manager_.getLocalRepository().getPath() + Path::Parse("latest_leapseconds.tls"));

        EXPECT_FALSE(expectedKernelFile.exists());

        Kernel kernel = Kernel(Kernel::Type::LSK, expectedKernelFile);

        // kernel file doesn't exist, so it should fetch
        Kernel fetchedKernel = manager_.findKernel(".*leapseconds.*");
        EXPECT_TRUE(fetchedKernel.isDefined());
        EXPECT_TRUE(fetchedKernel.getFile().exists());
    }

    {
        // check that it finds one that is already there
        File expectedKernelFile =
            File::Path(manager_.getLocalRepository().getPath() + Path::Parse("latest_leapseconds.tls"));

        EXPECT_TRUE(expectedKernelFile.exists());

        Kernel foundKernel = manager_.findKernel(".*leapseconds.*");

        EXPECT_TRUE(foundKernel.isDefined());
        EXPECT_EQ(
            expectedKernelFile.getPath().getNormalizedPath(), foundKernel.getFile().getPath().getNormalizedPath()
        );
    }

    {
        // check that it fetches one that is not there, earth_200101_[0-9]*_predict\\.bpc
        File expectedKernelFile =
            File::Path(manager_.getLocalRepository().getPath() + Path::Parse("earth_200101_990827_predict.bpc"));

        EXPECT_FALSE(expectedKernelFile.exists());

        Kernel fetchedKernel = manager_.findKernel("earth_200101_[0-9]*_predict\\.bpc");
        EXPECT_TRUE(fetchedKernel.isDefined());
        EXPECT_TRUE(fetchedKernel.getFile().exists());
    }

    manager_.getLocalRepository().remove();
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager, FindKernelPaths)
{
    // make subdir for test
    manager_.setLocalRepository(Directory::Path(
        Path::Parse("/app/.open-space-toolkit/physics/environment/ephemeris/spice/") +
        Path::Parse("FindKernelPathsTest/")
    ));

    if (manager_.getLocalRepository().exists())
    {
        manager_.getLocalRepository().remove();
    }
    manager_.getLocalRepository().create();

    {
        // Create test kernel files matching the patterns from Engine.cpp
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("latest_leapseconds.tls")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("de430.bsp")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("pck00010.tpc")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("pck00011.tpc")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("earth_assoc_itrf93.tf")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("earth_200101_990827_predict.bpc")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("earth_2025_250826_2125_predict.bpc"))
            .create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("moon_080317.tf")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("moon_assoc_me.tf")).create();
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("moon_pa_de421_1900-2050.bpc")).create();
        // Add a non-matching file to ensure it's not included
        File::Path(manager_.getLocalRepository().getPath() + Path::Parse("other_file.txt")).create();
    }

    {
        // Test exact match: latest_leapseconds.tls
        Array<Path> paths = manager_.findKernelPaths("latest_leapseconds.tls");
        EXPECT_EQ(paths.getSize(), 1);
        EXPECT_TRUE(paths.accessFirst().toString().find("latest_leapseconds.tls") != String::npos);
    }

    {
        // Test exact match: de430.bsp
        Array<Path> paths = manager_.findKernelPaths("de430.bsp");
        EXPECT_EQ(paths.getSize(), 1);
        EXPECT_TRUE(paths.accessFirst().toString().find("de430.bsp") != String::npos);
    }

    {
        // Test regex pattern: pck[0-9]*\\.tpc (should match multiple files)
        Array<Path> paths = manager_.findKernelPaths("pck[0-9]*\\.tpc");
        EXPECT_GE(paths.getSize(), 2);
        bool foundPck00010 = false;
        bool foundPck00011 = false;
        for (const auto& path : paths)
        {
            if (path.toString().find("pck00010.tpc") != String::npos)
            {
                foundPck00010 = true;
            }
            if (path.toString().find("pck00011.tpc") != String::npos)
            {
                foundPck00011 = true;
            }
        }
        EXPECT_TRUE(foundPck00010);
        EXPECT_TRUE(foundPck00011);
    }

    {
        // Test exact match: earth_assoc_itrf93.tf
        Array<Path> paths = manager_.findKernelPaths("earth_assoc_itrf93.tf");
        EXPECT_EQ(paths.getSize(), 1);
        EXPECT_TRUE(paths.accessFirst().toString().find("earth_assoc_itrf93.tf") != String::npos);
    }

    {
        // Test regex pattern: earth_.*_predict\\.bpc (should match multiple files)
        Array<Path> paths = manager_.findKernelPaths("earth_.*_predict\\.bpc");
        EXPECT_GE(paths.getSize(), 2);
        bool foundEarth200101 = false;
        bool foundEarth200102 = false;
        for (const auto& path : paths)
        {
            if (path.toString().find("earth_200101_990827_predict.bpc") != String::npos)
            {
                foundEarth200101 = true;
            }
            if (path.toString().find("earth_2025_250826_2125_predict.bpc") != String::npos)
            {
                foundEarth200102 = true;
            }
        }
        EXPECT_TRUE(foundEarth200101);
        EXPECT_TRUE(foundEarth200102);
    }

    {
        // Test exact match: moon_080317.tf
        Array<Path> paths = manager_.findKernelPaths("moon_080317.tf");
        EXPECT_EQ(paths.getSize(), 1);
        EXPECT_TRUE(paths.accessFirst().toString().find("moon_080317.tf") != String::npos);
    }

    {
        // Test exact match: moon_assoc_me.tf
        Array<Path> paths = manager_.findKernelPaths("moon_assoc_me.tf");
        EXPECT_EQ(paths.getSize(), 1);
        EXPECT_TRUE(paths.accessFirst().toString().find("moon_assoc_me.tf") != String::npos);
    }

    {
        // Test exact match: moon_pa_de421_1900-2050.bpc
        Array<Path> paths = manager_.findKernelPaths("moon_pa_de421_1900-2050.bpc");
        EXPECT_EQ(paths.getSize(), 1);
        EXPECT_TRUE(paths.accessFirst().toString().find("moon_pa_de421_1900-2050.bpc") != String::npos);
    }

    {
        // Test non-matching pattern (should return empty)
        Array<Path> paths = manager_.findKernelPaths("nonexistent_file\\.txt");
        EXPECT_EQ(paths.getSize(), 0);
    }

    {
        // Test regex pattern that matches other_file.txt
        Array<Path> paths = manager_.findKernelPaths(".*\\.txt");
        EXPECT_GE(paths.getSize(), 1);
        bool foundOtherFile = false;
        for (const auto& path : paths)
        {
            if (path.toString().find("other_file.txt") != String::npos)
            {
                foundOtherFile = true;
            }
        }
        EXPECT_TRUE(foundOtherFile);
    }

    manager_.getLocalRepository().remove();
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }
}
