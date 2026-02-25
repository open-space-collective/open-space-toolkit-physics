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
#include <OpenSpaceToolkit/Physics/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/data/environment/ephemeris/spice"

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

using ostk::core::container::Array;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::io::URL;

using ostk::physics::environment::ephemeris::spice::Kernel;
using ostk::physics::time::Instant;

using ManifestManager = ostk::physics::data::Manager;
using BaseManager = ostk::physics::Manager;

/// @brief SPICE Toolkit kernel manager
///
/// Fetches and manages necessary SPICE kernels.
///
/// The following environment variables can be defined:
///
/// - "OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"

class Manager : public BaseManager
{
   public:
    /// @brief Fetch kernel from remote
    ///
    /// @code
    ///     Manager::Get().fetchKernel(aKernel) ;
    /// @endcode
    ///
    /// @param [in] aKernel A kernel

    void fetchKernel(const Kernel& aKernel) const;

    /// @brief Fetch kernels matching regular expression
    ///
    /// @code
    ///     Array<Kernel> kernels = Manager::Get().fetchMatchingKernels("de430.*\\.bsp") ;
    /// @endcode
    ///
    /// @param [in] aRegexString A regular expression string
    /// @return An array of kernels

    Array<Kernel> fetchMatchingKernels(const String& aRegexString) const;

    /// @brief Find kernel paths matching regular expression in local repository.
    ///
    /// @code
    ///     Array<Path> paths = Manager::Get().findKernelPaths("de430.*\\.bsp") ;
    /// @endcode
    ///
    /// @param [in] aRegexString A regular expression
    /// @return An array of kernel paths

    Array<Path> findKernelPaths(const String& aRegexString) const;

    /// @brief Find kernels matching regular expression. Search locally first, then remotely.
    /// Always return the first found.
    ///
    /// @code
    ///     Kernel kernel = Manager::Get().findKernel("de430.*\\.bsp") ;
    /// @endcode
    ///
    /// @param [in] aRegexString A regular expression
    /// @return An array of kernels

    Kernel findKernel(const String& aRegexString) const;

    /// @brief Get manager singleton
    ///
    /// @code
    ///     Manager& manager = Manager::Get() ;
    /// @endcode
    ///
    /// @return Reference to manager

    static Manager& Get();

   private:
    Manager();
};

}  // namespace spice
}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
