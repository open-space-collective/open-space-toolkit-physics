/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Unit/Time.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Time(nanobind::module_& aModule)
{
    using namespace nanobind;

    using ostk::physics::unit::Time;

    class_<Time> time(
        aModule,
        "Time",
        R"doc(
            Time.

            https://en.wikipedia.org/wiki/Unit_of_time
        )doc"
    );

    time.def(
            init<double, Time::Unit>(),
            R"doc(
            Constructor.

            Args:
                aReal (float): A real number.
                aUnit (Time.Unit): A time unit.
        )doc"
    )

        .def(
            "__eq__",
            [](const Time& self, const Time& other)
            {
                return self == other;
            },
            is_operator()
        )
        .def(
            "__ne__",
            [](const Time& self, const Time& other)
            {
                return self != other;
            },
            is_operator()
        )

        // .def(self < self)
        // .def(self <= self)
        // .def(self > self)
        // .def(self >= self)

        // .def(self + self)
        // .def(self - self)

        // // .def(self * other<double>())
        // .def(self / other<double>())
        // .def(self *= other<double>())
        // .def(self /= other<double>())
        // .def("__mul__", [](const Time &aTime, double aReal) {return aTime * aReal;}, is_operator())
        // .def("__truediv__", [](const Time &aTime, double aReal) {return aTime / aReal;}, is_operator())
        // .def("__imul__", [](const Time &aTime, double aReal) {return aTime * aReal;}, is_operator())
        // .def("__itruediv__", [](const Time &aTime, double aReal) {return aTime / aReal;}, is_operator())

        // .def(self += self)
        // .def(self -= self)

        // .def("__str__", &(shiftToString<Time>))
        .def(
            "__repr__",
            +[](const Time& aTime) -> std::string
            {
                return aTime.toString();
            }
        )

        .def(
            "to_string",
            &Time::toString,
            "aPrecision"_a = -1,
            R"doc(
                Convert time to string.

                Args:
                    aPrecision (int): A precision.

                Returns:
                    str: String representation.
            )doc"
        )

        .def_static(
            "string_from_unit",
            &Time::StringFromUnit,
            R"doc(
                Get the string representation from a time unit.

                Args:
                    aUnit (Time.Unit): A time unit.

                Returns:
                    str: String representation.
            )doc"
        )
        .def_static(
            "symbol_from_unit",
            &Time::SymbolFromUnit,
            R"doc(
                Get the symbol representation from a time unit.

                Args:
                    aUnit (Time.Unit): A time unit.

                Returns:
                    str: Symbol representation.
            )doc"
        )

        ;

    enum_<Time::Unit>(time, "Unit")

        .value(
            "Nanosecond",
            Time::Unit::Nanosecond,
            R"doc(
                Nanosecond.
            )doc"
        )
        .value(
            "Microsecond",
            Time::Unit::Microsecond,
            R"doc(
                Microsecond.
            )doc"
        )
        .value(
            "Millisecond",
            Time::Unit::Millisecond,
            R"doc(
                Millisecond.
            )doc"
        )
        .value(
            "Second",
            Time::Unit::Second,
            R"doc(
                Second (SI).
            )doc"
        )
        .value(
            "Minute",
            Time::Unit::Minute,
            R"doc(
                Minute.
            )doc"
        )
        .value(
            "Hour",
            Time::Unit::Hour,
            R"doc(
                Hour.
            )doc"
        )
        .value(
            "Day",
            Time::Unit::Day,
            R"doc(
                Day.
            )doc"
        )
        .value(
            "Week",
            Time::Unit::Week,
            R"doc(
                Week.
            )doc"
        )

        ;
}
