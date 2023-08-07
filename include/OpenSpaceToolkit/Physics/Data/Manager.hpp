/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Manager__
#define __OpenSpaceToolkit_Physics_Data_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

// Base remote URL for OSTk data files
#define OSTK_PHYSICS_DATA_REMOTE_URL "https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data/"

#define OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY "./.open-space-toolkit/physics/data/"

#define OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY_LOCK_TIMEOUT 60

// Maximum age of the manifest file before it needs to be updated
// TBI: This can be be made configurable
#define OSTK_PHYSICS_DATA_MANAGER_MANIFEST_MAX_AGE_HOURS 24

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::physics::time::Instant;
using ostk::physics::time::Duration;
using ostk::physics::data::Manifest;

/// @brief                      OSTk Data manager base class (thread-safe)
///
///                             The base manager defines methods for tracking and checking the manifest file.

class Manager
{
   public:
    /// @brief              Get manager singleton
    ///
    /// @return             Reference to manager
    static Manager& Get();

    /// @brief              Check if there are updates for data of a certain name.
    ///
    /// @param              [in] aDataName name of the data to query. This is the key for the data entry in the manifest file.
    ///
    /// @return             Instant indicating when the data was last updated on the remote, according to the manifest record.
    Instant getLastUpdateTimestampFor(const String& aDataName);

    /// @brief              Get the remote URL. This points to the base URL for the OSTk input data.
    ///
    /// @return             Remote URL
    URL getRemoteUrl() const;

    /// @brief              Get a copy of the current manifest file.
    ///
    /// @return             Manifest file
    Manifest getManifest();

    /// @brief              Load a new manifest file.
    ///
    /// @param              [in] aManifest Manifest file to load
    void loadManifest(const Manifest& aManifest);

    /// @brief              Reset the manager.
    ///
    ///                     Unload the manifest file and forget manifest age.
    void reset();

    /// @brief              Clear the manifest repository.
    ///
    ///                     Delete the manifest repository directory and all its contents.
    void clearManifestRepository();

   protected:

    URL remoteUrl_;

    Manifest manifest_;
    mutable Instant manifestUpdateTimestamp_;

    Directory manifestRepository_;
    Duration manifestRepositoryLockTimeout_;

    mutable std::mutex mutex_;

    Manager();

    void setup_();


    File fetchLatestManifestFile_();
    Manifest getUpdatedManifest_();



    bool isManifestRepositoryLocked_() const;
    File getManifestRepositoryLockFile_() const;
    void lockManifestRepository_(const Duration& aTimeout);
    void unlockManifestRepository_();

    static Directory DefaultManifestRepository_();
    static Duration DefaultManifestRepositoryLockTimeout_();
    static URL DefaultRemoteUrl_();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
