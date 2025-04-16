/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager__
#define __OpenSpaceToolkit_Physics_Environment_Magnetic_Earth_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

#define OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/data/environment/magnetic/earth"

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{
namespace earth
{

using ostk::core::container::Array;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::String;

using ostk::io::URL;

using ostk::physics::time::Duration;
using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;
using BaseManager = ostk::physics::Manager;

/// @brief                      Earth magnetic model data manager
///
///                             Fetches and manages necessary magnetic model data files.
///
///                             The following environment variables can be defined:
///
///                             - "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_MODE" will override
///                             "DefaultMode"
///                             - "OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY" will override
///                             "DefaultLocalRepository"

class Manager : public BaseManager
{
   public:
    /// @brief                  Returns true if manager has data file for the given model type
    ///
    /// @param                  [in] aModelType A model type
    /// @return                 True if manager has data file for the given model type

    bool hasDataFilesForType(const EarthMagneticModel::Type& aModelType) const;

    /// @brief                  Returns array of file objects for the given type
    ///
    /// @param                  [in] aModelType A model type
    /// @return                 Array of Files

    Array<File> localDataFilesForType(const EarthMagneticModel::Type& aModelType) const;

    /// @brief                  Fetch data file from remote
    ///
    /// @param                  [in] aModelType A model type

    void fetchDataFilesForType(const EarthMagneticModel::Type& aModelType) const;

    /// @brief                  Get manager singleton
    ///
    /// @return                 Reference to manager

    static Manager& Get();

   private:
    Manager();

    Array<URL> getDataFileUrlsForType_(const EarthMagneticModel::Type& aModelType) const;

    static String DataFileNameFromType_(const EarthMagneticModel::Type& aModelType);
};

}  // namespace earth
}  // namespace magnetic
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
