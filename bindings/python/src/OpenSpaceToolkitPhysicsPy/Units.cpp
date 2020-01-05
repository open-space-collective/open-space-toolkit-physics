////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Units.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Units/Derived/Angle.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/Derived.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/ElectricCurrent.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/Time.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units/Length.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Units                      ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.physics.units")))) ;

    boost::python::scope().attr("units") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitPhysicsPy_Units_Length() ;
    OpenSpaceToolkitPhysicsPy_Units_Time() ;
    OpenSpaceToolkitPhysicsPy_Units_ElectricCurrent() ;
    OpenSpaceToolkitPhysicsPy_Units_Derived() ;
    OpenSpaceToolkitPhysicsPy_Units_Derived_Angle() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
