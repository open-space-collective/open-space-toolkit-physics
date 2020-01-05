////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           LibraryPhysicsPy/Coordinate/Velocity.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Velocity.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Coordinate_Velocity_toString_overloads, ostk::physics::coord::Velocity::toString, 0, 1)

inline void                     LibraryPhysicsPy_Coordinate_Velocity        ( )
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

        .def("isDefined", &Velocity::isDefined)

        .def("accessFrame", &Velocity::accessFrame)
        .def("getCoordinates", &Velocity::getCoordinates)
        .def("getUnit", &Velocity::getUnit)
        .def("inUnit", &Velocity::inUnit)
        .def("inFrame", &Velocity::inFrame)
        .def("toString", &Velocity::toString, LibraryPhysicsPy_Coordinate_Velocity_toString_overloads())

        .def("Undefined", &Velocity::Undefined).staticmethod("Undefined")
        .def("MetersPerSecond", &Velocity::MetersPerSecond).staticmethod("MetersPerSecond")
        .def("StringFromUnit", &Velocity::StringFromUnit).staticmethod("StringFromUnit")

    ;

    enum_<Velocity::Unit>("Unit")

        .value("Undefined", Velocity::Unit::Undefined)
        .value("MeterPerSecond", Velocity::Unit::MeterPerSecond)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
