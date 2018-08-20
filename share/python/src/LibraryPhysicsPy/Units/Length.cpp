////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Units/Length.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Length.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

        .def("isDefined", &Length::isDefined)

        .def("getUnit", &Length::getUnit)
        .def("in", &Length::in)
        .def("inMeters", &Length::inMeters)
        .def("inKilometers", &Length::inKilometers)
        .def("toString", &Length::toString)
        
        .def("Undefined", &Length::Undefined).staticmethod("Undefined")
        .def("Millimeters", &Length::Millimeters).staticmethod("Millimeters")
        .def("Meters", &Length::Meters).staticmethod("Meters")
        .def("Kilometers", &Length::Kilometers).staticmethod("Kilometers")
        // .def("Parse", &Length::Parse).staticmethod("Parse")
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

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////