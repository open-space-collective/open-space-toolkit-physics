/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

inline void OpenSpaceToolkitPhysicsPy_Time_Instant(pybind11::module &aModule)
{
    using namespace pybind11;

    using ostk::core::types::String;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Duration;
    using ostk::physics::time::DateTime;

    class_<Instant>(aModule, "Instant")

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        // Duration() is private in this context
        // .def(self + Duration())
        // .def(self - Duration())
        // .def(self += Duration())
        // .def(self -= Duration())
        .def(self - self)
        .def(
            "__add__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant + aDuration;
            },
            is_operator()
        )
        .def(
            "__sub__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant - aDuration;
            },
            is_operator()
        )
        .def(
            "__iadd__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant + aDuration;
            },
            is_operator()
        )
        .def(
            "__isub__",
            [](const Instant &anInstant, Duration aDuration)
            {
                return anInstant - aDuration;
            },
            is_operator()
        )

        .def("__str__", &(shiftToString<Instant>))
        .def(
            "__repr__",
            +[](const Instant &anInstant) -> std::string
            {
                return anInstant.toString();
            }
        )

        .def("is_defined", &Instant::isDefined)
        .def("is_post_epoch", &Instant::isPostEpoch)
        .def("is_near", &Instant::isNear)

        .def("get_date_time", &Instant::getDateTime)
        .def("get_julian_date", &Instant::getJulianDate)
        .def("get_modified_julian_date", &Instant::getModifiedJulianDate)
        .def("get_leap_second_count", &Instant::getLeapSecondCount)
        .def(
            "to_string",
            overload_cast<const Scale &, const DateTime::Format &>(&Instant::toString, const_),
            arg("scale") = DEFAULT_TIME_SCALE,
            arg("date_time_format") = DEFAULT_DATE_TIME_FORMAT
        )

        .def_static("undefined", &Instant::Undefined)
        .def_static("now", &Instant::Now)
        .def_static("J2000", &Instant::J2000)
        .def_static("date_time", &Instant::DateTime)
        .def_static("julian_date", &Instant::JulianDate)
        .def_static("modified_julian_date", &Instant::ModifiedJulianDate)

        ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
