/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Sun.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Sun(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::filesystem::Directory;
    using ostk::core::type::Shared;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::environment::gravitational::Sun;

    {
        class_<Sun, Model, Shared<Sun>> sun_class(
            aModule,
            "Sun",
            R"doc(
                Sun gravitational model.

                The gravitational potential of the Sun for now is kept as a simple spherical model.
            )doc"
        );

        sun_class

            .def(
                init<const Sun::Type&, const Directory&>(),
                arg("type"),
                arg("directory"),
                R"doc(
                    Construct a Sun gravitational model.

                    Args:
                        type (Sun.Type): Sun model type.
                        directory (Directory): Directory containing the gravity model data files.
                )doc"
            )

            .def(
                init<const Sun::Type&>(),
                arg("type"),
                R"doc(
                    Construct a Sun gravitational model.

                    Args:
                        type (Sun.Type): Sun model type.
                )doc"
            )

            .def(
                "is_defined",
                &Sun::isDefined,
                R"doc(
                    Check if the Sun model is defined.

                    Returns:
                        bool: True if defined.
                )doc"
            )

            .def(
                "get_type",
                &Sun::getType,
                R"doc(
                    Get the Sun model type.

                    Returns:
                        Sun.Type: Sun model type.
                )doc"
            )

            .def(
                "get_field_value_at",
                &Sun::getFieldValueAt,
                arg("position"),
                arg("instant"),
                R"doc(
                    Get the gravitational field value at a given position and instant.
                )doc"
            )

            .def_readonly_static(
                "spherical",
                &Sun::Spherical,
                R"doc(
                    Spherical gravitational model.
                )doc"
            )

            ;

        enum_<Sun::Type>(sun_class, "Type")

            .value(
                "Undefined",
                Sun::Type::Undefined,
                R"doc(
                    Undefined.
                )doc"
            )
            .value(
                "Spherical",
                Sun::Type::Spherical,
                R"doc(
                    The spherical gravity originating from a point source at the center of the Sun.
                )doc"
            )

            ;
    }
}
