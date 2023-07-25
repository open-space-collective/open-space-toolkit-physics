/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE Manager::Mode::Automatic
#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/coordinate/frame/providers/iers"
#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT 60

#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_BULLETIN_A_MANAGER_REMOTE_URL "https://media.githubusercontent.com/media/open-space-collective/open-space-toolkit-data/main/data/coordinate/frame/providers/iers/bulletin-A/"
#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_FINALS_2000_A_MANAGER_REMOTE_URL "https://media.githubusercontent.com/media/open-space-collective/open-space-toolkit-data/main/data/coordinate/frame/providers/iers/finals-2000A/"

namespace ostk
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

using ostk::core::types::Index;
using ostk::core::types::Real;
using ostk::core::ctnr::Array;
using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::math::obj::Vector2d;

using ostk::physics::time::Instant;
using ostk::physics::time::Duration;
using ostk::physics::coord::frame::provider::iers::BulletinA;
using ostk::physics::coord::frame::provider::iers::Finals2000A;

/// @brief                      IERS bulletins manager (thread-safe)
///
///                             The following environment variables can be defined:
///
///                             - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE" will override
///                             "DefaultMode"
///                             - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY" will override
///                             "DefaultLocalRepository"
///                             - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"
///                             will override "DefaultLocalRepositoryLockTimeout"
///                             - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_REMOTE_URL" will override
///                             "DefaultRemoteUrl"
///
/// @ref                        https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html

class Manager
{
   public:
    enum class Mode
    {

        Manual,    ///< Manually load and unload bulletins
        Automatic  ///< Automatically fetch, load and unload bulletins (from remote repositories)

    };

    /// @brief              Get manager mode
    ///
    /// @return             Manager mode

    Manager::Mode getMode() const;

    /// @brief              Get local repository
    ///
    /// @return             Local repository

    Directory getLocalRepository() const;

    /// @brief              Get Bulletin A directory
    ///
    /// @return             Bulletin A directory

    Directory getBulletinADirectory() const;

    /// @brief              Get Finals 2000A directory
    ///
    /// @return             Finals 2000A directory

    Directory getFinals2000ADirectory() const;

    /// @brief              Get Bulletin A remote URL
    ///
    /// @return             Remote URL

    URL getBulletinARemoteUrl() const;

    /// @brief              Get Finals 2000A remote URL
    ///
    /// @return             Remote URL

    URL getFinals2000ARemoteUrl() const;

    /// @brief              Get array of Bulletin A
    ///
    /// @return             Array of Bulletin A

    Array<BulletinA> getBulletinAArray() const;

    /// @brief              Get Bulletin A at instant
    ///
    /// @param              [in] anInstant An instant
    /// @return             Bulletin A

    BulletinA getBulletinAAt(const Instant& anInstant) const;

    /// @brief              Get array of Finals 2000A
    ///
    /// @return             Array of Finals 2000A

    Array<Finals2000A> getFinals2000AArray() const;

    /// @brief              Get Finals 2000A at instant
    ///
    /// @param              [in] anInstant An instant
    /// @return             Finals 2000A

    Finals2000A getFinals2000AAt(const Instant& anInstant) const;

    /// @brief              Get polar motion at instant
    ///
    /// @param              [in] anInstant An instant
    /// @return             [asec] Polar motion

    Vector2d getPolarMotionAt(const Instant& anInstant) const;

    /// @brief              Get UT1 - UTC at instant
    ///
    /// @param              [in] anInstant An instant
    /// @return             [sec] UT1 - UTC

    Real getUt1MinusUtcAt(const Instant& anInstant) const;

    /// @brief              Get length of day at instant
    ///
    /// @param              [in] anInstant An instant
    /// @return             [ms] Length of day

    Real getLodAt(const Instant& anInstant) const;

    /// @brief              Set manager mode
    ///
    /// @param              [in] aMode A manager mode

    void setMode(const Manager::Mode& aMode);

    /// @brief              Set local repository
    ///
    /// @param              [in] aDirectory A repository directory

    void setLocalRepository(const Directory& aDirectory);

    /// @brief              Set Bulletin A remote URL
    ///
    /// @param              [in] aRemoteUrl A remote URL

    void setBulletinARemoteUrl(const URL& aRemoteUrl);

    /// @brief              Set Finals 2000A remote URL
    ///
    /// @param              [in] aRemoteUrl A remote URL

    void setFinals2000ARemoteUrl(const URL& aRemoteUrl);

    /// @brief              Load Bulletin A
    ///
    /// @param              [in] aBulletinA A Bulletin A

    void loadBulletinA(const BulletinA& aBulletinA);

    /// @brief              Load Finals 2000A
    ///
    /// @param              [in] aFinals2000A A Finals 2000A

    void loadFinals2000A(const Finals2000A& aFinals2000A);

    /// @brief              Fetch latest Bulletin A file
    ///
    /// @return             Latest Bulletin A file

    File fetchLatestBulletinA();

    /// @brief              Fetch latest Finals 2000A file
    ///
    /// @return             Latest Finals 2000A file

    File fetchLatestFinals2000A();

    /// @brief              Reset manager
    ///
    ///                     Unload all bulletins and clear cache.

    void reset();

    /// @brief              Clear local repository
    ///
    ///                     Delete all files in local repository.

    void clearLocalRepository();

    /// @brief              Get manager singleton
    ///
    /// @return             Reference to manager

    static Manager& Get();

    /// @brief              Get default manager mode
    ///
    ///                     Overriden by: OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE
    ///
    /// @return             Default manager mode

    static Manager::Mode DefaultMode();

    /// @brief              Get default local repository
    ///
    ///                     Overriden by: OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY
    ///
    /// @return             Default local repository

    static Directory DefaultLocalRepository();

    /// @brief              Get default local repository lock timeout
    ///
    ///                     Overriden by:
    ///                     OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT
    ///
    /// @return             Default local repository lock timeout

    static Duration DefaultLocalRepositoryLockTimeout();

    /// @brief              Get default Bulletin A remote URL
    ///
    ///                     Overriden by: OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_BULLETIN_A_MANAGER_REMOTE_URL
    ///
    /// @return             Default remote URL

    static URL DefaultBulletinARemoteUrl();

    /// @brief              Get default Finals 2000A remote URL
    ///
    ///                     Overriden by: OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_FINALS_2000_A_MANAGER_REMOTE_URL
    ///
    /// @return             Default remote URL

    static URL DefaultFinals2000ARemoteUrl();

   private:
    Manager::Mode mode_;

    Directory localRepository_;
    Duration localRepositoryLockTimeout_;

    URL bulletinARemoteUrl_;
    URL finals2000ARemoteUrl_;

    Array<BulletinA> aBulletins_;
    Array<Finals2000A> finals2000aArray_;

    mutable std::mutex mutex_;

    mutable Index aBulletinIndex_;
    mutable Index finals2000aIndex_;

    mutable Instant bulletinAUpdateTimestamp_;
    mutable Instant finals2000AUpdateTimestamp_;

    Manager(const Manager::Mode& aMode = Manager::DefaultMode());

    bool isLocalRepositoryLocked() const;

    File getLocalRepositoryLockFile() const;

    const BulletinA* accessBulletinAAt(const Instant& anInstant) const;

    const Finals2000A* accessFinals2000AAt(const Instant& anInstant) const;

    File getLatestBulletinAFile() const;

    File getLatestFinals2000AFile() const;

    void setup();

    void loadBulletinA_(const BulletinA& aBulletinA);

    void loadFinals2000A_(const Finals2000A& aFinals2000A);

    File fetchLatestBulletinA_();

    File fetchLatestFinals2000A_();

    void lockLocalRepository(const Duration& aTimeout);

    void unlockLocalRepository();
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
