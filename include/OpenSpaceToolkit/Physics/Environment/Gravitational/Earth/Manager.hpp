/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

#include <experimental/filesystem>

#define OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE Manager::Mode::Automatic
#define OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/environment/gravitational/earth"

#define OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT 60

namespace ostk
{
namespace physics
{
namespace environment
{
namespace gravitational
{
namespace earth
{

using ostk::core::types::String;
using ostk::core::fs::Path;
using ostk::core::fs::File;
using ostk::core::fs::Directory;
using ostk::core::ctnr::Array;

using ostk::io::URL;

using ostk::physics::time::Duration;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

/// @brief                      Earth gravitational model data manager
///
///                             Fetches and manages necessary gravity model data files.
///
///                             The following environment variables can be defined:
///
///                             - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE" will override
///                             "DefaultMode"
///                             - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY" will override
///                             "DefaultLocalRepository"

class Manager
{
   public:
    enum class Mode
    {

        Manual,    ///< Manually load and unload gravity files
        Automatic  ///< Automatically fetch gravity files from remote repositories

    };

    /// @brief                  Get manager mode
    ///
    /// @return                 Manager mode

    Manager::Mode getMode() const;

    /// @brief                  Set manager mode
    ///
    /// @param                  [in] aMode A manager mode

    void setMode(const Manager::Mode& aMode);

    /// @brief                  Get default manager mode
    ///
    ///                         Overriden by: OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE
    ///
    /// @return                 Default manager mode

    static Manager::Mode DefaultMode();

    /// @brief                  Copy constructor (deleted)

    Manager(const Manager& aManager) = delete;

    /// @brief                  Copy assignment operator (deleted)

    Manager& operator=(const Manager& aManager) = delete;

    /// @brief                  Returns true if manager has data file for the given model type
    ///
    /// @param                  [in] aModelType A model type
    /// @return                 True if manager has data file for the given model type

    bool hasDataFilesForType(const EarthGravitationalModel::Type& aModelType) const;

    /// @brief                  Returns array of file objects for the given type
    ///
    /// @param                  [in] aModelType A model type
    /// @return                 Array of Files

    Array<File> localDataFilesForType(const EarthGravitationalModel::Type& aModelType) const;

    /// @brief                  Get local repository
    ///
    /// @return                 Local repository

    Directory getLocalRepository() const;

    /// @brief                  Reset the manager.
    ///
    ///                         Reset path and mode to default values.

    void reset();

    /// @brief                  Fetch data file from remote
    ///
    /// @param                  [in] aModelType A model type

    void fetchDataFilesForType(const EarthGravitationalModel::Type& aModelType) const;

    /// @brief                  Set local repository
    ///
    /// @param                  [in] aDirectory A repository directory

    void setLocalRepository(const Directory& aDirectory);

    /// @brief                  Get manager singleton
    ///
    /// @return                 Reference to manager

    static Manager& Get();

    /// @brief                  Get default local repository
    ///
    ///                         Overriden by: OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY
    ///
    /// @return                 Default local repository

    static Directory DefaultLocalRepository();

    /// @brief                  Get default local repository lock timeout
    ///
    ///                         Overriden by:
    ///                         OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT
    ///
    /// @return                 Default local repository lock timeout

    static Duration DefaultLocalRepositoryLockTimeout();

   private:
    Manager::Mode mode_;

    Directory localRepository_;
    Duration localRepositoryLockTimeout_;

    mutable std::mutex mutex_;

    Manager();

    Array<URL> getDataFileUrlsForType(const EarthGravitationalModel::Type& aModelType) const;

    static String DataFileNameFromType(const EarthGravitationalModel::Type& aModelType);

    bool isLocalRepositoryLocked() const;

    File getLocalRepositoryLockFile() const;

    void lockLocalRepository(const Duration& aTimeout);

    void unlockLocalRepository();
};

}  // namespace earth
}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
