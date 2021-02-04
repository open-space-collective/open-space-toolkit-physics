////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Position.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Position (         pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Shared ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Position ;
    using ostk::physics::coord::Frame ;

    class_<Position>(aModule, "Position")

        .def(init<Vector3d, Position::Unit, Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Position>))
        .def("__repr__", &(shiftToString<Position>))

        .def("is_defined", &Position::isDefined)
        .def("is_near", &Position::isNear)

        .def("access_frame", &Position::accessFrame)
        .def("get_coordinates", &Position::getCoordinates)
        .def("get_unit", &Position::getUnit)
        .def("in_unit", &Position::inUnit)
        .def("in_meters", &Position::inMeters)
        .def("in_frame", &Position::inFrame)
        .def("to_string", &Position::toString, "aPrecision"_a=Integer::Undefined())

        .def_static("undefined", &Position::Undefined)
        .def_static("meters", &Position::Meters)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
