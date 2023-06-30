/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

using ostk::core::types::String;
using ostk::core::types::Real;

using ostk::physics::units::Length;
using ostk::physics::units::Angle;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::coord::Frame;
using ostk::physics::environment::atmospheric::earth::NRLMSISE00;
using EarthCelestialBody = ostk::physics::env::obj::celest::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Constructor)
{
    {
        EXPECT_NO_THROW(NRLMSISE00 nrlmsise = {});
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Clone)
{
    {
        const NRLMSISE00 nrlmsise = {};

        EXPECT_NO_THROW(const NRLMSISE00* nrlmsisePtr = nrlmsise.clone(); delete nrlmsisePtr;);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, IsDefined)
{
    using ostk::physics::environment::atmospheric::earth::NRLMSISE00;

    {
        const NRLMSISE00 nrlmsise = {};

        EXPECT_TRUE(nrlmsise.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, getDensityAt)
{
    {
        const NRLMSISE00 nrlmsise = {};

        const LLA lla = LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0));

        const Position position = {
            lla.toCartesian(
                EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
            ),
            Position::Unit::Meter,
            Frame::ITRF()};

        const Real density = nrlmsise.getDensityAt(position, Instant::DateTime(DateTime::Parse("2020-01-01 00:00:00"), Scale::UTC));

        const Real referenceDensity = 1.77622e-08;
        const Real tolerance = 1e-13;

        EXPECT_TRUE(density.isNear(referenceDensity, tolerance)) << String::Format(
            "{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), (density - referenceDensity)
        );
    }
}
