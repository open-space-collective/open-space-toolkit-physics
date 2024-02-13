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

    class_<Earth, Shared<Earth>> earth_magnetic_class(aModule, "Earth");

    earth_magnetic_class
        .def(init<const Earth::Type&, const Directory&>(), arg("type"), arg("directory"))

        .def(init<const Earth::Type&>(), arg("type"))

        .def("get_type", &Earth::getType)

        .def("is_defined", &Earth::isDefined)

        .def("get_field_value_at", &Earth::getFieldValueAt)

        ;

    enum_<Earth::Type>(earth_magnetic_class, "Type")

        .value("Undefined", Earth::Type::Undefined)
        .value("Dipole", Earth::Type::Dipole)
        .value("EMM2010", Earth::Type::EMM2010)
        .value("EMM2015", Earth::Type::EMM2015)
        .value("EMM2017", Earth::Type::EMM2017)
        .value("IGRF11", Earth::Type::IGRF11)
        .value("IGRF12", Earth::Type::IGRF12)
        .value("WMM2010", Earth::Type::WMM2010)
        .value("WMM2015", Earth::Type::WMM2015)

        ;

    // Create "earth" python submodule
    auto earth = aModule.def_submodule("earth");


    OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Earth_Manager(earth);
}
