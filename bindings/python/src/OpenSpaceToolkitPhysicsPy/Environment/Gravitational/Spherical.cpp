/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Spherical(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::gravitational::Model;
    using ostk::physics::environment::gravitational::Spherical;

    class_<Spherical>(aModule, "Spherical")

        .def(init<const Model::Parameters&>(), arg("gravitational_parameters"))

        .def("get_field_value_at", &Spherical::getFieldValueAt, arg("position"), arg("instant"))

        .def("is_defined", &Spherical::isDefined)

        .def("get_parameters", &Spherical::getParameters)

        ;
}
