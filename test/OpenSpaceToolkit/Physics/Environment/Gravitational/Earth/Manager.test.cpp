/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>

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

using ostk::physics::environment::gravitational::earth::Manager;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

class OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        manager_.setMode(Manager::Mode::Automatic);
        manager_.setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/"))
        );

        // cache current directory environment variables
        localRepositoryPath = std::getenv(localRepositoryVarName_);
        fullDataPath_ = std::getenv(fullDataVarName_);
        modeValue_ = std::getenv(modeVarName_);
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

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";
    const char* modeVarName_ = "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE";

    char* localRepositoryPath;
    char* fullDataPath_;
    char* modeValue_;
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, HasDataFilesForType)
{
    {
        EXPECT_TRUE(manager_.hasDataFilesForType(EarthGravitationalModel::Type::EGM2008));
        EXPECT_THROW(
            manager_.hasDataFilesForType(EarthGravitationalModel::Type::Undefined), ostk::core::error::runtime::Wrong
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, LocalDataFilesForType)
{
    {
        Array<String> expectedFiles = {
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/egm2008.egm"))
                .toString(),
            File::Path(
                Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/egm2008.egm.cof")
            )
                .toString()
        };

        Array<File> actualFiles = manager_.localDataFilesForType(EarthGravitationalModel::Type::EGM2008);

        EXPECT_EQ(actualFiles[0].toString(), expectedFiles[0]);
        EXPECT_EQ(actualFiles[1].toString(), expectedFiles[1]);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, FetchDataFilesForType)
{
    {
        // Files already exists locally
        EXPECT_THROW(
            manager_.fetchDataFilesForType(EarthGravitationalModel::Type::EGM84), ostk::core::error::RuntimeError
        );

        // No files for this exist remotely
        EXPECT_THROW(
            manager_.fetchDataFilesForType(EarthGravitationalModel::Type::Undefined), ostk::core::error::RuntimeError
        );
    }

    {
        // I/O test - fetch WGS84 files since they are very small

        Directory localRepository =
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/environment/gravitational/earth"));
        if (!localRepository.exists())
        {
            localRepository.create();
        }

        // remove any lingering lock files
        File lockFile = File::Path(localRepository.getPath() + Path::Parse(".lock"));
        if (lockFile.exists())
        {
            lockFile.remove();
        }

        manager_.setLocalRepository(localRepository);

        // Remove files if they exist for a clean test
        if (manager_.hasDataFilesForType(EarthGravitationalModel::Type::WGS84))
        {
            for (File file : manager_.localDataFilesForType(EarthGravitationalModel::Type::WGS84))
            {
                file.remove();
            }
        }

        // Fetch WGS84 files
        EXPECT_NO_THROW(manager_.fetchDataFilesForType(EarthGravitationalModel::Type::WGS84));

        // Remove one file to test partial download
        Array<File> files = manager_.localDataFilesForType(EarthGravitationalModel::Type::WGS84);

        EXPECT_TRUE(files[0].exists());
        files[0].remove();

        EXPECT_NO_THROW(manager_.fetchDataFilesForType(EarthGravitationalModel::Type::WGS84));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }
}
