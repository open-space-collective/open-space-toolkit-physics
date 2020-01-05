////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkitPhysicsPy/Time.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Time/Interval.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time/Time.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time/Date.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time/DateTime.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time/Duration.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time/Instant.cpp>
#include <OpenSpaceToolkitPhysicsPy/Time/Scale.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Time                       ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("Library.Physics.Time")))) ;

    boost::python::scope().attr("Time") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitPhysicsPy_Time_Scale() ;
    OpenSpaceToolkitPhysicsPy_Time_Instant() ;
    OpenSpaceToolkitPhysicsPy_Time_Duration() ;
    OpenSpaceToolkitPhysicsPy_Time_DateTime() ;
    OpenSpaceToolkitPhysicsPy_Time_Date() ;
    OpenSpaceToolkitPhysicsPy_Time_Time() ;
    OpenSpaceToolkitPhysicsPy_Time_Interval() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
