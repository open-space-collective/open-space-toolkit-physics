/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Instant(pybind11::module &aModule)
{
    using namespace pybind11;

    using ostk::core::type::String;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Scale;

    class_<Instant>(
        aModule,
        "Instant",
        R"doc(
            Point in time.
        )doc"
    )

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        // Duration() is private in this context
        // .def(self + Duration())
        // .def(self - Duration())
        // .def(self += Duration())
        // .def(self -= Duration())
        .def(self - self)
        .def(
            "__add__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant + aDuration;
            },
            is_operator()
        )
        .def(
            "__sub__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant - aDuration;
            },
            is_operator()
        )
        .def(
            "__iadd__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant + aDuration;
            },
            is_operator()
        )
        .def(
            "__isub__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant - aDuration;
            },
            is_operator()
        )

        .def("__str__", &(shiftToString<Instant>))
        .def(
            "__repr__",
            +[](const Instant &anInstant) -> std::string
            {
                return anInstant.toString();
            }
        )

        .def(
            "is_defined",
            &Instant::isDefined,
            R"doc(
                Check if the instant is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def(
            "is_post_epoch",
            &Instant::isPostEpoch,
            R"doc(
                Check if the instant is post-epoch (J2000).

                Returns:
                    bool: True if post-epoch.
            )doc"
        )
        .def(
            "is_near",
            &Instant::isNear,
            R"doc(
                Check if instant is near another instant

                Return:
                    bool: True if near
            )doc"
        )

        .def(
            "get_date_time",
            &Instant::getDateTime,
            R"doc(
                Get date-time.

                Returns:
                    DateTime: Date-time.
            )doc"
        )
        .def(
            "get_julian_date",
            &Instant::getJulianDate,
            R"doc(
                Get Julian date.

                Returns:
                    float: Julian date.
            )doc"
        )
        .def(
            "get_modified_julian_date",
            &Instant::getModifiedJulianDate,
            R"doc(
                Get Modified Julian date.

                Returns:
                    float: Modified Julian date.
            )doc"
        )
        .def(
            "get_leap_second_count",
            &Instant::getLeapSecondCount,
            R"doc(
                Get leap second count.

                Returns:
                    int: Leap second count.
            )doc"
        )
        .def(
            "to_string",
            overload_cast<const Scale &, const DateTime::Format &>(&Instant::toString, const_),
            arg_v("scale", DEFAULT_TIME_SCALE, "Scale.UTC"),
            arg_v("date_time_format", DEFAULT_DATE_TIME_FORMAT, "Format.Standard"),
            R"doc(
                Convert to string.

                Args:
                    scale (Time.Scale): Time scale.
                    date_time_format (DateTime.Format): Date-time format.

                Returns:
                    str: String representation.
            )doc"
        )

        .def_static(
            "undefined",
            &Instant::Undefined,
            R"doc(
                Create an undefined instant.

                Returns:
                    Instant: Undefined instant.
            )doc"
        )
        .def_static(
            "now",
            &Instant::Now,
            R"doc(
                Get current instant.

                Returns:
                    Instant: Current instant.
            )doc"
        )
        .def_static(
            "J2000",
            &Instant::J2000,
            R"doc(
                Get J2000 instant.

                Returns:
                    Instant: J2000 instant.
            )doc"
        )
        .def_static(
            "GPS_epoch",
            &Instant::GPSEpoch,
            R"doc(
                Get the GPS epoch instant.

                Returns:
                    Instant: GPS epoch instant.
            )doc"
        )
        .def_static(
            "date_time",
            &Instant::DateTime,
            R"doc(
                Create an instant from a date-time.

                Args:
                    date_time (DateTime): Date-time.

                Returns:
                    Instant: Instant.
            )doc"
        )
        .def_static(
            "julian_date",
            &Instant::JulianDate,
            R"doc(
                Create an instant from a Julian date.

                Args:
                    julian_date (float): Julian date.

                Returns:
                    Instant: Instant.
            )doc"
        )
        .def_static(
            "modified_julian_date",
            &Instant::ModifiedJulianDate,
            R"doc(
                Create an instant from a Modified Julian date.

                Args:
                    modified_julian_date (float): Modified Julian date.

                Returns:
                    Instant: Instant.
            )doc"
        )

        .def_static(
            "parse",
            &Instant::Parse,
            arg("string"),
            arg("scale"),
            arg_v("date_time_format", DEFAULT_DATE_TIME_FORMAT, "Format.Standard"),

            R"doc(
                Create an instant from a string representation.

                Args:
                    string (str): String representation.
                    scale (Time.Scale): Time scale.
                    date_time_format (DateTime.Format): Date-time format.


                Returns:
                    Instant: Instant.
            )doc"
        )

        ;
}
