/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::Shared;

    using ostk::physics::units::Length;
    using ostk::physics::units::Derived;
    using ostk::physics::time::Instant;
    using ostk::physics::env::Ephemeris;
    using ostk::physics::env::obj::Celestial;
    using ostk::physics::env::obj::celest::Earth;
    using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
    using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;
    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;

    {
        class_<Earth, Shared<Earth>, Celestial>(aModule, "Earth")

            .def(
                init<
                    const Derived&,
                    const Length&,
                    const Real&,
                    const Real&,
                    const Real&,
                    const Shared<Ephemeris>&,
                    const Shared<EarthGravitationalModel>&,
                    const Shared<EarthMagneticModel>&,
                    const Shared<EarthAtmosphericModel>&>(),
                arg("gravitational_parameter"),
                arg("equatorial_radius"),
                arg("flattening"),
                arg("J2_parameter_value"),
                arg("J4_parameter_value"),
                arg("ephemeris"),
                arg("gravitational_model"),
                arg("magnetic_model"),
                arg("atmospheric_model")
            )

            .def(
                init<
                    const Shared<Ephemeris>&,
                    const Shared<EarthGravitationalModel>&,
                    const Shared<EarthMagneticModel>&,
                    const Shared<EarthAtmosphericModel>&>(),
                arg("ephemeris"),
                arg("gravitational_model"),
                arg("magnetic_model"),
                arg("atmospheric_model")
            )

            .def("__str__", &(shiftToString<Earth>))
            .def("__repr__", &(shiftToString<Earth>))

            .def_static("default", &Earth::Default)
            .def_static(
                "EGM2008", &Earth::EGM2008, arg("degree") = Integer::Undefined(), arg("order") = Integer::Undefined()
            )
            .def_static(
                "WGS84_EGM96",
                &Earth::WGS84_EGM96,
                arg("degree") = Integer::Undefined(),
                arg("order") = Integer::Undefined()
            )
            .def_static(
                "EGM96", &Earth::EGM96, arg("degree") = Integer::Undefined(), arg("order") = Integer::Undefined()
            )
            .def_static(
                "EGM84", &Earth::EGM84, arg("degree") = Integer::Undefined(), arg("order") = Integer::Undefined()
            )
            .def_static(
                "WGS84", &Earth::WGS84, arg("degree") = Integer::Undefined(), arg("order") = Integer::Undefined()
            )
            .def_static("spherical", &Earth::Spherical)

            ;
    }

    {
        // Create "earth" python submodule
        auto earth = aModule.def_submodule("earth");

        // Add __path__ attribute for "earth" submodule
        earth.attr("__path__") = "ostk.physics.environment.objects.celestial_bodies.earth";
    }
}
