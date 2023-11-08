/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Finals2000A.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE Manager::Mode::Automatic
#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/data/coordinate/frame/providers/iers"
#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT 60

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

    /// @brief              Get Bulletin A
    ///
    /// @return             Bulletin A

    BulletinA getBulletinA() const;

    /// @brief              Get Finals 2000A
    ///
    /// @return             Finals 2000A

    Finals2000A getFinals2000A() const;

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

    File fetchLatestBulletinA() const;

    /// @brief              Fetch latest Finals 2000A file
    ///
    /// @return             Latest Finals 2000A file

    File fetchLatestFinals2000A() const;

    /// @brief              Reset manager
    ///
    ///                     Unload all bulletins.

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

   private:
    Manager::Mode mode_;

    Directory localRepository_;
    Duration localRepositoryLockTimeout_;

    mutable BulletinA bulletinA_;
    mutable Finals2000A finals2000A_;

    mutable std::mutex mutex_;

    Manager(const Manager::Mode& aMode = Manager::DefaultMode());

    bool isLocalRepositoryLocked_() const;

    File getLocalRepositoryLockFile_() const;

    const BulletinA* accessBulletinA_() const;

    const Finals2000A* accessFinals2000A_() const;

    void setup_();

    void loadBulletinA_(const BulletinA& aBulletinA) const;

    void loadFinals2000A_(const Finals2000A& aFinals2000A) const;

    File fetchLatestBulletinA_() const;

    File fetchLatestFinals2000A_() const;

    void lockLocalRepository_(const Duration& aTimeout) const;

    void unlockLocalRepository_() const;
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
