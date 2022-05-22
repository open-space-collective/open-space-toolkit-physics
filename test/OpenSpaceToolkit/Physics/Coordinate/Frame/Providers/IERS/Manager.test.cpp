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

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetMode)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetLocalRepository)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetRemoteUrl)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetBulletinAAt)
// {

//     using ostk::core::fs::Path ;
//     using ostk::core::fs::File ;

//     using ostk::physics::coord::frame::provider::iers::BulletinA ;
//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         const File file = File::Path(Path::Parse("./.open-space-toolkit/physics/coordinate/frame/providers/iers/ser7.dat")) ;

//         const BulletinA bulletinA = BulletinA::Load(file) ;

//         Manager manager ;

//         manager.loadBulletinA(bulletinA) ;

//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessStart())) ;
//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessEnd())) ;

//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessStart())) ;
//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessEnd())) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetFinals2000AAt)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, GetPolarMotionAt)
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

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, SetMode)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, SetLocalRepository)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, SetRemoteUrl)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, LoadBulletinA)
// {

//     using ostk::core::fs::Path ;
//     using ostk::core::fs::File ;

//     using ostk::physics::coord::frame::provider::iers::BulletinA ;
//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         const File file = File::Path(Path::Parse("./.open-space-toolkit/physics/coordinate/frame/providers/iers/ser7.dat")) ;

//         const BulletinA bulletinA = BulletinA::Load(file) ;

//         Manager manager ;

//         manager.loadBulletinA(bulletinA) ;

//         EXPECT_ANY_THROW(manager.loadBulletinA(bulletinA)) ;
//         EXPECT_ANY_THROW(manager.loadBulletinA(BulletinA::Undefined())) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, LoadFinals2000A)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, FetchLatestBulletinA)
// {

//     using ostk::core::fs::File ;

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         Manager& manager = Manager::Get() ;

//         const File latestBulletinA = manager.fetchLatestBulletinA() ;

//         std::cout << latestBulletinA << std::endl ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IERS_Manager, Reset)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
