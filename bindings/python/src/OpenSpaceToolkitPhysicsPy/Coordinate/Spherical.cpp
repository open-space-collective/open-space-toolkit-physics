/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Spherical/AER.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Spherical/LLA.cpp>

inline void OpenSpaceToolkitPhysicsPy_Coordinate_Spherical(pybind11::module& aModule)
{
    // Create "spherical" python submodule
    auto spherical = aModule.def_submodule("spherical");

    // Add __path__ attribute for "spherical" submodule
    spherical.attr("__path__") = "ostk.physics.coordinate.spherical";

    // Add objects to python "spherical" submodules
    OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_LLA(spherical);
    OpenSpaceToolkitPhysicsPy_Coordinate_Spherical_AER(spherical);
}
