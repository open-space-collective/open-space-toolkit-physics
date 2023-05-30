/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential, Constructor)
{
    using ostk::physics::environment::atmospheric::earth::Exponential;

    {
        EXPECT_NO_THROW(Exponential exponential = {});
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential, Clone)
{
    using ostk::physics::environment::atmospheric::earth::Exponential;

    {
        const Exponential exponential = {};

        EXPECT_NO_THROW(const Exponential* exponentialPtr = exponential.clone(); delete exponentialPtr;);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential, getDensityAt)
{
    using ostk::core::types::String;
    using ostk::core::types::Real;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::time::Instant;
    using ostk::physics::coord::Position;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::coord::Frame;
    using ostk::physics::environment::atmospheric::earth::Exponential;
    using EarthCelestialBody = ostk::physics::env::obj::celest::Earth;

    {
        const Exponential exponential = {};

        const LLA lla = LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0));

        const Position position = {
            lla.toCartesian(EarthCelestialBody::EquatorialRadius, EarthCelestialBody::Flattening),
            Position::Unit::Meter,
            Frame::ITRF()};

        const Real density = exponential.getDensityAt(position, Instant::J2000());

        const Real referenceDensity = 1.77622e-08;
        const Real tolerance = 1e-13;

        EXPECT_TRUE(density.isNear(referenceDensity, tolerance)) << String::Format(
            "{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), (density - referenceDensity)
        );
    }
}
