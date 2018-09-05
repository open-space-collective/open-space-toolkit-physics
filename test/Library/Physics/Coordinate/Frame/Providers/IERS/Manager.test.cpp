////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Manager.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Tuple.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetBulletinAAt)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     using library::physics::coord::frame::provider::iers::BulletinA ;
//     using library::physics::coord::frame::provider::iers::Manager ;

//     {

//         const File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

//         const BulletinA bulletinA = BulletinA::Load(file) ;

//         Manager manager ;

//         manager.addBulletinA(bulletinA) ;

//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessStart())) ;
//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessEnd())) ;

//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessStart())) ;
//         EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessEnd())) ;

//     }

// }

// TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetFinals2000AAt)
// {

//     using library::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetPolarMotionAt)
{

    using library::core::types::Real ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::math::obj::Vector2d ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::Manager ;

    {

        const Array<Tuple<File, Real>> referenceScenarios =
        {
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/IERS/Manager/GetPolarMotionAt/Pole Wander 1.csv")), 1e-8 },
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/IERS/Manager/GetPolarMotionAt/Pole Wander 2.csv")), 1e-8 },
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/IERS/Manager/GetPolarMotionAt/Pole Wander 3.csv")), 1e-8 }
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const Manager manager ;

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

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetUt1MinusUtcAt)
{

    using library::core::types::Real ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Table ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::time::Scale ;
    using library::physics::time::Instant ;
    using library::physics::time::DateTime ;
    using library::physics::coord::frame::provider::iers::Manager ;

    {

        const Array<Tuple<File, Real>> referenceScenarios =
        {
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/IERS/Manager/GetUt1MinusUtcAt/DUT1 1.csv")), 1e-4 },
            { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/IERS/Manager/GetUt1MinusUtcAt/DUT1 2.csv")), 1e-4 },
            // { File::Path(Path::Parse("../test/Library/Physics/Coordinate/Frame/Providers/IERS/Manager/GetUt1MinusUtcAt/DUT1 3.csv")), 1e-4 } // [TBI] Discrepancy with STK at leap second crossing
        } ;

        for (const auto& referenceScenario : referenceScenarios)
        {

            const Manager manager ;

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

}

// TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetLodAt)
// {

//     using library::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, AddBulletinA)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     using library::physics::coord::frame::provider::iers::BulletinA ;
//     using library::physics::coord::frame::provider::iers::Manager ;

//     {

//         const File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

//         const BulletinA bulletinA = BulletinA::Load(file) ;

//         Manager manager ;

//         manager.addBulletinA(bulletinA) ;

//         EXPECT_ANY_THROW(manager.addBulletinA(bulletinA)) ;
//         EXPECT_ANY_THROW(manager.addBulletinA(BulletinA::Undefined())) ;

//     }

// }

// TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, AddFinals2000A)
// {

//     using library::physics::coord::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////