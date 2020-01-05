////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Units/Length.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitPhysicsPy/Utilities/IterableConverter.hpp>

#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Units_Length_toString_overloads, ostk::physics::units::Length::toString, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Units_Length_Interval_toString_overloads, ostk::math::obj::Interval<ostk::physics::units::Length>::toString, 0, 1)

inline void                     OpenSpaceToolkitPhysicsPy_Units_Length               ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::physics::units::Length ;

    scope in_Length = class_<Length>("Length", init<Real, Length::Unit>())

        .def(self == self)
        .def(self != self)

        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + self)
        .def(self - self)

        .def(self * other<Real>())
        .def(self / other<Real>())

        .def(self += self)
        .def(self -= self)

        .def(self *= other<Real>())
        .def(self /= other<Real>())

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Length& aLength) -> std::string { return aLength.toString() ; })

        .def("is_defined", &Length::isDefined)

        .def("get_unit", &Length::getUnit)
        .def("in_unit", &Length::in)
        .def("in_meters", &Length::inMeters)
        .def("in_kilometers", &Length::inKilometers)
        .def("to_string", &Length::toString, OpenSpaceToolkitPhysicsPy_Units_Length_toString_overloads())

        .def("undefined", &Length::Undefined).staticmethod("undefined")
        .def("millimeters", &Length::Millimeters).staticmethod("millimeters")
        .def("meters", &Length::Meters).staticmethod("meters")
        .def("kilometers", &Length::Kilometers).staticmethod("kilometers")
        .def("parse", &Length::Parse).staticmethod("parse")
        .def("string_from_unit", &Length::StringFromUnit).staticmethod("string_from_unit")
        .def("symbol_from_unit", &Length::SymbolFromUnit).staticmethod("symbol_from_unit")

    ;

    enum_<Length::Unit>("Unit")

        .value("Undefined", Length::Unit::Undefined)
        .value("Meter", Length::Unit::Meter)
        .value("Foot", Length::Unit::Foot)
        .value("TerrestrialMile", Length::Unit::TerrestrialMile)
        .value("NauticalMile", Length::Unit::NauticalMile)
        .value("AstronomicalUnit", Length::Unit::AstronomicalUnit)

    ;

    // using ostk::core::ctnr::Array ;

    // IterableConverter()

    //     .from_python<Array<Length>>()
    //     .to_python<Array<Length>>()

    // ;

    using ostk::math::obj::Interval ;

    class_<Interval<Length>>("Interval", init<const Length&, const Length&, const Interval<Length>::Type&>())

        .def(self == self)
        .def(self != self)

        .def("is_defined", &Interval<Length>::isDefined)
        .def("is_degenerate", &Interval<Length>::isDegenerate)
        .def("intersects", &Interval<Length>::intersects)
        .def("contains_length", +[] (const Interval<Length>& anInterval, const Length& aLength) -> bool { return anInterval.contains(aLength) ; })
        .def("contains_interval", +[] (const Interval<Length>& anInterval, const Interval<Length>& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

        .def("get_lower_bound", &Interval<Length>::getLowerBound)
        .def("get_upper_bound", &Interval<Length>::getUpperBound)

        .def("undefined", &Interval<Length>::Undefined).staticmethod("undefined")
        .def("closed", &Interval<Length>::Closed).staticmethod("closed")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
