////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time/Duration.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Duration.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Time_Duration               ( )
{

    using namespace boost::python ;

    using library::physics::time::Duration ;

    scope in_Duration = class_<Duration>("Duration", init<int>())

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + self)
        .def(self - self)
        .def(self * other<double>())
        .def(self / other<double>())

        .def(self += self)
        .def(self -= self)
        .def(self *= other<double>())
        .def(self /= other<double>())

        .def(self_ns::str(self_ns::self))

        .def("isDefined", &Duration::isDefined)
        .def("isZero", &Duration::isZero)
        .def("isPositive", &Duration::isPositive)
        .def("isStrictlyPositive", &Duration::isStrictlyPositive)

        .def("getNanoseconds", &Duration::getNanoseconds)
        .def("getMicroseconds", &Duration::getMicroseconds)
        .def("getMilliseconds", &Duration::getMilliseconds)
        .def("getSeconds", &Duration::getSeconds)
        .def("getMinutes", &Duration::getMinutes)
        .def("getHours", &Duration::getHours)
        .def("getDays", &Duration::getDays)
        .def("getWeeks", &Duration::getWeeks)
        .def("inNanoseconds", &Duration::inNanoseconds)
        .def("inMicroseconds", &Duration::inMicroseconds)
        .def("inMilliseconds", &Duration::inMilliseconds)
        .def("inSeconds", &Duration::inSeconds)
        .def("inMinutes", &Duration::inMinutes)
        .def("inHours", &Duration::inHours)
        .def("inDays", &Duration::inDays)
        .def("inWeeks", &Duration::inWeeks)
        .def("in", &Duration::in)
        .def("getAbsolute", &Duration::getAbsolute)
        .def("toString", &Duration::toString)

        .def("Undefined", &Duration::Undefined).staticmethod("Undefined")
        .def("Zero", &Duration::Zero).staticmethod("Zero")
        .def("Nanoseconds", &Duration::Nanoseconds).staticmethod("Nanoseconds")
        .def("Microseconds", &Duration::Microseconds).staticmethod("Microseconds")
        .def("Milliseconds", &Duration::Milliseconds).staticmethod("Milliseconds")
        .def("Seconds", &Duration::Seconds).staticmethod("Seconds")
        .def("Minutes", &Duration::Minutes).staticmethod("Minutes")
        .def("Hours", &Duration::Hours).staticmethod("Hours")
        .def("Days", &Duration::Days).staticmethod("Days")
        .def("Weeks", &Duration::Weeks).staticmethod("Weeks")
        .def("Between", &Duration::Between).staticmethod("Between")
        .def("Parse", &Duration::Parse).staticmethod("Parse")

    ;

    enum_<Duration::Format>("Format")

        .value("Undefined", Duration::Format::Undefined)
        .value("Standard", Duration::Format::Standard)
        .value("ISO8601", Duration::Format::ISO8601)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////