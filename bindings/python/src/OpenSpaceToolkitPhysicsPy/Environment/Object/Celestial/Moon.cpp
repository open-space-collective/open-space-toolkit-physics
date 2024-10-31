/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Moon.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial_Moon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::object::Celestial;
    using ostk::physics::environment::object::celestial::Moon;
    using ostk::physics::time::Instant;
    using MoonGravitationalModel = ostk::physics::environment::gravitational::Moon;

    {
        class_<Moon, Shared<Moon>, Celestial>(
            aModule,
            "Moon",
            R"doc(
                Moon.
            )doc"
        )

            .def(
                init<const Shared<Ephemeris>&, const Shared<MoonGravitationalModel>&>(),
                arg("ephemeris"),
                arg("gravitational_model"),
                R"doc(
                    Constructor.

                    Args:
                        ephemeris (Ephemeris): Ephemeris.
                        gravitational_model (MoonGravitationalModel): Gravitational model.
                )doc"
            )

            .def("__str__", &(shiftToString<Moon>))
            .def("__repr__", &(shiftToString<Moon>))

            .def_static(
                "default",
                &Moon::Default,
                R"doc(
                    Create a default Moon.

                    Returns:
                        Moon: Default Moon.
                )doc"
            )
            .def_static(
                "spherical",
                &Moon::Spherical,
                R"doc(
                    Spherical model.

                    Returns:
                        Moon: Moon.
                )doc"
            )

            ;
    }

    {
        // Create "moon" python submodule
        auto moon = aModule.def_submodule("moon");
    }
}
