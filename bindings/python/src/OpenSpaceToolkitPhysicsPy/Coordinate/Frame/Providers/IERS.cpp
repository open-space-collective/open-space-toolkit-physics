/// Apache License 2.0 

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/IERS/Manager.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/IERS/BulletinA.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Providers/IERS/Finals2000A.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IERS ( pybind11::module&       aModule                                     )
{

    // Create "iers" python submodule
    auto iers = aModule.def_submodule("iers") ;

    // Add __path__ attribute for "iers" submodule
    iers.attr("__path__") = "ostk.physics.coordinate.frame.providers.iers" ;

    // Add objects to python "iers" submodules
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IERS_Manager(iers) ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IERS_BulletinA(iers) ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Providers_IERS_Finals2000A(iers) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
