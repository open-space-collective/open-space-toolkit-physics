/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Environment/Atmospheric/Earth.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Atmospheric(pybind11::module& aModule)
{
    // Create "atmospheric" python submodule
    auto atmospheric = aModule.def_submodule("atmospheric");

    // Add __path__ attribute for "atmospheric" submodule
    atmospheric.attr("__path__") = "ostk.physics.environment.atmospheric";

    // Add objects to python "atmospheric" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Atmospheric_Earth(atmospheric);
}