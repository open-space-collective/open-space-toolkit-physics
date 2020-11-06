////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Time/Instant.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Utilities/IterableConverter.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Time_Instant               ( )
{

    using namespace boost::python ;

    using ostk::core::types::String ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

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

        .def("__repr__", +[] (const Instant& anInstant) -> std::string { return anInstant.toString() ; })

        .def("is_defined", &Instant::isDefined)
        .def("is_post_epoch", &Instant::isPostEpoch)
        .def("is_near", &Instant::isNear)

        .def("get_date_time", &Instant::getDateTime)
        .def("get_julian_date", &Instant::getJulianDate)
        .def("get_modified_julian_date", &Instant::getModifiedJulianDate)
        .def("get_leap_second_count", &Instant::getLeapSecondCount)
        .def("to_string", +[] (const Instant& anInstant) -> String { return anInstant.toString() ; })
        .def("to_string", +[] (const Instant& anInstant, const Scale& aScale) -> String { return anInstant.toString(aScale) ; })

        .def("undefined", &Instant::Undefined).staticmethod("undefined")
        .def("now", &Instant::Now).staticmethod("now")
        .def("J2000", &Instant::J2000).staticmethod("J2000")
        .def("date_time", &Instant::DateTime).staticmethod("date_time")
        .def("julian_date", &Instant::JulianDate).staticmethod("julian_date")
        .def("modified_julian_date", &Instant::ModifiedJulianDate).staticmethod("modified_julian_date")

    ;

    using ostk::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Instant>>()
        .to_python<Array<Instant>>()

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
