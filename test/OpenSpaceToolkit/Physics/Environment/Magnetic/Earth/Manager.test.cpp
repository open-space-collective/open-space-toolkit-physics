/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::ctnr::Tuple;
using ostk::core::ctnr::Array;
using ostk::core::fs::Path;
using ostk::core::fs::File;
using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::Duration;
using ostk::physics::time::DateTime;
using ostk::physics::environment::magnetic::earth::Manager;

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
    }

    void TearDown() override
    {
        // reset repository so other test suites do not use the test data
        manager_.reset();
    }

    Manager& manager_ = Manager::Get();
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
        EXPECT_EQ(Manager::Mode::Automatic, Manager::DefaultMode());
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
        EXPECT_EQ("earth", Manager::DefaultLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager, DefaultLocalRepositoryLockTimeout)
{
    {
        EXPECT_EQ(Duration::Seconds(60), Manager::DefaultLocalRepositoryLockTimeout());
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
