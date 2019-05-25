////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Coordinate/Position.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Position.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Coordinate_Position_toString_overloads, library::physics::coord::Position::toString, 0, 1)

inline void                     LibraryPhysicsPy_Coordinate_Position        ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;

    using library::math::obj::Vector3d ;

    using library::physics::coord::Position ;
    using library::physics::coord::Frame ;

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
        .def("inFrame", &Position::inFrame)
        .def("toString", &Position::toString, LibraryPhysicsPy_Coordinate_Position_toString_overloads())

        .def("Undefined", &Position::Undefined).staticmethod("Undefined")
        .def("Meters", &Position::Meters).staticmethod("Meters")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
