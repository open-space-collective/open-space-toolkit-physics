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
                    const EarthGravitationalModel::Type&,
                    const EarthMagneticModel::Type&,
                    const EarthAtmosphericModel::Type&>(),
                arg("gravitational_parameter"),
                arg("equatorial_radius"),
                arg("flattening"),
                arg("J2_parameter_value"),
                arg("J4_parameter_value"),
                arg("ephemeris"),
                arg("gravitational_model_type"),
                arg("magnetic_model_type"),
                arg("atmospheric_model_type")
            )

            .def(
                init<
                    const Derived&,
                    const Length&,
                    const Real&,
                    const Real&,
                    const Real&,
                    const Shared<Ephemeris>&,
                    const EarthGravitationalModel::Type&,
                    const Integer&,
                    const Integer&,
                    const EarthMagneticModel::Type&,
                    const EarthAtmosphericModel::Type&>(),
                arg("gravitational_parameter"),
                arg("equatorial_radius"),
                arg("flattening"),
                arg("J2_parameter_value"),
                arg("J4_parameter_value"),
                arg("ephemeris"),
                arg("gravitational_model_type"),
                arg("gravitational_model_degree"),
                arg("gravitational_model_order"),
                arg("magnetic_model_type"),
                arg("atmospheric_model_type")
            )

            .def_readonly_static("gravitational_parameter", &Earth::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Flattening)
            .def_readonly_static("C20", &Earth::C20)
            .def_readonly_static("C40", &Earth::C40)
            .def_readonly_static("J2", &Earth::J2)
            .def_readonly_static("J4", &Earth::J4)

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

        // Create "models" python submodule
        auto models = earth.def_submodule("models");

        // Add __path__ attribute for "models" submodule
        models.attr("__path__") = "ostk.physics.environment.objects.celestial_bodies.earth.models";

        class_<Earth::Models::EGM2008>(models, "EGM2008")

            .def_readonly_static("gravitational_parameter", &Earth::Models::EGM2008::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::EGM2008::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::EGM2008::Flattening)
            .def_readonly_static("C20", &Earth::Models::EGM2008::C20)
            .def_readonly_static("C40", &Earth::Models::EGM2008::C40)
            .def_readonly_static("J2", &Earth::Models::EGM2008::J2)
            .def_readonly_static("J4", &Earth::Models::EGM2008::J4)

            ;

        class_<Earth::Models::WGS84_EGM96>(models, "WGS84_EGM96")

            .def_readonly_static("gravitational_parameter", &Earth::Models::WGS84_EGM96::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::WGS84_EGM96::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::WGS84_EGM96::Flattening)
            .def_readonly_static("C20", &Earth::Models::WGS84_EGM96::C20)
            .def_readonly_static("C40", &Earth::Models::WGS84_EGM96::C40)
            .def_readonly_static("J2", &Earth::Models::WGS84_EGM96::J2)
            .def_readonly_static("J4", &Earth::Models::WGS84_EGM96::J4)

            ;

        class_<Earth::Models::EGM96>(models, "EGM96")

            .def_readonly_static("gravitational_parameter", &Earth::Models::EGM96::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::EGM96::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::EGM96::Flattening)
            .def_readonly_static("C20", &Earth::Models::EGM96::C20)
            .def_readonly_static("C40", &Earth::Models::EGM96::C40)
            .def_readonly_static("J2", &Earth::Models::EGM96::J2)
            .def_readonly_static("J4", &Earth::Models::EGM96::J4)

            ;

        class_<Earth::Models::EGM84>(models, "EGM84")

            .def_readonly_static("gravitational_parameter", &Earth::Models::EGM84::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::EGM84::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::EGM84::Flattening)
            .def_readonly_static("C20", &Earth::Models::EGM84::C20)
            .def_readonly_static("C40", &Earth::Models::EGM84::C40)
            .def_readonly_static("J2", &Earth::Models::EGM84::J2)
            .def_readonly_static("J4", &Earth::Models::EGM84::J4)

            ;

        class_<Earth::Models::WGS84>(models, "WGS84")

            .def_readonly_static("gravitational_parameter", &Earth::Models::WGS84::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::WGS84::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::WGS84::Flattening)
            .def_readonly_static("C20", &Earth::Models::WGS84::C20)
            .def_readonly_static("C40", &Earth::Models::WGS84::C40)
            .def_readonly_static("J2", &Earth::Models::WGS84::J2)
            .def_readonly_static("J4", &Earth::Models::WGS84::J4)

            ;

        class_<Earth::Models::Spherical>(models, "Spherical")

            .def_readonly_static("gravitational_parameter", &Earth::Models::Spherical::GravitationalParameter)
            .def_readonly_static("equatorial_radius", &Earth::Models::Spherical::EquatorialRadius)
            .def_readonly_static("flattening", &Earth::Models::Spherical::Flattening)
            .def_readonly_static("C20", &Earth::Models::Spherical::C20)
            .def_readonly_static("C40", &Earth::Models::Spherical::C40)
            .def_readonly_static("J2", &Earth::Models::Spherical::J2)
            .def_readonly_static("J4", &Earth::Models::Spherical::J4)

            ;
    }
}
