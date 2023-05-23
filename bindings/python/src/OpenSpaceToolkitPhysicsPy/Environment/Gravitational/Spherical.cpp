/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Spherical(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::units::Derived;
    using ostk::physics::environment::gravitational::Spherical;

    class_<Spherical>(aModule, "Spherical")

        .def(init<const Derived&>(), arg("gravitational_parameter"))

        .def("get_field_value_at", &Spherical::getFieldValueAt, arg("position"), arg("instant"))

        ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
