/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Manager__
#define __OpenSpaceToolkit_Physics_Manager__

#include <filesystem>
#include <mutex>

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{

using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::String;

using ostk::physics::time::Duration;
using ostk::physics::time::Instant;

/// @brief                      OSTk manager base class (thread-safe)
///
///                             The base manager defines methods for tracking and checking the manifest file.

class Manager
{
   public:
    enum class Mode
    {

        Manual,    ///< Manually load and unload bulletins
        Automatic  ///< Automatically fetch, load and unload bulletins (from remote repositories)

    };

    /// @brief                  Copy constructor (deleted)

    Manager(const Manager& aManager) = delete;

    /// @brief                  Copy assignment operator (deleted)

    Manager& operator=(const Manager& aManager) = delete;

    /// @brief                  move constructor (deleted)

    Manager(Manager&&) = delete;

    /// @brief                  move assignment operator (deleted)

    Manager& operator=(Manager&&) = delete;

    /// @brief              Get manager mode
    ///
    /// @return             Manager mode

    Manager::Mode getMode() const;

    /// @brief              Get local repository
    ///
    /// @return             Local repository

    Directory getLocalRepository() const;

    /// @brief              Get local repository timeout
    ///
    /// @return             Local repository timeout

    Duration getLocalRepositoryLockTimeout() const;

    /// @brief              Set manager mode
    ///
    /// @param              [in] aMode A manager mode

    void setMode(const Manager::Mode& aMode);

    /// @brief              Set local repository
    ///
    /// @param              [in] aDirectory A repository directory

    void setLocalRepository(const Directory& aDirectory);

    /// @brief                  Reset the manager.
    ///
    ///                         Unload the manifest file and forget manifest age.

    virtual void reset();

    /// @brief              Clear local repository
    ///
    ///                     Delete all files in local repository.

    void clearLocalRepository();

   protected:
    String managerModeEnvironmentVariableName_;
    Directory defaultLocalRepositoryDirectory_;
    String localRepositoryEnvironmentVariableName_;
    Path localRepositoryPath_;
    String localRepositoryLockTimeoutEnvironmentVariableName_;

    Manager::Mode mode_;
    Directory localRepository_;
    Duration localRepositoryLockTimeout_;

    mutable std::mutex mutex_;

    Manager(
        const String& aManagerModeEnvironmentVariableName,
        const Directory& aDefaultLocalRepositoryDirectory,
        const String& aLocalRepositoryEnvironmentVariableName,
        const Path& aLocalRepositoryPath,
        const String& aLocalRepositoryLockTimeoutEnvironmentVariableName
    );

    virtual void setup_();

    bool isLocalRepositoryLocked_() const;
    File getLocalRepositoryLockFile_() const;
    void lockLocalRepository_(const Duration& aTimeout) const;
    void unlockLocalRepository_() const;

    static Directory DefaultLocalRepository_(
        const Directory& aDefaultLocalRepositoryDirectory,
        const String& aLocalRepositoryEnvironmentVariableName,
        const Path& aLocalRepositoryPath
    );

    static Manager::Mode DefaultMode_(const String& aManagerModeEnvironmentVariableName);

    static Duration DefaultLocalRepositoryLockTimeout_(const String& aLocalRepositoryLockTimeoutEnvironmentVariableName
    );
};

}  // namespace physics
}  // namespace ostk

#endif
