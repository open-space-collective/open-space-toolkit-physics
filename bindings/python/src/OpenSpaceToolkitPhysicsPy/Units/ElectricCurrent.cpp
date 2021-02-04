////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Units/ElectricCurrent.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Units/ElectricCurrent.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitPhysicsPy_Units_ElectricCurrent (        pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;

    using ostk::physics::units::ElectricCurrent ;

    class_<ElectricCurrent> elec_current(aModule, "ElectricCurrent") ;

    elec_current.def(init<Real, ElectricCurrent::Unit>())

        // .def(self == self)
        // .def(self != self)

        // .def(self < self)
        // .def(self <= self)
        // .def(self > self)
        // .def(self >= self)

        // .def(self + self)
        // .def(self - self)

        // .def(self += self)
        // .def(self -= self)

        // .def("__mul__", [](const ElectricCurrent &anElectricCurrent, Real aReal) {return anElectricCurrent * aReal;}, is_operator())
        // .def("__truediv__", [](const ElectricCurrent &anElectricCurrent, Real aReal) {return anElectricCurrent / aReal;}, is_operator())
        // .def("__imul__", [](const ElectricCurrent &anElectricCurrent, Real aReal) {return anElectricCurrent * aReal;}, is_operator())
        // .def("__itruediv__", [](const ElectricCurrent &anElectricCurrent, Real aReal) {return anElectricCurrent / aReal;}, is_operator())

        // .def("__str__", &(shiftToString<ElectricCurrent>))
        .def("__repr__", +[] (const ElectricCurrent& aElectricCurrent) -> std::string { return aElectricCurrent.toString() ; })

        .def("is_defined", &ElectricCurrent::isDefined)

        .def("get_unit", &ElectricCurrent::getUnit)
        .def("in_unit", &ElectricCurrent::in)
        .def("in_amperes", &ElectricCurrent::inAmperes)
        .def("to_string", &ElectricCurrent::toString, "aPrecision"_a=Integer::Undefined())
        // .def("to_string", &ElectricCurrent::toString, OpenSpaceToolkitPhysicsPy_Units_ElectricCurrent_toString_overloads())

        .def_static("undefined", &ElectricCurrent::Undefined)
        .def_static("amperes", &ElectricCurrent::Amperes)
        // .def_static("parse", &ElectricCurrent::Parse)
        .def_static("string_from_unit", &ElectricCurrent::StringFromUnit)
        .def_static("symbol_from_unit", &ElectricCurrent::SymbolFromUnit)

    ;

    enum_<ElectricCurrent::Unit> (elec_current, "Unit")

        .value("Undefined", ElectricCurrent::Unit::Undefined)
        .value("Ampere", ElectricCurrent::Unit::Ampere)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
