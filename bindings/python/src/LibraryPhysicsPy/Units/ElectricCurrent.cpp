////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           LibraryPhysicsPy/Units/ElectricCurrent.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryPhysicsPy/Utilities/IterableConverter.hpp>

#include <Library/Physics/Units/ElectricCurrent.hpp>

#include <Library/Mathematics/Objects/Interval.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Units_ElectricCurrent_toString_overloads, library::physics::units::ElectricCurrent::toString, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Units_ElectricCurrent_Interval_toString_overloads, library::math::obj::Interval<library::physics::units::ElectricCurrent>::toString, 0, 1)

inline void                     LibraryPhysicsPy_Units_ElectricCurrent      ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::physics::units::ElectricCurrent ;

    scope in_ElectricCurrent = class_<ElectricCurrent>("ElectricCurrent", init<Real, ElectricCurrent::Unit>())

        .def(self == self)
        .def(self != self)

        // .def(self < self)
        // .def(self <= self)
        // .def(self > self)
        // .def(self >= self)

        // .def(self + self)
        // .def(self - self)

        // .def(self * other<Real>())
        // .def(self / other<Real>())

        // .def(self += self)
        // .def(self -= self)

        // .def(self *= other<Real>())
        // .def(self /= other<Real>())

        // .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const ElectricCurrent& aElectricCurrent) -> std::string { return aElectricCurrent.toString() ; })

        .def("isDefined", &ElectricCurrent::isDefined)

        .def("getUnit", &ElectricCurrent::getUnit)
        .def("inUnit", &ElectricCurrent::in)
        .def("inAmperes", &ElectricCurrent::inAmperes)
        .def("toString", &ElectricCurrent::toString, LibraryPhysicsPy_Units_ElectricCurrent_toString_overloads())

        .def("Undefined", &ElectricCurrent::Undefined).staticmethod("Undefined")
        .def("Amperes", &ElectricCurrent::Amperes).staticmethod("Amperes")
        // .def("Parse", &ElectricCurrent::Parse).staticmethod("Parse")
        .def("StringFromUnit", &ElectricCurrent::StringFromUnit).staticmethod("StringFromUnit")
        .def("SymbolFromUnit", &ElectricCurrent::SymbolFromUnit).staticmethod("SymbolFromUnit")

    ;

    enum_<ElectricCurrent::Unit>("Unit")

        .value("Undefined", ElectricCurrent::Unit::Undefined)
        .value("Ampere", ElectricCurrent::Unit::Ampere)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
