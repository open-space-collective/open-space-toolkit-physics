////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time/Interval.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Interval.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Time_Interval_toString_overloads, library::physics::time::Interval::toString, 0, 1)

inline void                     LibraryPhysicsPy_Time_Interval              ( )
{

    using namespace boost::python ;

    using library::physics::time::Instant ;
    using library::physics::time::Interval ;

    scope in_Interval = class_<Interval>("Interval", init<const Instant&, const Instant&, const Interval::Type&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        
        .def("__repr__", +[] (const Interval& anInterval) -> std::string { return anInterval.toString() ; })

        .def("isDefined", &Interval::isDefined)
        .def("isDegenerate", &Interval::isDegenerate)
        .def("intersects", &Interval::intersects)
        .def("containsInstant", +[] (const Interval& anInterval, const Instant& anInstant) -> bool { return anInterval.contains(anInstant) ; })
        .def("containsInterval", +[] (const Interval& anInterval, const Interval& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

        .def("getLowerBound", &Interval::getLowerBound)
        .def("getUpperBound", &Interval::getUpperBound)
        // .def("getIntersectionWith", &Interval::getIntersectionWith)
        // .def("getUnionWith", &Interval::getUnionWith)
        // .def("generateArrayWithStep", &Interval::generateArrayWithStep)
        // .def("generateArrayWithSize", &Interval::generateArrayWithSize)

        .def("getStart", &Interval::getStart)
        .def("getEnd", &Interval::getEnd)
        .def("getDuration", &Interval::getDuration)
        .def("getCenter", &Interval::getCenter)
        .def("toString", &Interval::toString, LibraryPhysicsPy_Time_Interval_toString_overloads())
        .def("generateGrid", &Interval::generateGrid)
        
        .def("Undefined", &Interval::Undefined).staticmethod("Undefined")
        .def("Closed", &Interval::Closed).staticmethod("Closed")
        .def("Centered", &Interval::Centered).staticmethod("Centered")
        .def("Parse", &Interval::Parse).staticmethod("Parse")

    ;

    enum_<Interval::Type>("Type")

        .value("Undefined", Interval::Type::Undefined)
        .value("Closed", Interval::Type::Closed)
        .value("Open", Interval::Type::Open)
        .value("HalfOpenLeft", Interval::Type::HalfOpenLeft)
        .value("HalfOpenRight", Interval::Type::HalfOpenRight)

    ;

    implicitly_convertible<Interval, library::math::obj::Interval<library::physics::time::Instant>>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////