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

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
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

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        EXPECT_NO_THROW(Geometry geometry(pyramid, Frame::GCRF()) ; ) ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, EqualToOperator)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry geometry = { pyramid, Frame::GCRF() } ;

        EXPECT_TRUE(geometry == geometry) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry firstGeometry = { pyramid, Frame::GCRF() } ;
        const Geometry secondGeometry = { pyramid, Frame::ITRF() } ;

        EXPECT_FALSE(firstGeometry == secondGeometry) ;

        EXPECT_FALSE(firstGeometry == Geometry::Undefined()) ;
        EXPECT_FALSE(Geometry::Undefined() == firstGeometry) ;

    }

    {

        EXPECT_FALSE(Geometry::Undefined() == Geometry::Undefined()) ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry geometry = { pyramid, Frame::GCRF() } ;

        EXPECT_FALSE(geometry != geometry) ;

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry firstGeometry = { pyramid, Frame::GCRF() } ;
        const Geometry secondGeometry = { pyramid, Frame::ITRF() } ;

        EXPECT_TRUE(firstGeometry != secondGeometry) ;

        EXPECT_TRUE(firstGeometry != Geometry::Undefined()) ;
        EXPECT_TRUE(Geometry::Undefined() != firstGeometry) ;

    }

    {

        EXPECT_TRUE(Geometry::Undefined() != Geometry::Undefined()) ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, StreamOperator)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry geometry = { pyramid, Frame::GCRF() } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << geometry << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, IsDefined)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry geometry = { pyramid, Frame::GCRF() } ;

        EXPECT_TRUE(geometry.isDefined()) ;

    }

    {

        EXPECT_FALSE(Geometry::Undefined().isDefined()) ;

    }

}

// TEST (Library_Physics_Environment_Object_Geometry, Intersects)
// {

//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Pyramid ;

//     using library::physics::coord::Frame ;
//     using library::physics::env::object::Geometry ;

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Geometry geometry = { pyramid, Frame::GCRF() } ;

//         EXPECT_TRUE(geometry.intersects(geometry)) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Geometry geometry = { pyramid, Frame::GCRF() } ;

//         EXPECT_ANY_THROW(Geometry::Undefined().intersects(Geometry::Undefined())) ;
//         EXPECT_ANY_THROW(geometry.intersects(Geometry::Undefined())) ;
//         EXPECT_ANY_THROW(Geometry::Undefined().intersects(geometry)) ;

//     }

// }

// TEST (Library_Physics_Environment_Object_Geometry, Contains)
// {

//     using library::physics::env::object::Geometry ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Physics_Environment_Object_Geometry, AccessComposite)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry geometry = { pyramid, Frame::GCRF() } ;

        EXPECT_EQ(Composite(pyramid), geometry.accessComposite()) ;

    }

    {

        EXPECT_ANY_THROW(Geometry::Undefined().accessComposite()) ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, AccessFrame)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Geometry geometry = { pyramid, Frame::GCRF() } ;

        EXPECT_EQ(Frame::GCRF(), geometry.accessFrame()) ;

    }

    {

        EXPECT_ANY_THROW(Geometry::Undefined().accessFrame()) ;

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
        
        EXPECT_TRUE(transformedGeometry.accessComposite().as<Pyramid>().getBase().isNear(referencePyramid.getBase(), 1e-8)) << referencePyramid.getBase() << transformedGeometry.accessComposite().as<Pyramid>().getBase() ;
        EXPECT_TRUE(transformedGeometry.accessComposite().as<Pyramid>().getApex().isNear(referencePyramid.getApex(), 1e-8)) << referencePyramid.getApex().toString() << transformedGeometry.accessComposite().as<Pyramid>().getApex().toString() ;

    }

    {

        EXPECT_ANY_THROW(Geometry::Undefined().in(Frame::ITRF(), Instant::J2000())) ;

    }

}

TEST (Library_Physics_Environment_Object_Geometry, IntersectionWith)
{

    using library::core::types::Shared ;
    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::LineString ;
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

        const Shared<const Frame> nedFrameSPtr = earthSPtr->getFrameAt(LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Meters(500e3)), Celestial::FrameType::NED) ;
        const Shared<const Frame> itrfFrameSPtr = Frame::ITRF() ;

        const Polygon base = { { { { -1.0, -1.0 }, { +1.0, -1.0 }, { +1.0, +1.0 }, { -1.0, +1.0 } } }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 0.0 } ;

        const Pyramid observerGeometry = { base, apex } ;

        const Geometry observerGeometry_NED = { observerGeometry, nedFrameSPtr } ;

        const Geometry observerGeometry_ITRF = observerGeometry_NED.in(itrfFrameSPtr, instant) ;

        const Geometry earthGeometry_ITRF = earthSPtr->getGeometryIn(itrfFrameSPtr) ;

        const Geometry intersectionGeometry_ITRF = observerGeometry_ITRF.intersectionWith(earthGeometry_ITRF) ;

        EXPECT_TRUE(intersectionGeometry_ITRF.isDefined()) ;

        EXPECT_EQ(2, intersectionGeometry_ITRF.accessComposite().getObjectCount()) ;

        EXPECT_TRUE(intersectionGeometry_ITRF.accessComposite().accessObjectAt(0).is<LineString>()) ;
        EXPECT_TRUE(intersectionGeometry_ITRF.accessComposite().accessObjectAt(1).is<LineString>()) ;

        const LineString firstIntersectionLineString_ITRF = intersectionGeometry_ITRF.accessComposite().accessObjectAt(0).as<LineString>() ;
        const LineString secondIntersectionLineString_ITRF = intersectionGeometry_ITRF.accessComposite().accessObjectAt(1).as<LineString>() ;

        EXPECT_TRUE(firstIntersectionLineString_ITRF.isDefined()) ;
        EXPECT_TRUE(secondIntersectionLineString_ITRF.isDefined()) ;

        const LineString firstIntersectionLineString_ITRF_reference =
        {
            {
                { 6330840.22670504, -547296.073294956, -547296.073294956 },
                { 6343400.40450232, -392459.403257506, -534735.895497679 },
                { 6350584.75268178, -265536.535503355, -527551.547318225 },
                { 6354600.65219536, -154066.259054871, -523535.64780464 },
                { 6356417.53526935, -50535.9519905773, -521718.764730647 },
                { 6356417.53526935, 50535.9519905773, -521718.764730647 },
                { 6354600.65219536, 154066.259054871, -523535.64780464 },
                { 6350584.75268178, 265536.535503355, -527551.547318225 },
                { 6343400.40450232, 392459.403257506, -534735.895497679 },
                { 6330840.22670504, 547296.073294956, -547296.073294957 },
                { 6330840.22670504, 547296.073294956, -547296.073294956 },
                { 6343480.95313559, 534655.346864411, -392400.286095536 },
                { 6350707.84711074, 527428.452889258, -265474.577447552 },
                { 6354746.4678595, 523389.832140503, -154023.348368695 },
                { 6356573.38754901, 521562.912450988, -50520.8554599275 },
                { 6356573.38754901, 521562.912450988, 50520.8554599268 },
                { 6354746.4678595, 523389.832140503, 154023.348368694 },
                { 6350707.84711074, 527428.452889258, 265474.577447551 },
                { 6343480.95313559, 534655.346864411, 392400.286095536 },
                { 6330840.22670504, 547296.073294956, 547296.073294956 },
                { 6330840.22670504, 547296.073294956, 547296.073294956 },
                { 6343400.40450232, 392459.403257506, 534735.895497678 },
                { 6350584.75268178, 265536.535503354, 527551.547318224 },
                { 6354600.65219536, 154066.259054871, 523535.647804639 },
                { 6356417.53526935, 50535.9519905773, 521718.764730647 },
                { 6356417.53526935, -50535.9519905773, 521718.764730647 },
                { 6354600.65219536, -154066.259054871, 523535.647804639 },
                { 6350584.75268178, -265536.535503355, 527551.547318225 },
                { 6343400.40450232, -392459.403257506, 534735.895497678 },
                { 6330840.22670504, -547296.073294956, 547296.073294956 },
                { 6330840.22670504, -547296.073294956, 547296.073294956 },
                { 6343480.95313559, -534655.346864411, 392400.286095536 },
                { 6350707.84711074, -527428.452889258, 265474.577447551 },
                { 6354746.4678595, -523389.832140503, 154023.348368694 },
                { 6356573.38754901, -521562.912450988, 50520.8554599268 },
                { 6356573.38754901, -521562.912450988, -50520.8554599276 },
                { 6354746.4678595, -523389.832140503, -154023.348368695 },
                { 6350707.84711074, -527428.452889258, -265474.577447552 },
                { 6343480.95313559, -534655.346864411, -392400.286095536 },
                { 6330840.22670504, -547296.073294956, -547296.073294956 }
            }
        } ;

        const LineString secondIntersectionLineString_ITRF_reference =
        {
            {
                { 2850286.2341284, -4027850.0658716, -4027850.0658716 },
                { 2008495.0335098, -3573982.07529378, -4869641.2664902 },
                { 1319079.2310724, -2798082.50445344, -5559057.0689276 },
                { 830226.414467597, -1779781.10004965, -6047909.8855324 },
                { 576720.733377391, -610382.558718058, -6301415.56662261 },
                { 576720.733377391, 610382.558718058, -6301415.56662261 },
                { 830226.414467597, 1779781.10004965, -6047909.8855324 },
                { 1319079.2310724, 2798082.50445345, -5559057.0689276 },
                { 2008495.0335098, 3573982.07529378, -4869641.2664902 },
                { 2850286.2341284, 4027850.0658716, -4027850.0658716 },
                { 2850286.2341284, 4027850.0658716, -4027850.0658716 },
                { 2001804.89505489, 4876331.40494511, -3578892.17721106 },
                { 1305374.15085261, 5572762.14914739, -2804980.78678975 },
                { 810699.067441951, 6067437.23255805, -1785527.61476765 },
                { 553895.431828732, 6324240.86817127, -612593.516845716 },
                { 553895.431828732, 6324240.86817127, 612593.516845717 },
                { 810699.067441951, 6067437.23255805, 1785527.61476766 },
                { 1305374.15085261, 5572762.14914739, 2804980.78678975 },
                { 2001804.89505489, 4876331.40494511, 3578892.17721106 },
                { 2850286.2341284, 4027850.0658716, 4027850.0658716 },
                { 2850286.2341284, 4027850.0658716, 4027850.0658716 },
                { 2008495.0335098, 3573982.07529378, 4869641.2664902 },
                { 1319079.2310724, 2798082.50445344, 5559057.06892761 },
                { 830226.414467596, 1779781.10004965, 6047909.88553241 },
                { 576720.733377391, 610382.558718057, 6301415.56662261 },
                { 576720.733377391, -610382.558718057, 6301415.56662261 },
                { 830226.414467596, -1779781.10004965, 6047909.88553241 },
                { 1319079.2310724, -2798082.50445345, 5559057.0689276 },
                { 2008495.0335098, -3573982.07529378, 4869641.2664902 },
                { 2850286.2341284, -4027850.0658716, 4027850.0658716 },
                { 2850286.2341284, -4027850.0658716, 4027850.0658716 },
                { 2001804.89505489, -4876331.40494511, 3578892.17721106 },
                { 1305374.15085261, -5572762.14914739, 2804980.78678975 },
                { 810699.067441951, -6067437.23255805, 1785527.61476765 },
                { 553895.431828732, -6324240.86817127, 612593.516845716 },
                { 553895.431828732, -6324240.86817127, -612593.516845717 },
                { 810699.067441951, -6067437.23255805, -1785527.61476766 },
                { 1305374.15085261, -5572762.14914739, -2804980.78678976 },
                { 2001804.89505489, -4876331.40494511, -3578892.17721106 },
                { 2850286.2341284, -4027850.0658716, -4027850.0658716 }
            }
        } ;

        EXPECT_TRUE(firstIntersectionLineString_ITRF.isNear(firstIntersectionLineString_ITRF_reference, 1e-8)) ;
        EXPECT_TRUE(secondIntersectionLineString_ITRF.isNear(secondIntersectionLineString_ITRF_reference, 1e-8)) ;

    }

    {

        EXPECT_ANY_THROW(Geometry::Undefined().intersectionWith(Geometry::Undefined())) ;
        
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