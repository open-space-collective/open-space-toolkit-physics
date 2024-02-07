/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>

#include <Global.test.hpp>

using ostk::core::type::Shared;
using ostk::core::type::Real;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coord::Frame;
using ostk::physics::coord::Position;
using ostk::physics::units::Length;

class OpenSpaceToolkit_Physics_Coordinate_Position : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        positionGCRF_ = {vector_, Position::Unit::Meter, Frame::GCRF()};
        positionITRF_ = {vector_, Position::Unit::Meter, Frame::ITRF()};
    }

    const Vector3d vector_ = {0.0, 0.0, 0.0};

    Position positionGCRF_ = Position::Undefined();
    Position positionITRF_ = Position::Undefined();
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, EqualToOperator)
{
    {
        EXPECT_TRUE(positionGCRF_ == positionGCRF_);
        EXPECT_TRUE(positionITRF_ == positionITRF_);
    }

    {
        EXPECT_FALSE(positionGCRF_ == Position({1.0, 0.0, 0.0}, Position::Unit::Meter, Frame::GCRF()));
        EXPECT_FALSE(positionGCRF_ == Position({0.0, 0.0, 0.0}, Position::Unit::Foot, Frame::GCRF()));
        EXPECT_FALSE(positionGCRF_ == positionITRF_);
    }

    {
        EXPECT_FALSE(Position::Undefined() == Position::Undefined());
        EXPECT_FALSE(positionGCRF_ == Position::Undefined());
        EXPECT_FALSE(Position::Undefined() == positionGCRF_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, NotEqualToOperator)
{
    {
        EXPECT_FALSE(positionGCRF_ != positionGCRF_);
        EXPECT_FALSE(positionITRF_ != positionITRF_);
    }

    {
        EXPECT_TRUE(positionGCRF_ != Position({1.0, 0.0, 0.0}, Position::Unit::Meter, Frame::GCRF()));
        EXPECT_TRUE(positionGCRF_ != Position({0.0, 0.0, 0.0}, Position::Unit::Foot, Frame::GCRF()));
        EXPECT_TRUE(positionGCRF_ != positionITRF_);
    }

    {
        EXPECT_TRUE(Position::Undefined() != Position::Undefined());
        EXPECT_TRUE(positionGCRF_ != Position::Undefined());
        EXPECT_TRUE(Position::Undefined() != positionGCRF_);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << positionGCRF_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, IsDefined)
{
    {
        EXPECT_TRUE(positionGCRF_.isDefined());
    }

    {
        EXPECT_FALSE(Position::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, IsNear)
{
    {
        EXPECT_TRUE(positionGCRF_.isNear(positionGCRF_, Length::Meters(0.0)));
    }

    {
        const Position firstPosition = {{0.0, 0.0, 0.0}, Position::Unit::Meter, Frame::GCRF()};
        const Position secondPosition = {{1.0, 0.0, 0.0}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_TRUE(firstPosition.isNear(secondPosition, Length::Meters(1.0)));
        EXPECT_FALSE(firstPosition.isNear(secondPosition, Length::Meters(0.9)));
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().isNear(Position::Undefined(), Length::Undefined()));
        EXPECT_ANY_THROW(positionGCRF_.isNear(Position::Undefined(), Length::Meters(0.0)));
        EXPECT_ANY_THROW(Position::Undefined().isNear(positionGCRF_, Length::Meters(0.0)));
        EXPECT_ANY_THROW(positionGCRF_.isNear(positionGCRF_, Length::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, AccessCoordinates)
{
    {
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), positionGCRF_.accessCoordinates());
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().accessCoordinates());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, AccessFrame)
{
    {
        EXPECT_EQ(Frame::GCRF(), positionGCRF_.accessFrame());
    }

    {
        EXPECT_EQ(Frame::ITRF(), positionITRF_.accessFrame());
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().accessFrame());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, GetCoordinates)
{
    {
        EXPECT_EQ(vector_, positionGCRF_.getCoordinates());
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().getCoordinates());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, GetUnit)
{
    {
        EXPECT_EQ(Position::Unit::Meter, positionGCRF_.getUnit());
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().getUnit());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, InUnit)
{
    {
        const Position position = {{1.0, 0.0, 0.0}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_TRUE(
            position.inUnit(Position::Unit::Foot).getCoordinates().isNear(Vector3d(3.28083989501312, 0.0, 0.0), 1e-14)
        );
        EXPECT_EQ(Position::Unit::Foot, position.inUnit(Position::Unit::Foot).getUnit());
        EXPECT_EQ(Frame::GCRF(), position.inUnit(Position::Unit::Foot).accessFrame());
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().inUnit(Position::Unit::Meter));
        EXPECT_ANY_THROW(positionGCRF_.inUnit(Position::Unit::Undefined));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, InMeters)
{
    {
        const Position position = {{1.0, 0.0, 0.0}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), position.inMeters().getCoordinates());
        EXPECT_EQ(Position::Unit::Meter, position.inMeters().getUnit());
        EXPECT_EQ(Frame::GCRF(), position.inMeters().accessFrame());
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().inMeters());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, InFrame)
{
    using ostk::physics::time::Instant;

    {
        const Position position_GCRF = {{7000e3, 1000e3, 500e3}, Position::Unit::Meter, Frame::GCRF()};

        const Position position_ITRF = position_GCRF.inFrame(Frame::ITRF(), Instant::J2000());

        EXPECT_TRUE(
            position_ITRF.getCoordinates().isNear(Vector3d(254638.493586864, 7066495.80294488, 499796.263037415), 1e-8)
        ) << position_ITRF;
        EXPECT_EQ(Position::Unit::Meter, position_ITRF.getUnit()) << position_ITRF;
        EXPECT_EQ(Frame::ITRF(), position_ITRF.accessFrame()) << position_ITRF;
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().inFrame(Frame::ITRF(), Instant::J2000()));
        EXPECT_ANY_THROW(positionGCRF_.inFrame(Frame::Undefined(), Instant::J2000()));
        EXPECT_ANY_THROW(positionGCRF_.inFrame(Frame::ITRF(), Instant::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, ToString)
{
    {
        const Position position = {{1.0, 2.0, 3.0}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_EQ("[1.0, 2.0, 3.0] [m] @ GCRF", position.toString()) << position.toString();
    }

    {
        EXPECT_ANY_THROW(Position::Undefined().toString());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, Undefined)
{
    {
        EXPECT_NO_THROW(Position::Undefined());

        EXPECT_FALSE(Position::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, Meters)
{
    {
        const Shared<const Frame> gcrfSPtr = Frame::GCRF();

        const Position position = Position::Meters({0.0, 0.0, 0.0}, gcrfSPtr);

        EXPECT_TRUE(Position(position).isDefined());
    }
}
