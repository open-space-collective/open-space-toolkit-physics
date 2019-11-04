////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Environment/Magnetic/Earth/Manager.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Magnetic_Earth_Manager__
#define __Library_Physics_Environment_Magnetic_Earth_Manager__

#include <Library/Physics/Environment/Magnetic/Earth.hpp>

#include <Library/IO/URL.hpp>

#include <Library/Core/FileSystem/Directory.hpp>
#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Types/String.hpp>

#include <mutex>

#define LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_ENABLED true
#define LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY "./.library/physics/environment/magnetic/earth"
#define LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_REMOTE_URL "https://sourceforge.net/projects/geographiclib/files/magnetic-distrib/"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace environment
{
namespace magnetic
{
namespace earth
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::String ;
using library::core::fs::Path ;
using library::core::fs::File ;
using library::core::fs::Directory ;

using library::io::URL ;

using EarthMagneticModel = library::physics::environment::magnetic::Earth ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Earth magnetic model data manager
///
///                             Fetches and manages necessary magnetic model data files.
///
///                             The following environment variables can be defined:
///
///                             - "LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_ENABLED" will override "DefaultEnabled"
///                             - "LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
///                             - "LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_REMOTE_URL" will override "DefaultRemoteUrl"

class Manager
{

    public:

        /// @brief              Copy constructor (deleted)

                                Manager                                     (   const   Manager&                    aManager                                    ) = delete ;

        /// @brief              Copy assignment operator (deleted)

        Manager&                operator =                                  (   const   Manager&                    aManager                                    ) = delete ;

        /// @brief              Returns true is manager is enabled
        ///
        /// @return             True is manager is enabled

        bool                    isEnabled                                   ( ) const ;

        /// @brief              Returns true if manager has data file for the given model type
        ///
        /// @param              [in] aModelType A model type
        /// @return             True if manager has data file for the given model type

        bool                    hasDataFileForType                          (   const   EarthMagneticModel::Type&   aModelType                                  ) const ;

        /// @brief              Get local repository
        ///
        /// @return             Local repository

        Directory               getLocalRepository                          ( ) const ;

        /// @brief              Get remote URL
        ///
        /// @return             Remote URL

        URL                     getRemoteUrl                                ( ) const ;

        /// @brief              Fetch data file from remote
        ///
        /// @param              [in] aModelType A model type

        void                    fetchDataFileForType                        (   const   EarthMagneticModel::Type&   aModelType                                  ) const ;

        /// @brief              Set local repository
        ///
        /// @param              [in] aDirectory A repository directory

        void                    setLocalRepository                          (   const   Directory&                  aDirectory                                  ) ;

        /// @brief              Set remote URL
        ///
        /// @param              [in] aRemoteUrl A remote URL

        void                    setRemoteUrl                                (   const   URL&                        aRemoteUrl                                  ) ;

        /// @brief              Enable manager

        void                    enable                                      ( ) ;

        /// @brief              Disable manager

        void                    disable                                     ( ) ;

        /// @brief              Set enabled flag
        ///
        /// @param              [in] aBoolean An enabled flag

        void                    setEnabled                                  (   const   bool                        aBoolean                                    ) ;

        /// @brief              Get manager singleton
        ///
        /// @return             Reference to manager

        static Manager&         Get                                         ( ) ;

        /// @brief              Get default enabled flag
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_ENABLED
        ///
        /// @return             Default enabled flag

        static bool             DefaultEnabled                              ( ) ;

        /// @brief              Get default local repository
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY
        ///
        /// @return             Default local repository

        static Directory        DefaultLocalRepository                      ( ) ;

        /// @brief              Get default remote URL
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_REMOTE_URL
        ///
        /// @return             Default remote URL

        static URL              DefaultRemoteUrl                            ( ) ;

    private:

        Directory               localRepository_ ;

        URL                     remoteUrl_ ;

        bool                    enabled_ ;

        mutable std::mutex      mutex_ ;

                                Manager                                     ( ) ;

        URL                     getDataFileUrlForType                       (   const   EarthMagneticModel::Type&   aModelType                                  ) const ;

        static String           DataFileNameFromType                        (   const   EarthMagneticModel::Type&   aModelType                                  ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
