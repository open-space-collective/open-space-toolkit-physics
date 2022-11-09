////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Velocity.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Velocity (          pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Shared ;

    using ostk::math::obj::Vector3d ;

    using ostk::physics::coord::Velocity ;
    using ostk::physics::coord::Frame ;

    class_<Velocity> velocity(aModule, "Velocity") ;

    velocity

        .def(init<Vector3d, Velocity::Unit, Shared<const Frame>&>(), arg("coordinates"), arg("unit"), arg("frame"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Velocity>))
        .def("__repr__", &(shiftToString<Velocity>))

        .def("is_defined", &Velocity::isDefined)

        .def("access_frame", &Velocity::accessFrame)

        .def("get_coordinates", &Velocity::getCoordinates)
        .def("get_unit", &Velocity::getUnit)
        .def("in_unit", &Velocity::inUnit, arg("unit"))
        .def("in_frame", &Velocity::inFrame, arg("position"), arg("frame"), arg("instant"))
        .def("to_string", &Velocity::toString, arg("precision") = DEFAULT_PRECISION)

        .def_static("undefined", &Velocity::Undefined)
        .def_static("meters_per_second", &Velocity::MetersPerSecond, arg("coordinates"), arg("frame"))
        .def_static("string_from_unit", &Velocity::StringFromUnit, arg("unit"))

    ;

    enum_<Velocity::Unit>(velocity, "Unit")

        .value("Undefined", Velocity::Unit::Undefined)
        .value("MeterPerSecond", Velocity::Unit::MeterPerSecond)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
