/// Apache License 2.0 

#include <OpenSpaceToolkit/Physics/Time/Time.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Time_Time         (            pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::String ;

    using ostk::physics::time::Time ;

    class_<Time> time_class(aModule, "Time") ;

    time_class.def(init<int, int, int, int, int, int>())

        .def(init<int, int, int>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Time>))
        .def("__repr__", +[] (const Time& aTime) -> std::string { return aTime.toString() ; })

        .def("is_defined", &Time::isDefined)

        .def("get_hour", &Time::getHour)
        .def("get_minute", &Time::getMinute)
        .def("get_second", &Time::getSecond)
        .def("get_millisecond", &Time::getMillisecond)
        .def("get_microsecond", &Time::getMicrosecond)
        .def("get_nanosecond", &Time::getNanosecond)
        .def("get_floating_seconds", &Time::getFloatingSeconds)
        .def("to_string", &Time::toString)
        .def("set_hour", &Time::setHour)
        .def("set_minute", &Time::setMinute)
        .def("set_second", &Time::setSecond)
        .def("set_millisecond", &Time::setMillisecond)
        .def("set_microsecond", &Time::setMicrosecond)
        .def("set_nanosecond", &Time::setNanosecond)
        .def("to_string", +[] (const Time& aTime) -> String { return aTime.toString() ; })
        .def("to_string", +[] (const Time& aTime, const Time::Format& aFormat) -> String { return aTime.toString(aFormat) ; })

        .def_static("undefined", &Time::Undefined)
        .def_static("midnight", &Time::Midnight)
        .def_static("noon", &Time::Noon)

    ;

    enum_<Time::Format>(time_class, "Format")

        .value("Undefined", Time::Format::Undefined)
        .value("Standard", Time::Format::Standard)
        .value("ISO8601", Time::Format::ISO8601)

    ;

    time_class.def_static("parse", &Time::Parse, "aString"_a, "aFormat"_a=Time::Format::Undefined) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
