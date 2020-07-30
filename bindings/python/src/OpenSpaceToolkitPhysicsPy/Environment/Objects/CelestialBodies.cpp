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

inline void                     OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.environment.objects.celestial_bodies")))) ;

    boost::python::scope().attr("celestial_bodies") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Earth() ;
    OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Moon() ;
    OpenSpaceToolkitPhysicsPy_Environment_Objects_CelestialBodies_Sun() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
