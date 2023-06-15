/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Sun.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Sun(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::fs::Directory;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::environment::gravitational::Sun;

    {
        class_<Sun, Model> sun_class(aModule, "Sun");

        sun_class

            .def(init<const Sun::Type&, const Directory&>(), arg("type"), arg("directory"))

            .def(init<const Sun::Type&>(), arg("type"))

            .def("is_defined", &Sun::isDefined)

            .def("get_parameters", &Sun::getParameters)

            .def("get_type", &Sun::getType)

            .def("get_field_value_at", &Sun::getFieldValueAt, arg("position"), arg("instant"))

            .def_readonly_static("spherical", &Sun::SphericalParameters)

            ;

        enum_<Sun::Type>(sun_class, "SunType")

            .value("Undefined", Sun::Type::Undefined)
            .value("Spherical", Sun::Type::Spherical)

            ;
    }
}
