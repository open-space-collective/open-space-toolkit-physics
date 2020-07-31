////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies/Moon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Moon ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;

    using ostk::physics::time::Instant ;
    using ostk::physics::env::Ephemeris ;
    using ostk::physics::env::obj::Celestial ;
    using ostk::physics::env::obj::celest::Moon ;

    {

        scope in_Moon = class_<Moon, bases<Celestial>>("Moon", init<const Shared<Ephemeris>&, const Instant&>())

            .def_readonly("gravitational_parameter", &Moon::GravitationalParameter)
            .def_readonly("equatorial_radius", &Moon::EquatorialRadius)
            .def_readonly("flattening", &Moon::Flattening)

            .def(self_ns::str(self_ns::self))
            .def(self_ns::repr(self_ns::self))

            .def("default", &Moon::Default).staticmethod("default")

        ;

    }

    {

        boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.environment.objects.celestial_bodies.moon")))) ;

        boost::python::scope().attr("moon") = module ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
