/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Interval(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::String;

    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    class_<Interval> interval_class(
        aModule,
        "Interval",
        R"doc(
            Time interval.
        )doc"
    );

    interval_class

        .def(
            init<const Instant&, const Instant&, const Interval::Type&>(),
            arg("start_instant"),
            arg("end_instant"),
            arg("type"),
            R"doc(
                Constructor.

                Args:
                    start_instant (Instant): Start instant.
                    end_instant (Instant): End instant.
                    type (Interval.Type): Interval type.
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Interval>))
        .def(
            "__repr__",
            +[](const Interval& anInterval) -> std::string
            {
                return anInterval.toString();
            }
        )

        .def(
            "is_defined",
            &Interval::isDefined,
            R"doc(
                Check if the interval is defined.

                Returns:
                    bool: True if defined.
            )doc"
        )
        .def(
            "is_degenerate",
            &Interval::isDegenerate,
            R"doc(
                Check if interval is degenerate, i.e. its lower and upper bounds are the equal.

                Returns:
                    bool: True if degenerate.
            )doc"
        )
        .def(
            "intersects",
            +[](const Interval& anInterval, const Interval& anotherInterval) -> bool
            {
                return anInterval.intersects(anotherInterval);
            },
            arg("interval"),
            R"doc(
                Check if the interval intersects another interval.

                Args:
                    interval (Interval): Another interval.

                Returns:
                    bool: True if the interval intersects another interval.
            )doc"
        )
        .def(
            "contains_instant",
            +[](const Interval& anInterval, const Instant& anInstant) -> bool
            {
                return anInterval.contains(anInstant);
            },
            arg("instant"),
            R"doc(
                Check if the interval contains an instant.

                Args:
                    instant (Instant): An instant.

                Returns:
                    bool: True if the interval contains the instant.
            )doc"
        )
        .def(
            "contains_interval",
            +[](const Interval& anInterval, const Interval& anOtherInterval) -> bool
            {
                return anInterval.contains(anOtherInterval);
            },
            arg("interval"),
            R"doc(
                Check if the interval contains another interval.

                Args:
                    interval (Interval): Another interval.

                Returns:
                    bool: True if the interval contains the other interval.
            )doc"
        )

        .def(
            "get_lower_bound",
            &Interval::getLowerBound,
            R"doc(
                Get the lower bound.

                Returns:
                    Instant: Lower bound.
            )doc"
        )
        .def(
            "get_upper_bound",
            &Interval::getUpperBound,
            R"doc(
                Get the upper bound.

                Returns:
                    Instant: Upper bound.
            )doc"
        )
        // .def("get_intersection_with", &Interval::getIntersectionWith)
        // .def("get_union_with", &Interval::geteUnionWith)
        // .def("generate_array_with_step", &Interval::generateArrayWithStep)
        // .def("generate_array_with_size", &Interval::generateArrayWithSize)

        .def(
            "get_start",
            &Interval::getStart,
            R"doc(
                Get the start instant.

                Returns:
                    Instant: Start instant.
            )doc"
        )
        .def(
            "get_end",
            &Interval::getEnd,
            R"doc(
                Get the end instant.

                Returns:
                    Instant: End instant.
            )doc"
        )
        .def(
            "get_duration",
            &Interval::getDuration,
            R"doc(
                Get the duration.

                Returns:
                    Duration: Duration.
            )doc"
        )
        .def(
            "get_center",
            &Interval::getCenter,
            R"doc(
                Get the center instant.

                Returns:
                    Instant: Center instant.
            )doc"
        )
        .def(
            "to_string",
            &Interval::toString,
            "aTimeScale"_a = Scale::UTC,
            R"doc(
                Convert the interval to a string.

                Args:
                    aTimeScale (Scale): Time scale.

                Returns:
                    str: String representation of the interval.
            )doc"
        )
        .def(
            "generate_grid",
            &Interval::generateGrid,
            R"doc(
                Generate a grid of instants with a given time step.

                Args:
                    aTimeStep (Duration): Time step.

                Returns:
                    List[Instant]: Grid of instants.
            )doc"
        )

        .def_static(
            "undefined",
            &Interval::Undefined,
            R"doc(
                Create an undefined interval.

                Returns:
                    Interval: Undefined interval.
            )doc"
        )
        .def_static(
            "closed",
            &Interval::Closed,
            arg("start_instant"),
            arg("end_instant"),
            R"doc(
                Create a closed interval.

                Args:
                    start_instant (Instant): Start instant.
                    end_instant (Instant): End instant.

                Returns:
                    Interval: Closed interval.
            )doc"
        )
        .def_static(
            "centered",
            &Interval::Centered,
            arg("instant"),
            arg("duration"),
            arg("type"),
            R"doc(
                Create a centered interval.

                Args:
                    instant (Instant): Central instant.
                    duration (Duration): Duration.
                    type (Interval.Type): Interval type.

                Returns:
                    Interval: Centered interval.
            )doc"
        )
        .def_static(
            "parse",
            &Interval::Parse,
            R"doc(
                Parse an interval from a string representation.

                Args:
                    aString (str): String representation.

                Returns:
                    Interval: Interval.
            )doc"
        )

        ;

    // https://github.com/pybind/pybind11/pull/949 locally to avoid conflicts with other potential objects in other ostk
    // modules
    enum_<Interval::Type>(interval_class, "Type", pybind11::module_local())

        .value(
            "Undefined",
            Interval::Type::Undefined,
            R"doc(
                Undefined interval type.
            )doc"
        )
        .value(
            "Closed",
            Interval::Type::Closed,
            R"doc(
                Closed interval type.
            )doc"
        )
        .value(
            "Open",
            Interval::Type::Open,
            R"doc(
                Open interval type.
            )doc"
        )
        .value(
            "HalfOpenLeft",
            Interval::Type::HalfOpenLeft,
            R"doc(
                Half-open left interval type.
            )doc"
        )
        .value(
            "HalfOpenRight",
            Interval::Type::HalfOpenRight,
            R"doc(
                Half-open right interval type.
            )doc"
        )

        ;

    implicitly_convertible<ostk::mathematics::object::Interval<ostk::physics::time::Instant>, Interval>();
}
