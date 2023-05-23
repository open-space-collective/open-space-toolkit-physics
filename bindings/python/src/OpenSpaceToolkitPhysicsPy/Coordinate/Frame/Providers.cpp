/// Apache License 2.0 

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/Dynamic.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/Static.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/IERS.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/IAU.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers (        pybind11::module&     aModule                                     )
{

    // Create "providers" python submodule
    auto providers = aModule.def_submodule("providers") ;

    // Add __path__ attribute for "providers" submodule
    providers.attr("__path__") = "ostk.physics.coordinate.frame.providers" ;

    // Add objects to python "providers" submodules
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_Static(providers) ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_Dynamic(providers) ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IERS(providers) ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IAU(providers) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
