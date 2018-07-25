////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Manager.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetBulletinAAt)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::coord::frame::provider::iers::BulletinA ;
    using library::physics::coord::frame::provider::iers::Manager ;

    {

        const File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        Manager manager ;

        manager.addBulletinA(bulletinA) ;

        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessStart())) ;
        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getObservationInterval().accessEnd())) ;

        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessStart())) ;
        EXPECT_NO_THROW(manager.getBulletinAAt(bulletinA.getPredictionInterval().accessEnd())) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetFinals2000AAt)
{

    using library::physics::coord::frame::provider::iers::Manager ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetPolarMotionAt)
{

    using library::physics::coord::frame::provider::iers::Manager ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, GetUt1MinusUtc)
{

    using library::physics::coord::frame::provider::iers::Manager ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, AddBulletinA)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::coord::frame::provider::iers::BulletinA ;
    using library::physics::coord::frame::provider::iers::Manager ;

    {

        const File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

        const BulletinA bulletinA = BulletinA::Load(file) ;

        Manager manager ;

        manager.addBulletinA(bulletinA) ;

        EXPECT_ANY_THROW(manager.addBulletinA(bulletinA)) ;
        EXPECT_ANY_THROW(manager.addBulletinA(BulletinA::Undefined())) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, AddFinals2000A)
{

    using library::physics::coord::frame::provider::iers::Manager ;

    {

        FAIL() ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////