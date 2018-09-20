////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Coordinate.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryPhysicsPy/Coordinate/Axes.cpp>
#include <LibraryPhysicsPy/Coordinate/Transform.cpp>
#include <LibraryPhysicsPy/Coordinate/Frame.cpp>
#include <LibraryPhysicsPy/Coordinate/Velocity.cpp>
#include <LibraryPhysicsPy/Coordinate/Position.cpp>
#include <LibraryPhysicsPy/Coordinate/Spherical.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Coordinate                      ( )
{
    
    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Physics.Coordinate")))) ;
    
    boost::python::scope().attr("Coordinate") = module ;
    
    boost::python::scope scope = module ;
    
    LibraryPhysicsPy_Coordinate_Spherical() ;
    LibraryPhysicsPy_Coordinate_Position() ;
    LibraryPhysicsPy_Coordinate_Velocity() ;
    LibraryPhysicsPy_Coordinate_Frame() ;
    LibraryPhysicsPy_Coordinate_Transform() ;
    LibraryPhysicsPy_Coordinate_Axes() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////