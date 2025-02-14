/// Apache License 2.0

#include <datetime.h>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_DateTime(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::String;

    using ostk::physics::time::Date;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Time;

    class_<DateTime> datetime_class(
        aModule,
        "DateTime",
        R"doc(
            Date-time.
        )doc"
    );

    datetime_class

        .def(
            init<Date, Time>(),
            arg("date"),
            arg("time"),
            R"doc(
                Constructor.

                Args:
                    date (Date): A date
                    time (Time): A time
            )doc"
        )

        .def(
            init<int, int, int, int, int, int, int, int, int>(),
            arg("year"),
            arg("month"),
            arg("day"),
            arg("hour") = DEFAULT_HOUR,
            arg("minute") = DEFAULT_MINUTE,
            arg("second") = DEFAULT_SECOND,
            arg("millisecond") = DEFAULT_MILLISECOND,
            arg("microsecond") = DEFAULT_MICROSECOND,
            arg("nanosecond") = DEFAULT_NANOSECOND,
            R"doc(
                Constructor.

                Args:
                    year (int): Year
                    month (int): Month
                    day (int): Day
                    hour (int): Hour
                    minute (int): Minute
                    second (int): Second
                    millisecond (int): Millisecond
                    microsecond (int): Microsecond
                    nanosecond (int): Nanosecond
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<DateTime>))
        .def(
            "__repr__",
            +[](const DateTime& aDateTime) -> std::string
            {
                return aDateTime.toString();
            }
        )

        .def(
            "is_defined",
            &DateTime::isDefined,
            R"doc(
                Check if the date-time is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def(
            "get_date",
            &DateTime::getDate,
            R"doc(
                Get date.

                Returns:
                    Date: Date.
            )doc"
        )
        .def(
            "get_time",
            &DateTime::getTime,
            R"doc(
                Get time.

                Returns:
                    Time: Time.
            )doc"
        )
        .def(
            "get_julian_date",
            &DateTime::getJulianDate,
            R"doc(
                Get Julian date.

                Returns:
                    float: Julian date.
            )doc"
        )
        .def(
            "get_modified_julian_date",
            &DateTime::getModifiedJulianDate,
            R"doc(
                Get Modified Julian date.

                Returns:
                    float: Modified Julian date.
            )doc"
        )
        .def(
            "to_string",
            +[](const DateTime& aDateTime) -> String
            {
                return aDateTime.toString();
            }
        )
        .def(
            "to_string",
            +[](const DateTime& aDateTime, const DateTime::Format& aFormat) -> String
            {
                return aDateTime.toString(aFormat);
            }
        )

        .def_static(
            "undefined",
            &DateTime::Undefined,
            R"doc(
                Create an undefined date-time.

                Returns:
                    DateTime: Undefined date-time.
            )doc"
        )
        .def_static(
            "J2000",
            &DateTime::J2000,
            R"doc(
                J2000 epoch (2000-01-01 12:00:00.000.000.00).

                Returns:
                    DateTime: J2000 date-time.
            )doc"
        )
        .def_static(
            "GPS_epoch",
            &DateTime::GPSEpoch,
            R"doc(
                GPS epoch (1980-01-06 00:00:00.000.000.000).

                Returns:
                    DateTime: Date-time at GPS epoch.
            )doc"
        )
        .def_static(
            "unix_epoch",
            &DateTime::UnixEpoch,
            R"doc(
                Unix epoch (1970-01-01 00:00:00.000.000.000).
                
                Returns:
                    DateTime: Date-time at Unix epoch.
                    
            )doc"
        )
        .def_static(
            "modified_julian_date_epoch",
            &DateTime::ModifiedJulianDateEpoch,
            R"doc(
                Modified Julian Date epoch (1858-11-17 00:00:00.000.000.000).

                Returns:
                    Date-time: Date-time at Modified Julian Date epoch.
                )doc"
        )
        .def_static(
            "julian_date",
            &DateTime::JulianDate,
            arg("julian_date"),
            R"doc(
                Date-time from Julian Date.

                Args:
                    julian_date (float): A Julian Date.

                Returns:
                    DateTime: Date-time.
            )doc"
        )
        .def_static(
            "modified_julian_date",
            &DateTime::ModifiedJulianDate,
            arg("modified_julian_date"),
            R"doc(
                Date-time from Modified Julian Date.

                Args:
                    modified_julian_date (float): A Modified Julian Date.

                Returns:
                    DateTime: Date-time.
            )doc"
        )

        ;

    implicitly_convertible<PyDateTime_DateTime, DateTime>();

    enum_<DateTime::Format>(datetime_class, "Format")

        .value(
            "Undefined",
            DateTime::Format::Undefined,
            R"doc(
                Undefined format.
            )doc"
        )
        .value(
            "Standard",
            DateTime::Format::Standard,
            R"doc(
                Standard format (YYYY-MM-DD hh:mm:ss.sss.sss.sss).
            )doc"
        )
        .value(
            "ISO8601",
            DateTime::Format::ISO8601,
            R"doc(
                ISO 8601 format (YYYY-MM-DDThh:mm:ss.ssssss).
            )doc"
        )
        .value(
            "STK",
            DateTime::Format::STK,
            R"doc(
                STK format (d Mon YYYY hh:mm:ss.ssssss).
            )doc"
        )

        ;

    // https://pybind11.readthedocs.io/en/stable/advanced/functions.html#default-arguments-revisited
    // "default arguments are converted to Python objects right at declaration time"
    // The following parsing function requires DateTime::Format to be binded for proper declaration
    datetime_class.def_static("parse", &DateTime::Parse, arg("string"), arg("format") = DateTime::Format::Undefined);
}
