/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>

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

using ostk::physics::environment::magnetic::earth::Manager;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;

class OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        manager_.setMode(Manager::Mode::Automatic);
        manager_.setLocalRepository(
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/"))
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

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";
    const char* modeVarName_ = "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_MODE";

    char* localRepositoryPath;
    char* fullDataPath_;
    char* modeValue_;
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, GetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, SetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());

        manager_.setMode(Manager::Mode::Manual);

        EXPECT_EQ(Manager::Mode::Manual, manager_.getMode());

        manager_.setMode(Manager::Mode::Automatic);

        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, DefaultMode)
{
    {
        unsetenv(modeVarName_);
        Manager::Get().reset();
        EXPECT_EQ(Manager::Mode::Automatic, Manager::Get().getMode());
    }
    {
        setenv(modeVarName_, "SuperUltraAutomatic", true);
        EXPECT_THROW(Manager::Get().reset();, ostk::core::error::runtime::Wrong);
    }
    {
        setenv(modeVarName_, "Automatic", true);
        Manager::Get().reset();
        EXPECT_EQ(Manager::Mode::Automatic, Manager::Get().getMode());
    }
    {
        setenv(modeVarName_, "Manual", true);
        Manager::Get().reset();
        EXPECT_EQ(Manager::Mode::Manual, Manager::Get().getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, HasDataFilesForType)
{
    {
        EXPECT_TRUE(manager_.hasDataFilesForType(EarthMagneticModel::Type::EMM2010));
        EXPECT_THROW(
            manager_.hasDataFilesForType(EarthMagneticModel::Type::Undefined), ostk::core::error::runtime::Wrong
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, LocalDataFilesForType)
{
    {
        Array<String> expectedFiles = {
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/emm2010.wmm"))
                .toString(),
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/emm2010.wmm.cof"))
                .toString()
        };

        Array<File> actualFiles = manager_.localDataFilesForType(EarthMagneticModel::Type::EMM2010);

        EXPECT_EQ(actualFiles[0].toString(), expectedFiles[0]);
        EXPECT_EQ(actualFiles[1].toString(), expectedFiles[1]);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, GetLocalRepository)
{
    {
        EXPECT_EQ("Earth", manager_.getLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, SetLocalRepository)
{
    {
        EXPECT_EQ("Earth", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/environment/magnetic/earth"))
        );

        EXPECT_EQ("earth", manager_.getLocalRepository().getName());

        EXPECT_THROW(manager_.setLocalRepository(Directory::Undefined()), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, Reset)
{
    {
        EXPECT_EQ("Earth", manager_.getLocalRepository().getName());
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());

        manager_.setLocalRepository(Directory::Path(Path::Parse("/tmp")));
        manager_.setMode(Manager::Mode::Manual);

        EXPECT_EQ("tmp", manager_.getLocalRepository().getName());
        EXPECT_EQ(Manager::Mode::Manual, manager_.getMode());

        manager_.reset();

        EXPECT_EQ("earth", manager_.getLocalRepository().getName());
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, DefaultLocalRepository)
{
    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        Manager::Get().reset();

        EXPECT_EQ(
            Manager::Get().getLocalRepository(),
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/environment/magnetic/earth"))
        );
    }

    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        setenv(fullDataVarName_, "/tmp", true);

        Manager::Get().reset();

        EXPECT_EQ(Manager::Get().getLocalRepository(), Directory::Path(Path::Parse("/tmp/environment/magnetic/earth")));
    }

    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        setenv(fullDataVarName_, "/tmp", true);
        setenv(localRepositoryVarName_, "/local_override", true);

        Manager::Get().reset();

        EXPECT_EQ(Manager::Get().getLocalRepository(), Directory::Path(Path::Parse("/local_override")));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, FetchDataFilesForType)
{
    {
        // Files already exists locally
        EXPECT_THROW(
            manager_.fetchDataFilesForType(EarthMagneticModel::Type::EMM2010), ostk::core::error::RuntimeError
        );

        // No files for this exist remotely
        EXPECT_THROW(
            manager_.fetchDataFilesForType(EarthMagneticModel::Type::Undefined), ostk::core::error::RuntimeError
        );
    }

    {
        // I/O test - fetch WMM2010 files since they are very small

        Directory localRepository =
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/environment/magnetic/earth"));
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
        if (manager_.hasDataFilesForType(EarthMagneticModel::Type::WMM2010))
        {
            for (File file : manager_.localDataFilesForType(EarthMagneticModel::Type::WMM2010))
            {
                file.remove();
            }
        }

        // Fetch WMM2010 files
        EXPECT_NO_THROW(manager_.fetchDataFilesForType(EarthMagneticModel::Type::WMM2010));

        // Remove one file to test partial download
        Array<File> files = manager_.localDataFilesForType(EarthMagneticModel::Type::WMM2010);

        EXPECT_TRUE(files[0].exists());
        files[0].remove();

        EXPECT_NO_THROW(manager_.fetchDataFilesForType(EarthMagneticModel::Type::WMM2010));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }
}
