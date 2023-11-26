/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Earth.hpp>

#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Earth/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Integer;
    using ostk::core::types::Shared;
    using ostk::core::filesystem::Directory;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::environment::gravitational::Earth;
    using ostk::physics::environment::gravitational::earth::Manager;

    {
        class_<Earth, Model, Shared<Earth>> earth_class(aModule, "Earth");

        earth_class

            .def(init<const Earth::Type&, const Directory&>(), arg("type"), arg("directory"))

            .def(init<const Earth::Type&>(), arg("type"))

            .def(
                init<const Earth::Type&, const Directory&, const Integer&, const Integer&>(),
                arg("type"),
                arg("directory"),
                arg("gravitational_model_degree"),
                arg("gravitational_model_order")
            )

            .def("is_defined", &Earth::isDefined)

            .def("get_type", &Earth::getType)

            .def("get_field_value_at", &Earth::getFieldValueAt, arg("position"), arg("instant"))

            .def_readonly_static("EGM2008", &Earth::EGM2008)
            .def_readonly_static("EGM96", &Earth::EGM96)
            .def_readonly_static("EGM84", &Earth::EGM84)
            .def_readonly_static("WGS84_EGM96", &Earth::WGS84_EGM96)
            .def_readonly_static("WGS84", &Earth::WGS84)
            .def_readonly_static("spherical", &Earth::Spherical)
            .def_readonly_static("gravity_constant", &Earth::gravityConstant)

            ;

        enum_<Earth::Type>(earth_class, "Type")

            .value("Undefined", Earth::Type::Undefined)
            .value("Spherical", Earth::Type::Spherical)
            .value("WGS84", Earth::Type::WGS84)
            .value("EGM84", Earth::Type::EGM84)
            .value("WGS84_EGM96", Earth::Type::WGS84_EGM96)
            .value("EGM96", Earth::Type::EGM96)
            .value("EGM2008", Earth::Type::EGM2008);
    }

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth");

    // Add __path__ attribute for "earth" submodule
    earth.attr("__path__") = "ostk.physics.environment.gravitational.earth";

    OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth_Manager(earth);
}
