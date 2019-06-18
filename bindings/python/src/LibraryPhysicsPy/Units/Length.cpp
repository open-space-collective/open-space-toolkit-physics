////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Units/Length.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryPhysicsPy/Utilities/IterableConverter.hpp>

#include <Library/Physics/Units/Length.hpp>

#include <Library/Mathematics/Objects/Interval.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Units_Length_toString_overloads, library::physics::units::Length::toString, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Units_Length_Interval_toString_overloads, library::math::obj::Interval<library::physics::units::Length>::toString, 0, 1)

inline void                     LibraryPhysicsPy_Units_Length               ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::physics::units::Length ;

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

        .def("isDefined", &Length::isDefined)

        .def("getUnit", &Length::getUnit)
        .def("inUnit", &Length::in)
        .def("inMeters", &Length::inMeters)
        .def("inKilometers", &Length::inKilometers)
        .def("toString", &Length::toString, LibraryPhysicsPy_Units_Length_toString_overloads())

        .def("Undefined", &Length::Undefined).staticmethod("Undefined")
        .def("Millimeters", &Length::Millimeters).staticmethod("Millimeters")
        .def("Meters", &Length::Meters).staticmethod("Meters")
        .def("Kilometers", &Length::Kilometers).staticmethod("Kilometers")
        .def("Parse", &Length::Parse).staticmethod("Parse")
        .def("StringFromUnit", &Length::StringFromUnit).staticmethod("StringFromUnit")
        .def("SymbolFromUnit", &Length::SymbolFromUnit).staticmethod("SymbolFromUnit")

    ;

    enum_<Length::Unit>("Unit")

        .value("Undefined", Length::Unit::Undefined)
        .value("Meter", Length::Unit::Meter)
        .value("Foot", Length::Unit::Foot)
        .value("TerrestrialMile", Length::Unit::TerrestrialMile)
        .value("NauticalMile", Length::Unit::NauticalMile)
        .value("AstronomicalUnit", Length::Unit::AstronomicalUnit)

    ;

    // using library::core::ctnr::Array ;

    // IterableConverter()

    //     .from_python<Array<Length>>()
    //     .to_python<Array<Length>>()

    // ;

    using library::math::obj::Interval ;

    class_<Interval<Length>>("Interval", init<const Length&, const Length&, const Interval<Length>::Type&>())

        .def(self == self)
        .def(self != self)

        .def("isDefined", &Interval<Length>::isDefined)
        .def("isDegenerate", &Interval<Length>::isDegenerate)
        .def("intersects", &Interval<Length>::intersects)
        .def("containsLength", +[] (const Interval<Length>& anInterval, const Length& aLength) -> bool { return anInterval.contains(aLength) ; })
        .def("containsInterval", +[] (const Interval<Length>& anInterval, const Interval<Length>& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

        .def("getLowerBound", &Interval<Length>::getLowerBound)
        .def("getUpperBound", &Interval<Length>::getUpperBound)

        .def("Undefined", &Interval<Length>::Undefined).staticmethod("Undefined")
        .def("Closed", &Interval<Length>::Closed).staticmethod("Closed")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
