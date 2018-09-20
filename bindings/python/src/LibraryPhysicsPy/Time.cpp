////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryPhysicsPy/Time/Interval.cpp>
#include <LibraryPhysicsPy/Time/Time.cpp>
#include <LibraryPhysicsPy/Time/Date.cpp>
#include <LibraryPhysicsPy/Time/DateTime.cpp>
#include <LibraryPhysicsPy/Time/Duration.cpp>
#include <LibraryPhysicsPy/Time/Instant.cpp>
#include <LibraryPhysicsPy/Time/Scale.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Time                       ( )
{
    
    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Physics.Time")))) ;
    
    boost::python::scope().attr("Time") = module ;
    
    boost::python::scope scope = module ;
    
    LibraryPhysicsPy_Time_Scale() ;
    LibraryPhysicsPy_Time_Instant() ;
    LibraryPhysicsPy_Time_Duration() ;
    LibraryPhysicsPy_Time_DateTime() ;
    LibraryPhysicsPy_Time_Date() ;
    LibraryPhysicsPy_Time_Time() ;
    LibraryPhysicsPy_Time_Interval() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////