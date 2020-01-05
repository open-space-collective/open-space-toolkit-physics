////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Environment/Objects/Celestial.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/Analytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Weak.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Physics_Environment_Objects_Celestial, Constructor)
// {

//     using ostk::physics::env::Object ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Environment_Objects_Celestial, GetGravitationalFieldAt)
{

    using ostk::core::types::Shared ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::Unit ;
    using ostk::physics::units::Length ;
    using ostk::physics::units::Time ;
    using ostk::physics::units::Derived ;
    using ostk::physics::data::Vector ;
    using ostk::physics::time::Instant ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;
    using ostk::physics::env::obj::Celestial ;
    using ostk::physics::env::Ephemeris ;
    using ostk::physics::env::ephem::Analytical ;
    using GravitationalModel = ostk::physics::environment::gravitational::Model ;
    using ostk::physics::environment::gravitational::Spherical ;

    {

        const String name = "Some Planet" ;
        const Celestial::Type type = Celestial::Type::Earth ;
        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;
        const Length equatorialRadius = Length::Kilometers(1000.0) ;
        const Real flattening = 0.0 ;
        const Real j2 = 0.0 ;
        const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF()) ;
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalParameter) ;
        const Instant instant = Instant::J2000() ;

        const Celestial celestial =
        {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            ephemeris,
            gravitationalModel,
            nullptr,
            instant
        } ;

        {

            const Position position = { { 1.0, 0.0, 0.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position) ;

            EXPECT_TRUE(gravitationalFieldValue.isDefined()) ;

            EXPECT_TRUE(gravitationalFieldValue.getValue().isNear(Vector3d { -1.0, 0.0, 0.0 }, 1e-20)) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)), gravitationalFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame()) ;

        }

        {

            const Position position = { { 0.0, 0.0, 1.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position) ;

            EXPECT_TRUE(gravitationalFieldValue.isDefined()) ;

            EXPECT_TRUE(gravitationalFieldValue.getValue().isNear(Vector3d { 0.0, 0.0, -1.0 }, 1e-20)) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)), gravitationalFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame()) ;

        }

        {

            const Position position = { { 2.0, 0.0, 0.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position) ;

            EXPECT_TRUE(gravitationalFieldValue.isDefined()) ;

            EXPECT_TRUE(gravitationalFieldValue.getValue().isNear(Vector3d { -0.25, 0.0, 0.0 }, 1e-20)) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)), gravitationalFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame()) ;

        }

    }

}

TEST (Library_Physics_Environment_Objects_Celestial, GetMagneticFieldAt)
{

    using ostk::core::types::Shared ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::Unit ;
    using ostk::physics::units::Length ;
    using ostk::physics::units::Time ;
    using ostk::physics::units::Derived ;
    using ostk::physics::data::Vector ;
    using ostk::physics::time::Instant ;
    using ostk::physics::coord::Frame ;
    using ostk::physics::coord::Position ;
    using ostk::physics::env::obj::Celestial ;
    using ostk::physics::env::Ephemeris ;
    using ostk::physics::env::ephem::Analytical ;
    using MagneticModel = ostk::physics::environment::magnetic::Model ;
    using ostk::physics::environment::magnetic::Dipole ;

    {

        const String name = "Some Planet" ;
        const Celestial::Type type = Celestial::Type::Earth ;
        const Derived gravitationalParameter = { 1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;
        const Length equatorialRadius = Length::Kilometers(1000.0) ;
        const Real flattening = 0.0 ;
        const Real j2 = 0.0 ;
        const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF()) ;
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d { 0.0, 0.0, 1.0 }) ;
        const Instant instant = Instant::J2000() ;

        const Celestial celestial =
        {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            ephemeris,
            nullptr,
            magneticModel,
            instant
        } ;

        {

            const Position position = { { 1.0, 0.0, 0.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector magneticFieldValue = celestial.getMagneticFieldAt(position) ;

            EXPECT_TRUE(magneticFieldValue.isDefined()) ;

            EXPECT_TRUE(magneticFieldValue.getValue().isNear(Vector3d { 0.0, 0.0, -1e-07 }, 1e-20 )) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Tesla()), magneticFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), magneticFieldValue.getFrame()) ;

        }

        {

            const Position position = { { 0.0, 0.0, 1.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector magneticFieldValue = celestial.getMagneticFieldAt(position) ;

            EXPECT_TRUE(magneticFieldValue.isDefined()) ;

            EXPECT_TRUE(magneticFieldValue.getValue().isNear(Vector3d { 0.0, 0.0, +2e-07 }, 1e-20 )) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Tesla()), magneticFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), magneticFieldValue.getFrame()) ;

        }

        {

            const Position position = { { 2.0, 0.0, 0.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector magneticFieldValue = celestial.getMagneticFieldAt(position) ;

            EXPECT_TRUE(magneticFieldValue.isDefined()) ;

            EXPECT_TRUE(magneticFieldValue.getValue().isNear(Vector3d { 0.0, 0.0, -1.25e-08 }, 1e-20 )) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Tesla()), magneticFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), magneticFieldValue.getFrame()) ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
