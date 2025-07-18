/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Environment/Utility/Eclipse.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Utility(pybind11::module& aModule)
{
    using namespace pybind11;

    // Create "utility" python submodule
    auto utility = aModule.def_submodule("utility");

    // Add elements to utility
    OpenSpaceToolkitPhysicsPy_Environment_Utility_Eclipse(utility);
}
