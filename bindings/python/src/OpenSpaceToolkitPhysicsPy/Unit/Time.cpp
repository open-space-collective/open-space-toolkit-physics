/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Unit/Time.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Time(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;

    using ostk::physics::unit::Time;

    class_<Time> time(aModule, "Time");

    time.def(init<Real, Time::Unit>())

        .def(self == self)
        .def(self != self)

        // .def(self < self)
        // .def(self <= self)
        // .def(self > self)
        // .def(self >= self)

        // .def(self + self)
        // .def(self - self)

        // // .def(self * other<Real>())
        // .def(self / other<Real>())
        // .def(self *= other<Real>())
        // .def(self /= other<Real>())
        // .def("__mul__", [](const Time &aTime, Real aReal) {return aTime * aReal;}, is_operator())
        // .def("__truediv__", [](const Time &aTime, Real aReal) {return aTime / aReal;}, is_operator())
        // .def("__imul__", [](const Time &aTime, Real aReal) {return aTime * aReal;}, is_operator())
        // .def("__itruediv__", [](const Time &aTime, Real aReal) {return aTime / aReal;}, is_operator())

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

        .def("is_defined", &Time::isDefined)

        .def("to_string", &Time::toString, "aPrecision"_a = Integer::Undefined())

        .def_static("undefined", &Time::Undefined)
        .def_static("string_from_unit", &Time::StringFromUnit)
        .def_static("symbol_from_unit", &Time::SymbolFromUnit)

        ;

    enum_<Time::Unit>(time, "Unit")

        .value("Undefined", Time::Unit::Undefined)
        .value("Nanosecond", Time::Unit::Nanosecond)
        .value("Microsecond", Time::Unit::Microsecond)
        .value("Millisecond", Time::Unit::Millisecond)
        .value("Second", Time::Unit::Second)
        .value("Minute", Time::Unit::Minute)
        .value("Hour", Time::Unit::Hour)
        .value("Day", Time::Unit::Day)
        .value("Week", Time::Unit::Week)

        ;
}
