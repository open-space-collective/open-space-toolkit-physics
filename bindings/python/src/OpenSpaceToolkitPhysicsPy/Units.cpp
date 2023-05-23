/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Units/Derived/Angle.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/Derived.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/ElectricCurrent.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/Time.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/Mass.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/Length.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Units             (           pybind11::module&           aModule                                     )
{

    // Create "units" python submodule
    auto units = aModule.def_submodule("units") ;

    // Add __path__ attribute for "units" submodule
    units.attr("__path__") = "ostk.physics.units" ;

    // Add objects to python "units" submodules
    OpenSpaceToolkitPhysicsPy_Units_Length(units) ;
    OpenSpaceToolkitPhysicsPy_Units_Mass(units) ;
    OpenSpaceToolkitPhysicsPy_Units_Time(units) ;
    OpenSpaceToolkitPhysicsPy_Units_ElectricCurrent(units) ;
    OpenSpaceToolkitPhysicsPy_Units_Derived(units) ;
    OpenSpaceToolkitPhysicsPy_Units_Derived_Angle(units) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
