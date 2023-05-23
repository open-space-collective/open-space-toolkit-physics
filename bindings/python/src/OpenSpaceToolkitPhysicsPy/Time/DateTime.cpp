/// Apache License 2.0

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

    datetime_class

        .def
        (
            init<Date, Time>(),
            arg("date"),
            arg("time")
        )

        .def
        (
            init<int, int, int, int, int, int, int, int, int>(),
            arg("year"),
            arg("month"),
            arg("day"),
            arg("hour") = DEFAULT_HOUR,
            arg("minute") = DEFAULT_MINUTE,
            arg("second") = DEFAULT_SECOND,
            arg("millisecond") = DEFAULT_MILLISECOND,
            arg("microsecond") = DEFAULT_MICROSECOND,
            arg("nanosecond") = DEFAULT_NANOSECOND
        )

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
        .def_static("julian_date", &DateTime::JulianDate, arg("julian_date"))
        .def_static("modified_julian_date", &DateTime::ModifiedJulianDate, arg("modified_julian_date"))

    ;

    implicitly_convertible<PyDateTime_DateTime, DateTime>() ;

    enum_<DateTime::Format>(datetime_class, "Format")

        .value("Undefined", DateTime::Format::Undefined)
        .value("Standard", DateTime::Format::Standard)
        .value("ISO8601", DateTime::Format::ISO8601)
        .value("STK", DateTime::Format::STK)

    ;

    // https://pybind11.readthedocs.io/en/stable/advanced/functions.html#default-arguments-revisited
    // "default arguments are converted to Python objects right at declaration time"
    // The following parsing function requires DateTime::Format to be binded for proper declaration
    datetime_class.def_static
    (
        "parse",
        &DateTime::Parse,
        arg("string"),
        arg("format") = DateTime::Format::Undefined
    ) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
