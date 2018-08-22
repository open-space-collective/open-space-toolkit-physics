////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Environment/Objects/CelestialBodies/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Environment_Objects_CelestialBodies_Earth ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;

    using library::physics::time::Instant ;
    using library::physics::env::Ephemeris ;
    using library::physics::env::obj::Celestial ;
    using library::physics::env::obj::celest::Earth ;

    scope in_Earth = class_<Earth, bases<Celestial>>("Earth", init<const Shared<Ephemeris>&, const Instant&>())

        .def_readonly("GravitationalConstant", &Earth::GravitationalConstant)
        .def_readonly("EquatorialRadius", &Earth::EquatorialRadius)
        .def_readonly("Flattening", &Earth::Flattening)
        .def_readonly("C20", &Earth::C20)
        .def_readonly("J2", &Earth::J2)

        .def(self_ns::str(self_ns::self))

        .def("accessGeometry", &Earth::accessGeometry, return_value_policy<reference_existing_object>())
        
        .def("Analytical", &Earth::Analytical).staticmethod("Analytical")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////