////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Coordinate/Spherical/LLA.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_LLA   ( )
{

    using namespace boost::python ;

    using ostk::physics::units::Length ;
    using ostk::physics::units::Angle ;
    using ostk::physics::coord::spherical::LLA ;

    scope in_LLA = class_<LLA>("LLA", init<const Angle&, const Angle&, const Length&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &LLA::isDefined)

        .def("get_latitude", &LLA::getLatitude)
        .def("get_longitude", &LLA::getLongitude)
        .def("get_altitude", &LLA::getAltitude)
        .def("to_vector", &LLA::toVector)
        .def("to_cartesian", &LLA::toCartesian)
        .def("to_string", &LLA::toString)

        .def("undefined", &LLA::Undefined).staticmethod("undefined")
        .def("vector", &LLA::Vector).staticmethod("vector")
        .def("cartesian", &LLA::Cartesian).staticmethod("cartesian")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
