/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager__
#define __OpenSpaceToolkit_Physics_Environment_Ephemerides_SPICE_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Index.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/environment/ephemerides/spice"
#define OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_REMOTE_URL \
    "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/"

namespace ostk
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

using ostk::core::types::Shared;
using ostk::core::types::String;
using ostk::core::ctnr::Array;
using ostk::core::fs::Path;
using ostk::core::fs::File;
using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::physics::time::Instant;
using ostk::physics::env::ephem::spice::Kernel;
using ostk::physics::env::ephem::spice::Index;

/// @brief                      SPICE Toolkit kernel manager
///
///                             Fetches and manages necessary SPICE kernels.
///
///                             The following environment variables can be defined:
///
///                             - "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY" will override
///                             "DefaultLocalRepository"
///                             - "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_REMOTE_URL" will override
///                             "DefaultRemoteUrl"

class Manager
{
   public:
    /// @brief              Copy constructor (deleted)

    Manager(const Manager& aSpiceManager) = delete;

    /// @brief              Copy assignment operator (deleted)

    Manager& operator=(const Manager& aSpiceManager) = delete;

    /// @brief              Get local repository
    ///
    /// @return             Local repository

    Directory getLocalRepository() const;

    /// @brief              Get remote URL
    ///
    /// @return             Remote URL

    URL getRemoteUrl() const;

    /// @brief              Get index file
    ///
    /// @return             Index file

    File getIndexFile() const;

    /// @brief              Fetch kernel from remote
    ///
    /// @param              [in] aKernel A kernel

    void fetchKernel(const Kernel& aKernel) const;

    /// @brief              Fetch kernels matching regular expression
    ///
    /// @param              [in] aRegex A regular expression
    /// @return             An array of kernels

    Array<Kernel> fetchMatchingKernels(const std::regex& aRegex) const;

    /// @brief              Find kernels matching regular expression. Search locally first, then remotely.
    ///                     Always return the first found.
    ///
    /// @param              [in] aRegex A regular expression
    /// @return             An array of kernels

    Kernel findKernel(const String& aRegexString) const;

    /// @brief              Set local repository
    ///
    /// @param              [in] aDirectory A repository directory

    void setLocalRepository(const Directory& aDirectory);

    /// @brief              Set remote URL
    ///
    /// @param              [in] aRemoteUrl A remote URL

    void setRemoteUrl(const URL& aRemoteUrl);

    /// @brief              Refresh manager
    ///
    ///                     This will re-fetch a new index.

    void refresh();

    /// @brief              Get manager singleton
    ///
    /// @return             Reference to manager

    static Manager& Get();

    /// @brief              Get default local repository
    ///
    ///                     Overriden by: OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY
    ///
    /// @return             Default local repository

    static Directory DefaultLocalRepository();

    /// @brief              Get default remote URL
    ///
    ///                     Overriden by: OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_REMOTE_URL
    ///
    /// @return             Default remote URL

    static URL DefaultRemoteUrl();

   private:
    Directory localRepository_;

    URL remoteUrl_;

    mutable Index index_;

    mutable std::mutex mutex_;

    Manager();

    File getIndexFile_() const;

    void updateIndex();

    void fetchIndexAt(const URL& aUrl);

    void loadIndex();

    void flushIndex();
};

}  // namespace spice
}  // namespace ephem
}  // namespace env
}  // namespace physics
}  // namespace ostk

#endif
