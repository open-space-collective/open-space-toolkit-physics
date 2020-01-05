////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Coordinate/Position.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, Constructor)
{

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        EXPECT_NO_THROW(Position position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, EqualToOperator)
{

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        EXPECT_TRUE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) == Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF())) ;
        EXPECT_TRUE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::ITRF()) == Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::ITRF())) ;

    }

    {

        EXPECT_FALSE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) == Position({ 1.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF())) ;
        EXPECT_FALSE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) == Position({ 0.0, 0.0, 0.0 }, Position::Unit::Foot, Frame::GCRF())) ;
        EXPECT_FALSE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) == Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::ITRF())) ;

    }

    {

        EXPECT_FALSE(Position::Undefined() == Position::Undefined()) ;
        EXPECT_FALSE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) == Position::Undefined()) ;
        EXPECT_FALSE(Position::Undefined() == Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, NotEqualToOperator)
{

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        EXPECT_FALSE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) != Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF())) ;
        EXPECT_FALSE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::ITRF()) != Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::ITRF())) ;

    }

    {

        EXPECT_TRUE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) != Position({ 1.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF())) ;
        EXPECT_TRUE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) != Position({ 0.0, 0.0, 0.0 }, Position::Unit::Foot, Frame::GCRF())) ;
        EXPECT_TRUE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) != Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::ITRF())) ;

    }

    {

        EXPECT_TRUE(Position::Undefined() != Position::Undefined()) ;
        EXPECT_TRUE(Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF()) != Position::Undefined()) ;
        EXPECT_TRUE(Position::Undefined() != Position({ 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, StreamOperator)
{

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << position << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, IsDefined)
{

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_TRUE(position.isDefined()) ;

    }

    {

        EXPECT_FALSE(Position::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, IsNear)
{

    using ostk::physics::units::Length ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_TRUE(position.isNear(position, Length::Meters(0.0))) ;

    }

    {

        const Position firstPosition = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;
        const Position secondPosition = { { 1.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_TRUE(firstPosition.isNear(secondPosition, Length::Meters(1.0))) ;
        EXPECT_FALSE(firstPosition.isNear(secondPosition, Length::Meters(0.9))) ;

    }

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_ANY_THROW(Position::Undefined().isNear(Position::Undefined(), Length::Undefined())) ;
        EXPECT_ANY_THROW(position.isNear(Position::Undefined(), Length::Meters(0.0))) ;
        EXPECT_ANY_THROW(Position::Undefined().isNear(position, Length::Meters(0.0))) ;
        EXPECT_ANY_THROW(position.isNear(position, Length::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, AccessCoordinates)
{

    using ostk::math::obj::Vector3d ;

    using ostk::physics::units::Length ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), position.accessCoordinates()) ;

    }

    {

        EXPECT_ANY_THROW(Position::Undefined().accessCoordinates()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, AccessFrame)
{

    using ostk::physics::units::Length ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_EQ(Frame::GCRF(), position.accessFrame()) ;

    }

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::ITRF() } ;

        EXPECT_EQ(Frame::ITRF(), position.accessFrame()) ;

    }

    {

        EXPECT_ANY_THROW(Position::Undefined().accessFrame()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, GetCoordinates)
{

    using ostk::math::obj::Vector3d ;

    using ostk::physics::units::Length ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), position.getCoordinates()) ;

    }

    {

        EXPECT_ANY_THROW(Position::Undefined().getCoordinates()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, GetUnit)
{

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_EQ(Position::Unit::Meter, position.getUnit()) ;

    }

    {

        EXPECT_ANY_THROW(Position::Undefined().getUnit()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, InUnit)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 1.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_TRUE(position.inUnit(Position::Unit::Foot).getCoordinates().isNear(Vector3d(3.28083989501312, 0.0, 0.0), 1e-14)) ;
        EXPECT_EQ(Position::Unit::Foot, position.inUnit(Position::Unit::Foot).getUnit()) ;
        EXPECT_EQ(Frame::GCRF(), position.inUnit(Position::Unit::Foot).accessFrame()) ;

    }

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_ANY_THROW(Position::Undefined().inUnit(Position::Unit::Meter)) ;
        EXPECT_ANY_THROW(position.inUnit(Position::Unit::Undefined)) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, InMeters)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 1.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), position.inMeters().getCoordinates()) ;
        EXPECT_EQ(Position::Unit::Meter, position.inMeters().getUnit()) ;
        EXPECT_EQ(Frame::GCRF(), position.inMeters().accessFrame()) ;

    }

    {

        EXPECT_ANY_THROW(Position::Undefined().inMeters()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, InFrame)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::units::Length ;
    using ostk::physics::time::Instant ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position_GCRF = { { 7000e3, 1000e3, 500e3 }, Position::Unit::Meter, Frame::GCRF() } ;

        const Position position_ITRF = position_GCRF.inFrame(Frame::ITRF(), Instant::J2000()) ;

        EXPECT_TRUE(position_ITRF.getCoordinates().isNear(Vector3d(254638.493586864, 7066495.80294488, 499796.263037415), 1e-8)) << position_ITRF ;
        EXPECT_EQ(Position::Unit::Meter, position_ITRF.getUnit()) << position_ITRF ;
        EXPECT_EQ(Frame::ITRF(), position_ITRF.accessFrame()) << position_ITRF ;

    }

    {

        const Position position = { { 0.0, 0.0, 0.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_ANY_THROW(Position::Undefined().inFrame(Frame::ITRF(), Instant::J2000())) ;
        EXPECT_ANY_THROW(position.inFrame(Frame::Undefined(), Instant::J2000())) ;
        EXPECT_ANY_THROW(position.inFrame(Frame::ITRF(), Instant::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, ToString)
{

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Position position = { { 1.0, 2.0, 3.0 }, Position::Unit::Meter, Frame::GCRF() } ;

        EXPECT_EQ("[1.0, 2.0, 3.0] [m] @ GCRF", position.toString()) << position.toString() ;

    }

    {

        EXPECT_ANY_THROW(Position::Undefined().toString()) ;

    }

}

TEST (OpenSpaceToolkit_Physics_Coordinate_Position, Undefined)
{

    using ostk::physics::coord::Position ;

    {

        EXPECT_NO_THROW(Position::Undefined()) ;

        EXPECT_FALSE(Position::Undefined().isDefined()) ;

    }

}


TEST (OpenSpaceToolkit_Physics_Coordinate_Position, Meters)
{

    using ostk::core::types::Shared ;

    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;

    {

        const Shared<const Frame> gcrfSPtr = Frame::GCRF() ;

        const Position position = Position::Meters({ 0.0, 0.0, 0.0 }, gcrfSPtr) ;

        EXPECT_TRUE(Position(position).isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
