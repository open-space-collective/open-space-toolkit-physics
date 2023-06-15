/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Model.hpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Model(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::environment::gravitational::Model;

    {
        class_<Model> (aModule, "Model");
    }
}
