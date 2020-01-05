////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Time/Date.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Time_Date                  ( )
{

    using namespace boost::python ;

    using ostk::core::types::String ;

    using ostk::physics::time::Date ;

    scope in_Date = class_<Date>("Date", init<int, int, int>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Date& aDate) -> std::string { return aDate.toString() ; })

        .def("is_defined", &Date::isDefined)

        .def("get_year", &Date::getYear)
        .def("get_month", &Date::getMonth)
        .def("get_day", &Date::getDay)
        .def("to_string", &Date::toString)
        .def("to_string", +[] (const Date& aDate) -> String { return aDate.toString() ; })
        .def("to_string", +[] (const Date& aDate, const Date::Format& aFormat) -> String { return aDate.toString(aFormat) ; })
        .def("set_year", &Date::setYear)
        .def("set_month", &Date::setMonth)
        .def("set_day", &Date::setDay)

        .def("undefined", &Date::Undefined).staticmethod("undefined")
        .def("J2000", &Date::J2000).staticmethod("J2000")
        .def("GPS_epoch", &Date::GPSEpoch).staticmethod("GPS_epoch")
        .def("unix_epoch", &Date::UnixEpoch).staticmethod("unix_epoch")
        .def("modified_julian_date_epoch", &Date::ModifiedJulianDateEpoch).staticmethod("modified_julian_date_epoch")
        .def("parse", +[] (const String& aString) -> Date { return Date::Parse(aString) ; })
        .def("parse", +[] (const String& aString, const Date::Format& aFormat) -> Date { return Date::Parse(aString, aFormat) ; })

    ;

    enum_<Date::Format>("Format")

        .value("Undefined", Date::Format::Undefined)
        .value("Standard", Date::Format::Standard)
        .value("STK", Date::Format::STK)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
