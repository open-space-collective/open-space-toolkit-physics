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

        const Shared<const Frame> gcrfSPtr = Frame::GCRF() ;

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, gcrfSPtr } ;

        EXPECT_TRUE(position.isDefined()) ;

    }

}

// TEST (Library_Physics_Coordinate_Position, EqualToOperator)
// TEST (Library_Physics_Coordinate_Position, NotEqualToOperator)
// TEST (Library_Physics_Coordinate_Position, StreamOperator)
// TEST (Library_Physics_Coordinate_Position, IsDefined)
// TEST (Library_Physics_Coordinate_Position, IsNear)
// TEST (Library_Physics_Coordinate_Position, AccessCoordinates)
// TEST (Library_Physics_Coordinate_Position, AccessFrame)
// TEST (Library_Physics_Coordinate_Position, GetCoordinates)
// TEST (Library_Physics_Coordinate_Position, GetUnit)
// TEST (Library_Physics_Coordinate_Position, InUnit)
// TEST (Library_Physics_Coordinate_Position, InFrame)
// TEST (Library_Physics_Coordinate_Position, ToString)
// TEST (Library_Physics_Coordinate_Position, Undefined)

TEST (Library_Physics_Coordinate_Position, Meters)
{

    using library::core::types::Shared ;

    using library::physics::coord::Frame ;
    using library::physics::coord::Position ;

    {

        const Shared<const Frame> gcrfSPtr = Frame::GCRF() ;

        const Position position = Position::Meters({ 0.0, 0.0, 0.0 }, gcrfSPtr) ;

        EXPECT_TRUE(Position(position).isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////