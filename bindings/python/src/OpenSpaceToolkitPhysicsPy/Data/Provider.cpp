/// Apache License 2.0

#include <nanobind/nanobind.h>

#include <OpenSpaceToolkitPhysicsPy/Data/Provider/Nadir.cpp>

inline void OpenSpaceToolkitPhysicsPy_Data_Provider(nanobind::module_& aModule)
{
    using namespace nanobind;

    // Create "provider" python submodule
    auto provider = aModule.def_submodule("provider");

    // Add objects to python "provider" submodules
    OpenSpaceToolkitPhysicsPy_Data_Provider_Nadir(provider);
}
