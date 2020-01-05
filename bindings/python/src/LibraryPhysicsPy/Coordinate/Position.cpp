////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkitPhysicsPy/Coordinate/Position.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Coordinate_Position_toString_overloads, ostk::physics::coord::Position::toString, 0, 1)

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Position        ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Position ;
    using ostk::physics::coord::Frame ;

    scope in_Position = class_<Position>("Position", init<Vector3d, Position::Unit, Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Position::isDefined)
        .def("isNear", &Position::isNear)

        .def("accessFrame", &Position::accessFrame)
        .def("getCoordinates", &Position::getCoordinates)
        .def("getUnit", &Position::getUnit)
        .def("inUnit", &Position::inUnit)
        .def("inMeters", &Position::inMeters)
        .def("inFrame", &Position::inFrame)
        .def("toString", &Position::toString, OpenSpaceToolkitPhysicsPy_Coordinate_Position_toString_overloads())

        .def("Undefined", &Position::Undefined).staticmethod("Undefined")
        .def("Meters", &Position::Meters).staticmethod("Meters")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
