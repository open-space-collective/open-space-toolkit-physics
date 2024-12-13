/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Model(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::unit::Derived;
    using ostk::physics::unit::Length;

    {
        class_<Model, Shared<Model>>(
            aModule,
            "Model",
            R"doc(
                Earth Gravitational model.
            )doc"
        )

            .def("get_parameters", &Model::getParameters)

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
                self == self,
                R"doc(
                    Equal to operator
                    
                    Args:
                        other (GravitationalParameters): Other parameters.

                    Returns:
                        bool: True if equal
                )doc"
            )
            .def(
                self != self,
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

            .def_readwrite(
                "gravitational_parameter",
                &Model::Parameters::gravitationalParameter_,
                R"doc(
                    Gravitational parameter [m^3/s^2].
                )doc"
            )
            .def_readwrite(
                "equatorial_radius",
                &Model::Parameters::equatorialRadius_,
                R"doc(
                    Equatorial radius [m].
                )doc"
            )
            .def_readwrite(
                "flattening",
                &Model::Parameters::flattening_,
                R"doc(
                    Flattening.
                )doc"
            )
            .def_readwrite(
                "J2",
                &Model::Parameters::J2_,
                R"doc(
                    J2.
                )doc"
            )
            .def_readwrite(
                "J3",
                &Model::Parameters::J3_,
                R"doc(
                    J3.
                )doc"
            )
            .def_readwrite(
                "J4",
                &Model::Parameters::J4_,
                R"doc(
                    J4.
                )doc"
            )
            .def_readwrite(
                "C20",
                &Model::Parameters::C20_,
                R"doc(
                    C20.
                )doc"
            )
            .def_readwrite(
                "C30",
                &Model::Parameters::C30_,
                R"doc(
                    C30.
                )doc"
            )
            .def_readwrite(
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
