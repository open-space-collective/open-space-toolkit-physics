////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object/Geometry.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Environment/Object/Geometry.hpp>
#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Spherical/LLA.hpp>
#include <Library/Physics/Time/Interval.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Scale.hpp>
#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Weak.hpp>
#include <Library/Core/Types/Shared.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Physics_Environment_Object_Geometry, Constructor)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, EqualToOperator)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, NotEqualToOperator)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, StreamOperator)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, IsDefined)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, Intersects)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, Contains)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, AccessFrame)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, In)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::time::Instant ;
    using library::physics::coord::spherical::LLA ;
    using library::physics::coord::Frame ;
    using library::physics::Environment ;
    using library::physics::env::object::Geometry ;
    using library::physics::env::obj::Celestial ;

    {

        const Environment environment = Environment::Default() ;

        const Shared<const Celestial> earthSPtr = environment.accessCelestialObjectWithName("Earth") ;

        const Instant instant = Instant::J2000() ;

        const Shared<const Frame> nedFrameSPtr = earthSPtr->getFrameAt(LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(0.0)), Celestial::FrameType::NED) ;
        const Shared<const Frame> itrfFrameSPtr = Frame::ITRF() ;

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry geometry = { pyramid, nedFrameSPtr } ;

        const Geometry transformedGeometry = geometry.in(itrfFrameSPtr, instant) ;

        const Polygon referenceBase = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 6378134.3, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point referenceApex = { 6378135.3, 0.0, 0.0 } ;

        const Pyramid referencePyramid = { referenceBase, referenceApex } ;

        EXPECT_EQ(*itrfFrameSPtr, *transformedGeometry.accessFrame()) ;
        
        EXPECT_TRUE(transformedGeometry.as<Pyramid>().getBase().isNear(referencePyramid.getBase(), 1e-8)) << referencePyramid.getBase() << transformedGeometry.as<Pyramid>().getBase() ;
        EXPECT_TRUE(transformedGeometry.as<Pyramid>().getApex().isNear(referencePyramid.getApex(), 1e-8)) << referencePyramid.getApex().toString() << transformedGeometry.as<Pyramid>().getApex().toString() ;

    }

    {

        EXPECT_ANY_THROW(Geometry::Undefined().in(Frame::ITRF(), Instant::J2000())) ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, Is)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, As)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, IntersectionWith)
{

    using library::physics::env::object::Geometry ;

    {

        FAIL() ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, Undefined)
{

    using library::physics::env::object::Geometry ;

    {

        EXPECT_NO_THROW(Geometry::Undefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////