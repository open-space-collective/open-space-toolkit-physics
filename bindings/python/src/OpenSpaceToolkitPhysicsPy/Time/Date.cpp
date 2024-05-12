/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Date(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::String;

    using ostk::physics::time::Date;

    class_<Date> date_class(
        aModule,
        "Date",
        R"doc(
            Date as year, month and day.
        )doc"
    );

    date_class
        .def(init<int, int, int>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Date>))
        .def(
            "__repr__",
            +[](const Date& aDate) -> std::string
            {
                return aDate.toString();
            }
        )

        .def(
            "is_defined",
            &Date::isDefined,
            R"doc(
                Check if the date is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )

        .def(
            "get_year",
            &Date::getYear,
            R"doc(
                Get year (1400 - 9999).

                Returns:
                    int: Year.
            )doc"
        )
        .def(
            "get_month",
            &Date::getMonth,
            R"doc(
                Get month (1 - 12).

                Returns:
                    int: Month.
            )doc"
        )
        .def(
            "get_day",
            &Date::getDay,
            R"doc(
                Get day (1 - 31).

                Returns:
                    int: Day.
            )doc"
        )
        .def(
            "to_string",
            &Date::toString,
            R"doc(
                Get string representation of date.

                Args:
                    format (Date.Format): Date format.

                Returns:
                    str: String representation of date.
            )doc"
        )
        .def(
            "to_string",
            +[](const Date& aDate) -> String
            {
                return aDate.toString();
            }
        )
        .def(
            "to_string",
            +[](const Date& aDate, const Date::Format& aFormat) -> String
            {
                return aDate.toString(aFormat);
            }
        )
        .def(
            "set_year",
            &Date::setYear,
            R"doc(
                Set year.

                Args:
                    year (int): Year (1400 - 9999).
            )doc"
        )
        .def(
            "set_month",
            &Date::setMonth,
            R"doc(
                Set month.

                Args:
                    month (int): Month (1 - 12).
            )doc"
        )
        .def(
            "set_day",
            &Date::setDay,
            R"doc(
                Set day.

                Args:
                    day (int): Day (1 - 31).
            )doc"
        )

        .def_static(
            "undefined",
            &Date::Undefined,
            R"doc(
                Create an undefined date.

                Returns:
                    Date: Undefined date.
            )doc"
        )
        .def_static(
            "J2000",
            &Date::J2000,
            R"doc(
                J2000 epoch (2000-01-01).

                .. seealso:: https://en.wikipedia.org/wiki/Epoch_(astronomy)#Julian_years_and_J2000

                Returns:
                    Date: J2000 epoch.
            )doc"
        )
        .def_static(
            "GPS_epoch",
            &Date::GPSEpoch,
            R"doc(
                GPS epoch (1980-01-06).

                .. seealso:: http://tycho.usno.navy.mil/gpstt.html

                Returns:
                    Date: GPS epoch.
            )doc"
        )
        .def_static(
            "unix_epoch",
            &Date::UnixEpoch,
            R"doc(
                Unix epoch (1970-01-01).

                .. seealso:: https://en.wikipedia.org/wiki/Unix_time

                Returns:
                    Date: Unix epoch.
            )doc"
        )
        .def_static(
            "modified_julian_date_epoch",
            &Date::ModifiedJulianDateEpoch,
            R"doc(
                Modified julian dates epoch (1858-11-17).

                .. seealso:: https://en.wikipedia.org/wiki/Julian_day

                Returns:
                    Date: Modified Julian epoch.
            )doc"

        );

    enum_<Date::Format>(date_class, "Format", pybind11::module_local())

        .value(
            "Undefined",
            Date::Format::Undefined,
            R"doc(
                Undefined date format.
            )doc"
        )
        .value(
            "Standard",
            Date::Format::Standard,
            R"doc(
                Standard date format (YYYY-MM-DD).
            )doc"
        )
        .value(
            "STK",
            Date::Format::STK,
            R"doc(
                STK date format (d Mon YYYY).
            )doc"
        )

        ;

    date_class.def_static("parse", &Date::Parse, "aString"_a, "aFormat"_a = Date::Format::Undefined);
}
