/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Model(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::physics::units::Derived;
    using ostk::physics::units::Length;
    using ostk::physics::environment::gravitational::Model;

    {
        class_<Model, Shared<Model>>(aModule, "Model").def("get_parameters", &Model::getParameters);
    }

    {
        class_<Model::Parameters>(aModule, "GravitationalParameters")

            .def(
                init<const Derived&, const Length&, const Real&, const Real&, const Real&>(),
                arg("gravitational_parameter"),
                arg("equatorial_radius"),
                arg("flattening"),
                arg("C20"),
                arg("C40")
            )

            .def(self == self)
            .def(self != self)

            .def("__str__", &(shiftToString<Model::Parameters>))
            .def("__repr__", &(shiftToString<Model::Parameters>))

            .def("is_defined", &Model::Parameters::isDefined)

            .def_readwrite("gravitational_parameter", &Model::Parameters::gravitationalParameter_)
            .def_readwrite("equatorial_radius", &Model::Parameters::equatorialRadius_)
            .def_readwrite("flattening", &Model::Parameters::flattening_)
            .def_readwrite("J2", &Model::Parameters::J2_)
            .def_readwrite("J4", &Model::Parameters::J4_)
            .def_readwrite("C20", &Model::Parameters::C20_)
            .def_readwrite("C40", &Model::Parameters::C40_)

            .def_static("undefined", &Model::Parameters::Undefined)

            ;
    }
}
