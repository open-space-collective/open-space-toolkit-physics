////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetMode)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Manager& manager = Manager::Get() ;

        EXPECT_EQ(Manager::Mode::Automatic, manager.getMode()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetLocalRepository)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Manager& manager = Manager::Get() ;

        EXPECT_EQ("iers", manager.getLocalRepository().getName()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetBulletinADirectory)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Manager& manager = Manager::Get() ;

        EXPECT_EQ("bulletin-A", manager.getBulletinADirectory().getName()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetFinals2000ADirectory)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Manager& manager = Manager::Get() ;

        EXPECT_EQ("finals-2000A", manager.getFinals2000ADirectory().getName()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetRemoteUrl)
{

    using ostk::io::URL ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Manager& manager = Manager::Get() ;

        EXPECT_EQ(URL::Parse("https://maia.usno.navy.mil/ser7/"), manager.getRemoteUrl()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetBulletinAArray)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Manager& manager = Manager::Get() ;

        EXPECT_NO_THROW(manager.getBulletinAArray()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetBulletinAAt)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::physics::coord::frame::provider::iers::BulletinA ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const File file = File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        Manager& manager = Manager::Get() ;

        manager.loadBulletinA(bulletinA) ;

        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessStart())) ;
        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessEnd())) ;

        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessStart())) ;
        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessEnd())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetFinals2000AArray)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Manager& manager = Manager::Get() ;

        EXPECT_NO_THROW(manager.getFinals2000AArray()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetFinals2000AAt)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::physics::coord::frame::provider::iers::Finals2000A ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const File file = File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Finals2000A/finals2000A.data")) ;

        const Finals2000A finals2000a = Finals2000A::Load(file) ;

        Manager& manager = Manager::Get() ;

        manager.loadFinals2000A(finals2000a) ;

        EXPECT_NO_THROW(manager.getFinals2000AAt(finals2000a.getInterval().accessStart())) ;
        EXPECT_NO_THROW(manager.getFinals2000AAt(finals2000a.getInterval().accessEnd())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetPolarMotionAtPreviousTime)
{

    using ostk::core::types::Real ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;
    using ostk::core::ctnr::Table ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::math::obj::Vector2d ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Array<Tuple<File, Real>> referenceScenarios =
        {
            { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/GetPolarMotionAt/Pole Wander 1.csv")), 1e-8 },
            { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/GetPolarMotionAt/Pole Wander 2.csv")), 1e-8 },
            { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/GetPolarMotionAt/Pole Wander 3.csv")), 1e-8 }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const Manager& manager = Manager::Get() ;

            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario) ;
            const Real tolerance = std::get<1>(referenceScenario) ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            // Test

            for (const auto& referenceRow : referenceData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI) ;

                const Vector2d referencePolarMotion_rad = { referenceRow[1].accessReal(), referenceRow[2].accessReal() } ;

                const Vector2d polarMotion_rad = manager.getPolarMotionAt(instant) * (Real::Pi() / 180.0 / 3600.0) ;

                EXPECT_TRUE(polarMotion_rad.isNear(referencePolarMotion_rad, tolerance)) << String::Format("{} - {} ~ {}", instant.toString(Scale::TAI), referencePolarMotion_rad.toString(), polarMotion_rad.toString()) ;

            }

        }

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetPolarMotionAtFutureTime)
{

    using ostk::core::types::Real ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;
    using ostk::core::ctnr::Table ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::math::obj::Vector2d ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Duration ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {
        const Manager& manager = Manager::Get() ;

        const Instant instant = Instant::Now() + Duration::Weeks(12.0) ;

        manager.getPolarMotionAt(instant) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetUt1MinusUtcAt)
{

    using ostk::core::types::Real ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;
    using ostk::core::ctnr::Table ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::DateTime ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const Array<Tuple<File, Real>> referenceScenarios =
        {
            { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/GetUt1MinusUtcAt/DUT1 1.csv")), 1e-4 },
            { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/GetUt1MinusUtcAt/DUT1 2.csv")), 1e-4 },
            // { File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/GetUt1MinusUtcAt/DUT1 3.csv")), 1e-4 } // [TBI] Discrepancy with STK at leap second crossing
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const Manager& manager = Manager::Get() ;

            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario) ;
            const Real tolerance = std::get<1>(referenceScenario) ;

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true) ;

            // Test

            for (const auto& referenceRow : referenceData)
            {

                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI) ;

                const Real referenceDUT1 = { referenceRow[3].accessReal() } ;

                const Real dUT1 = manager.getUt1MinusUtcAt(instant) ;

                EXPECT_NEAR(referenceDUT1, dUT1, tolerance) << String::Format("{} - {} ~ {}", instant.toString(Scale::TAI), referenceDUT1, dUT1) ;

            }

        }

    }

    {

        const Manager& manager = Manager::Get() ;

        const Instant instant = Instant::DateTime(DateTime(2018, 10, 10, 0, 0, 0), Scale::UTC) ;

        EXPECT_NO_THROW(manager.getUt1MinusUtcAt(instant)) ;

    }

}

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetLodAt)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, SetMode)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        Manager& manager = Manager::Get() ;

        EXPECT_EQ(Manager::Mode::Automatic, manager.getMode()) ;

        manager.setMode(Manager::Mode::Manual) ;

        EXPECT_EQ(Manager::Mode::Manual, manager.getMode()) ;

        manager.setMode(Manager::Mode::Automatic) ;

        EXPECT_EQ(Manager::Mode::Automatic, manager.getMode()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, SetLocalRepository)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        Manager& manager = Manager::Get() ;

        EXPECT_EQ("iers", manager.getLocalRepository().getName()) ;

        manager.setLocalRepository(Directory::Path(Path::Parse("/tmp"))) ;

        EXPECT_EQ("tmp", manager.getLocalRepository().getName()) ;

        manager.setLocalRepository(Directory::Path(Path::Parse("./.open-space-toolkit/physics/coordinate/frame/providers/iers"))) ;

        EXPECT_EQ("iers", manager.getLocalRepository().getName()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, SetRemoteUrl)
{

    using ostk::io::URL ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        Manager& manager = Manager::Get() ;

        EXPECT_EQ(URL::Parse("https://maia.usno.navy.mil/ser7/"), manager.getRemoteUrl()) ;

        manager.setRemoteUrl(URL::Parse("http://example.com")) ;

        EXPECT_EQ(URL::Parse("http://example.com"), manager.getRemoteUrl()) ;

        manager.setRemoteUrl(URL::Parse("https://maia.usno.navy.mil/ser7/")) ;

        EXPECT_EQ(URL::Parse("https://maia.usno.navy.mil/ser7/"), manager.getRemoteUrl()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, LoadBulletinA)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::physics::coord::frame::provider::iers::BulletinA ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const File file = File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/BulletinA/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        Manager& manager = Manager::Get() ;

        manager.reset() ;
        manager.loadBulletinA(bulletinA) ;

        EXPECT_ANY_THROW(manager.loadBulletinA(bulletinA)) ;
        EXPECT_ANY_THROW(manager.loadBulletinA(BulletinA::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, LoadFinals2000A)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::physics::coord::frame::provider::iers::Finals2000A ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        const File file = File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Finals2000A/finals2000A.data")) ;

        const Finals2000A finals2000a = Finals2000A::Load(file) ;

        Manager& manager = Manager::Get() ;

        manager.reset() ;
        manager.loadFinals2000A(finals2000a) ;

        EXPECT_ANY_THROW(manager.loadFinals2000A(finals2000a)) ;
        EXPECT_ANY_THROW(manager.loadFinals2000A(Finals2000A::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, FetchLatestBulletinA)
{

    using ostk::core::fs::File ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        Manager& manager = Manager::Get() ;

        manager.reset() ;
        manager.clearLocalRepository() ;

        const File latestBulletinA = manager.fetchLatestBulletinA() ;

        EXPECT_EQ("ser7.dat", latestBulletinA.getName()) ;
        EXPECT_EQ("bulletin-A", latestBulletinA.getParentDirectory().getParentDirectory().getName()) ;
        EXPECT_EQ(manager.getLocalRepository().getPath().getNormalizedPath(), latestBulletinA.getParentDirectory().getParentDirectory().getParentDirectory().getPath().getNormalizedPath()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, FetchLatestFinals2000A)
{

    using ostk::core::fs::File ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        Manager& manager = Manager::Get() ;

        manager.reset() ;
        manager.clearLocalRepository() ;

        const File latestFinals2000A = manager.fetchLatestFinals2000A() ;

        EXPECT_EQ("finals2000A.data", latestFinals2000A.getName()) ;
        EXPECT_EQ("finals-2000A", latestFinals2000A.getParentDirectory().getParentDirectory().getName()) ;
        EXPECT_EQ(manager.getLocalRepository().getPath().getNormalizedPath(), latestFinals2000A.getParentDirectory().getParentDirectory().getParentDirectory().getPath().getNormalizedPath()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, Reset)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        Manager& manager = Manager::Get() ;

        manager.reset() ;

        EXPECT_TRUE(manager.getBulletinAArray().isEmpty()) ;
        EXPECT_TRUE(manager.getFinals2000AArray().isEmpty()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, ClearLocalRepository)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        Manager& manager = Manager::Get() ;

        manager.clearLocalRepository() ;

        EXPECT_TRUE(manager.getBulletinADirectory().isEmpty()) ;
        EXPECT_TRUE(manager.getFinals2000ADirectory().isEmpty()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, Get)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        EXPECT_NO_THROW(Manager::Get()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, DefaultMode)
{

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        EXPECT_EQ(Manager::Mode::Automatic, Manager::DefaultMode()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, DefaultLocalRepository)
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        EXPECT_EQ("iers", Manager::DefaultLocalRepository().getName()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, DefaultLocalRepositoryLockTimeout)
{

    using ostk::physics::time::Duration ;
    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        EXPECT_EQ(Duration::Seconds(60.0), Manager::DefaultLocalRepositoryLockTimeout()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, DefaultRemoteUrl)
{

    using ostk::io::URL ;

    using ostk::physics::coord::frame::provider::iers::Manager ;

    {

        EXPECT_EQ(URL::Parse("https://maia.usno.navy.mil/ser7/"), Manager::DefaultRemoteUrl()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
