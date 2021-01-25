////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Time/Instant.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <OpenSpaceToolkitPhysicsPy/Utilities/IterableConverter.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Time_Instant               (           pybind11::module&                     aModule                 )
{

    using namespace pybind11 ;

    using ostk::core::types::String ;

    using ostk::physics::time::Scale ;
    using ostk::physics::time::Instant ;
    using ostk::physics::time::Duration ;

    class_<Instant>(aModule, "Instant")

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        // .def(self + other<Duration>())
        // .def(self - other<Duration>())
        // .def(self - self)
        // .def(self += other<Duration>())
        // .def(self -= other<Duration>())

        // .def(self_ns::str(self_ns::self))

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

        .def_static("undefined", &Instant::Undefined)
        .def_static("now", &Instant::Now)
        .def_static("J2000", &Instant::J2000)
        .def_static("date_time", &Instant::DateTime)
        .def_static("julian_date", &Instant::JulianDate)
        .def_static("modified_julian_date", &Instant::ModifiedJulianDate)

    ;

    // using ostk::core::ctnr::Array ;

    // IterableConverter()

    //     .from_python<Array<Instant>>()
    //     .to_python<Array<Instant>>()

    // ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
