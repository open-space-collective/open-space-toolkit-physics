/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager__

#include <mutex>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/BulletinA.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A.hpp>
#include <OpenSpaceToolkit/Physics/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#define OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY \
    "./.open-space-toolkit/physics/data/coordinate/frame/provider/iers"

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{
namespace iers
{

using ostk::core::container::Array;
using ostk::core::filesystem::Directory;
using ostk::core::type::Index;
using ostk::core::type::Real;

using ostk::mathematics::object::Vector2d;

using ostk::physics::coordinate::frame::provider::iers::BulletinA;
using ostk::physics::coordinate::frame::provider::iers::Finals2000A;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using BaseManager = ostk::physics::Manager;

/// @brief IERS bulletins manager (thread-safe)
///
/// The following environment variables can be defined:
///
/// - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_MODE" will override "DefaultMode"
/// - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY" will override "DefaultLocalRepository"
/// - "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT"
/// will override "DefaultLocalRepositoryLockTimeout"
///
/// @ref https://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html
class Manager : public BaseManager
{
   public:
    /// @brief Get Bulletin A directory
    ///
    /// @code
    ///     Directory directory = Manager::Get().getBulletinADirectory();
    /// @endcode
    ///
    /// @return Bulletin A directory
    Directory getBulletinADirectory() const;

    /// @brief Get Finals 2000A directory
    ///
    /// @code
    ///     Directory directory = Manager::Get().getFinals2000ADirectory();
    /// @endcode
    ///
    /// @return Finals 2000A directory
    Directory getFinals2000ADirectory() const;

    /// @brief Get Bulletin A
    ///
    /// @code
    ///     BulletinA bulletinA = Manager::Get().getBulletinA();
    /// @endcode
    ///
    /// @return Bulletin A
    BulletinA getBulletinA() const;

    /// @brief Get Finals 2000A
    ///
    /// @code
    ///     Finals2000A finals2000A = Manager::Get().getFinals2000A();
    /// @endcode
    ///
    /// @return Finals 2000A
    Finals2000A getFinals2000A() const;

    /// @brief Get polar motion at instant
    ///
    /// @code
    ///     Vector2d polarMotion = Manager::Get().getPolarMotionAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return [asec] Polar motion
    Vector2d getPolarMotionAt(const Instant& anInstant) const;

    /// @brief Get UT1 - UTC at instant
    ///
    /// @code
    ///     Real ut1MinusUtc = Manager::Get().getUt1MinusUtcAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return [sec] UT1 - UTC
    Real getUt1MinusUtcAt(const Instant& anInstant) const;

    /// @brief Get length of day at instant
    ///
    /// @code
    ///     Real lod = Manager::Get().getLodAt(anInstant);
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return [ms] Length of day
    Real getLodAt(const Instant& anInstant) const;

    /// @brief Load Bulletin A
    ///
    /// @code
    ///     Manager::Get().loadBulletinA(bulletinA);
    /// @endcode
    ///
    /// @param [in] aBulletinA A Bulletin A
    void loadBulletinA(const BulletinA& aBulletinA);

    /// @brief Load Finals 2000A
    ///
    /// @code
    ///     Manager::Get().loadFinals2000A(finals2000A);
    /// @endcode
    ///
    /// @param [in] aFinals2000A A Finals 2000A
    void loadFinals2000A(const Finals2000A& aFinals2000A);

    /// @brief Fetch latest Bulletin A file
    ///
    /// @code
    ///     File file = Manager::Get().fetchLatestBulletinA();
    /// @endcode
    ///
    /// @return Latest Bulletin A file
    File fetchLatestBulletinA() const;

    /// @brief Fetch latest Finals 2000A file
    ///
    /// @code
    ///     File file = Manager::Get().fetchLatestFinals2000A();
    /// @endcode
    ///
    /// @return Latest Finals 2000A file
    File fetchLatestFinals2000A() const;

    /// @brief Reset manager
    ///
    /// @code
    ///     Manager::Get().reset();
    /// @endcode
    ///
    /// Unload all bulletins.
    virtual void reset() override;

    /// @brief Clear local repository
    ///
    /// @code
    ///     Manager::Get().clearLocalRepository();
    /// @endcode
    ///
    /// Delete all files in local repository.
    void clearLocalRepository();

    /// @brief Get manager singleton
    ///
    /// @code
    ///     Manager& manager = Manager::Get();
    /// @endcode
    ///
    /// @return Reference to manager
    static Manager& Get();

   private:
    mutable BulletinA bulletinA_;
    mutable Finals2000A finals2000A_;

    Manager();

    virtual void setup_() override;

    // const private methods that modify mutable members
    // none of these are mutex-protected, but are called exclusively by methods that are
    void loadBulletinA_(const BulletinA& aBulletinA) const;
    void loadFinals2000A_(const Finals2000A& aFinals2000A) const;

    const BulletinA* accessBulletinA_() const;
    const Finals2000A* accessFinals2000A_() const;

    File fetchLatestBulletinA_() const;
    File fetchLatestFinals2000A_() const;
};

}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
