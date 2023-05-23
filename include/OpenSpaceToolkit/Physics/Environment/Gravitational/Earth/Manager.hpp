/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager__
#define __OpenSpaceToolkit_Physics_Environment_Gravitational_Earth_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>

#define OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_ENABLED true
#define OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/environment/gravitational/earth"
#define OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_REMOTE_URL \
    "https://sourceforge.net/projects/geographiclib/files/gravity-distrib/"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::String;
using ostk::core::fs::Path;
using ostk::core::fs::File;
using ostk::core::fs::Directory;

using ostk::io::URL;

using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Earth gravitational model data manager
///
///                             Fetches and manages necessary gravity model data files.
///
///                             The following environment variables can be defined:
///
///                             - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_ENABLED" will override
///                             "DefaultEnabled"
///                             - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY" will override
///                             "DefaultLocalRepository"
///                             - "OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_REMOTE_URL" will override
///                             "DefaultRemoteUrl"

class Manager
{
   public:
    /// @brief              Copy constructor (deleted)

    Manager(const Manager& aManager) = delete;

    /// @brief              Copy assignment operator (deleted)

    Manager& operator=(const Manager& aManager) = delete;

    /// @brief              Returns true is manager is enabled
    ///
    /// @return             True is manager is enabled

    bool isEnabled() const;

    /// @brief              Returns true if manager has data file for the given model type
    ///
    /// @param              [in] aModelType A model type
    /// @return             True if manager has data file for the given model type

    bool hasDataFileForType(const EarthGravitationalModel::Type& aModelType) const;

    /// @brief              Get local repository
    ///
    /// @return             Local repository

    Directory getLocalRepository() const;

    /// @brief              Get remote URL
    ///
    /// @return             Remote URL

    URL getRemoteUrl() const;

    /// @brief              Fetch data file from remote
    ///
    /// @param              [in] aModelType A model type

    void fetchDataFileForType(const EarthGravitationalModel::Type& aModelType) const;

    /// @brief              Set local repository
    ///
    /// @param              [in] aDirectory A repository directory

    void setLocalRepository(const Directory& aDirectory);

    /// @brief              Set remote URL
    ///
    /// @param              [in] aRemoteUrl A remote URL

    void setRemoteUrl(const URL& aRemoteUrl);

    /// @brief              Enable manager

    void enable();

    /// @brief              Disable manager

    void disable();

    /// @brief              Set enabled flag
    ///
    /// @param              [in] aBoolean An enabled flag

    void setEnabled(const bool aBoolean);

    /// @brief              Get manager singleton
    ///
    /// @return             Reference to manager

    static Manager& Get();

    /// @brief              Get default enabled flag
    ///
    ///                     Overriden by: OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_ENABLED
    ///
    /// @return             Default enabled flag

    static bool DefaultEnabled();

    /// @brief              Get default local repository
    ///
    ///                     Overriden by: OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY
    ///
    /// @return             Default local repository

    static Directory DefaultLocalRepository();

    /// @brief              Get default remote URL
    ///
    ///                     Overriden by: OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_REMOTE_URL
    ///
    /// @return             Default remote URL

    static URL DefaultRemoteUrl();

   private:
    Directory localRepository_;

    URL remoteUrl_;

    bool enabled_;

    mutable std::mutex mutex_;

    Manager();

    URL getDataFileUrlForType(const EarthGravitationalModel::Type& aModelType) const;

    static String DataFileNameFromType(const EarthGravitationalModel::Type& aModelType);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace earth
}  // namespace gravitational
}  // namespace environment
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
