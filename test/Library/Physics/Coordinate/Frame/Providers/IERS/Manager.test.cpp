////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/IERS/Manager.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/IERS/Manager.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, AccessBulletinAAt)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::coord::frame::provider::iers::BulletinA ;
    using library::physics::coord::frame::provider::iers::Manager ;

    {

        File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

        BulletinA bulletinA = BulletinA::Load(file) ;

        Manager manager ;

        manager.addBulletinA(bulletinA) ;

        EXPECT_NO_THROW(manager.accessBulletinAAt(bulletinA.getObservationInterval().accessStart())) ;
        EXPECT_NO_THROW(manager.accessBulletinAAt(bulletinA.getObservationInterval().accessEnd())) ;

        EXPECT_NO_THROW(manager.accessBulletinAAt(bulletinA.getPredictionInterval().accessStart())) ;
        EXPECT_NO_THROW(manager.accessBulletinAAt(bulletinA.getPredictionInterval().accessEnd())) ;

    }

}

TEST (Library_Physics_Coordinate_Frame_Providers_IERS_Manager, AddBulletinA)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    using library::physics::coord::frame::provider::iers::BulletinA ;
    using library::physics::coord::frame::provider::iers::Manager ;

    {

        File file = File::Path(Path::Parse("/app/share/data/ser7.dat")) ;

        BulletinA bulletinA = BulletinA::Load(file) ;

        Manager manager ;

        manager.addBulletinA(bulletinA) ;

        EXPECT_ANY_THROW(manager.addBulletinA(bulletinA)) ;
        EXPECT_ANY_THROW(manager.addBulletinA(BulletinA::Undefined())) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////