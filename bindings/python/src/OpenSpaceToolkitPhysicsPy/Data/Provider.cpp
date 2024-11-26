/// Apache License 2.0

#include <pybind11/pybind11.h>

#include <OpenSpaceToolkitPhysicsPy/Data/Provider/Nadir.cpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Provider(pybind11::module& aModule)
{
    using namespace pybind11;

    // Create "provider" python submodule
    auto provider = aModule.def_submodule("provider");

    // Add objects to python "provider" submodules
    OpenSpaceToolkitPhysicsPy_Data_Provider_Nadir(provider);
}
