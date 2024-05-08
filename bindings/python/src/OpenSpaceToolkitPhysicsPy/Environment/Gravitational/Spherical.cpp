/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Spherical(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::environment::gravitational::Spherical;

    class_<Spherical, Model, Shared<Spherical>>(aModule, "Spherical",
        R"doc(
            Spherical gravitational model.

        )doc"
    )

        .def(init<const Model::Parameters&>(), arg("gravitational_parameters"),
            R"doc(
                Construct a Spherical gravitational model.

                Args:
                    gravitational_parameters (GravitationalParameters): Gravitational model parameters.
            )doc"
        )

        .def("get_field_value_at", &Spherical::getFieldValueAt, arg("position"), arg("instant"),
            R"doc(
                Get the gravitational field value at a given position and instant.

                Args:
                    position (Vector3d): Position, expressed in the gravitational object frame [m].
                    instant (Instant): Instant.

                Returns:
                    Vector3d: Gravitational field value, expressed in the gravitational object frame [m.s-2].
            )doc"
        )

        .def("is_defined", &Spherical::isDefined,
            R"doc(
                Check if the Spherical gravitational model is defined.

                Returns:
                    bool: True if the Spherical gravitational model is defined.
            )doc"
        );

        ;
}
