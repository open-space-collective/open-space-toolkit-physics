/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Moon.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Moon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::filesystem::Directory;
    using ostk::core::type::Shared;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::environment::gravitational::Moon;

    {
        class_<Moon, Shared<Moon>, Model> moon_class(
            aModule,
            "Moon",
            R"doc(
                Moon gravitational model.

                The gravitational potential of the Moon for now is kept as a simple spherical model.
            )doc"
        );

        moon_class

            .def(
                init<const Moon::Type&, const Directory&>(),
                arg("type"),
                arg("directory"),
                R"doc(
                    Construct a Moon gravitational model.

                    Args:
                        type (Moon.Type): Moon model type.
                        directory (Directory): Directory containing the gravity model data files.
                )doc"
            )

            .def(
                init<const Moon::Type&>(),
                arg("type"),
                R"doc(
                    Construct a Moon gravitational model.

                    Args:
                        type (Moon.Type): Moon model type.
                )doc"
            )

            .def(
                "is_defined",
                &Moon::isDefined,
                R"doc(
                    Check if the Moon model is defined.

                    Returns:
                        bool: True if defined.
                )doc"
            )

            .def(
                "get_type",
                &Moon::getType,
                R"doc(
                    Get the Moon model type.

                    Returns:
                        Moon.Type: Moon model type.
                )doc"
            )

            .def(
                "get_field_value_at",
                &Moon::getFieldValueAt,
                arg("position"),
                arg("instant"),
                R"doc(
                    Get the gravitational field value at a position.

                    Args:
                        position (np.ndarray): A position.
                        instant (Instant): An instant.

                    Returns:
                        np.ndarray: Gravitational field value.
                )doc"
            )

            ;

        enum_<Moon::Type>(moon_class, "Type")

            .value(
                "Undefined",
                Moon::Type::Undefined,
                R"doc(
                    Undefined Moon model type.
                )doc"
            )
            .value(
                "Spherical",
                Moon::Type::Spherical,
                R"doc(
                    Spherical Moon model type.
                )doc"
            )

            ;
    }
}
