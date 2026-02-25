/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Manager__
#define __OpenSpaceToolkit_Physics_Data_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

// Base remote URL for OSTk data files
#define OSTK_PHYSICS_DATA_REMOTE_URL "https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data/"

#define OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY "./.open-space-toolkit/physics/data/"

// Maximum frequency at which OSTk tries to freshen its data
// Note: necessary data fetches still occur (i.e. if a data file is missing)
#define OSTK_PHYSICS_DATA_REFRESH_RATE_H 24

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::filesystem::Directory;

using ostk::io::URL;

using ostk::physics::data::Manifest;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using BaseManager = ostk::physics::Manager;

/// @brief OSTk Data manager base class (thread-safe)
///
/// The base manager defines methods for tracking and checking the manifest file.
class Manager : public BaseManager
{
   public:
    /// @brief Check if there are updates for data of a certain name.
    ///
    /// @code
    ///     Instant timestamp = Manager::Get().getLastUpdateTimestampFor("earth-gravity-egm96");
    /// @endcode
    ///
    /// @param [in] aDataName name of the data to query. This is the key for the data entry in the manifest file.
    ///
    /// @return Instant indicating when the data was last updated on the remote, according to the manifest record.
    const Instant getLastUpdateTimestampFor(const String& aDataName);

    /// @brief Get the remote URL. This points to the base URL for the OSTk input data.
    ///
    /// @code
    ///     URL remoteUrl = Manager::Get().getRemoteUrl();
    /// @endcode
    ///
    /// @return Remote URL
    const URL getRemoteUrl() const;

    /// @brief Set the remote URL.
    ///
    /// @code
    ///     Manager::Get().setRemoteUrl(URL::Parse("https://example.com/data/"));
    /// @endcode
    ///
    /// @param [in] aRemoteUrl A remote URL
    void setRemoteUrl(const URL& aRemoteUrl);

    /// @brief Get the remote data URL for a given data name.
    ///
    /// @code
    ///     Array<URL> urls = Manager::Get().getRemoteDataUrls("earth-gravity-egm96");
    /// @endcode
    ///
    /// @param [in] aDataName name of the data. i.e. the key for the data entry in the manifest
    /// @return Array of URLs
    Array<URL> getRemoteDataUrls(const String& aDataName) const;

    /// @brief Find remote URLs of data matching regular expression string
    ///
    /// @code
    ///     Array<URL> urls = Manager::Get().findRemoteDataUrls("earth-gravity-.*");
    /// @endcode
    ///
    /// @param [in] aDataNameRegex A regular expression string
    /// @return Array of URLs
    Array<URL> findRemoteDataUrls(const String& aDataNameRegex) const;

    /// @brief Get a copy of the current manifest file.
    ///
    /// @code
    ///     Manifest manifest = Manager::Get().getManifest();
    /// @endcode
    ///
    /// @return Manifest file
    const Manifest getManifest() const;

    /// @brief Load a new manifest file.
    ///
    /// @code
    ///     Manager::Get().loadManifest(manifest);
    /// @endcode
    ///
    /// @param [in] aManifest Manifest file to load
    void loadManifest(const Manifest& aManifest);

    /// @brief Return true if a manifest file already exists in the directory
    ///
    /// @code
    ///     Boolean exists = Manager::Get().manifestFileExists();
    /// @endcode
    ///
    /// @return True if manifest file exists
    bool manifestFileExists() const;

    /// @brief Reset the manager.
    ///
    /// @code
    ///     Manager::Get().reset();
    /// @endcode
    ///
    /// Unload the manifest file and forget manifest age.
    virtual void reset() override;

    /// @brief Get manager singleton
    ///
    /// @code
    ///     Manager& manager = Manager::Get();
    /// @endcode
    ///
    /// @return Reference to manager
    static Manager& Get();

    /// @brief Get the default remote URL for data fetching.
    ///
    /// @code
    ///     URL defaultUrl = Manager::DefaultRemoteUrl();
    /// @endcode
    ///
    /// @return Default remote URL
    static URL DefaultRemoteUrl();

   protected:
    URL remoteUrl_;

    mutable Manifest manifest_;

    /// @brief Default constructor.
    ///
    /// @code
    ///     Manager manager;
    /// @endcode
    Manager();

    /// @brief Fetch the latest manifest file from the remote.
    ///
    /// @code
    ///     File manifestFile = manager.fetchLatestManifestFile_();
    /// @endcode
    ///
    /// @return The fetched manifest file
    virtual File fetchLatestManifestFile_() const;

    /// @brief Check the age of the manifest to determine if it should be updated before querying it
    /// for other data files.
    ///
    /// @code
    ///     manager.checkManifestAgeAndUpdate_();
    /// @endcode
    ///
    /// We fetch the manifest file from the remote if: - It does not exist locally
    /// - We are past the next predicted update for the manifest based on its own "manifest" entry.

    void checkManifestAgeAndUpdate_() const;

    /// @brief Load a manifest object into internal state.
    ///
    /// @code
    ///     manager.loadManifest_(manifest);
    /// @endcode
    ///
    /// @param [in] aManifest A manifest to load

    void loadManifest_(const Manifest& aManifest) const;

    /// @brief Determines how often OSTk should do non-critical IO to freshen its data.
    /// We limit this by limiting how frequently the manifest file is updated.
    ///
    /// @code
    ///     Duration refreshRate = Manager::DataRefreshRate_();
    /// @endcode
    ///
    /// @return Frequency in hours. Default is 24. Overriden by the OSTK_PHYSICS_DATA_REFRESH_RATE environment variable.
    static Duration DataRefreshRate_();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
