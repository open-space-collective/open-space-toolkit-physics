/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Interval(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::String;

    using ostk::physics::time::Instant;
    using ostk::physics::time::Interval;
    using ostk::physics::time::Scale;

    class_<Interval> interval_class(aModule, "Interval");

    interval_class

        .def(
            init<const Instant&, const Instant&, const Interval::Type&>(),
            arg("start_instant"),
            arg("end_instant"),
            arg("type")
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

        .def("is_defined", &Interval::isDefined)
        .def("is_degenerate", &Interval::isDegenerate)
        .def(
            "intersects",
            +[](const Interval& anInterval, const Interval& anotherInterval) -> bool
            {
                return anInterval.intersects(anotherInterval);
            },
            arg("interval")
        )
        .def(
            "contains_instant",
            +[](const Interval& anInterval, const Instant& anInstant) -> bool
            {
                return anInterval.contains(anInstant);
            },
            arg("instant")
        )
        .def(
            "contains_interval",
            +[](const Interval& anInterval, const Interval& anOtherInterval) -> bool
            {
                return anInterval.contains(anOtherInterval);
            },
            arg("interval")
        )

        .def("get_lower_bound", &Interval::getLowerBound)
        .def("get_upper_bound", &Interval::getUpperBound)
        // .def("get_intersection_with", &Interval::getIntersectionWith)
        // .def("get_union_with", &Interval::geteUnionWith)
        // .def("generate_array_with_step", &Interval::generateArrayWithStep)
        // .def("generate_array_with_size", &Interval::generateArrayWithSize)

        .def("get_start", &Interval::getStart)
        .def("get_end", &Interval::getEnd)
        .def("get_duration", &Interval::getDuration)
        .def("get_center", &Interval::getCenter)
        .def("to_string", &Interval::toString, "aTimeScale"_a = Scale::UTC)
        .def("generate_grid", &Interval::generateGrid)

        .def_static("undefined", &Interval::Undefined)
        .def_static("closed", &Interval::Closed, arg("start_instant"), arg("end_instant"))
        .def_static("centered", &Interval::Centered, arg("instant"), arg("duration"), arg("type"))
        .def_static("parse", &Interval::Parse)

        ;

    // https://github.com/pybind/pybind11/pull/949 locally to avoid conflicts with other potential objects in other ostk
    // modules
    enum_<Interval::Type>(interval_class, "Type", pybind11::module_local())

        .value("Undefined", Interval::Type::Undefined)
        .value("Closed", Interval::Type::Closed)
        .value("Open", Interval::Type::Open)
        .value("HalfOpenLeft", Interval::Type::HalfOpenLeft)
        .value("HalfOpenRight", Interval::Type::HalfOpenRight)

        ;

    implicitly_convertible<ostk::math::object::Interval<ostk::physics::time::Instant>, Interval>();
}
