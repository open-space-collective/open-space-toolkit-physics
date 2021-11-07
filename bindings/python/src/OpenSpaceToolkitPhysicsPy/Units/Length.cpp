////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Units/Length.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Units_Length      (           pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;

    using ostk::physics::units::Length ;

    class_<Length> length(aModule, "Length") ;

    length.def(init<Real, Length::Unit>())

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + self)
        .def(self - self)

        .def(self += self)
        .def(self -= self)

        .def(+self)
        .def(-self)

        .def("__mul__", [](const Length &aLength, Real aReal) {return aLength * aReal;}, is_operator())
        .def("__truediv__", [](const Length &aLength, Real aReal) {return aLength / aReal;}, is_operator())
        .def("__imul__", [](const Length &aLength, Real aReal) {return aLength * aReal;}, is_operator())
        .def("__itruediv__", [](const Length &aLength, Real aReal) {return aLength / aReal;}, is_operator())

        .def("__str__", &(shiftToString<Length>))
        .def("__repr__", +[] (const Length& aLength) -> std::string { return aLength.toString() ; })

        .def("is_defined", &Length::isDefined)
        .def("is_zero", &Length::isZero)

        .def("get_unit", &Length::getUnit)
        .def("in_unit", &Length::in)
        .def("in_meters", &Length::inMeters)
        .def("in_kilometers", &Length::inKilometers)
        .def("to_string", &Length::toString, "aPrecision"_a=Integer::Undefined())

        .def_static("undefined", &Length::Undefined)
        .def_static("millimeters", &Length::Millimeters)
        .def_static("meters", &Length::Meters)
        .def_static("kilometers", &Length::Kilometers)
        .def_static("parse", &Length::Parse)
        .def_static("string_from_unit", &Length::StringFromUnit)
        .def_static("symbol_from_unit", &Length::SymbolFromUnit)

    ;

    enum_<Length::Unit> (length, "Unit")

        .value("Undefined", Length::Unit::Undefined)
        .value("Meter", Length::Unit::Meter)
        .value("Foot", Length::Unit::Foot)
        .value("TerrestrialMile", Length::Unit::TerrestrialMile)
        .value("NauticalMile", Length::Unit::NauticalMile)
        .value("AstronomicalUnit", Length::Unit::AstronomicalUnit)

    ;

    using ostk::math::obj::Interval ;

    class_<Interval<Length>>(aModule, "Interval")

        .def(init<const Length&, const Length&, const Interval<Length>::Type&>())

        .def(self == self)
        .def(self != self)

        .def("is_defined", &Interval<Length>::isDefined)
        .def("is_degenerate", &Interval<Length>::isDegenerate)
        .def("intersects", &Interval<Length>::intersects)
        .def("contains_length", +[] (const Interval<Length>& anInterval, const Length& aLength) -> bool { return anInterval.contains(aLength) ; })
        .def("contains_interval", +[] (const Interval<Length>& anInterval, const Interval<Length>& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

        .def("get_lower_bound", &Interval<Length>::getLowerBound)
        .def("get_upper_bound", &Interval<Length>::getUpperBound)

        .def_static("undefined", &Interval<Length>::Undefined)
        .def_static("closed", &Interval<Length>::Closed)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
