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

/// @brief OSTk manager base class (thread-safe)
///
/// The base manager defines methods for tracking and checking the manifest file.
class Manager
{
   public:
    enum class Mode
    {

        Manual,    ///< Manually load and unload bulletins
        Automatic  ///< Automatically fetch, load and unload bulletins (from remote repositories)

    };

    /// @brief Copy constructor (deleted)
    Manager(const Manager& aManager) = delete;

    /// @brief Copy assignment operator (deleted)
    Manager& operator=(const Manager& aManager) = delete;

    /// @brief move constructor (deleted)
    Manager(Manager&&) = delete;

    /// @brief move assignment operator (deleted)
    Manager& operator=(Manager&&) = delete;

    /// @brief Destructor
    virtual ~Manager() = default;

    /// @brief Get manager mode
    ///
    /// @code
    ///     Manager::Mode mode = manager.getMode();
    /// @endcode
    ///
    /// @return Manager mode
    Manager::Mode getMode() const;

    /// @brief Get local repository
    ///
    /// @code
    ///     Directory localRepository = manager.getLocalRepository();
    /// @endcode
    ///
    /// @return Local repository
    Directory getLocalRepository() const;

    /// @brief Get local repository timeout, the maximum time to lock the local repository
    ///
    /// @code
    ///     Duration timeout = manager.getLocalRepositoryLockTimeout();
    /// @endcode
    ///
    /// @return Local repository timeout
    Duration getLocalRepositoryLockTimeout() const;

    /// @brief Set manager mode
    ///
    /// @code
    ///     manager.setMode(Manager::Mode::Automatic);
    /// @endcode
    ///
    /// @param [in] aMode A manager mode
    void setMode(const Manager::Mode& aMode);

    /// @brief Set local repository
    ///
    /// @code
    ///     manager.setLocalRepository(Directory::Path(Path::Parse("/path/to/repo")));
    /// @endcode
    ///
    /// @param [in] aDirectory A repository directory
    void setLocalRepository(const Directory& aDirectory);

    /// @brief Reset the manager to it's default state
    ///
    /// @code
    ///     manager.reset();
    /// @endcode
    virtual void reset();

    /// @brief Clear local repository, removing all files.
    ///
    /// @code
    ///     manager.clearLocalRepository();
    /// @endcode
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

    /// @brief Construct a manager with configuration from environment variables.
    ///
    /// @code
    ///     Manager manager("OSTK_MODE", defaultDir, "OSTK_REPO", path, "OSTK_TIMEOUT");
    /// @endcode
    ///
    /// @param [in] aManagerModeEnvironmentVariableName Environment variable name for the manager mode
    /// @param [in] aDefaultLocalRepositoryDirectory Default local repository directory
    /// @param [in] aLocalRepositoryEnvironmentVariableName Environment variable name for the local repository
    /// @param [in] aLocalRepositoryPath Path to the local repository
    /// @param [in] aLocalRepositoryLockTimeoutEnvironmentVariableName Environment variable name for lock timeout
    Manager(
        const String& aManagerModeEnvironmentVariableName,
        const Directory& aDefaultLocalRepositoryDirectory,
        const String& aLocalRepositoryEnvironmentVariableName,
        const Path& aLocalRepositoryPath,
        const String& aLocalRepositoryLockTimeoutEnvironmentVariableName
    );

    /// @brief Set up the manager, initializing configuration from environment variables.
    ///
    /// @code
    ///     manager.setup_();
    /// @endcode
    virtual void setup_();

    /// @brief Check if the local repository is currently locked.
    ///
    /// @code
    ///     Boolean isLocked = manager.isLocalRepositoryLocked_();
    /// @endcode
    ///
    /// @return True if the local repository is locked
    bool isLocalRepositoryLocked_() const;

    /// @brief Get the lock file for the local repository.
    ///
    /// @code
    ///     File lockFile = manager.getLocalRepositoryLockFile_();
    /// @endcode
    ///
    /// @return The lock file
    File getLocalRepositoryLockFile_() const;

    /// @brief Lock the local repository with a timeout.
    ///
    /// @code
    ///     manager.lockLocalRepository_(Duration::Seconds(30.0));
    /// @endcode
    ///
    /// @param [in] aTimeout Maximum duration to wait for the lock
    void lockLocalRepository_(const Duration& aTimeout) const;

    /// @brief Unlock the local repository.
    ///
    /// @code
    ///     manager.unlockLocalRepository_();
    /// @endcode
    void unlockLocalRepository_() const;

    /// @brief Get the default local repository directory from environment or defaults.
    ///
    /// @code
    ///     Directory dir = Manager::DefaultLocalRepository_(defaultDir, "OSTK_REPO", path);
    /// @endcode
    ///
    /// @param [in] aDefaultLocalRepositoryDirectory Default directory if environment variable is not set
    /// @param [in] aLocalRepositoryEnvironmentVariableName Environment variable name to check
    /// @param [in] aLocalRepositoryPath Relative path within the repository
    /// @return The default local repository directory
    static Directory DefaultLocalRepository_(
        const Directory& aDefaultLocalRepositoryDirectory,
        const String& aLocalRepositoryEnvironmentVariableName,
        const Path& aLocalRepositoryPath
    );

    /// @brief Get the default manager mode from an environment variable.
    ///
    /// @code
    ///     Manager::Mode mode = Manager::DefaultMode_("OSTK_MODE");
    /// @endcode
    ///
    /// @param [in] aManagerModeEnvironmentVariableName Environment variable name to check
    /// @return The default manager mode
    static Manager::Mode DefaultMode_(const String& aManagerModeEnvironmentVariableName);

    /// @brief Get the default local repository lock timeout from an environment variable.
    ///
    /// @code
    ///     Duration timeout = Manager::DefaultLocalRepositoryLockTimeout_("OSTK_TIMEOUT");
    /// @endcode
    ///
    /// @param [in] aLocalRepositoryLockTimeoutEnvironmentVariableName Environment variable name to check
    /// @return The default lock timeout duration
    static Duration DefaultLocalRepositoryLockTimeout_(
        const String& aLocalRepositoryLockTimeoutEnvironmentVariableName
    );
};

}  // namespace physics
}  // namespace ostk

#endif
