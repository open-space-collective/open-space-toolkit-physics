////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkitPhysicsPy/Coordinate.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Coordinate/Axes.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Transform.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Frame.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Velocity.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Position.cpp>
#include <OpenSpaceToolkitPhysicsPy/Coordinate/Spherical.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Coordinate                      ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Physics.Coordinate")))) ;

    boost::python::scope().attr("Coordinate") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitPhysicsPy_Coordinate_Spherical() ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Position() ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Velocity() ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Frame() ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Transform() ;
    OpenSpaceToolkitPhysicsPy_Coordinate_Axes() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
