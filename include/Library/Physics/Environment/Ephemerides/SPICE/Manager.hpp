////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Ephemerides/SPICE/Manager.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Environment_Ephemerides_SPICE_Manager__
#define __Library_Physics_Environment_Ephemerides_SPICE_Manager__

#include <Library/Physics/Environment/Ephemerides/SPICE/Index.hpp>
#include <Library/Physics/Environment/Ephemerides/SPICE/Kernel.hpp>
#include <Library/Physics/Environment/Ephemerides/SPICE.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/IO/URL.hpp>

#include <Library/Core/FileSystem/Directory.hpp>
#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <mutex>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace ephem
{
namespace spice
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;
using library::core::types::String ;
using library::core::ctnr::Array ;
using library::core::fs::Path ;
using library::core::fs::File ;
using library::core::fs::Directory ;

using library::io::URL ;

using library::physics::time::Instant ;
using library::physics::env::ephem::spice::Kernel ;
using library::physics::env::ephem::spice::Index ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      SPICE Toolkit kernel manager
///
///                             Fetches and manages necessary SPICE kernels.

class Manager
{

    public:

        /// @brief              Copy constructor (deleted)

                                Manager                                     (   const   Manager&                    aSpiceManager                               ) = delete ;

        /// @brief              Copy assignment operator (deleted)

        Manager&                operator =                                  (   const   Manager&                    aSpiceManager                               ) = delete ;

        /// @brief              Get local repository
        ///
        /// @return             Local repository

        Directory               getLocalRepository                          ( ) const ;

        /// @brief              Get remote URL
        ///
        /// @return             Remote URL

        URL                     getRemoteUrl                                ( ) const ;

        /// @brief              Fetch kernel from remote
        ///
        /// @param              [in] aKernel A kernel

        void                    fetchKernel                                 (   const   Kernel&                     aKernel                                     ) const ;

        /// @brief              Fetch kernels matching regular expression
        ///
        /// @param              [in] aRegex A regular expression
        /// @return             An array of kernels

        Array<Kernel>           fetchMatchingKernels                        (   const   std::regex&                 aRegex                                      ) const ;
        
        /// @brief              Set local repository
        ///
        /// @param              [in] aDirectory A repository directory

        void                    setLocalRepository                          (   const   Directory&                  aDirectory                                  ) ;

        /// @brief              Set remote URL
        ///
        /// @param              [in] aRemoteUrl A remote URL

        void                    setRemoteUrl                                (   const   URL&                        aRemoteUrl                                  ) ;

        /// @brief              Refresh manager
        ///
        ///                     This will re-fetch a new index.

        void                    refresh                                     ( ) ;

        /// @brief              Get manager singleton
        ///
        /// @return             Reference to manager

        static Manager&         Get                                         ( ) ;

        /// @brief              Get default local repository
        ///
        /// @return             Default local repository

        static Directory        DefaultLocalRepository                      ( ) ;

        /// @brief              Get default remote URL
        ///
        /// @return             Default remote URL

        static URL              DefaultRemoteUrl                            ( ) ;

    private:

        Directory               localRepository_ ;

        URL                     remoteUrl_ ;
        
        File                    indexFile_ ;
        mutable Index           index_ ;

        mutable std::mutex      mutex_ ;

                                Manager                                     ( ) ;

        void                    updateIndex                                 ( ) ;

        void                    fetchIndexAt                                (   const   URL&                        aUrl                                        ) ;

        void                    loadIndex                                   ( ) ;
        
        void                    flushIndex                                  ( ) ;

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