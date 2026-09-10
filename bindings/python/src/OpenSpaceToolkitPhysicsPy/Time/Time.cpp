/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Time.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Time(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::String;
    using ostk::core::type::Uint16;
    using ostk::core::type::Uint8;

    using ostk::physics::time::Time;

    class_<Time> time_class(
        aModule,
        "Time",
        R"doc(
            Time as hour, minute, second, millisecond, microsecond and nanosecond.
        )doc"
    );

    enum_<Time::Format>(time_class, "Format")

        .value(
            "Undefined",
            Time::Format::Undefined,
            R"doc(
                Undefined time format.
            )doc"
        )
        .value(
            "Standard",
            Time::Format::Standard,
            R"doc(
                Standard time format.
            )doc"
        )
        .value(
            "ISO8601",
            Time::Format::ISO8601,
            R"doc(
                ISO 8601 time format.
            )doc"
        )

        ;

    time_class
        .def(
            init<int, int, int, int, int, int>(),
            R"doc(
                Constructor.

                Args:
                    an_hour (int): An hour count (0 - 23).
                    a_minute (int): A minute count (0 - 59).
                    a_second (int): A second count (0 - 60).
                    a_millisecond (int): A millisecond count (0 - 999).
                    a_microsecond (int): A microsecond count (0 - 999).
                    a_nanosecond (int): A nanosecond count (0 - 999).
            )doc"
        )

        .def(
            init<int, int, int>(),
            R"doc(
                Constructor.

                Args:
                    an_hour (int): An hour count (0 - 23).
                    a_minute (int): A minute count (0 - 59).
                    a_second (int): A second count (0 - 60).
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Time>))
        .def(
            "__repr__",
            +[](const Time& aTime) -> std::string
            {
                return aTime.toString();
            }
        )

        .def(
            "is_defined",
            &Time::isDefined,
            R"doc(
                Check if the time is defined.

                Returns:
                    bool: True if defined
            )doc"
        )

        .def(
            "get_hour",
            &Time::getHour,
            R"doc(
                Get hour count.

                Returns:
                    int: Hour count.
            )doc"
        )
        .def(
            "get_minute",
            &Time::getMinute,
            R"doc(
                Get minute count.

                Returns:
                    int: Minute count.
            )doc"
        )
        .def(
            "get_second",
            &Time::getSecond,
            R"doc(
                Get second count.

                Returns:
                    int: Second count.
            )doc"
        )
        .def(
            "get_millisecond",
            &Time::getMillisecond,
            R"doc(
                Get millisecond count.

                Returns:
                    int: Millisecond count.
            )doc"
        )
        .def(
            "get_microsecond",
            &Time::getMicrosecond,
            R"doc(
                Get microsecond count.

                Returns:
                    int: Microsecond count.
            )doc"
        )
        .def(
            "get_nanosecond",
            &Time::getNanosecond,
            R"doc(
                Get nanosecond count.

                Returns:
                    int: Nanosecond count.
            )doc"
        )
        .def(
            "get_floating_seconds",
            &Time::getFloatingSeconds,
            R"doc(
                Get floating seconds.

                Returns:
                    float: Floating seconds.
            )doc"
        )
        .def(
            "get_total_floating_seconds",
            &Time::getTotalFloatingSeconds,
            R"doc(
                Get total floating seconds.

                Returns:
                    float: Total floating seconds.
            )doc"
        )
        .def(
            "get_total_floating_hours",
            &Time::getTotalFloatingHours,
            R"doc(
                Get total floating hours.

                Returns:
                    float: Total floating hours.
            )doc"
        )
        .def(
            "to_string",
            &Time::toString,
            R"doc(
                Get string representation of time.

                Returns:
                    str: String representation of time.
            )doc"
        )
        .def(
            "set_hour",
            +[](Time& aTime, const Uint8 anHour) -> void
            {
                PyErr_WarnEx(
                    PyExc_DeprecationWarning,
                    "Use Time(hour, minute, second, millisecond, microsecond, nanosecond) instead.",
                    1
                );
                aTime.setHour(anHour);
            },
            R"doc(
                Set hour count.

                Args:
                    an_hour (int): An hour count (0 - 23).
            )doc",
            arg("an_hour")
        )
        .def(
            "set_minute",
            +[](Time& aTime, const Uint8 aMinute) -> void
            {
                PyErr_WarnEx(
                    PyExc_DeprecationWarning,
                    "Use Time(hour, minute, second, millisecond, microsecond, nanosecond) instead.",
                    1
                );
                aTime.setMinute(aMinute);
            },
            R"doc(
                Set minute count.

                Args:
                    a_minute (int): A minute count (0 - 59).
            )doc",
            arg("a_minute")
        )
        .def(
            "set_second",
            +[](Time& aTime, const Uint8 aSecond) -> void
            {
                PyErr_WarnEx(
                    PyExc_DeprecationWarning,
                    "Use Time(hour, minute, second, millisecond, microsecond, nanosecond) instead.",
                    1
                );
                aTime.setSecond(aSecond);
            },
            R"doc(
                Set second count.

                Args:
                    a_second (int): A second count (0 - 60).
            )doc",
            arg("a_second")
        )
        .def(
            "set_millisecond",
            +[](Time& aTime, const Uint16 aMillisecond) -> void
            {
                PyErr_WarnEx(
                    PyExc_DeprecationWarning,
                    "Use Time(hour, minute, second, millisecond, microsecond, nanosecond) instead.",
                    1
                );
                aTime.setMillisecond(aMillisecond);
            },
            R"doc(
                Set millisecond count.

                Args:
                    a_millisecond (int): A millisecond count (0 - 999).
            )doc",
            arg("a_millisecond")
        )
        .def(
            "set_microsecond",
            +[](Time& aTime, const Uint16 aMicrosecond) -> void
            {
                PyErr_WarnEx(
                    PyExc_DeprecationWarning,
                    "Use Time(hour, minute, second, millisecond, microsecond, nanosecond) instead.",
                    1
                );
                aTime.setMicrosecond(aMicrosecond);
            },
            R"doc(
                Set microsecond count.

                Args:
                    a_microsecond (int): A microsecond count (0 - 999).
            )doc",
            arg("a_microsecond")
        )
        .def(
            "set_nanosecond",
            +[](Time& aTime, const Uint16 aNanosecond) -> void
            {
                PyErr_WarnEx(
                    PyExc_DeprecationWarning,
                    "Use Time(hour, minute, second, millisecond, microsecond, nanosecond) instead.",
                    1
                );
                aTime.setNanosecond(aNanosecond);
            },
            R"doc(
                Set nanosecond count.

                Args:
                    a_nanosecond (int): A nanosecond count (0 - 999).
            )doc",
            arg("a_nanosecond")
        )
        .def(
            "to_string",
            +[](const Time& aTime) -> String
            {
                return aTime.toString();
            },
            R"doc(
                Get string representation of time.

                Returns:
                    str: String representation of time.
            )doc"
        )
        .def(
            "to_string",
            +[](const Time& aTime, const Time::Format& aFormat) -> String
            {
                return aTime.toString(aFormat);
            },
            R"doc(
                Get string representation of time.

                Args:
                    aFormat (Time.Format): Time format.

                Returns:
                    str: String representation of time.
            )doc"
        )

        .def_static(
            "undefined",
            &Time::Undefined,
            R"doc(
                Create an undefined time.

                Returns:
                    Time: Undefined time.
            )doc"
        )
        .def_static(
            "midnight",
            &Time::Midnight,
            R"doc(
                Create a time at midnight.

                Returns:
                    Time: Time at midnight.
            )doc"
        )
        .def_static(
            "noon",
            &Time::Noon,
            R"doc(
                Create a time at noon.

                Returns:
                    Time: Time at noon.
            )doc"
        )
        .def_static(
            "parse",
            &Time::Parse,
            R"doc(
                Create a time from a string representation.

                Args:
                    string (str): A string.
                    format (Time.Format, optional): A time format (automatic detection if Undefined).

                Returns:
                    Time: Time.
            )doc",
            arg("string"),
            arg("format") = Time::Format::Undefined
        )
        .def_static(
            "hours",
            &Time::Hours,
            R"doc(
                Create a time from a real number of hours.

                Args:
                    value (float): A real number of hours.

                Returns:
                    Time: Time.
            )doc",
            arg("value")
        )
        .def_static(
            "seconds",
            &Time::Seconds,
            R"doc(
                Create a time from a real number of seconds.

                Args:
                    value (float): A real number of seconds.

                Returns:
                    Time: Time.
            )doc",
            arg("value")
        )

        ;
}
