/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Environment/Magnetic/Dipole.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Magnetic/Earth.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Magnetic(nanobind::module_& aModule)
{
    // Create "magnetic" python submodule
    auto magnetic = aModule.def_submodule("magnetic");

    // Add objects to python "magnetic" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Dipole(magnetic);
    OpenSpaceToolkitPhysicsPy_Environment_Magnetic_Earth(magnetic);
}
