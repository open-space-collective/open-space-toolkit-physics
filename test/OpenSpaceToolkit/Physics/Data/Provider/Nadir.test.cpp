/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Provider/Nadir.hpp>

#include <Global.test.hpp>

using ostk::mathematics::object::Vector3d;

using ostk::physics::coord::Position;
using ostk::physics::coord::Frame;
using ostk::physics::Environment;
using ostk::physics::environment::object::Celestial;
using ostk::physics::data::Direction;
using ostk::physics::data::provider::Nadir;

TEST(OpenSpaceToolkit_Physics_Data_Provider_Nadir, Nadir)
{
    {
        const Environment environment = Environment::Default();
        const Celestial celestialObject = *environment.accessCelestialObjectWithName("Earth");
        const Position position = Position::Meters({7000e3, 0.0, 0.0}, Frame::ITRF());

        const Direction nadir = Nadir(position, celestialObject, environment);

        EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), nadir.getValue());
        EXPECT_TRUE(nadir.getUnit().isNone());
        EXPECT_EQ(Frame::ITRF(), nadir.getFrame());
    }
}