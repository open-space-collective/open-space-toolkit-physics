////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Coordinate/Spherical/LLA.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Spherical/LLA.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Coordinate_Spherical_LLA   ( )
{

    using namespace boost::python ;

    using library::physics::units::Length ;
    using library::physics::units::Angle ;
    using library::physics::coord::spherical::LLA ;

    scope in_LLA = class_<LLA>("LLA", init<const Angle&, const Angle&, const Length&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &LLA::isDefined)

        .def("getLatitude", &LLA::getLatitude)
        .def("getLongitude", &LLA::getLongitude)
        .def("getAltitude", &LLA::getAltitude)
        .def("toVector", &LLA::toVector)
        .def("toCartesian", &LLA::toCartesian)
        .def("toString", &LLA::toString)
        
        .def("Undefined", &LLA::Undefined).staticmethod("Undefined")
        .def("Vector", &LLA::Vector).staticmethod("Vector")
        .def("Cartesian", &LLA::Cartesian).staticmethod("Cartesian")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////