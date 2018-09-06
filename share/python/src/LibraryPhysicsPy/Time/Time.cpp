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

    using library::core::types::String ;

    using library::physics::time::Time ;

    scope in_Time = class_<Time>("Time", init<int, int, int, int, int, int>())

        .def(init<int, int, int>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Time& aTime) -> std::string { return aTime.toString() ; })

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
        .def("toString", +[] (const Time& aTime) -> String { return aTime.toString() ; })
        .def("toString", +[] (const Time& aTime, const Time::Format& aFormat) -> String { return aTime.toString(aFormat) ; })
        
        .def("Undefined", &Time::Undefined).staticmethod("Undefined")
        .def("Midnight", &Time::Midnight).staticmethod("Midnight")
        .def("Noon", &Time::Noon).staticmethod("Noon")
        .def("Parse", +[] (const String& aString) -> Time { return Time::Parse(aString) ; })
        .def("Parse", +[] (const String& aString, const Time::Format& aFormat) -> Time { return Time::Parse(aString, aFormat) ; })

    ;

    enum_<Time::Format>("Format")

        .value("Undefined", Time::Format::Undefined)
        .value("Standard", Time::Format::Standard)
        .value("ISO8601", Time::Format::ISO8601)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////