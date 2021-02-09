////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies/Moon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Moon (        pybind11::module& aModule                           )
{

    using namespace pybind11 ;

    using ostk::core::types::Shared ;

    using ostk::physics::time::Instant ;
    using ostk::physics::env::Ephemeris ;
    using ostk::physics::env::obj::Celestial ;
    using ostk::physics::env::obj::celest::Moon ;

    {

        class_<Moon, Shared<Moon>, Celestial>(aModule, "Moon")

            .def(init<const Shared<Ephemeris>&, const Instant&>())

            .def_readonly_static("gravitational_parameter", &Moon::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Moon::EquatorialRadius)
            .def_readonly_static("flattening", &Moon::Flattening)

            .def("__str__", &(shiftToString<Moon>))
            .def("__repr__", &(shiftToString<Moon>))

            .def_static("default", &Moon::Default)

        ;

    }

    {

        // Create "moon" python submodule
        auto moon = aModule.def_submodule("moon") ;

        // Add __path__ attribute for "moon" submodule
        moon.attr("__path__") = "ostk.physics.environment.objects.celestial_bodies.moon" ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
