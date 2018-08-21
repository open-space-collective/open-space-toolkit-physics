////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Position.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Coordinate_Position, Constructor)
{

    using library::core::types::Shared ;

    using library::physics::coord::Frame ;
    using library::physics::coord::Position ;

    {

        // const Shared<const Frame> gcrfSPtr = std::make_shared<const Frame>(Frame::GCRF()) ;
        const Shared<const Frame> gcrfSPtr = Frame::GCRFShared() ;

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, gcrfSPtr } ;

        EXPECT_TRUE(position.isDefined()) ;

    }

}

TEST (Library_Physics_Coordinate_Position, Meters)
{

    using library::core::types::Shared ;

    using library::physics::coord::Frame ;
    using library::physics::coord::Position ;

    {

        // const Shared<const Frame> gcrfSPtr = std::make_shared<const Frame>(Frame::GCRF()) ;
        const Shared<const Frame> gcrfSPtr = Frame::GCRFShared() ;

        const Position position = Position::Meters({ 0.0, 0.0, 0.0 }, gcrfSPtr) ;

        EXPECT_TRUE(Position(position).isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////