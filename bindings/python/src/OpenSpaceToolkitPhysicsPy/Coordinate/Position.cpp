////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Position.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Coordinate_Position_toString_overloads, ostk::physics::coord::Position::toString, 0, 1)

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Position        (            pybind11::module&                     aModule                )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Position ;
    using ostk::physics::coord::Frame ;

    class_<Position>(aModule, "Position")

        .def(init<Vector3d, Position::Unit, Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        // .def(self_ns::str(self_ns::self))
        // .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Position::isDefined)
        .def("is_near", &Position::isNear)

        .def("access_frame", &Position::accessFrame)
        .def("get_coordinates", &Position::getCoordinates)
        .def("get_unit", &Position::getUnit)
        .def("in_unit", &Position::inUnit)
        .def("in_meters", &Position::inMeters)
        .def("in_frame", &Position::inFrame)
        // .def("to_string", &Position::toString, OpenSpaceToolkitPhysicsPy_Coordinate_Position_toString_overloads())

        .def_static("undefined", &Position::Undefined)
        .def_static("meters", &Position::Meters)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
