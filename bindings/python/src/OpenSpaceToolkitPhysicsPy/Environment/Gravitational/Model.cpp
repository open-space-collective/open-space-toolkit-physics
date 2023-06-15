/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Model(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Real;
    using ostk::core::types::Shared;

    using ostk::physics::units::Derived;
    using ostk::physics::units::Length;
    using ostk::physics::environment::gravitational::Model;

    {
        class_<Model, Shared<Model>> (aModule, "Model");
    }

    {
    class_<Model::Parameters>(aModule, "GravitationalParameters")

        .def(
            init<const Derived&, const Length&, const Real&, const Real&, const Real&>(),
            arg("gravitational_parameter"),
            arg("equatorial_radius"),
            arg("flattening"),
            arg("J2"),
            arg("J4")
        )

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
