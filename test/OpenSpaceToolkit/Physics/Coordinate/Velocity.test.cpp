/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

#include <Global.test.hpp>

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::Velocity;
using ostk::physics::time::Instant;

TEST(OpenSpaceToolkit_Physics_Coordinate_Velocity, InFrame)
{
    {
        // The transport term (angular velocity x position) is in meters per second, so a position in feet must give
        // the same result as the same position in meters

        const Position position_GCRF = {{7000e3, 1000e3, 500e3}, Position::Unit::Meter, Frame::GCRF()};
        const Velocity velocity_GCRF = {{-1000.0, 7000.0, 100.0}, Velocity::Unit::MeterPerSecond, Frame::GCRF()};

        const Velocity velocity_ITRF = velocity_GCRF.inFrame(position_GCRF, Frame::ITRF(), Instant::J2000());
        const Velocity velocity_ITRF_fromFeet =
            velocity_GCRF.inFrame(position_GCRF.inUnit(Position::Unit::Foot), Frame::ITRF(), Instant::J2000());

        EXPECT_EQ(Velocity::Unit::MeterPerSecond, velocity_ITRF_fromFeet.getUnit());
        EXPECT_TRUE(velocity_ITRF_fromFeet.getCoordinates().isNear(velocity_ITRF.getCoordinates(), 1e-9))
            << velocity_ITRF_fromFeet << " ~ " << velocity_ITRF;
    }

    {
        EXPECT_ANY_THROW(Velocity::Undefined().inFrame(
            Position::Meters({7000e3, 0.0, 0.0}, Frame::GCRF()), Frame::ITRF(), Instant::J2000()
        ));
        EXPECT_ANY_THROW(
            Velocity::MetersPerSecond({0.0, 7000.0, 0.0}, Frame::GCRF())
                .inFrame(Position::Meters({7000e3, 0.0, 0.0}, Frame::GCRF()), Frame::Undefined(), Instant::J2000())
        );
    }
}
