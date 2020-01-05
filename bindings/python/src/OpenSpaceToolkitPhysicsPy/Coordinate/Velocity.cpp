////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Velocity.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Coordinate_Velocity_toString_overloads, ostk::physics::coord::Velocity::toString, 0, 1)

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Velocity        ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Velocity ;
    using ostk::physics::coord::Frame ;

    scope in_Velocity = class_<Velocity>("Velocity", init<Vector3d, Velocity::Unit, Shared<const Frame>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Velocity::isDefined)

        .def("access_frame", &Velocity::accessFrame)
        .def("get_coordinates", &Velocity::getCoordinates)
        .def("get_unit", &Velocity::getUnit)
        .def("in_unit", &Velocity::inUnit)
        .def("in_frame", &Velocity::inFrame)
        .def("to_string", &Velocity::toString, OpenSpaceToolkitPhysicsPy_Coordinate_Velocity_toString_overloads())

        .def("undefined", &Velocity::Undefined).staticmethod("undefined")
        .def("meters_per_second", &Velocity::MetersPerSecond).staticmethod("meters_per_second")
        .def("string_from_unit", &Velocity::StringFromUnit).staticmethod("string_from_unit")

    ;

    enum_<Velocity::Unit>("Unit")

        .value("Undefined", Velocity::Unit::Undefined)
        .value("MeterPerSecond", Velocity::Unit::MeterPerSecond)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
