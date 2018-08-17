////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Time/Instant.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Time/Instant.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryPhysicsPy_Time_Instant               ( )
{

    using namespace boost::python ;

    using library::physics::time::Instant ;
    using library::physics::time::Duration ;

    scope in_Instant = class_<Instant>("Instant", no_init)

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + other<Duration>())
		.def(self - other<Duration>())
		.def(self - self)
		.def(self += other<Duration>())
		.def(self -= other<Duration>())

        .def(self_ns::str(self_ns::self))

        .def("isDefined", &Instant::isDefined)
        .def("isPostEpoch", &Instant::isPostEpoch)
        
        .def("getDateTime", &Instant::getDateTime)
        .def("getJulianDate", &Instant::getJulianDate)
        .def("getModifiedJulianDate", &Instant::getModifiedJulianDate)
        .def("toString", &Instant::toString)

        .def("Undefined", &Instant::Undefined).staticmethod("Undefined")
        .def("Now", &Instant::Now).staticmethod("Now")
        .def("J2000", &Instant::J2000).staticmethod("J2000")
        .def("DateTime", &Instant::DateTime).staticmethod("DateTime")
        .def("JulianDate", &Instant::JulianDate).staticmethod("JulianDate")
        .def("ModifiedJulianDate", &Instant::ModifiedJulianDate).staticmethod("ModifiedJulianDate")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////