/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Environment/Objects/Celestial.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies.cpp>

inline void OpenSpaceToolkitPhysicsPy_Environment_Objects(pybind11::module& aModule)
{
    // Create "objects" python submodule
    auto objects = aModule.def_submodule("objects");

    // Add __path__ attribute for "objects" submodule
    objects.attr("__path__") = "ostk.physics.environment.objects";

    // Add objects to python "objects" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Objects_Celestial(objects);
    OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies(objects);
}
