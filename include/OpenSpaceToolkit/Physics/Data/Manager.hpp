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
    /// @brief                  Get manager singleton
    ///
    /// @return                 Reference to manager

    static Manager& Get();

    /// @brief                  Check if there are updates for data of a certain name.
    ///
    /// @param                  [in] aDataName name of the data to query. This is the key for the data entry in the
    /// manifest
    ///                         file.
    ///
    /// @return                 Instant indicating when the data was last updated on the remote, according to the
    /// manifest
    ///                         record.

    const Instant getLastUpdateTimestampFor(const String& aDataName);

    /// @brief                  Get the remote URL. This points to the base URL for the OSTk input data.
    ///
    /// @return                 Remote URL

    const URL getRemoteUrl() const;

    /// @brief                  Set the remote URL.
    ///
    /// @return                 Remote URL

    void setRemoteUrl(const URL& aRemoteUrl);

    /// @brief                  Get the default remote URL for data fetching.
    ///
    /// @return                 Default remote URL

    static URL DefaultRemoteUrl();

    /// @brief                  Get the manifest repository.
    ///
    /// @return                 Manifest repository

    const Directory getManifestRepository() const;

    /// @brief                  Set the manifest repository.
    ///
    /// @param                  [in] aManifestRepository Manifest repository

    void setManifestRepository(const Directory& aManifestRepository);

    /// @brief                  Get the default manifest repository.
    ///
    /// @return                 Default manifest repository

    static Directory DefaultManifestRepository();

    /// @brief                  Get the remote data URL for a given data name.
    ///
    /// @param                  [in] aDataName name of the data. i.e. the key for the data entry in the manifest
    /// @return                 Array of URLs

    Array<URL> getRemoteDataUrls(const String& aDataName) const;

    /// @brief                  Find remote URLs of data matching regular expression string
    ///
    /// @param                  [in] aKernelNameRegexString A regular expression string
    /// @return                 Array of URLs

    Array<URL> findRemoteDataUrls(const String& aDataNameRegex) const;

    /// @brief                  Get a copy of the current manifest file.
    ///
    /// @return                 Manifest file

    const Manifest getManifest() const;

    /// @brief                  Load a new manifest file.
    ///
    /// @param                  [in] aManifest Manifest file to load

    void loadManifest(const Manifest& aManifest);

    /// @brief                  Return true if a manifest file already exists in the directory
    ///
    /// @return                 True if manifest file exists

    bool manifestFileExists() const;

    /// @brief                  Reset the manager.
    ///
    ///                         Unload the manifest file and forget manifest age.

    void reset();

   protected:
    URL remoteUrl_;

    Manifest manifest_;

    Directory manifestRepository_;
    Duration manifestRepositoryLockTimeout_;

    mutable std::mutex mutex_;

    Manager();

    void setup();

    // virtual so we can mock in testing
    virtual File fetchLatestManifestFile();

    /// @brief                  Check the age of the manifest to determine if it should be updated before querying it
    /// for other data files.
    ///
    ///                         We fetch the manifest file from the remote if:
    ///                         - It does not exist locally
    ///                         - We are past the next predicted update for the manifest based on its own "manifest"
    ///                         entry.

    void checkManifestAgeAndUpdate();

    bool isManifestRepositoryLocked() const;
    File getManifestRepositoryLockFile() const;
    void lockManifestRepository(const Duration& aTimeout);
    void unlockManifestRepository();

    static Duration DefaultManifestRepositoryLockTimeout();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
