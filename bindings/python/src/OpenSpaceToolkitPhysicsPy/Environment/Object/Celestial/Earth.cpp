/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Object_Celestial_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::physics::unit::Length;
    using ostk::physics::unit::Derived;
    using ostk::physics::coordinate::Frame;
    using ostk::physics::time::Instant;
    using ostk::physics::environment::Ephemeris;
    using ostk::physics::environment::ephemeris::Analytical;
    using ostk::physics::environment::object::Celestial;
    using ostk::physics::environment::object::celestial::Earth;
    using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
    using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;
    using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;

    {
        class_<Earth, Celestial, Shared<Earth>>(aModule, "Earth")

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
                arg("atmospheric_model"),
                R"doc(
                    Constructor

                    Args:
                        gravitational_parameter (Derived): Gravitational parameter [m³/s²]
                        equatorial_radius (Length): Equatorial radius [m]
                        flattening (Real): Flattening
                        J2_parameter_value (Real): J2 parameter value
                        J4_parameter_value (Real): J4 parameter value
                        ephemeris (Ephemeris): Ephemeris
                        gravitational_model (EarthGravitationalModel): Gravitational model
                        magnetic_model (EarthMagneticModel): Magnetic model
                        atmospheric_model (EarthAtmosphericModel): Atmospheric model

                )doc"
            )

            .def(
                init<
                    const Shared<Ephemeris>&,
                    const Shared<EarthGravitationalModel>&,
                    const Shared<EarthMagneticModel>&,
                    const Shared<EarthAtmosphericModel>&>(),
                arg("ephemeris"),
                arg("gravitational_model") = pybind11::none(),
                arg("magnetic_model") = pybind11::none(),
                arg("atmospheric_model") = pybind11::none(),
                R"doc(
                    Constructor

                    Args:
                        ephemeris (Ephemeris): Ephemeris
                        gravitational_model (EarthGravitationalModel): Gravitational model
                        magnetic_model (EarthMagneticModel): Magnetic model
                        atmospheric_model (EarthAtmosphericModel): Atmospheric model
                )doc"
            )

            .def("__str__", &(shiftToString<Earth>))
            .def("__repr__", &(shiftToString<Earth>))

            .def_static("default", &Earth::Default,
                R"doc(
                    Default Earth model (EGM2008).

                    Returns:
                        Earth: Earth

                )doc"
            )
            .def_static(
                "EGM2008",
                &Earth::EGM2008,
                arg_v("degree", Integer::Undefined(), "Integer.undefined()"),
                arg_v("order", Integer::Undefined(), "Integer.undefined()"),
                R"doc(
                    Earth Gravity Model 2008 model (EGM2008).

                    Args:
                        degree (int): Degree
                        order (int): Order

                    Returns:
                        Earth: Earth

                )doc"
            )
            .def_static(
                "WGS84_EGM96",
                &Earth::WGS84_EGM96,
                arg_v("degree", Integer::Undefined(), "Integer.undefined()"),
                arg_v("order", Integer::Undefined(), "Integer.undefined()"),
                R"doc(
                    World Geodetic System 1984 (WGS84) + Earth Gravity Model 1996 (EGM96)

                    EGM96 coefficients and WGS84 shape.
                    Gravitational parameter: 398600441800000 [m^3/s^2].
                    Equatorial radius: 6378137.0 [m].

                    Args:
                        degree (int): Degree
                        order (int): Order

                    Returns:
                        Earth: Earth

                )doc"
            )
            .def_static(
                "EGM96",
                &Earth::EGM96,
                arg_v("degree", Integer::Undefined(), "Integer.undefined()"),
                arg_v("order", Integer::Undefined(), "Integer.undefined()"),
                R"doc(
                    Earth Gravity Model 1996 (EGM96).

                    Args:
                        degree (int): Degree
                        order (int): Order

                    Returns:
                        Earth: Earth
                )doc"
            )
            .def_static(
                "EGM84",
                &Earth::EGM84,
                arg_v("degree", Integer::Undefined(), "Integer.undefined()"),
                arg_v("order", Integer::Undefined(), "Integer.undefined()"),
                R"doc(
                    Earth Gravity Model 1984 (EGM84).

                    Args:
                        degree (int): Degree
                        order (int): Order

                    Returns:
                        Earth: Earth
                )doc"
            )
            .def_static(
                "WGS84",
                &Earth::WGS84,
                arg_v("degree", Integer::Undefined(), "Integer.undefined()"),
                arg_v("order", Integer::Undefined(), "Integer.undefined()"),
                R"doc(
                    World Geodetic System 1984 (WGS84).

                    Args:
                        degree (int): Degree
                        order (int): Order

                    Returns:
                        Earth: Earth
                )doc"
            )
            .def_static("spherical", &Earth::Spherical,
                R"doc(
                    Spherical model.

                    Returns:
                        Earth: Earth
                )doc"
            )

            .def_static("gravitational_only", &Earth::GravitationalOnly, arg("gravity_model"),
                R"doc(
                    Just gravity model

                    Args:
                        gravity_model (EarthGravitationalModel): Gravitational model

                    Returns:
                        Earth: Earth
                )doc"
            )
            .def_static("magnetic_only", &Earth::MagneticOnly, arg("magnetic_model"),
                R"doc(
                    Just magnetic model

                    Args:
                        magnetic_model (EarthMagneticModel): Magnetic model

                    Returns:
                        Earth: Earth
                )doc"
            )
            .def_static("atmospheric_only", &Earth::AtmosphericOnly, arg("atmospheric_model"),
                R"doc(
                    Just atmospheric model

                    Args:
                        atmospheric_model (EarthAtmosphericModel): Atmospheric model

                    Returns:
                        Earth: Earth
                )doc"
            )
            .def_static(
                "from_models", &Earth::FromModels, arg("gravity_model"), arg("magnetic_model"), arg("atmospheric_model"),
                R"doc(
                    Create earth from specified models

                    Args:
                        gravity_model (EarthGravitationalModel): Gravitational model
                        magnetic_model (EarthMagneticModel): Magnetic model
                        atmospheric_model (EarthAtmosphericModel): Atmospheric model

                    Returns:
                        Earth: Earth
                )doc"
            )

            ;
    }
}
