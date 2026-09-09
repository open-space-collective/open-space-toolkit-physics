/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Model(nanobind::module_& aModule)
{
    using namespace nanobind;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::unit::Derived;
    using ostk::physics::unit::Length;

    {
        class_<Model>(
            aModule,
            "Model",
            R"doc(
                Earth Gravitational model.
            )doc"
        )

            .def("get_parameters", &Model::getParameters)

            .def(
                "is_point_mass",
                &Model::isPointMass,
                R"doc(
                    Check if the gravitational model is a point mass model.

                    Returns:
                        bool: True if the gravitational model is a point mass model.
                )doc"
            )

            ;
    }

    {
        class_<Model::Parameters>(
            aModule,
            "GravitationalParameters",
            R"doc(
                Gravitational model parameters.

            )doc"
        )

            .def(
                init<const Derived&, const Length&, const Real&, const Real&, const Real&>(),
                arg("gravitational_parameter"),
                arg("equatorial_radius"),
                arg("flattening"),
                arg("C20"),
                arg("C40"),
                R"doc(
                    Constructor.

                    Args:
                        gravitational_parameter (Derived): Gravitational parameter [m^3/s^2].
                        equatorial_radius (Length): Equatorial radius [m].
                        flattening (Real): Flattening.
                        C20 (Real): C20.
                        C40 (Real): C40.
                )doc"
            )

            .def(
                init<const Derived&, const Length&, const Real&, const Real&, const Real&, const Real&>(),
                arg("gravitational_parameter"),
                arg("equatorial_radius"),
                arg("flattening"),
                arg("C20"),
                arg("C30"),
                arg("C40"),
                R"doc(
                    Constructor.

                    Args:
                        gravitational_parameter (Derived): Gravitational parameter [m^3/s^2].
                        equatorial_radius (Length): Equatorial radius [m].
                        flattening (Real): Flattening.
                        C20 (Real): C20.
                        C30 (Real): C30.
                        C40 (Real): C40.
                )doc"
            )

            .def(
                "__eq__",
                [](const Model::Parameters& self, const Model::Parameters& other)
                {
                    return self == other;
                },
                nanobind::is_operator(),
                R"doc(
                    Equal to operator
                    
                    Args:
                        other (GravitationalParameters): Other parameters.

                    Returns:
                        bool: True if equal
                )doc"
            )
            .def(
                "__ne__",
                [](const Model::Parameters& self, const Model::Parameters& other)
                {
                    return self != other;
                },
                nanobind::is_operator(),
                R"doc(
                    Not equal to operator
                    
                    Args:
                        other (GravitationalParameters): Other parameters.

                    Returns:
                        bool: True if not equal
                )doc"
            )

            .def("__str__", &(shiftToString<Model::Parameters>))
            .def("__repr__", &(shiftToString<Model::Parameters>))

            .def(
                "is_defined",
                &Model::Parameters::isDefined,
                R"doc(
                    Check if the parameters are defined.

                    Returns:
                        bool: True if defined.
                )doc"
            )

            .def(
                "compute_geocentric_radius_at",
                &Model::Parameters::computeGeocentricRadiusAt,
                arg("latitude"),
                R"doc(
                    Compute geocentric radius of ellipsoid at a given latitude.

                    Args:
                        latitude (Angle): A latitude.

                    Returns:
                        Length: Geocentric radius of ellipsoid at a given latitude.
                )doc"
            )

            .def_rw(
                "gravitational_parameter",
                &Model::Parameters::gravitationalParameter_,
                R"doc(
                    Gravitational parameter [m^3/s^2].
                )doc"
            )
            .def_rw(
                "equatorial_radius",
                &Model::Parameters::equatorialRadius_,
                R"doc(
                    Equatorial radius [m].
                )doc"
            )
            .def_rw(
                "flattening",
                &Model::Parameters::flattening_,
                R"doc(
                    Flattening.
                )doc"
            )
            .def_rw(
                "J2",
                &Model::Parameters::J2_,
                R"doc(
                    J2.
                )doc"
            )
            .def_rw(
                "J3",
                &Model::Parameters::J3_,
                R"doc(
                    J3.
                )doc"
            )
            .def_rw(
                "J4",
                &Model::Parameters::J4_,
                R"doc(
                    J4.
                )doc"
            )
            .def_rw(
                "C20",
                &Model::Parameters::C20_,
                R"doc(
                    C20.
                )doc"
            )
            .def_rw(
                "C30",
                &Model::Parameters::C30_,
                R"doc(
                    C30.
                )doc"
            )
            .def_rw(
                "C40",
                &Model::Parameters::C40_,
                R"doc(
                    C40.
                )doc"
            )

            .def_static(
                "undefined",
                &Model::Parameters::Undefined,
                R"doc(
                    Get undefined parameters.

                    Returns:
                        GravitationalParameters: Undefined parameters.
                )doc"
            )

            ;
    }
}
