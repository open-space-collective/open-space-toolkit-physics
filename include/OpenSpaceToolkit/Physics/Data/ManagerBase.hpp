/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Manager__
#define __OpenSpaceToolkit_Physics_Data_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Data/Manifest.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

// Base remote URL for OSTk data files
#define OSTK_PHYSICS_DATA_REMOTE_URL "https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data/"

#define OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY "./.open-space-toolkit/physics/data/"

#define OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY_LOCK_TIMEOUT 60

// Maximum age of the manifest file before it needs to be updated
#define OSTK_PHYSICS_DATA_MANAGER_MANIFEST_MAX_AGE_HOURS 24

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::types::Index;
using ostk::core::types::Real;
using ostk::core::ctnr::Array;
using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::math::obj::Vector2d;

using ostk::physics::time::Instant;
using ostk::physics::time::Duration;

using ostk::physics::data::Manifest;

/// @brief                      OSTk Data manager base class (thread-safe)
///
///                             The base manager defines methods for tracking and checking the manifest file.

class ManagerBase
{
   protected:
    /// @brief              Check if there are updates for data of a certain name.
    Instant getLastUpdateTimestampFor(const String& aDataName);

    URL remoteUrl;

    ManagerBase();

    mutable std::mutex mutex_;

   private:
    Manifest manifest_;
    mutable Instant manifestUpdateTimestamp_;

    Directory manifestRepository_;
    Duration manifestRepositoryLockTimeout_;

    void setupBase();

    File fetchLatestManifestFile_();

    Manifest getUpdatedManifest_();

    void loadManifest_(const Manifest& aManifest);

    void resetManifest_();

    void clearManifestRepository_();

    bool isManifestRepositoryLocked_() const;

    File getManifestRepositoryLockFile_() const;

    void lockManifestRepository_(const Duration& aTimeout);

    void unlockManifestRepository_();

    static Directory DefaultManifestRepository_();
    static Duration DefaultManifestRepositoryLockTimeout_();
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
