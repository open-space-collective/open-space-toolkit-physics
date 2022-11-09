////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Axes.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Axes   (           pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Axes ;
    using ostk::physics::coord::Frame ;

    class_<Axes>(aModule, "Axes")

        .def
        (
            init<const Vector3d&, const Vector3d&, const Vector3d&, const Shared<const Frame>&>(),
            arg("x_axis"),
            arg("y_axis"),
            arg("z_axis"),
            arg("frame")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Axes>))
        .def("__repr__", &(shiftToString<Axes>))

        .def("is_defined", &Axes::isDefined)

        .def("x", +[] (const Axes& anAxes) -> Vector3d { return anAxes.x() ; })
        .def("y", +[] (const Axes& anAxes) -> Vector3d { return anAxes.y() ; })
        .def("z", +[] (const Axes& anAxes) -> Vector3d { return anAxes.z() ; })
        .def("get_frame", &Axes::getFrame)
        .def("in_frame", &Axes::inFrame, arg("frame"), arg("instant"))

        .def_static("undefined", &Axes::Undefined)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
