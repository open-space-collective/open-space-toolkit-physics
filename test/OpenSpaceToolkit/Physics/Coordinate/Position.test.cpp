/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::type::Shared;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::Environment;
using ostk::physics::environment::object::celestial::Earth;
using ostk::physics::time::Instant;
using ostk::physics::unit::Length;

class OpenSpaceToolkit_Physics_Coordinate_Position : public ::testing::Test
{
   protected:
    const Vector3d vector_ = {0.0, 0.0, 0.0};

    Position positionGCRF_ = {vector_, Position::Unit::Meter, Frame::GCRF()};
    Position positionITRF_ = {vector_, Position::Unit::Meter, Frame::ITRF()};
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
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << positionGCRF_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
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
        EXPECT_ANY_THROW(positionGCRF_.isNear(positionGCRF_, Length::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, AccessCoordinates)
{
    {
        EXPECT_EQ(Vector3d(0.0, 0.0, 0.0), positionGCRF_.accessCoordinates());
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
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, GetCoordinates)
{
    {
        EXPECT_EQ(vector_, positionGCRF_.getCoordinates());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, GetNorm)
{
    {
        const Position position = {{3.0, -4.0, 12.0}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_EQ(Length::Meters(13.0), position.getNorm());
    }

    {
        const Position position = {{3.0, -4.0, 12.0}, Position::Unit::Foot, Frame::GCRF()};

        EXPECT_EQ(Length(13.0, Length::Unit::Foot), position.getNorm());
    }

    {
        const Position position = {{0.0, 0.0, 0.0}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_EQ(Length(0.0, Length::Unit::Meter), position.getNorm());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, GetUnit)
{
    {
        EXPECT_EQ(Position::Unit::Meter, positionGCRF_.getUnit());
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
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, InFrame)
{
    using ostk::physics::time::Instant;
    using FrameManager = ostk::physics::coordinate::frame::Manager;

    {
        const Position position_GCRF = {{7000e3, 1000e3, 500e3}, Position::Unit::Meter, Frame::GCRF()};

        const Position position_ITRF = position_GCRF.inFrame(Frame::ITRF(), Instant::J2000());

        EXPECT_TRUE(
            position_ITRF.getCoordinates().isNear(Vector3d(254638.49423473, 7066495.80292154, 499796.263037414), 1e-3)
        ) << position_ITRF;
        EXPECT_EQ(Position::Unit::Meter, position_ITRF.getUnit()) << position_ITRF;
        EXPECT_EQ(Frame::ITRF(), position_ITRF.accessFrame()) << position_ITRF;
    }

    {
        EXPECT_ANY_THROW(positionGCRF_.inFrame(Frame::ITRF(), Instant::Undefined()));
    }

    {
        const Position position_GCRF = {{7000e3, 1000e3, 500e3}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_NO_THROW(position_GCRF.inFrame(Frame::ITRF(), Instant::J2000()));

        FrameManager::Get().clearAllFrames();

        EXPECT_NO_THROW(position_GCRF.inFrame(Frame::ITRF(), Instant::J2000()));
    }

    {
        // Frame shifted from ITRF, as a ground station local frame: the transform translation is in meters, so a
        // position in feet must give the same result as the same position in meters

        using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
        using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
        using ostk::physics::coordinate::frame::provider::Static;
        using ostk::physics::coordinate::Transform;
        using ostk::physics::unit::Angle;

        const Shared<const Frame> stationFrameSPtr = Frame::Construct(
            "Station",
            false,
            Frame::ITRF(),
            std::make_shared<Static>(Static(Transform::Passive(
                Instant::J2000(),
                Vector3d(-4.0e6, 3.0e6, 3.5e6),
                Vector3d::Zero(),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(30.0))),
                Vector3d::Zero()
            )))
        );

        const Position position_GCRF = {{7000e3, 1000e3, 500e3}, Position::Unit::Meter, Frame::GCRF()};
        const Position position_GCRF_ft = position_GCRF.inUnit(Position::Unit::Foot);

        const Position position_STATION = position_GCRF.inFrame(stationFrameSPtr, Instant::J2000());
        const Position position_STATION_ft = position_GCRF_ft.inFrame(stationFrameSPtr, Instant::J2000());

        EXPECT_EQ(Position::Unit::Foot, position_STATION_ft.getUnit());
        EXPECT_EQ(stationFrameSPtr, position_STATION_ft.accessFrame());
        EXPECT_TRUE(position_STATION_ft.inMeters().getCoordinates().isNear(position_STATION.getCoordinates(), 1e-6))
            << position_STATION_ft.inMeters() << " ~ " << position_STATION;

        const Position position_GCRF_ft_roundTrip = position_STATION_ft.inFrame(Frame::GCRF(), Instant::J2000());

        EXPECT_EQ(Position::Unit::Foot, position_GCRF_ft_roundTrip.getUnit());
        EXPECT_TRUE(position_GCRF_ft_roundTrip.inMeters().getCoordinates().isNear(position_GCRF.getCoordinates(), 1e-6))
            << position_GCRF_ft_roundTrip.inMeters() << " ~ " << position_GCRF;

        Frame::Destruct("Station");
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, ToString)
{
    {
        const Position position = {{1.0, 2.0, 3.0}, Position::Unit::Meter, Frame::GCRF()};

        EXPECT_EQ("[1.0, 2.0, 3.0] [m] @ GCRF", position.toString()) << position.toString();
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, Meters)
{
    {
        const Shared<const Frame> gcrfSPtr = Frame::GCRF();

        const Position position = Position::Meters({0.0, 0.0, 0.0}, gcrfSPtr);

        EXPECT_EQ(position, Position(position));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, FromLLA)
{
    const Shared<const Earth> earthSPtr = std::make_shared<const Earth>(Earth::Default());

    const LLA lla = LLA::Vector({0.0, 0.0, 0.0});

    {
        EXPECT_THROW(Position::FromLLA(lla), ostk::core::error::RuntimeError);
    }

    {
        const Position position = Position::FromLLA(lla, earthSPtr);
        EXPECT_VECTORS_ALMOST_EQUAL(position.accessCoordinates(), Vector3d(6378137.0, 0.0, 0.0), 1e-8);
    }

    {
        Environment::Default(true);

        const Position position = Position::FromLLA(lla);
        EXPECT_VECTORS_ALMOST_EQUAL(position.accessCoordinates(), Vector3d(6378137.0, 0.0, 0.0), 1e-8);

        Environment::ResetGlobalInstance();
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, Constructor_NullFrame)
{
    EXPECT_THROW(Position({0.0, 0.0, 0.0}, Position::Unit::Meter, nullptr), ostk::core::error::runtime::Undefined);
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Position, InFrame_NullFrame)
{
    const Position position = Position::Meters({1.0, 2.0, 3.0}, Frame::GCRF());

    EXPECT_THROW(position.inFrame(nullptr, Instant::J2000()), ostk::core::error::runtime::Undefined);
}
