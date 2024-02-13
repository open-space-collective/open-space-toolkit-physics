/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/IERS/BulletinA.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/IERS/Finals2000A.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/IERS/Manager.cpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS(pybind11::module& aModule)
{
    // Create "iers" python submodule
    auto iers = aModule.def_submodule("iers");


    // Add objects to python "iers" submodules
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_Manager(iers);
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_BulletinA(iers);
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IERS_Finals2000A(iers);
}
