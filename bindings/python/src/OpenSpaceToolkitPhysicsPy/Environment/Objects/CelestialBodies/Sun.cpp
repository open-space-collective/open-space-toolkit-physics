////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies/Sun.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Sun.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Sun ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;

    using ostk::physics::time::Instant ;
    using ostk::physics::env::Ephemeris ;
    using ostk::physics::env::obj::Celestial ;
    using ostk::physics::env::obj::celest::Sun ;

    {

        scope in_Sun = class_<Sun, bases<Celestial>>("Sun", init<const Shared<Ephemeris>&, const Instant&>())

            .def_readonly("gravitational_parameter", &Sun::GravitationalParameter)
            .def_readonly("equatorial_radius", &Sun::EquatorialRadius)
            .def_readonly("flattening", &Sun::Flattening)

            .def(self_ns::str(self_ns::self))
            .def(self_ns::repr(self_ns::self))

            .def("default", &Sun::Default).staticmethod("default")

        ;

    }

    {

        boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.environment.objects.celestial_bodies.sun")))) ;

        boost::python::scope().attr("sun") = module ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
