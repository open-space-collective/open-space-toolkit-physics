/// Apache License 2.0

#include <datetime.h>

#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Duration(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::String;

    using ostk::physics::time::Duration;

    class_<Duration> duration_class(aModule, "Duration",
        R"doc(
            Duration format.
        )doc"
    );

    duration_class

        .def(init<int>(),
            R"doc(
                Constructor.

            )doc"
        )

        .def(init(
            [](const float& aCount)
            {
                return new Duration(aCount);
            }
        ))

        .def(init(
            [](const double& aCount)
            {
                return new Duration(aCount);
            }
        ))

        .def(init(
            [](const std::chrono::microseconds& aCount)
            {
                return new Duration(aCount.count() * 1000);
            }
        ),
        R"doc(
            Constructor.

            Args:
                count (int): A nanosecond count.
        )doc"
        )

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + self)
        .def(self - self)
        .def(self * double())
        .def(self / double())

        .def(self += self)
        .def(self -= self)
        .def(self *= double())
        .def(self /= double())

        .def("__str__", &(shiftToString<Duration>))
        .def(
            "__repr__",
            +[](const Duration& aDuration) -> std::string
            {
                return aDuration.toString();
            }
        )

        .def("is_defined", &Duration::isDefined,
            R"doc(
                Check if the duration is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def("is_zero", &Duration::isZero,
            R"doc(
                Check if the duration is zero.

                Returns:
                    bool: True if zero.
            )doc"
        )
        .def("is_positive", &Duration::isPositive,
            R"doc(
                Check if the duration is positive.

                Returns:
                    bool: True if positive.
            )doc"
        )
        .def("is_strictly_positive", &Duration::isStrictlyPositive,
            R"doc(
                Check if the duration is strictly positive.

                Returns:
                    bool: True if strictly positive.
            )doc"
        )
        .def("is_near", &Duration::isNear, arg("duration"), arg("tolerance"),
            R"doc(
                Check if the duration is near another duration.

                Args:
                    duration (Duration): Duration to compare with.
                    tolerance (Duration): Tolerance.

                Returns:
                    bool: True if near.
            )doc"
        )

        .def("get_nanoseconds", &Duration::getNanoseconds,
            R"doc(
                Get the nanosecond count.

                Returns:
                    int: Nanosecond count.
            )doc"
        )
        .def("get_microseconds", &Duration::getMicroseconds,
            R"doc(
                Get the microsecond count.

                Returns:
                    int: Microsecond count.
            )doc"
        )
        .def("get_milliseconds", &Duration::getMilliseconds,
            R"doc(
                Get the millisecond count.

                Returns:
                    int: Millisecond count.
            )doc"
        )
        .def("get_seconds", &Duration::getSeconds,
            R"doc(
                Get the second count.

                Returns:
                    int: Second count.
            )doc"
        )
        .def("get_minutes", &Duration::getMinutes,
            R"doc(
                Get the minute count.

                Returns:
                    int: Minute count.
            )doc"
        )
        .def("get_hours", &Duration::getHours,
            R"doc(
                Get the hour count.

                Returns:
                    int: Hour count.
            )doc"
        )
        .def("get_days", &Duration::getDays,
            R"doc(
                Get the day count.

                Returns:
                    int: Day count.
            )doc"
        )
        .def("get_weeks", &Duration::getWeeks,
            R"doc(
                Get the week count.

                Returns:
                    int: Week count.
            )doc"
        )
        .def("in_nanoseconds", &Duration::inNanoseconds,
            R"doc(
                Get the duration in nanoseconds.

                Returns:
                    int: Duration in nanoseconds.
            )doc"
        )
        .def("in_microseconds", &Duration::inMicroseconds,
            R"doc(
                Get the duration in microseconds.

                Returns:
                    int: Duration in microseconds.
            )doc"
        )
        .def("in_milliseconds", &Duration::inMilliseconds,
            R"doc(
                Get the duration in milliseconds.

                Returns:
                    int: Duration in milliseconds.
            )doc"
        )
        .def("in_seconds", &Duration::inSeconds,
            R"doc(
                Get the duration in seconds.

                Returns:
                    int: Duration in seconds.
            )doc"
        )
        .def("in_minutes", &Duration::inMinutes,
            R"doc(
                Get the duration in minutes.

                Returns:
                    int: Duration in minutes.
            )doc"
        )
        .def("in_hours", &Duration::inHours,
            R"doc(
                Get the duration in hours.

                Returns:
                    int: Duration in hours.
            )doc"
        )
        .def("in_days", &Duration::inDays,
            R"doc(
                Get the duration in days.

                Returns:
                    int: Duration in days.
            )doc"
        )
        .def("in_weeks", &Duration::inWeeks,
            R"doc(
                Get the duration in weeks.

                Returns:
                    int: Duration in weeks.
            )doc"
        )
        .def("in_unit", &Duration::in,
            R"doc(
                Get the duration in a unit.

                Returns:
                    int: Duration in unit.
            )doc"
        )
        .def("get_absolute", &Duration::getAbsolute,
            R"doc(
                Get the absolute duration.

                Returns:
                    Duration: Absolute duration.
            )doc"
        )
        .def(
            "to_string",
            +[](const Duration& aDuration) -> String
            {
                return aDuration.toString();
            }
        )
        .def(
            "to_string",
            +[](const Duration& aDuration, const Duration::Format& aFormat) -> String
            {
                return aDuration.toString(aFormat);
            }
        )
        .def(
            "to_timedelta",
            +[](const Duration& aDuration) -> std::chrono::microseconds
            {
                return std::chrono::microseconds(aDuration.inMicroseconds());
            }
        )

        .def_static("undefined", &Duration::Undefined,
            R"doc(
                Create an undefined duration.

                Returns:
                    Duration: Undefined duration.
            )doc"
        )
        .def_static("zero", &Duration::Zero,
            R"doc(
                Create a zero duration.

                Returns:
                    Duration: Zero duration.
            )doc"
        )
        .def_static("nanoseconds", &Duration::Nanoseconds,
            R"doc(
                Create a duration in nanoseconds.

                Returns:
                    Duration: Duration in nanoseconds.
            )doc"
        )
        .def_static("microseconds", &Duration::Microseconds,
            R"doc(
                Create a duration in microseconds.

                Returns:
                    Duration: Duration in microseconds.
            )doc"
        )
        .def_static("milliseconds", &Duration::Milliseconds,
            R"doc(
                Create a duration in milliseconds.

                Returns:
                    Duration: Duration in milliseconds.
            )doc"
        )
        .def_static("seconds", &Duration::Seconds,
            R"doc(
                Create a duration in seconds.

                Returns:
                    Duration: Duration in seconds.
            )doc"
        )
        .def_static("minutes", &Duration::Minutes,
            R"doc(
                Create a duration in minutes.

                Returns:
                    Duration: Duration in minutes.
            )doc"
        )
        .def_static("hours", &Duration::Hours,
            R"doc(
                Create a duration in hours.

                Returns:
                    Duration: Duration in hours.
            )doc"
        )
        .def_static("days", &Duration::Days,
            R"doc(
                Create a duration in days.

                Returns:
                    Duration: Duration in days.
            )doc"
        )
        .def_static("weeks", &Duration::Weeks,
            R"doc(
                Create a duration in weeks.

                Returns:
                    Duration: Duration in weeks.
            )doc"
        )
        .def_static("between", &Duration::Between,
            R"doc(
                Constructs a duration between two instants

                Returns:
                    Duration: Duration between two instants.
            )doc"
        )

        ;

    implicitly_convertible<PyDateTime_Delta, Duration>();

    enum_<Duration::Format>(duration_class, "Format")

        .value("Undefined", Duration::Format::Undefined,
            R"doc(
                Undefined format.
            )doc"
        )
        .value("Standard", Duration::Format::Standard,
            R"doc(
                Standard format (d hh:mm:ss.mmm.uuu.nnn)
            )doc"
        )
        .value("ISO8601", Duration::Format::ISO8601,
            R"doc(
                ISO 8601 format (PnDTnHnMnS)
            )doc"
        )

        ;

    duration_class.def_static("parse", &Duration::Parse, arg("string"), arg("format") = Duration::Format::Undefined);
}
