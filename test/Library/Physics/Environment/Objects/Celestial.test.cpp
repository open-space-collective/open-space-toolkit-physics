////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/Celestial.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Gravitational/Spherical.hpp>
#include <Library/Physics/Environment/Ephemerides/Analytical.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Coordinate/Spherical/LLA.hpp>
#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Physics_Environment_Objects_Celestial, Constructor)
// {

//     using library::physics::env::Object ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Environment_Objects_Celestial, GetGravitationalFieldAt)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;

    using library::physics::Unit ;
    using library::physics::units::Length ;
    using library::physics::units::Time ;
    using library::physics::units::Derived ;
    using library::physics::data::Vector ;
    using library::physics::time::Instant ;
    using library::physics::coord::Frame ;
    using library::physics::coord::Position ;
    using library::physics::env::obj::Celestial ;
    using library::physics::env::Ephemeris ;
    using library::physics::env::ephem::Analytical ;
    using GravitationalModel = library::physics::environment::gravitational::Model ;
    using library::physics::environment::gravitational::Spherical ;

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
            instant
        } ;

        {

            const Position position = { { 1.0, 0.0, 0.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position) ;

            EXPECT_TRUE(gravitationalFieldValue.isDefined()) ;

            EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), gravitationalFieldValue.getValue()) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)), gravitationalFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame()) ;

        }

        {

            const Position position = { { 0.0, 0.0, 1.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position) ;

            EXPECT_TRUE(gravitationalFieldValue.isDefined()) ;

            EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), gravitationalFieldValue.getValue()) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)), gravitationalFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame()) ;

        }

        {

            const Position position = { { 2.0, 0.0, 0.0 }, Length::Unit::Meter, celestial.accessFrame() } ;

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position) ;

            EXPECT_TRUE(gravitationalFieldValue.isDefined()) ;

            EXPECT_EQ(Vector3d(-0.25, 0.0, 0.0), gravitationalFieldValue.getValue()) ;
            EXPECT_EQ(Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)), gravitationalFieldValue.getUnit()) ;
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame()) ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////