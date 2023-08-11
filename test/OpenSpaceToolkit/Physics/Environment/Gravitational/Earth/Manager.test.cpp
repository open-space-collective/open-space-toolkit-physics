/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/Manager.hpp>

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
using ostk::physics::environment::gravitational::earth::Manager;

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
    }

    Manager& manager_ = Manager::Get();
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, GetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, SetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());

        manager_.setMode(Manager::Mode::Manual);

        EXPECT_EQ(Manager::Mode::Manual, manager_.getMode());

        manager_.setMode(Manager::Mode::Automatic);

        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, DefaultMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, Manager::DefaultMode());
    }
}

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
            File::Path(Path::Parse("test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/egm2008.egm"))
                .toString(),
            File::Path(Path::Parse("test/OpenSpaceToolkit/Physics/Environment/Gravitational/Earth/egm2008.egm.cof"))
                .toString()
        };

        Array<File> actualFiles = manager_.localDataFilesForType(EarthGravitationalModel::Type::EGM2008);

        EXPECT_EQ(actualFiles[0].toString(), expectedFiles[0]);
        EXPECT_EQ(actualFiles[1].toString(), expectedFiles[1]);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, GetLocalRepository)
{
    {
        EXPECT_EQ("Earth", manager_.getLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, SetLocalRepository)
{
    {
        EXPECT_EQ("Earth", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/environment/gravitational/earth"))
        );

        EXPECT_EQ("earth", manager_.getLocalRepository().getName());

        EXPECT_THROW(manager_.setLocalRepository(Directory::Undefined()), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, DefaultLocalRepository)
{
    {
        EXPECT_EQ("earth", Manager::DefaultLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager, DefaultLocalRepositoryLockTimeout)
{
    {
        EXPECT_EQ(Duration::Seconds(60), Manager::DefaultLocalRepositoryLockTimeout());
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
