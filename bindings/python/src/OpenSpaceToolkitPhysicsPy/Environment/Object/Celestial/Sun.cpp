/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial_Sun(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::time::Instant;
    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::object::Celestial;
    using ostk::physics::environment::object::celestial::Sun;
    using SunGravitationalModel = ostk::physics::environment::gravitational::Sun;

    {
        class_<Sun, Shared<Sun>, Celestial>(aModule, "Sun")

            .def(
                init<const Shared<Ephemeris>&, const Shared<SunGravitationalModel>&>(),
                arg("ephemeris"),
                arg("gravitational_model")
            )

            .def("__str__", &(shiftToString<Sun>))
            .def("__repr__", &(shiftToString<Sun>))

            .def_static("default", &Sun::Default)
            .def_static("spherical", &Sun::Spherical)

            ;
    }

    {
        // Create "sun" python submodule
        auto sun = aModule.def_submodule("sun");

    }
}
