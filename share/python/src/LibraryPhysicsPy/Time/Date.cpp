////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time/Date.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Date.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Time_Date                  ( )
{

    using namespace boost::python ;

    using library::core::types::String ;

    using library::physics::time::Date ;

    scope in_Date = class_<Date>("Date", init<int, int, int>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        
        .def("__repr__", +[] (const Date& aDate) -> std::string { return aDate.toString() ; })

        .def("isDefined", &Date::isDefined)
        
        .def("getYear", &Date::getYear)
        .def("getMonth", &Date::getMonth)
        .def("getDay", &Date::getDay)
        .def("toString", &Date::toString)
        .def("setYear", &Date::setYear)
        .def("setMonth", &Date::setMonth)
        .def("setDay", &Date::setDay)
        .def("toString", +[] (const Date& aDate) -> String { return aDate.toString() ; })
        .def("toString", +[] (const Date& aDate, const Date::Format& aFormat) -> String { return aDate.toString(aFormat) ; })
        
        .def("Undefined", &Date::Undefined).staticmethod("Undefined")
        .def("J2000", &Date::J2000).staticmethod("J2000")
        .def("GPSEpoch", &Date::GPSEpoch).staticmethod("GPSEpoch")
        .def("UnixEpoch", &Date::UnixEpoch).staticmethod("UnixEpoch")
        .def("ModifiedJulianDateEpoch", &Date::ModifiedJulianDateEpoch).staticmethod("ModifiedJulianDateEpoch")
        .def("Parse", +[] (const String& aString) -> Date { return Date::Parse(aString) ; })
        .def("Parse", +[] (const String& aString, const Date::Format& aFormat) -> Date { return Date::Parse(aString, aFormat) ; })

    ;

    enum_<Date::Format>("Format")

        .value("Undefined", Date::Format::Undefined)
        .value("Standard", Date::Format::Standard)
        .value("STK", Date::Format::STK)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////