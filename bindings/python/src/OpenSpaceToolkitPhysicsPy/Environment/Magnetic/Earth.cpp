/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Earth/Manager.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Magnetic/Earth/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::filesystem::Directory;
    using ostk::core::type::Shared;

    using ostk::physics::unit::Derived;
    using ostk::physics::environment::magnetic::Earth;
    using ostk::physics::environment::magnetic::earth::Manager;

    class_<Earth, Shared<Earth>> earth_magnetic_class(aModule, "Earth",
        R"doc(
            Earth magnetic model.

            .. seealso:: https://geographiclib.sourceforge.io/html/magnetic.html
        )doc"
    );

    earth_magnetic_class
        .def(init<const Earth::Type&, const Directory&>(), arg("type"), arg("directory"),
            R"doc(
                Construct an Earth magnetic model.

                Args:
                    type (Earth.Type): Earth model type.
                    directory (Directory): Directory containing the magnetic model data files.
            )doc"
        )

        .def(init<const Earth::Type&>(), arg("type"),
            R"doc(
                Construct an Earth magnetic model.

                Args:
                    type (Earth.Type): Earth model type.
            )doc"
        )

        .def("get_type", &Earth::getType,
            R"doc(
                Get Earth model type.

                Returns:
                    Earth.Type: Earth model type.
            )doc"
        )

        .def("is_defined", &Earth::isDefined,
            R"doc(
                Check if the magnetic model is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def("get_field_value_at", &Earth::getFieldValueAt,
            R"doc(
                Get the magnetic field value at a given position and instant.

                Args:
                    position (Vector3d): Position, expressed in the magnetic object frame [m].
                    instant (Instant): Instant.

                Returns:
                    Vector3d: Magnetic field value, expressed in the magnetic object frame [T].
            )doc"
        )

        ;

    enum_<Earth::Type>(earth_magnetic_class, "Type")

        .value("Undefined", Earth::Type::Undefined,
            R"doc(
                Undefined Earth model type.
            )doc"
        )
        .value("Dipole", Earth::Type::Dipole,
            R"doc(
                Dipole Earth model type.
            )doc"
        )
        .value("EMM2010", Earth::Type::EMM2010,
            R"doc(
                Enhanced Magnetic Model 2010: approximates the main and crustal magnetic fields for the period 2010–2015.
            )doc"
        )
        .value("EMM2015", Earth::Type::EMM2015,
            R"doc(
                Enhanced Magnetic Model 2015: approximates the main and crustal magnetic fields for the period 2000–2020.
            )doc"
        )
        .value("EMM2017", Earth::Type::EMM2017,
            R"doc(
                Enhanced Magnetic Model 2017: approximates the main and crustal magnetic fields for the period 2000–2022.
            )doc"
        )
        .value("IGRF11", Earth::Type::IGRF11,
            R"doc(
                International Geomagnetic Reference Field (11th generation): approximates the main magnetic field for the period 1900–2015.
            )doc"
        )
        .value("IGRF12", Earth::Type::IGRF12,
            R"doc(
                International Geomagnetic Reference Field (12th generation): approximates the main magnetic field for the period 1900–2020.
            )doc"
        )
        .value("WMM2010", Earth::Type::WMM2010,
            R"doc(
                World Magnetic Model 2010: approximates the main magnetic field for the period 2010–2015.
            )doc"
        )
        .value("WMM2015", Earth::Type::WMM2015,
            R"doc(
                World Magnetic Model 2015: approximates the main magnetic field for the period 2015–2020.
            )doc"
        )

        ;

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth");


    OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Earth_Manager(earth);
}
