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

        // TBR: Remove these methods, use getStart and getEnd instead
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
            "get_type",
            &Interval::getType,
            R"doc(
                Get the type of the interval.

                Returns:
                    Interval.Type: The type of the interval.
            )doc"
        )
        .def(
            "get_intersection_with",
            &Interval::getIntersectionWith,
            R"doc(
                Get the intersection with another interval.

                Args:
                    (Interval): Another interval.

                Returns:
                    Interval: Intersection interval (Undefined if there is no intersection).
            )doc"
        )
        .def(
            "get_union_with",
            &Interval::getUnionWith,
            R"doc(
                Get the union with another interval.

                Args:
                    (Interval): Another interval.

                Returns:
                    Interval: Union interval (Undefined if there is no single-interval union).
            )doc"
        )
        .def(
            "to_string",
            &Interval::toString,
            arg("time_scale") = Scale::UTC,
            R"doc(
                Convert the interval to a string.

                Args:
                    time_scale (Scale): Time scale.

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
                    (Duration): Time step.

                Returns:
                    list[Instant]: Grid of instants.
            )doc"
        )
        .def(
            "to_datetime_span",
            [](const Interval& anInterval, const Scale& aScale) -> std::tuple<DateTime, DateTime>
            {
                return {anInterval.getStart().getDateTime(aScale), anInterval.getEnd().getDateTime(aScale)};
            },
            R"doc(
                Get the datetime span.

                Args:
                    scale (Scale): Time scale. Defaults to UTC.

                Returns:
                    tuple[datetime, datetime]: Datetime span.
            )doc",
            arg("scale") = Scale::UTC
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
            "open",
            &Interval::Open,
            arg("start_instant"),
            arg("end_instant"),
            R"doc(
                Create a open interval.

                Args:
                    start_instant (Instant): Start instant.
                    end_instant (Instant): End instant.

                Returns:
                    Interval: Open interval.
            )doc"
        )
        .def_static(
            "half_open_left",
            &Interval::HalfOpenLeft,
            arg("start_instant"),
            arg("end_instant"),
            R"doc(
                Create a half-open left interval.

                Args:
                    start_instant (Instant): Start instant.
                    end_instant (Instant): End instant.

                Returns:
                    Interval: Half-open left interval.
            )doc"
        )
        .def_static(
            "half_open_right",
            &Interval::HalfOpenRight,
            arg("start_instant"),
            arg("end_instant"),
            R"doc(
                Create a half-open right interval.

                Args:
                    start_instant (Instant): Start instant.
                    end_instant (Instant): End instant.

                Returns:
                    Interval: Half-open right interval.
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
            "clip",
            &Interval::Clip,
            arg("intervals"),
            arg("interval"),
            R"doc(
                Creates a clipped list of intervals.

                ```
                intervals = [[1, 3], [5, 7], [9, 11]]
                interval = [4, 10]
                output = [[5, 7], [9, 10]]
                ```

                Args:
                    intervals (list[Interval]): A list of intervals.
                    interval (Interval): The clipping interval.

                Returns:
                    list[Interval]: Clipped intervals.
            )doc"
        )
        .def_static(
            "sort",
            &Interval::Sort,
            arg("intervals"),
            arg("by_lower_bound") = true,
            arg("ascending") = true,
            R"doc(
                Creates a sorted list of intervals.

                Args:
                    intervals (list[Interval]): A list of intervals.
                    by_lower_bound (bool): Use lower bound for sorting. Defaults to True.
                    ascending (bool): Sort in ascending order. Defaults to True.

                Returns:
                    list[Interval]: Sorted intervals.
            )doc"
        )
        .def_static(
            "merge",
            &Interval::Merge,
            arg("intervals"),
            R"doc(
                Creates a merged list of intervals.

                ```
                intervals = [[1, 3], [2, 4], [5, 7]]
                output = [[1, 4], [5, 7]]
                ```

                Args:
                    intervals (list[Interval]): A list of intervals.

                Returns:
                    list[Interval]: Merged intervals.
            )doc"
        )
        .def_static(
            "get_gaps",
            &Interval::GetGaps,
            arg("intervals"),
            arg_v("interval", Interval::Undefined(), "Interval::Undefined()"),
            R"doc(
                Creates a list of intervals gaps.

                ```
                intervals = [[1, 3], [5, 7], [9, 11]]
                interval = [0, 12]
                output = [[0, 1], [3, 5], [7, 9], [11, 12]]
                ```

                Args:
                    intervals (list[Interval]): A list of intervals.
                    interval (Interval): The analysis interval. Used to compute gaps for the first and last interval. Defaults to Undefined.

                Returns:
                    list[Interval]: Intervals gaps.
            )doc"
        )
        .def_static(
            "logical_or",
            &Interval::LogicalOr,
            arg("intervals_1"),
            arg("intervals_2"),
            R"doc(
                Creates a list of intervals by a logical-or conjunction.

                ```
                intervals_1 = [[-1, 1], [2, 4]]
                intervals_2 = [[0.5, 1.5], [3, 5], [7, 8]]
                output = [[-1, 1.5], [2, 5], [7, 8]]
                ```

                Args:
                    intervals_1 (list[Interval]): A list of intervals.
                    intervals_2 (list[Interval]): Another list of intervals.

                Returns:
                    list[Interval]: Logical-or intervals.
            )doc"
        )
        .def_static(
            "logical_and",
            &Interval::LogicalAnd,
            arg("intervals_1"),
            arg("intervals_2"),
            R"doc(
                Creates a list of intervals by a logical-and conjunction.

                ```
                intervals_1 = [[-1, 1], [2, 4]]
                intervals_2 = [[0.5, 1.5], [3, 5], [7, 8]]
                output = [[0.5, 1], [3, 4]]
                ```

                Args:
                    intervals_1 (list[Interval]): A list of intervals.
                    intervals_2 (list[Interval]): Another list of intervals.

                Returns:
                    list[Interval]: Logical-and intervals.
            )doc"
        )
        .def_static(
            "parse",
            &Interval::Parse,
            R"doc(
                Parse an interval from a string representation.

                Args:
                    (str): String representation.

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
