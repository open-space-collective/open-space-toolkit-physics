////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Environment/Object/Geometry.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Object/Geometry.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment_Object_Geometry ( )
{

    using namespace boost::python ;

    using library::core::types::Unique ;
    using library::core::types::Shared ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::LineString ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;

    using library::physics::coord::Frame ;
    using library::physics::env::object::Geometry ;

    scope in_Geometry = class_<Geometry>("Geometry", init<const Geometry::Object&, const Shared<const Frame>&>())

        .def(init<const Unique<Geometry::Object>&, const Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Geometry::isDefined)
        .def("intersects", &Geometry::intersects)
        // .def("contains", &Geometry::contains)
        
        .def("accessFrame", &Geometry::accessFrame)
        .def("in", &Geometry::in)
        .def("isPoint", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Point>() ; })
        .def("isPointSet", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<PointSet>() ; })
        .def("isLine", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Line>() ; })
        .def("isRay", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Ray>() ; })
        .def("isSegment", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Segment>() ; })
        .def("isLineString", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<LineString>() ; })
        .def("isPolygon", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Polygon>() ; })
        .def("isPlane", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Plane>() ; })
        .def("isSphere", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Sphere>() ; })
        .def("isEllipsoid", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Ellipsoid>() ; })
        .def("isPyramid", +[] (const Geometry& aGeometry) -> bool { return aGeometry.is<Pyramid>() ; })
        .def("asPoint", +[] (const Geometry& aGeometry) -> Point { return aGeometry.as<Point>() ; })
        .def("asPointSet", +[] (const Geometry& aGeometry) -> PointSet { return aGeometry.as<PointSet>() ; })
        .def("asLine", +[] (const Geometry& aGeometry) -> Line { return aGeometry.as<Line>() ; })
        .def("asRay", +[] (const Geometry& aGeometry) -> Ray { return aGeometry.as<Ray>() ; })
        .def("asSegment", +[] (const Geometry& aGeometry) -> Segment { return aGeometry.as<Segment>() ; })
        .def("asLineString", +[] (const Geometry& aGeometry) -> LineString { return aGeometry.as<LineString>() ; })
        .def("asPolygon", +[] (const Geometry& aGeometry) -> Polygon { return aGeometry.as<Polygon>() ; })
        .def("asPlane", +[] (const Geometry& aGeometry) -> Plane { return aGeometry.as<Plane>() ; })
        .def("asSphere", +[] (const Geometry& aGeometry) -> Sphere { return aGeometry.as<Sphere>() ; })
        .def("asEllipsoid", +[] (const Geometry& aGeometry) -> Ellipsoid { return aGeometry.as<Ellipsoid>() ; })
        .def("asPyramid", +[] (const Geometry& aGeometry) -> Pyramid { return aGeometry.as<Pyramid>() ; })
        .def("intersectionWith", &Geometry::intersectionWith)
        
        .def("Undefined", &Geometry::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////