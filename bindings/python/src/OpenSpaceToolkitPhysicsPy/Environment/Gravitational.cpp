/// Apache License 2.0

#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Earth.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Moon.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Sun.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Gravitational/Spherical.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Gravitational (        pybind11::module&      aModule                                     )
{

    // Create "gravitational" python submodule
    auto gravitational = aModule.def_submodule("gravitational") ;

    // Add __path__ attribute for "gravitational" submodule
    gravitational.attr("__path__") = "ostk.physics.environment.gravitational" ;

    // Add objects to python "gravitational" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Spherical(gravitational) ;
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Sun(gravitational) ;
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Moon(gravitational) ;
    OpenSpaceToolkitPhysicsPy_Environment_Gravitational_Earth(gravitational) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
