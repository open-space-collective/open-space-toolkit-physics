/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Object/Geometry.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Object_Geometry(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Unique;
    using ostk::core::types::Shared;

    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::PointSet;
    using ostk::math::geometry::d3::objects::Line;
    using ostk::math::geometry::d3::objects::Ray;
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::LineString;
    using ostk::math::geometry::d3::objects::Polygon;
    using ostk::math::geometry::d3::objects::Plane;
    using ostk::math::geometry::d3::objects::Sphere;
    using ostk::math::geometry::d3::objects::Ellipsoid;
    using ostk::math::geometry::d3::objects::Pyramid;
    using ostk::math::geometry::d3::objects::Composite;

    using ostk::physics::coord::Frame;
    using ostk::physics::environment::object::Geometry;

    class_<Geometry>(aModule, "Geometry")

        // Define constructors from children -> parents (to ensure that parent constructor is not always used by
        // default)
        .def(init<const Composite&, const Shared<const Frame>&>())
        .def(init<const Geometry::Object&, const Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Geometry>))
        .def("__repr__", &(shiftToString<Geometry>))

        .def("is_defined", &Geometry::isDefined)
        .def("intersects", &Geometry::intersects)
        .def("contains", &Geometry::contains)

        // .def("access_composite", &Geometry::accessComposite, return_value_policy<reference_existing_object>())
        .def("access_composite", &Geometry::accessComposite, return_value_policy::reference)
        .def("access_frame", &Geometry::accessFrame)
        .def("in_frame", &Geometry::in)
        .def("intersection_with", &Geometry::intersectionWith)

        .def_static("undefined", &Geometry::Undefined)

        ;
}
