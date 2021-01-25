////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy.cxx
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/chrono.h>

#include <OpenSpaceToolkitPhysicsPy/Environment.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time.cpp>
#include <OpenSpaceToolkitPhysicsPy/Units.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PYBIND11_MODULE (OpenSpaceToolkitPhysicsPy, m)
{

    // Add optional docstring for package OpenSpaceToolkitPhysicsPy
    m.doc() = "Physical units, time, reference frames, environment modeling for OpenSpaceToolkit" ;

    // Add __path__ attribute to python package
    m.attr("__path__") = "ostk.physics" ;

    // Change attribute __name__ to make OpenSpaceToolkitPhysicsPy invisible in modules path
    m.attr("__name__") = "ostk.phsyics" ;

    // Package version information
    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO ;
    #else
        m.attr("__version__") = "dev" ;
    #endif

    // Add python submodules to OpenSpaceToolkitPhysicsPy
    OpenSpaceToolkitPhysicsPy_Units(m) ;
    OpenSpaceToolkitPhysicsPy_Time(m) ;
    OpenSpaceToolkitPhysicsPy_Coordinate(m) ;
    OpenSpaceToolkitPhysicsPy_Environment(m) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
