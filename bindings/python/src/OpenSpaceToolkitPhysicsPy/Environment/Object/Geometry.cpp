/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Object/Geometry.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Object_Geometry(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Unique;
    using ostk::core::type::Shared;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Composite;

    using ostk::physics::coordinate::Frame;
    using ostk::physics::environment::object::Geometry;

    class_<Geometry>(aModule, "Geometry",
        R"doc(
            Geometry.
        )doc"
    )

        // Define constructors from children -> parents (to ensure that parent constructor is not always used by
        // default)
        .def(init<const Composite&, const Shared<const Frame>&>())
        .def(init<const Geometry::Object&, const Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Geometry>))
        .def("__repr__", &(shiftToString<Geometry>))

        .def("is_defined", &Geometry::isDefined,
            R"doc(
                Check if the geometry is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def("intersects", &Geometry::intersects,
            R"doc(
                Check if the geometry intersects with another geometry.

                Args:
                    aGeometry (Geometry): Another geometry

                Returns:
                    bool: True if geometries intersect.
            )doc"
        )
        .def("contains", &Geometry::contains,
            R"doc(
                Check if the geometry contains a point.

                Args:
                    aPoint (Point): A point

                Returns:
                    bool: True if geometry contains point.
            )doc"
        )

        // .def("access_composite", &Geometry::accessComposite, return_value_policy<reference_existing_object>())
        .def("access_composite", &Geometry::accessComposite, return_value_policy::reference,
            R"doc(
                Access composite.

                Returns:
                    Composite: Composite.
            )doc"
        )
        .def("access_frame", &Geometry::accessFrame,
            R"doc(
                Access frame.

                Returns:
                    Frame: Frame.
            )doc"
        )
        .def("in_frame", &Geometry::in,
            R"doc(
                Get geometry expressed in a given frame.

                Args:
                    aFrame (Frame): Frame
                    anInstant (Instant): An instant

                Returns:
                    Geometry: Geometry expressed in a given frame.
            )doc"
        )
        .def("intersection_with", &Geometry::intersectionWith,
            R"doc(
                Compute intersection of geometry with another geometry.

                Args:
                    aGeometry (Geometry): Another geometry

                Returns:
                    Geometry: Intersection of geometry with another geometry.
            )doc"
        )

        .def_static("undefined", &Geometry::Undefined,
            R"doc(
                Constructs an undefined geometry.

                Returns:
                    Geometry: Undefined geometry.
            )doc"
        )

        ;
}
