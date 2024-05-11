/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Earth/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Shared;
    using ostk::core::filesystem::Directory;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::environment::gravitational::Earth;
    using ostk::physics::environment::gravitational::earth::Manager;

    {
        class_<Earth, Model, Shared<Earth>> earth_class(
            aModule,
            "Earth",
            R"doc(
                Earth gravitational model.

                The gravitational potential is expanded as sum of spherical harmonics.

                :seealso: https://en.wikipedia.org/wiki/Spherical_harmonics
                :seealso: https://geographiclib.sourceforge.io/html/gravity.html
            )doc"
        );

        earth_class

            .def(
                init<const Earth::Type&, const Directory&>(),
                arg("type"),
                arg("directory"),
                R"doc(
                    Construct an Earth gravitational model.

                    Args:
                        type (Earth.Type): Earth model type.
                        directory (Directory): Directory containing the gravity model data files.
                )doc"
            )

            .def(
                init<const Earth::Type&>(),
                arg("type"),
                R"doc(
                    Construct an Earth gravitational model.

                    Args:
                        type (Earth.Type): Earth model type.
                )doc"
            )

            .def(
                init<const Earth::Type&, const Directory&, const Integer&, const Integer&>(),
                arg("type"),
                arg("directory"),
                arg("gravitational_model_degree"),
                arg("gravitational_model_order"),
                R"doc(
                    Construct an Earth gravitational model.

                    Args:
                        type (Earth.Type): Earth model type.
                        directory (Directory): Directory containing the gravity model data files.
                        gravitational_model_degree (int): Degree of the gravitational model.
                        gravitational_model_order (int): Order of the gravitational model.
                )doc"
            )

            .def(
                "is_defined",
                &Earth::isDefined,
                R"doc(
                    Check if the Earth model is defined.

                    Returns:
                        bool: True if the model is defined.
                )doc"
            )

            .def(
                "get_type",
                &Earth::getType,
                R"doc(
                    Get the Earth model type.

                    Returns:
                        Earth.Type: Earth model type.
                )doc"
            )

            .def(
                "get_degree",
                &Earth::getDegree,
                R"doc(
                    Get the Earth model degree.

                    Returns:
                        int: Earth model degree.
                )doc"
            )
            .def(
                "get_order",
                &Earth::getOrder,
                R"doc(
                    Get the Earth model order.

                    Returns:
                        int: Earth model order.
                )doc"
            )

            .def(
                "get_field_value_at",
                &Earth::getFieldValueAt,
                arg("position"),
                arg("instant"),
                R"doc(
                    Get the gravitational field value at a given position and instant.

                    Args:
                        position (Position): A position.
                        instant (Instant): An instant.

                    Returns:
                        Vector3d: Gravitational field value [m.s^-2].
                )doc"
            )

            .def_readonly_static(
                "EGM2008",
                &Earth::EGM2008,
                R"doc(
                    The Earth Gravity Model 2008, which includes terms up to degree 2190.
                )doc"
            )
            .def_readonly_static(
                "EGM96",
                &Earth::EGM96,
                R"doc(
                    The Earth Gravity Model 1996, which includes terms up to degree 360.
                )doc"
            )
            .def_readonly_static(
                "EGM84",
                &Earth::EGM84,
                R"doc(
                    The Earth Gravity Model 1984, which includes terms up to degree 180.
                )doc"
            )
            .def_readonly_static(
                "WGS84_EGM96",
                &Earth::WGS84_EGM96,
                R"doc(
                    The normal gravitational field for the reference ellipsoid plus the Earth Gravity Model 1996,
                    which includes terms up to degree 360.
                )doc"
            )
            .def_readonly_static(
                "WGS84",
                &Earth::WGS84,
                R"doc(
                    The normal gravitational field for the reference ellipsoid. This includes the zonal coefficients up to order 20.
                )doc"
            )
            .def_readonly_static(
                "spherical",
                &Earth::Spherical,
                R"doc(
                    The spherical gravity originating from a point source at the center of the Earth.
                )doc"
            )
            .def_readonly_static(
                "gravity_constant",
                &Earth::gravityConstant,
                R"doc(
                    The gravitational constant [m^3.kg^-1.s^-2].
                )doc"
            )

            ;

        enum_<Earth::Type>(earth_class, "Type")

            .value(
                "Undefined",
                Earth::Type::Undefined,
                R"doc(
                    Undefined.
                )doc"
            )
            .value(
                "Spherical",
                Earth::Type::Spherical,
                R"doc(
                    The spherical gravity originating from a point source at the center of the Earth.
                )doc"
            )
            .value(
                "WGS84",
                Earth::Type::WGS84,
                R"doc(
                    The normal gravitational field for the reference ellipsoid. This includes the zonal coefficients up to order 20.
                )doc"
            )
            .value(
                "EGM84",
                Earth::Type::EGM84,
                R"doc(
                    The Earth Gravity Model 1984, which includes terms up to degree 180.
                )doc"
            )
            .value(
                "WGS84_EGM96",
                Earth::Type::WGS84_EGM96,
                R"doc(
                    The normal gravitational field for the reference ellipsoid plus the Earth Gravity Model 1996,
                    which includes terms up to degree 360.
                )doc"
            )
            .value(
                "EGM96",
                Earth::Type::EGM96,
                R"doc(
                    The Earth Gravity Model 1996, which includes terms up to degree 360.
                )doc"
            )
            .value(
                "EGM2008",
                Earth::Type::EGM2008,
                R"doc(
                    The Earth Gravity Model 2008, which includes terms up to degree 2190.
                )doc"
            );
    }

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth");

    OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth_Manager(earth);
}
