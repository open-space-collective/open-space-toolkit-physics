/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Unit/Derived.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Derived/Angle.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/ElectricCurrent.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Length.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Mass.cpp>
#include <OpenSpaceToolkitPhysicsPy/Unit/Time.cpp>

inline void OpenSpaceToolkitPhysicsPy_Unit(pybind11::module& aModule)
{
    // Create "unit" python submodule
    auto unit = aModule.def_submodule("unit");


    // Add objects to python "unit" submodules
    OpenSpaceToolkitPhysicsPy_Unit_Length(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Mass(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Time(unit);
    OpenSpaceToolkitPhysicsPy_Unit_ElectricCurrent(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Derived(unit);
    OpenSpaceToolkitPhysicsPy_Unit_Derived_Angle(unit);
}
