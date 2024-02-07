/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager__
#define __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE/Kernel.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/data/environment/ephemerides/spice"

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{
namespace spice
{

using ostk::core::type::Shared;
using ostk::core::type::String;
using ostk::core::container::Array;
using ostk::core::filesystem::Path;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Directory;

using ostk::io::URL;

using ostk::physics::time::Instant;
using ostk::physics::environment::ephemeris::spice::Kernel;

using ManifestManager = ostk::physics::data::Manager;

/// @brief                      SPICE Toolkit kernel manager
///
///                             Fetches and manages necessary SPICE kernels.
///
///                             The following environment variables can be defined:
///
///                             - "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY" will override
///                             "DefaultLocalRepository"

class Manager
{
   public:
    /// @brief              Copy constructor (deleted)

    Manager(const Manager& aSpiceManager) = delete;

    /// @brief              Copy assignment operator (deleted)

    Manager& operator=(const Manager& aSpiceManager) = delete;

    /// @brief              Get manager singleton
    ///
    /// @return             Reference to manager

    static Manager& Get();

    /// @brief              Get local repository
    ///
    /// @return             Local repository

    Directory getLocalRepository() const;

    /// @brief              Set local repository
    ///
    /// @param              [in] aDirectory A repository directory

    void setLocalRepository(const Directory& aDirectory);

    /// @brief              Get default local repository
    ///
    ///                     Overriden by: OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY
    ///
    /// @return             Default local repository

    static Directory DefaultLocalRepository();

    /// @brief              Fetch kernel from remote
    ///
    /// @param              [in] aKernel A kernel

    void fetchKernel(const Kernel& aKernel) const;

    /// @brief              Fetch kernels matching regular expression
    ///
    /// @param              [in] aRegexString A regular expression string
    /// @return             An array of kernels

    Array<Kernel> fetchMatchingKernels(const String& aRegexString) const;

    /// @brief              Find kernels matching regular expression. Search locally first, then remotely.
    ///                     Always return the first found.
    ///
    /// @param              [in] aRegexString A regular expression
    /// @return             An array of kernels

    Kernel findKernel(const String& aRegexString) const;

    /// @brief              Refresh manager
    ///
    ///                     This will re-fetch a new index.

    void refresh();

   private:
    Directory localRepository_;

    mutable std::mutex mutex_;

    Manager();
};

}  // namespace spice
}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
