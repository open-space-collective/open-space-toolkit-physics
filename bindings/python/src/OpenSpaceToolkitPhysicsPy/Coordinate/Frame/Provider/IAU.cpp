/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame/Provider/IAU/Theory.cpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IAU(pybind11::module& aModule)
{
    // Create "IAU" python submodule
    auto IAU = aModule.def_submodule("iau");

    // Add __path__ attribute for "IAU" submodule
    IAU.attr("__path__") = "ostk.physics.coordinate.frame.provider.iau";

    // Add objects to python "IAU" submodules
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame_Provider_IAU_Theory(IAU);
}
