/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Engine.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Manager.hpp>

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
using ostk::physics::env::ephem::spice::Kernel;
using ostk::physics::env::ephem::spice::Engine;
using ostk::physics::env::ephem::spice::Manager;

class OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        manager_.setLocalRepository(
            Directory::Path(Path::Parse("test/OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/"))
        );
    }

    Manager& manager_ = Manager::Get();
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager, GetLocalRepository)
{
    {
        EXPECT_EQ("SPICE", manager_.getLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager, SetLocalRepository)
{
    {
        EXPECT_EQ("SPICE", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/environment/ephemerides/spice"))
        );

        EXPECT_EQ("spice", manager_.getLocalRepository().getName());

        EXPECT_THROW(manager_.setLocalRepository(Directory::Undefined()), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager, DefaultLocalRepository)
{
    {
        EXPECT_EQ("spice", Manager::DefaultLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager, FetchKernel)
{
    // clear all kernels to reset test
    manager_.setLocalRepository(Manager::DefaultLocalRepository());
    if (manager_.getLocalRepository().exists())
    {
        manager_.getLocalRepository().remove();
    }

    {
        File kernelFile = File::Path(manager_.getLocalRepository().getPath() + Path::Parse("latest_leapseconds.tls"));

        EXPECT_FALSE(kernelFile.exists());

        Kernel kernel = Kernel(Kernel::Type::LSK, kernelFile);

        EXPECT_NO_THROW(manager_.fetchKernel(kernel));

        EXPECT_TRUE(kernelFile.exists());

        // already exists
        EXPECT_THROW(manager_.fetchKernel(kernel), ostk::core::error::RuntimeError);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager, FetchMatchingKernels)
{
    // make subdir for test
    manager_.setLocalRepository(
        Directory::Path(Manager::DefaultLocalRepository().getPath() + Path::Parse("FetchMatchingKernelsTest/"))
    );
    manager_.getLocalRepository().create();

    {
        File expectedKernelFile =
            File::Path(manager_.getLocalRepository().getPath() + Path::Parse("latest_leapseconds.tls"));

        EXPECT_FALSE(expectedKernelFile.exists());

        EXPECT_NO_THROW(manager_.fetchMatchingKernels(std::regex(".*leapseconds.*")));

        EXPECT_TRUE(expectedKernelFile.exists());
    }

    manager_.getLocalRepository().remove();
    manager_.setLocalRepository(Manager::DefaultLocalRepository());
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager, FindKernel)
{
    // make subdir for test
    manager_.setLocalRepository(
        Directory::Path(Manager::DefaultLocalRepository().getPath() + Path::Parse("FindKernelTest/"))
    );
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

    manager_.getLocalRepository().remove();
    manager_.setLocalRepository(Manager::DefaultLocalRepository());
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }
}
