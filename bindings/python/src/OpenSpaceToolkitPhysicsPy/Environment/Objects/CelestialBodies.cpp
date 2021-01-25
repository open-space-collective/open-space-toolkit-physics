////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies/Earth.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies/Moon.cpp>
#include <OpenSpaceToolkitPhysicsPy/Environment/Objects/CelestialBodies/Sun.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies   (          pybind11::module&                     aModule       )
{

    // Create "celestial_bodies" python submodule
    auto celestial_bodies = aModule.def_submodule("celestial_bodies") ;

    // Add __path__ attribute for "celestial_bodies" submodule
    celestial_bodies.attr("__path__") = "ostk.physics.environment.objects.celestial_bodies" ;

    // Add objects to python "celestial_bodies" submodules
    OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Earth(celestial_bodies) ;
    OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Moon(celestial_bodies) ;
    OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Sun(celestial_bodies) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
