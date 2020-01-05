////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Data/Providers/Nadir.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Data/Providers/Nadir.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Data_Providers_Nadir, Nadir)
{

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Position ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::Environment ;
    using ostk::physics::env::obj::Celestial ;
    using ostk::physics::data::Direction ;
    using ostk::physics::data::providers::Nadir ;

    {

        const Environment environment = Environment::Default() ;
        const Celestial celestialObject = *environment.accessCelestialObjectWithName("Earth") ;
        const Position position = Position::Meters({ 7000e3, 0.0, 0.0 }, Frame::ITRF()) ;

        const Direction nadir = Nadir(position, celestialObject, environment) ;

        EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), nadir.getValue()) ;
        EXPECT_TRUE(nadir.getUnit().isNone()) ;
        EXPECT_EQ(Frame::ITRF(), nadir.getFrame()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
