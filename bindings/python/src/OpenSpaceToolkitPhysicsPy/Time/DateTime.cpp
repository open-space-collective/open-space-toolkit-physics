////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Time/DateTime.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <datetime.h>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Time_DateTime     (            pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::String ;

    using ostk::physics::time::DateTime ;
    using ostk::physics::time::Date ;
    using ostk::physics::time::Time ;

    class_<DateTime> datetime_class(aModule, "DateTime") ;

    datetime_class.def(init<Date, Time>())

        .def(init<int, int, int, int, int, int, int, int, int>())
        .def(init<int, int, int, int, int, int>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<DateTime>))
        .def("__repr__", +[] (const DateTime& aDateTime) -> std::string { return aDateTime.toString() ; })

        .def("is_defined", &DateTime::isDefined)

        .def("get_date", &DateTime::getDate)
        .def("get_time", &DateTime::getTime)
        .def("get_julian_date", &DateTime::getJulianDate)
        .def("get_modified_julian_date", &DateTime::getModifiedJulianDate)
        .def("to_string", +[] (const DateTime& aDateTime) -> String { return aDateTime.toString() ; })
        .def("to_string", +[] (const DateTime& aDateTime, const DateTime::Format& aFormat) -> String { return aDateTime.toString(aFormat) ; })

        .def_static("undefined", &DateTime::Undefined)
        .def_static("J2000", &DateTime::J2000)
        .def_static("GPS_epoch", &DateTime::GPSEpoch)
        .def_static("unix_epoch", &DateTime::UnixEpoch)
        .def_static("modified_julian_date_epoch", &DateTime::ModifiedJulianDateEpoch)
        .def_static("julian_date", &DateTime::JulianDate)
        .def_static("modified_julian_date", &DateTime::ModifiedJulianDate)
        .def("parse", +[] (const String& aString) -> DateTime { return DateTime::Parse(aString) ; })
        .def("parse", +[] (const String& aString, const DateTime::Format& aFormat) -> DateTime { return DateTime::Parse(aString, aFormat) ; })

    ;

    implicitly_convertible<PyDateTime_DateTime, DateTime>() ;

    enum_<DateTime::Format>(datetime_class, "Format")

        .value("Undefined", DateTime::Format::Undefined)
        .value("Standard", DateTime::Format::Standard)
        .value("ISO8601", DateTime::Format::ISO8601)
        .value("STK", DateTime::Format::STK)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
