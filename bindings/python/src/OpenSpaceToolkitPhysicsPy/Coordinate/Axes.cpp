////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Axes.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Axes            ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Axes ;
    using ostk::physics::coord::Frame ;

    scope in_Axes = class_<Axes>("Axes", init<const Vector3d&, const Vector3d&, const Vector3d&, const Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Axes::isDefined)

        .def("x", +[] (const Axes& anAxes) -> Vector3d { return anAxes.x() ; })
        .def("y", +[] (const Axes& anAxes) -> Vector3d { return anAxes.y() ; })
        .def("z", +[] (const Axes& anAxes) -> Vector3d { return anAxes.z() ; })
        .def("getFrame", &Axes::getFrame)
        .def("inFrame", &Axes::inFrame)

        .def("Undefined", &Axes::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
