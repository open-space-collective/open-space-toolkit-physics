// test/OpenSpaceToolkit/Physics/Manager.test.cpp

#include <gtest/gtest.h>

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>

#include <OpenSpaceToolkit/Physics/Manager.hpp>

using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Integer;
using ostk::core::type::String;

using ostk::physics::Manager;
using ostk::physics::time::Duration;

class ManagerMock : public Manager
{
   public:
    ManagerMock(
        const String& aManagerModeEnvironmentVariableName,
        const Directory& aDefaultLocalRepositoryDirectory,
        const String& aLocalRepositoryEnvironmentVariableName,
        const Path& aLocalRepositoryPath,
        const String& aLocalRepositoryLockTimeoutEnvironmentVariableName
    )
        : Manager(
              aManagerModeEnvironmentVariableName,
              aDefaultLocalRepositoryDirectory,
              aLocalRepositoryEnvironmentVariableName,
              aLocalRepositoryPath,
              aLocalRepositoryLockTimeoutEnvironmentVariableName
          ) {};
};

class OpenSpaceToolkit_Physics_Manager : public ::testing::Test
{
   protected:
    void TearDown() override
    {
        // Clean up any created directories
        if (localRepository_.isDefined() && localRepository_.exists())
        {
            localRepository_.remove();
        }
        unsetenv(modeEnvVar_.c_str());
        unsetenv(localRepositoryEnvVar_.c_str());
        unsetenv(lockTimeoutEnvVar_.c_str());
    }

    Directory localRepository_ = Directory::Path(Path::Parse("/tmp/test_manager_local_repository"));
    const Path localPath_ = Path::Parse("/some/local/path");
    const String modeEnvVar_ = "MANAGER_MODE_ENV_VAR";
    const String localRepositoryEnvVar_ = "LOCAL_REPOSITORY_ENV_VAR";
    const String lockTimeoutEnvVar_ = "LOCAL_REPOSITORY_LOCK_TIMEOUT_ENV_VAR";
};

TEST_F(OpenSpaceToolkit_Physics_Manager, Constructor)
{
    EXPECT_NO_THROW(
        ManagerMock manager(modeEnvVar_, localRepository_, localRepositoryEnvVar_, localPath_, lockTimeoutEnvVar_)
    );
}

TEST_F(OpenSpaceToolkit_Physics_Manager, GetSetMode)
{
    ManagerMock manager(modeEnvVar_, localRepository_, localRepositoryEnvVar_, localPath_, lockTimeoutEnvVar_);

    // Default mode should be Automatic
    EXPECT_EQ(manager.getMode(), Manager::Mode::Automatic);

    // Set to Manual mode
    EXPECT_NO_THROW(manager.setMode(Manager::Mode::Manual));
    EXPECT_EQ(manager.getMode(), Manager::Mode::Manual);

    // Set back to Automatic mode
    EXPECT_NO_THROW(manager.setMode(Manager::Mode::Automatic));
    EXPECT_EQ(manager.getMode(), Manager::Mode::Automatic);
}

TEST_F(OpenSpaceToolkit_Physics_Manager, GetSetLocalRepository)
{
    ManagerMock manager(modeEnvVar_, localRepository_, localRepositoryEnvVar_, localPath_, lockTimeoutEnvVar_);

    // Default local repository
    Directory defaultLocalRepository = manager.getLocalRepository();
    EXPECT_TRUE(defaultLocalRepository.isDefined());

    // Set a new local repository
    localRepository_ = Directory::Path(Path::Parse("/tmp/test_manager_new_local_repository"));
    EXPECT_NO_THROW(manager.setLocalRepository(localRepository_));
    EXPECT_EQ(manager.getLocalRepository(), localRepository_);
}

TEST_F(OpenSpaceToolkit_Physics_Manager, GetLocalRepositoryLockTimeout)
{
    setenv(lockTimeoutEnvVar_.c_str(), "45", 1);

    ManagerMock manager(modeEnvVar_, localRepository_, localRepositoryEnvVar_, localPath_, lockTimeoutEnvVar_);

    Duration lockTimeout = manager.getLocalRepositoryLockTimeout();
    EXPECT_EQ(lockTimeout.inSeconds(), 45.0);
}

TEST_F(OpenSpaceToolkit_Physics_Manager, Reset)
{
    setenv(localRepositoryEnvVar_.c_str(), localRepository_.getPath().toString().c_str(), 1);
    setenv(modeEnvVar_.c_str(), "Manual", 1);
    setenv(lockTimeoutEnvVar_.c_str(), "45", 1);

    ManagerMock manager(modeEnvVar_, localRepository_, localRepositoryEnvVar_, localPath_, lockTimeoutEnvVar_);

    // Change settings
    manager.setMode(Manager::Mode::Automatic);
    const Directory newDirectory = Directory::Path(Path::Parse("/tmp/test_manager_new_local_repository"));
    manager.setLocalRepository(newDirectory);
    ASSERT_EQ(manager.getMode(), Manager::Mode::Automatic);
    ASSERT_EQ(manager.getLocalRepository(), newDirectory);

    // Reset manager
    EXPECT_NO_THROW(manager.reset());

    // After reset, settings should be back to default values
    EXPECT_EQ(manager.getMode(), Manager::Mode::Manual);
    EXPECT_EQ(manager.getLocalRepository(), localRepository_);
    EXPECT_EQ(manager.getLocalRepositoryLockTimeout().inSeconds(), 45.0);
}

TEST_F(OpenSpaceToolkit_Physics_Manager, ClearLocalRepository)
{
    setenv(localRepositoryEnvVar_.c_str(), localRepository_.getPath().toString().c_str(), 1);
    setenv(modeEnvVar_.c_str(), "Manual", 1);
    setenv(lockTimeoutEnvVar_.c_str(), "45", 1);

    ManagerMock manager(modeEnvVar_, localRepository_, localRepositoryEnvVar_, localPath_, lockTimeoutEnvVar_);

    // Ensure local repository exists and create a test file
    Directory localRepository = manager.getLocalRepository();
    File testFile = File::Path(localRepository.getPath() + Path::Parse("/test_file.txt"));
    testFile.create();
    EXPECT_TRUE(testFile.exists());

    // Clear local repository
    EXPECT_NO_THROW(manager.clearLocalRepository());

    // Local repository should exist but be empty
    EXPECT_TRUE(localRepository.exists());
    EXPECT_TRUE(localRepository.isEmpty());
}
