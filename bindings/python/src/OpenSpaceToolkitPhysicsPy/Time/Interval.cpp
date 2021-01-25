////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Time/Interval.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Time_Interval_toString_overloads, ostk::physics::time::Interval::toString, 0, 1)

inline void                     OpenSpaceToolkitPhysicsPy_Time_Interval              (           pybind11::module&                     aModule                 )
{

    using namespace pybind11 ;

    using ostk::core::types::String ;

    using ostk::physics::time::Instant ;
    using ostk::physics::time::Interval ;

    class_<Interval> interval(aModule, "Interval") ;

    interval.def(init<const Instant&, const Instant&, const Interval::Type&>())

        .def(self == self)
        .def(self != self)

        // .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Interval& anInterval) -> std::string { return anInterval.toString() ; })

        .def("is_defined", &Interval::isDefined)
        .def("is_degenerate", &Interval::isDegenerate)
        .def("intersects", &Interval::intersects)
        .def("contains_instant", +[] (const Interval& anInterval, const Instant& anInstant) -> bool { return anInterval.contains(anInstant) ; })
        .def("contains_interval", +[] (const Interval& anInterval, const Interval& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

        .def("get_lower_bound", &Interval::getLowerBound)
        .def("get_upper_bound", &Interval::getUpperBound)
        // .def("get_intersection_with", &Interval::getIntersectionWith)
        // .def("get_union_with", &Interval::getUnionWith)
        // .def("generate_array_with_step", &Interval::generateArrayWithStep)
        // .def("generate_array_with_size", &Interval::generateArrayWithSize)

        .def("get_start", &Interval::getStart)
        .def("get_end", &Interval::getEnd)
        .def("get_duration", &Interval::getDuration)
        .def("get_center", &Interval::getCenter)
        // .def("to_string", &Interval::toString, OpenSpaceToolkitPhysicsPy_Time_Interval_toString_overloads())
        .def("generate_grid", &Interval::generateGrid)

        .def_static("undefined", &Interval::Undefined)
        .def_static("closed", &Interval::Closed)
        .def_static("centered", &Interval::Centered)
        .def_static("parse", &Interval::Parse)

    ;

    enum_<Interval::Type>(interval, "TimeIntervalType")

        .value("Undefined", Interval::Type::Undefined)
        .value("Closed", Interval::Type::Closed)
        .value("Open", Interval::Type::Open)
        .value("HalfOpenLeft", Interval::Type::HalfOpenLeft)
        .value("HalfOpenRight", Interval::Type::HalfOpenRight)

    ;

    implicitly_convertible<Interval, ostk::math::obj::Interval<ostk::physics::time::Instant>>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
