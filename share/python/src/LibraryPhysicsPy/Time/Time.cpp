////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time/Time.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Time.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Time_Time                  ( )
{

    using namespace boost::python ;

    using library::physics::time::Time ;

    scope in_Time = class_<Time>("Time", init<int, int, int, int, int, int>())

        .def(init<int, int, int>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))

        .def("isDefined", &Time::isDefined)
        
        .def("getHour", &Time::getHour)
        .def("getMinute", &Time::getMinute)
        .def("getSecond", &Time::getSecond)
        .def("getMillisecond", &Time::getMillisecond)
        .def("getMicrosecond", &Time::getMicrosecond)
        .def("getNanosecond", &Time::getNanosecond)
        .def("getFloatingSeconds", &Time::getFloatingSeconds)
        .def("toString", &Time::toString)
        .def("setHour", &Time::setHour)
        .def("setMinute", &Time::setMinute)
        .def("setSecond", &Time::setSecond)
        .def("setMillisecond", &Time::setMillisecond)
        .def("setMicrosecond", &Time::setMicrosecond)
        .def("setNanosecond", &Time::setNanosecond)
        
        .def("Undefined", &Time::Undefined).staticmethod("Undefined")
        .def("Midnight", &Time::Midnight).staticmethod("Midnight")
        .def("Noon", &Time::Noon).staticmethod("Noon")
        .def("Parse", &Time::Parse).staticmethod("Parse")

    ;

    enum_<Time::Format>("Format")

        .value("Undefined", Time::Format::Undefined)
        .value("Standard", Time::Format::Standard)
        .value("ISO8601", Time::Format::ISO8601)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////