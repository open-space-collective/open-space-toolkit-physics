/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Moon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::time::Instant;
    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::object::Celestial;
    using ostk::physics::environment::object::celestial::Moon;
    using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

    {
        class_<Moon, Shared<Moon>, Celestial>(aModule, "Moon")

            .def(
                init<const Shared<Ephemeris>&, const Shared<MoonGravitationalModel>&>(),
                arg("ephemeris"),
                arg("gravitational_model")
            )

            .def("__str__", &(shiftToString<Moon>))
            .def("__repr__", &(shiftToString<Moon>))

            .def_static("default", &Moon::Default)
            .def_static("spherical", &Moon::Spherical)

            ;
    }

    {
        // Create "moon" python submodule
        auto moon = aModule.def_submodule("moon");

        // Add __path__ attribute for "moon" submodule
        moon.attr("__path__") = "ostk.physics.environment.objects.celestial_bodies.moon";
    }
}
