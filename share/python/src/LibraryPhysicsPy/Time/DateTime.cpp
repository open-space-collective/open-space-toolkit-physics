////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time/DateTime.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/DateTime.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Time_DateTime              ( )
{

    using namespace boost::python ;

    using library::core::types::String ;

    using library::physics::time::DateTime ;
    using library::physics::time::Date ;
    using library::physics::time::Time ;

    scope in_DateTime = class_<DateTime>("DateTime", init<Date, Time>())

        .def(init<int, int, int, int, int, int, int, int, int>())
        .def(init<int, int, int, int, int, int>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        
        .def("__repr__", +[] (const DateTime& aDateTime) -> std::string { return aDateTime.toString() ; })

        .def("isDefined", &DateTime::isDefined)

        .def("getDate", +[] (const DateTime& aDateTime) -> Date { return aDateTime.accessDate() ; })
        .def("getTime", +[] (const DateTime& aDateTime) -> Time { return aDateTime.accessTime() ; })
        .def("getJulianDate", &DateTime::getJulianDate)
        .def("getModifiedJulianDate", &DateTime::getModifiedJulianDate)
        .def("toString", +[] (const DateTime& aDateTime) -> String { return aDateTime.toString() ; })
        .def("toString", +[] (const DateTime& aDateTime, const DateTime::Format& aFormat) -> String { return aDateTime.toString(aFormat) ; })

        .def("Undefined", &DateTime::Undefined).staticmethod("Undefined")
        .def("J2000", &DateTime::J2000).staticmethod("J2000")
        .def("GPSEpoch", &DateTime::GPSEpoch).staticmethod("GPSEpoch")
        .def("UnixEpoch", &DateTime::UnixEpoch).staticmethod("UnixEpoch")
        .def("ModifiedJulianDateEpoch", &DateTime::ModifiedJulianDateEpoch).staticmethod("ModifiedJulianDateEpoch")
        .def("JulianDate", &DateTime::JulianDate).staticmethod("JulianDate")
        .def("ModifiedJulianDate", &DateTime::ModifiedJulianDate).staticmethod("ModifiedJulianDate")
        .def("Parse", +[] (const String& aString) -> DateTime { return DateTime::Parse(aString) ; })
        .def("Parse", +[] (const String& aString, const DateTime::Format& aFormat) -> DateTime { return DateTime::Parse(aString, aFormat) ; })

    ;

    enum_<DateTime::Format>("Format")

        .value("Undefined", DateTime::Format::Undefined)
        .value("Standard", DateTime::Format::Standard)
        .value("ISO8601", DateTime::Format::ISO8601)
        .value("STK", DateTime::Format::STK)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////