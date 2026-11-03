/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

#include <Global.test.hpp>

using ostk::core::type::String;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::environment::atmospheric::earth::Exponential;
using ostk::physics::time::Instant;
using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using EarthCelestial = ostk::physics::environment::object::celestial::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using ostk::physics::utility::DoubleToString;

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential, Constructor)
{
    {
        EXPECT_NO_THROW(Exponential());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential, Clone)
{
    {
        const Exponential exponential = {};

        EXPECT_NO_THROW(exponential.clone());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential, IsDefined)
{
    using ostk::physics::environment::atmospheric::earth::Exponential;

    {
        const Exponential exponential = {};

        EXPECT_TRUE(exponential.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Exponential, getDensityAt)
{
    {
        const Exponential exponential = {};

        const LLA lla = LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0));

        const double density = exponential.getDensityAt(lla, Instant::J2000());

        const double referenceDensity = 1.77622e-08;
        const double tolerance = 1e-13;

        EXPECT_TRUE(std::abs(density - referenceDensity) <= tolerance) << String::Format(
            "{} ≈ {} Δ {} [T]", DoubleToString(density), DoubleToString(referenceDensity), (density - referenceDensity)
        );
    }
}
