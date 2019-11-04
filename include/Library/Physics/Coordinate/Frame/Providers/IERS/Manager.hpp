////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Frame_Providers_IERS_Manager__
#define __Library_Physics_Coordinate_Frame_Providers_IERS_Manager__

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/IO/URL.hpp>

#include <Library/Core/FileSystem/Directory.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Index.hpp>

#include <mutex>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE Manager::Mode::Automatic
#define LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY "./.library/physics/coordinate/frame/providers/iers"
#define LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT 60
#define LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_REMOTE_URL "ftp://cddis.gsfc.nasa.gov/pub/products/iers/"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{
namespace iers
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Index ;
using library::core::types::Real ;
using library::core::ctnr::Array ;
using library::core::fs::Directory ;

using library::io::URL ;

using library::math::obj::Vector2d ;

using library::physics::time::Instant ;
using library::physics::time::Duration ;
using library::physics::coord::frame::provider::iers::BulletinA ;
using library::physics::coord::frame::provider::iers::Finals2000A ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      IERS bulletins manager (thread-safe)
///
///                             The following environment variables can be defined:
///
///                             - "LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE" will override "DefaultMode"
///                             - "LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
///                             - "LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT" will override "DefaultLocalRepositoryLockTimeout"
///                             - "LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_REMOTE_URL" will override "DefaultRemoteUrl"
///
/// @ref                        https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html

class Manager
{

    public:

        enum class Mode
        {

            Manual,             ///< Manually load and unload bulletins
            Automatic           ///< Automatically fetch, load and unload bulletins (from remote repositories)

        } ;

        /// @brief              Get manager mode
        ///
        /// @return             Manager mode

        Manager::Mode           getMode                                     ( ) const ;

        /// @brief              Get local repository
        ///
        /// @return             Local repository

        Directory               getLocalRepository                          ( ) const ;

        /// @brief              Get remote URL
        ///
        /// @return             Remote URL

        URL                     getRemoteUrl                                ( ) const ;

        /// @brief              Get Bulletin A at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             Bulletin A

        BulletinA               getBulletinAAt                              (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Get Finals 2000A at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             Finals 2000A

        Finals2000A             getFinals2000AAt                            (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Get polar motion at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             [asec] Polar motion

        Vector2d                getPolarMotionAt                            (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Get UT1 - UTC at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             [sec] UT1 - UTC

        Real                    getUt1MinusUtcAt                            (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Get length of day at instant
        ///
        /// @param              [in] anInstant An instant
        /// @return             [ms] Length of day

        Real                    getLodAt                                    (   const   Instant&                    anInstant                                   ) const ;

        /// @brief              Set manager mode
        ///
        /// @param              [in] aMode A manager mode

        void                    setMode                                     (   const   Manager::Mode&              aMode                                       ) ;

        /// @brief              Set local repository
        ///
        /// @param              [in] aDirectory A repository directory

        void                    setLocalRepository                          (   const   Directory&                  aDirectory                                  ) ;

        /// @brief              Set remote URL
        ///
        /// @param              [in] aRemoteUrl A remote URL

        void                    setRemoteUrl                                (   const   URL&                        aRemoteUrl                                  ) ;

        /// @brief              Load Bulletin A
        ///
        /// @param              [in] aBulletinA A Bulletin A

        void                    loadBulletinA                               (   const   BulletinA&                  aBulletinA                                  ) ;

        /// @brief              Load Finals 2000A
        ///
        /// @param              [in] aFinals2000A A Finals 2000A

        void                    loadFinals2000A                             (   const   Finals2000A&                aFinals2000A                                ) ;

        /// @brief              Fetch latest Bulletin A file
        ///
        /// @return             Latest Bulletin A file

        File                    fetchLatestBulletinA                        ( ) ;

        /// @brief              Fetch latest Finals 2000A file
        ///
        /// @return             Latest Finals 2000A file

        File                    fetchLatestFinals2000A                      ( ) ;

        /// @brief              Reset manager
        ///
        ///                     Unload all bulletins and clear cache.

        void                    reset                                       ( ) ;

        /// @brief              Get manager singleton
        ///
        /// @return             Reference to manager

        static Manager&         Get                                         ( ) ;

        /// @brief              Get default manager mode
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE
        ///
        /// @return             Default manager mode

        static Manager::Mode    DefaultMode                                 ( ) ;

        /// @brief              Get default local repository
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY
        ///
        /// @return             Default local repository

        static Directory        DefaultLocalRepository                      ( ) ;

        /// @brief              Get default local repository lock timeout
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT
        ///
        /// @return             Default local repository lock timeout

        static Duration         DefaultLocalRepositoryLockTimeout           ( ) ;

        /// @brief              Get default remote URL
        ///
        ///                     Overriden by: LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_REMOTE_URL
        ///
        /// @return             Default remote URL

        static URL              DefaultRemoteUrl                            ( ) ;

    private:

        Manager::Mode           mode_ ;

        Directory               localRepository_ ;
        Duration                localRepositoryLockTimeout_ ;

        URL                     remoteUrl_ ;

        Array<BulletinA>        aBulletins_ ;
        Array<Finals2000A>      finals2000aArray_ ;

        mutable std::mutex      mutex_ ;

        mutable Index           aBulletinIndex_ ;
        mutable Index           finals2000aIndex_ ;

        mutable Instant         bulletinAUpdateTimestamp_ ;
        mutable Instant         finals2000AUpdateTimestamp_ ;

                                Manager                                     (   const   Manager::Mode&              aMode                                       =   Manager::DefaultMode() ) ;

        bool                    isLocalRepositoryLocked                     ( ) const ;

        File                    getLocalRepositoryLockFile                  ( ) const ;

        const BulletinA*        accessBulletinAAt                           (   const   Instant&                    anInstant                                   ) const ;

        const Finals2000A*      accessFinals2000AAt                         (   const   Instant&                    anInstant                                   ) const ;

        File                    getLatestBulletinAFile                      ( ) const ;

        File                    getLatestFinals2000AFile                    ( ) const ;

        void                    setup                                       ( ) ;

        void                    loadBulletinA_                              (   const   BulletinA&                  aBulletinA                                  ) ;

        void                    loadFinals2000A_                            (   const   Finals2000A&                aFinals2000A                                ) ;

        File                    fetchLatestBulletinA_                       ( ) ;

        File                    fetchLatestFinals2000A_                     ( ) ;

        void                    lockLocalRepository                         (   const   Duration&                   aTimeout                                    ) ;

        void                    unlockLocalRepository                       ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
