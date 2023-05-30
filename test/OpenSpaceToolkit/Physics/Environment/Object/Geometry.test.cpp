/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Weak.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Geometry.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, Constructor)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::coord::Frame;
    using ostk::physics::env::object::Geometry;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_NO_THROW(Geometry geometry(pyramid, Frame::GCRF()););
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, EqualToOperator)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::coord::Frame;
    using ostk::physics::env::object::Geometry;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, Frame::GCRF()};

        EXPECT_TRUE(geometry == geometry);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry firstGeometry = {pyramid, Frame::GCRF()};
        const Geometry secondGeometry = {pyramid, Frame::ITRF()};

        EXPECT_FALSE(firstGeometry == secondGeometry);

        EXPECT_FALSE(firstGeometry == Geometry::Undefined());
        EXPECT_FALSE(Geometry::Undefined() == firstGeometry);
    }

    {
        EXPECT_FALSE(Geometry::Undefined() == Geometry::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, NotEqualToOperator)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::coord::Frame;
    using ostk::physics::env::object::Geometry;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, Frame::GCRF()};

        EXPECT_FALSE(geometry != geometry);
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry firstGeometry = {pyramid, Frame::GCRF()};
        const Geometry secondGeometry = {pyramid, Frame::ITRF()};

        EXPECT_TRUE(firstGeometry != secondGeometry);

        EXPECT_TRUE(firstGeometry != Geometry::Undefined());
        EXPECT_TRUE(Geometry::Undefined() != firstGeometry);
    }

    {
        EXPECT_TRUE(Geometry::Undefined() != Geometry::Undefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, StreamOperator)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::coord::Frame;
    using ostk::physics::env::object::Geometry;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, Frame::GCRF()};

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << geometry << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, IsDefined)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::coord::Frame;
    using ostk::physics::env::object::Geometry;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, Frame::GCRF()};

        EXPECT_TRUE(geometry.isDefined());
    }

    {
        EXPECT_FALSE(Geometry::Undefined().isDefined());
    }
}

// TEST (OpenSpaceToolkit_Physics_Environment_Object_Geometry, Intersects)
// {

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::Polygon ;
//     using ostk::math::geom::d3::objects::Pyramid ;

//     using ostk::physics::coord::Frame ;
//     using ostk::physics::env::object::Geometry ;

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 },
//         { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ; const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Geometry geometry = { pyramid, Frame::GCRF() } ;

//         EXPECT_TRUE(geometry.intersects(geometry)) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 },
//         { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ; const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Geometry geometry = { pyramid, Frame::GCRF() } ;

//         EXPECT_ANY_THROW(Geometry::Undefined().intersects(Geometry::Undefined())) ;
//         EXPECT_ANY_THROW(geometry.intersects(Geometry::Undefined())) ;
//         EXPECT_ANY_THROW(Geometry::Undefined().intersects(geometry)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Physics_Environment_Object_Geometry, Contains)
// {

//     using ostk::physics::env::object::Geometry ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, AccessComposite)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;
    using ostk::math::geom::d3::objects::Composite;

    using ostk::physics::coord::Frame;
    using ostk::physics::env::object::Geometry;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, Frame::GCRF()};

        EXPECT_EQ(Composite(pyramid), geometry.accessComposite());
    }

    {
        EXPECT_ANY_THROW(Geometry::Undefined().accessComposite());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, AccessFrame)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::coord::Frame;
    using ostk::physics::env::object::Geometry;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, Frame::GCRF()};

        EXPECT_EQ(Frame::GCRF(), geometry.accessFrame());
    }

    {
        EXPECT_ANY_THROW(Geometry::Undefined().accessFrame());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, In)
{
    using ostk::core::types::Shared;
    using ostk::core::types::Real;

    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::time::Instant;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::coord::Frame;
    using ostk::physics::Environment;
    using ostk::physics::env::object::Geometry;
    using ostk::physics::env::obj::Celestial;

    {
        const Environment environment = Environment::Default();

        const Shared<const Celestial> earthSPtr = environment.accessCelestialObjectWithName("Earth");

        const Instant instant = Instant::J2000();

        const Angle latitude = Angle::Degrees(0.0);
        const Angle longitude = Angle::Degrees(0.0);
        const Length altitude = Length::Meters(0.0);

        const Shared<const Frame> nedFrameSPtr =
            earthSPtr->getFrameAt(LLA(latitude, longitude, altitude), Celestial::FrameType::NED);
        const Shared<const Frame> itrfFrameSPtr = Frame::ITRF();

        const Point vertex = {0.0, 0.0, 0.0};

        const Geometry geometry = {vertex, nedFrameSPtr};

        const Geometry transformedGeometry = geometry.in(itrfFrameSPtr, instant);

        const Point referenceVertex = {earthSPtr->getEquatorialRadius().inMeters(), 0.0, 0.0};

        EXPECT_EQ(itrfFrameSPtr, transformedGeometry.accessFrame());

        EXPECT_TRUE(transformedGeometry.accessComposite().as<Point>().isNear(referenceVertex, 1e-8))
            << referenceVertex.toString() << transformedGeometry.accessComposite().as<Point>().toString();
    }

    {
        const Environment environment = Environment::Default();

        const Shared<const Celestial> earthSPtr = environment.accessCelestialObjectWithName("Earth");

        const Instant instant = Instant::J2000();

        const Angle latitude = Angle::Degrees(0.0);
        const Angle longitude = Angle::Degrees(0.0);
        const Length altitude = Length::Meters(0.0);

        const Shared<const Frame> nedFrameSPtr =
            earthSPtr->getFrameAt(LLA(latitude, longitude, altitude), Celestial::FrameType::NED);
        const Shared<const Frame> itrfFrameSPtr = Frame::ITRF();

        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, nedFrameSPtr};

        const Geometry transformedGeometry = geometry.in(itrfFrameSPtr, instant);

        const Polygon referenceBase = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}},
            {earthSPtr->getEquatorialRadius().inMeters() - 2.0, 0.0, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, 1.0, 0.0}};
        const Point referenceApex = {earthSPtr->getEquatorialRadius().inMeters() - 1.0, 0.0, 0.0};

        const Pyramid referencePyramid = {referenceBase, referenceApex};

        EXPECT_EQ(itrfFrameSPtr, transformedGeometry.accessFrame());

        EXPECT_TRUE(
            transformedGeometry.accessComposite().as<Pyramid>().getBase().isNear(referencePyramid.getBase(), 1e-8)
        ) << referencePyramid.getBase()
          << transformedGeometry.accessComposite().as<Pyramid>().getBase();
        EXPECT_TRUE(
            transformedGeometry.accessComposite().as<Pyramid>().getApex().isNear(referencePyramid.getApex(), 1e-8)
        ) << referencePyramid.getApex().toString()
          << transformedGeometry.accessComposite().as<Pyramid>().getApex().toString();
    }

    {
        const Environment environment = Environment::Default();

        const Shared<const Celestial> earthSPtr = environment.accessCelestialObjectWithName("Earth");

        const Instant instant = Instant::J2000();

        const Angle latitude = Angle::Degrees(0.0);
        const Angle longitude = Angle::Degrees(180.0);
        const Length altitude = Length::Meters(0.0);

        const Shared<const Frame> nedFrameSPtr =
            earthSPtr->getFrameAt(LLA(latitude, longitude, altitude), Celestial::FrameType::NED);
        const Shared<const Frame> itrfFrameSPtr = Frame::ITRF();

        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 1.0};

        const Pyramid pyramid = {base, apex};

        const Geometry geometry = {pyramid, nedFrameSPtr};

        const Geometry transformedGeometry = geometry.in(itrfFrameSPtr, instant);

        const Polygon referenceBase = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}},
            {-(earthSPtr->getEquatorialRadius().inMeters() - 2.0), 0.0, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, -1.0, 0.0}};
        const Point referenceApex = {-(earthSPtr->getEquatorialRadius().inMeters() - 1.0), 0.0, 0.0};

        const Pyramid referencePyramid = {referenceBase, referenceApex};

        EXPECT_EQ(itrfFrameSPtr, transformedGeometry.accessFrame());

        EXPECT_TRUE(
            transformedGeometry.accessComposite().as<Pyramid>().getBase().isNear(referencePyramid.getBase(), 1e-8)
        ) << referencePyramid.getBase()
          << transformedGeometry.accessComposite().as<Pyramid>().getBase();
        EXPECT_TRUE(
            transformedGeometry.accessComposite().as<Pyramid>().getApex().isNear(referencePyramid.getApex(), 1e-8)
        ) << referencePyramid.getApex().toString()
          << transformedGeometry.accessComposite().as<Pyramid>().getApex().toString();
    }

    {
        EXPECT_ANY_THROW(Geometry::Undefined().in(Frame::ITRF(), Instant::J2000()));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, IntersectionWith)
{
    using ostk::core::types::Shared;
    using ostk::core::types::Real;

    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::LineString;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Pyramid;

    using ostk::physics::units::Length;
    using ostk::physics::units::Angle;
    using ostk::physics::time::Instant;
    using ostk::physics::coord::spherical::LLA;
    using ostk::physics::coord::Frame;
    using ostk::physics::Environment;
    using ostk::physics::env::object::Geometry;
    using ostk::physics::env::obj::Celestial;

    {
        const Environment environment = Environment::Default();

        const Shared<const Celestial> earthSPtr = environment.accessCelestialObjectWithName("Earth");

        const Instant instant = Instant::J2000();

        const Shared<const Frame> nedFrameSPtr = earthSPtr->getFrameAt(
            LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(500e3)), Celestial::FrameType::NED
        );
        const Shared<const Frame> itrfFrameSPtr = Frame::ITRF();

        const Polygon base = {
            {{{-1.0, -1.0}, {+1.0, -1.0}, {+1.0, +1.0}, {-1.0, +1.0}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}};
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid observerGeometry = {base, apex};

        const Geometry observerGeometry_NED = {observerGeometry, nedFrameSPtr};

        const Geometry observerGeometry_ITRF = observerGeometry_NED.in(itrfFrameSPtr, instant);

        const Geometry earthGeometry_ITRF = earthSPtr->getGeometryIn(itrfFrameSPtr);

        const Geometry intersectionGeometry_ITRF = observerGeometry_ITRF.intersectionWith(earthGeometry_ITRF);

        EXPECT_TRUE(intersectionGeometry_ITRF.isDefined());

        EXPECT_EQ(2, intersectionGeometry_ITRF.accessComposite().getObjectCount());

        EXPECT_TRUE(intersectionGeometry_ITRF.accessComposite().accessObjectAt(0).is<LineString>());
        EXPECT_TRUE(intersectionGeometry_ITRF.accessComposite().accessObjectAt(1).is<LineString>());

        const LineString firstIntersectionLineString_ITRF =
            intersectionGeometry_ITRF.accessComposite().accessObjectAt(0).as<LineString>();
        const LineString secondIntersectionLineString_ITRF =
            intersectionGeometry_ITRF.accessComposite().accessObjectAt(1).as<LineString>();

        EXPECT_TRUE(firstIntersectionLineString_ITRF.isDefined());
        EXPECT_TRUE(secondIntersectionLineString_ITRF.isDefined());

        // WGS84 + EGM96

        const LineString firstIntersectionLineString_ITRF_reference = {
            {{6330840.93303221, -547296.066967795, -547296.066967795},
             {6343401.10890961, -392459.400022857, -534735.891090387},
             {6350585.45607374, -265536.533796054, -527551.543926265},
             {6354601.35504462, -154066.258216391, -523535.644955385},
             {6356418.23787876, -50535.9517378191, -521718.762121244},
             {6356418.23787876, 50535.9517378192, -521718.762121244},
             {6354601.35504462, 154066.258216391, -523535.644955385},
             {6350585.45607374, 265536.533796054, -527551.543926265},
             {6343401.10890961, 392459.400022858, -534735.891090388},
             {6330840.93303221, 547296.066967795, -547296.066967795},
             {6330840.93303221, 547296.066967795, -547296.066967795},
             {6343481.65753117, 534655.342468828, -392400.28286948},
             {6350708.55048581, 527428.449514193, -265474.575748755},
             {6354747.17068938, 523389.829310627, -154023.347535917},
             {6356574.09013801, 521562.909861996, -50520.8552091462},
             {6356574.09013801, 521562.909861996, 50520.8552091463},
             {6354747.17068938, 523389.829310627, 154023.347535918},
             {6350708.55048581, 527428.449514193, 265474.575748755},
             {6343481.65753117, 534655.342468828, 392400.28286948},
             {6330840.93303221, 547296.066967795, 547296.066967795},
             {6330840.93303221, 547296.066967795, 547296.066967795},
             {6343401.10890961, 392459.400022857, 534735.891090387},
             {6350585.45607374, 265536.533796054, 527551.543926265},
             {6354601.35504462, 154066.258216391, 523535.644955385},
             {6356418.23787876, 50535.9517378191, 521718.762121244},
             {6356418.23787876, -50535.9517378192, 521718.762121244},
             {6354601.35504462, -154066.258216391, 523535.644955385},
             {6350585.45607374, -265536.533796054, 527551.543926265},
             {6343401.10890961, -392459.400022858, 534735.891090388},
             {6330840.93303221, -547296.066967795, 547296.066967795},
             {6330840.93303221, -547296.066967795, 547296.066967795},
             {6343481.65753117, -534655.342468828, 392400.28286948},
             {6350708.55048581, -527428.449514193, 265474.575748755},
             {6354747.17068938, -523389.829310627, 154023.347535917},
             {6356574.09013801, -521562.909861996, 50520.8552091462},
             {6356574.09013801, -521562.909861996, -50520.8552091463},
             {6354747.17068938, -523389.829310627, -154023.347535918},
             {6350708.55048581, -527428.449514193, -265474.575748755},
             {6343481.65753117, -534655.342468828, -392400.28286948},
             {6330840.93303221, -547296.066967795, -547296.066967795}}};

        const LineString secondIntersectionLineString_ITRF_reference = {
            {{2850286.4621806, -4027850.5378194, -4027850.5378194},
             {2008495.17908957, -3573982.48220013, -4869641.82091044},
             {1319079.3082356, -2798082.81795063, -5559057.6917644},
             {830226.442830807, -1779781.29769917, -6047910.5571692},
             {576720.736365641, -610382.626233652, -6301416.26363436},
             {576720.736365642, 610382.626233652, -6301416.26363436},
             {830226.442830807, 1779781.29769917, -6047910.5571692},
             {1319079.30823561, 2798082.81795063, -5559057.6917644},
             {2008495.17908957, 3573982.48220013, -4869641.82091044},
             {2850286.4621806, 4027850.53781941, -4027850.5378194},
             {2850286.4621806, 4027850.5378194, -4027850.5378194},
             {2001805.03997369, 4876331.96002631, -3578892.58460252},
             {1305374.22665044, 5572762.77334956, -2804981.10097418},
             {810699.093852041, 6067437.90614796, -1785527.81299194},
             {553895.432530277, 6324241.56746973, -612593.584582811},
             {553895.432530278, 6324241.56746973, 612593.584582812},
             {810699.093852041, 6067437.90614796, 1785527.81299194},
             {1305374.22665045, 5572762.77334956, 2804981.10097418},
             {2001805.03997369, 4876331.96002631, 3578892.58460252},
             {2850286.4621806, 4027850.5378194, 4027850.53781941},
             {2850286.4621806, 4027850.5378194, 4027850.5378194},
             {2008495.17908957, 3573982.48220013, 4869641.82091044},
             {1319079.3082356, 2798082.81795063, 5559057.6917644},
             {830226.442830807, 1779781.29769917, 6047910.5571692},
             {576720.736365641, 610382.626233652, 6301416.26363436},
             {576720.736365642, -610382.626233652, 6301416.26363436},
             {830226.442830807, -1779781.29769917, 6047910.5571692},
             {1319079.30823561, -2798082.81795063, 5559057.6917644},
             {2008495.17908957, -3573982.48220013, 4869641.82091044},
             {2850286.4621806, -4027850.53781941, 4027850.5378194},
             {2850286.4621806, -4027850.5378194, 4027850.5378194},
             {2001805.03997369, -4876331.96002631, 3578892.58460252},
             {1305374.22665044, -5572762.77334956, 2804981.10097418},
             {810699.093852041, -6067437.90614796, 1785527.81299194},
             {553895.432530277, -6324241.56746973, 612593.584582811},
             {553895.432530278, -6324241.56746973, -612593.584582812},
             {810699.093852041, -6067437.90614796, -1785527.81299194},
             {1305374.22665045, -5572762.77334956, -2804981.10097418},
             {2001805.03997369, -4876331.96002631, -3578892.58460252},
             {2850286.4621806, -4027850.5378194, -4027850.53781941}}};

        // EGM96

        // const LineString firstIntersectionLineString_ITRF_reference =
        // {
        //     {
        //         { 6330840.22670504, -547296.073294956, -547296.073294956 },
        //         { 6343400.40450232, -392459.403257506, -534735.895497679 },
        //         { 6350584.75268178, -265536.535503355, -527551.547318225 },
        //         { 6354600.65219536, -154066.259054871, -523535.64780464 },
        //         { 6356417.53526935, -50535.9519905773, -521718.764730647 },
        //         { 6356417.53526935, 50535.9519905773, -521718.764730647 },
        //         { 6354600.65219536, 154066.259054871, -523535.64780464 },
        //         { 6350584.75268178, 265536.535503355, -527551.547318225 },
        //         { 6343400.40450232, 392459.403257506, -534735.895497679 },
        //         { 6330840.22670504, 547296.073294956, -547296.073294957 },
        //         { 6330840.22670504, 547296.073294956, -547296.073294956 },
        //         { 6343480.95313559, 534655.346864411, -392400.286095536 },
        //         { 6350707.84711074, 527428.452889258, -265474.577447552 },
        //         { 6354746.4678595, 523389.832140503, -154023.348368695 },
        //         { 6356573.38754901, 521562.912450988, -50520.8554599275 },
        //         { 6356573.38754901, 521562.912450988, 50520.8554599268 },
        //         { 6354746.4678595, 523389.832140503, 154023.348368694 },
        //         { 6350707.84711074, 527428.452889258, 265474.577447551 },
        //         { 6343480.95313559, 534655.346864411, 392400.286095536 },
        //         { 6330840.22670504, 547296.073294956, 547296.073294956 },
        //         { 6330840.22670504, 547296.073294956, 547296.073294956 },
        //         { 6343400.40450232, 392459.403257506, 534735.895497678 },
        //         { 6350584.75268178, 265536.535503354, 527551.547318224 },
        //         { 6354600.65219536, 154066.259054871, 523535.647804639 },
        //         { 6356417.53526935, 50535.9519905773, 521718.764730647 },
        //         { 6356417.53526935, -50535.9519905773, 521718.764730647 },
        //         { 6354600.65219536, -154066.259054871, 523535.647804639 },
        //         { 6350584.75268178, -265536.535503355, 527551.547318225 },
        //         { 6343400.40450232, -392459.403257506, 534735.895497678 },
        //         { 6330840.22670504, -547296.073294956, 547296.073294956 },
        //         { 6330840.22670504, -547296.073294956, 547296.073294956 },
        //         { 6343480.95313559, -534655.346864411, 392400.286095536 },
        //         { 6350707.84711074, -527428.452889258, 265474.577447551 },
        //         { 6354746.4678595, -523389.832140503, 154023.348368694 },
        //         { 6356573.38754901, -521562.912450988, 50520.8554599268 },
        //         { 6356573.38754901, -521562.912450988, -50520.8554599276 },
        //         { 6354746.4678595, -523389.832140503, -154023.348368695 },
        //         { 6350707.84711074, -527428.452889258, -265474.577447552 },
        //         { 6343480.95313559, -534655.346864411, -392400.286095536 },
        //         { 6330840.22670504, -547296.073294956, -547296.073294956 }
        //     }
        // } ;

        // const LineString secondIntersectionLineString_ITRF_reference =
        // {
        //     {
        //         { 2850286.23412841, -4027850.0658716, -4027850.0658716 },
        //         { 2008495.0335098, -3573982.07529378, -4869641.2664902 },
        //         { 1319079.2310724, -2798082.50445344, -5559057.06892761 },
        //         { 830226.414467599, -1779781.10004965, -6047909.8855324 },
        //         { 576720.733377395, -610382.558718057, -6301415.56662261 },
        //         { 576720.733377396, 610382.558718058, -6301415.56662261 },
        //         { 830226.414467599, 1779781.10004965, -6047909.8855324 },
        //         { 1319079.2310724, 2798082.50445345, -5559057.0689276 },
        //         { 2008495.0335098, 3573982.07529378, -4869641.2664902 },
        //         { 2850286.23412841, 4027850.06587159, -4027850.06587159 },
        //         { 2850286.23412841, 4027850.0658716, -4027850.0658716 },
        //         { 2001804.89505489, 4876331.40494511, -3578892.17721106 },
        //         { 1305374.15085261, 5572762.14914739, -2804980.78678975 },
        //         { 810699.067441951, 6067437.23255805, -1785527.61476765 },
        //         { 553895.431828734, 6324240.86817127, -612593.516845716 },
        //         { 553895.431828735, 6324240.86817127, 612593.516845717 },
        //         { 810699.067441951, 6067437.23255805, 1785527.61476766 },
        //         { 1305374.15085261, 5572762.14914739, 2804980.78678975 },
        //         { 2001804.89505489, 4876331.40494511, 3578892.17721106 },
        //         { 2850286.23412841, 4027850.0658716, 4027850.0658716 },
        //         { 2850286.23412841, 4027850.0658716, 4027850.0658716 },
        //         { 2008495.0335098, 3573982.07529378, 4869641.2664902 },
        //         { 1319079.2310724, 2798082.50445344, 5559057.06892761 },
        //         { 830226.414467599, 1779781.10004965, 6047909.8855324 },
        //         { 576720.733377395, 610382.558718057, 6301415.56662261 },
        //         { 576720.733377396, -610382.558718058, 6301415.56662261 },
        //         { 830226.414467599, -1779781.10004965, 6047909.8855324 },
        //         { 1319079.2310724, -2798082.50445345, 5559057.0689276 },
        //         { 2008495.0335098, -3573982.07529378, 4869641.2664902 },
        //         { 2850286.23412841, -4027850.06587159, 4027850.06587159 },
        //         { 2850286.23412841, -4027850.0658716, 4027850.0658716 },
        //         { 2001804.89505489, -4876331.40494511, 3578892.17721106 },
        //         { 1305374.15085261, -5572762.14914739, 2804980.78678975 },
        //         { 810699.067441951, -6067437.23255805, 1785527.61476765 },
        //         { 553895.431828734, -6324240.86817127, 612593.516845716 },
        //         { 553895.431828735, -6324240.86817127, -612593.516845717 },
        //         { 810699.067441951, -6067437.23255805, -1785527.61476766 },
        //         { 1305374.15085261, -5572762.14914739, -2804980.78678975 },
        //         { 2001804.89505489, -4876331.40494511, -3578892.17721106 },
        //         { 2850286.23412841, -4027850.0658716, -4027850.0658716 }
        //     }
        // } ;

        EXPECT_TRUE(firstIntersectionLineString_ITRF.isNear(firstIntersectionLineString_ITRF_reference, 1e-8));
        EXPECT_TRUE(secondIntersectionLineString_ITRF.isNear(secondIntersectionLineString_ITRF_reference, 1e-8));
    }

    {
        EXPECT_ANY_THROW(Geometry::Undefined().intersectionWith(Geometry::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Geometry, Undefined)
{
    using ostk::physics::env::object::Geometry;

    {
        EXPECT_NO_THROW(Geometry::Undefined());
    }
}
