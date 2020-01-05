////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           bindings/python/src/OpenSpaceToolkitPhysicsPy/Units/Derived.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitPhysicsPy_Units_Derived_toString_overloads, ostk::physics::units::Derived::toString, 0, 1)

inline void                     OpenSpaceToolkitPhysicsPy_Units_Derived              ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::physics::units::Length ;
    using ostk::physics::units::Mass ;
    using ostk::physics::units::Time ;
    using ostk::physics::units::ElectricCurrent ;
    using ostk::physics::units::Angle ;
    using ostk::physics::units::Derived ;

    scope in_Derived = class_<Derived>("Derived", init<Real, Derived::Unit>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Derived& aDerived) -> std::string { return aDerived.toString() ; })

        .def("is_defined", &Derived::isDefined)

        .def("get_unit", &Derived::getUnit)
        .def("in_unit", &Derived::in)
        .def("to_string", &Derived::toString, OpenSpaceToolkitPhysicsPy_Units_Derived_toString_overloads())

        .def("undefined", &Derived::Undefined).staticmethod("undefined")
        // .def("parse", &Derived::Parse).staticmethod("undefined")
        .def("string_from_unit", &Derived::StringFromUnit).staticmethod("string_from_unit")
        .def("symbol_from_unit", &Derived::SymbolFromUnit).staticmethod("symbol_from_unit")

    ;

    class_<Derived::Order>("Order", init<int>())

        .def(init<int, int>())

        .def(self == self)
        .def(self != self)

        .def("is_zero", &Derived::Order::isZero)
        .def("is_unity", &Derived::Order::isUnity)

        .def("get_numerator", &Derived::Order::getNumerator)
        .def("get_denominator", &Derived::Order::getDenominator)
        .def("get_value", &Derived::Order::getValue)
        .def("to_string", &Derived::Order::toString)

        .def("zero", &Derived::Order::Zero).staticmethod("zero")
        .def("one", &Derived::Order::One).staticmethod("one")
        .def("two", &Derived::Order::Two).staticmethod("two")

    ;

    class_<Derived::Unit>("Unit", init<const Length::Unit&, const Derived::Order&, const Mass::Unit&, const Derived::Order&, const Time::Unit&, const Derived::Order&, const ElectricCurrent::Unit&, const Derived::Order&, const Angle::Unit&, const Derived::Order&>())

        .def(self == self)
        .def(self != self)

        .def("is_defined", &Derived::Unit::isDefined)
        .def("is_compatible_with", &Derived::Unit::isCompatibleWith)

        // .def("access_length_unit", &Derived::Unit::accessLengthUnit, return_value_policy<reference_existing_object>())
        // .def("access_length_order", &Derived::Unit::accessLengthOrder, return_value_policy<reference_existing_object>())
        // .def("access_mass_unit", &Derived::Unit::accessMassUnit, return_value_policy<reference_existing_object>())
        // .def("access_mass_order", &Derived::Unit::accessMassOrder, return_value_policy<reference_existing_object>())
        // .def("access_time_unit", &Derived::Unit::accessTimeUnit, return_value_policy<reference_existing_object>())
        // .def("access_time_order", &Derived::Unit::accessTimeOrder, return_value_policy<reference_existing_object>())
        // .def("access_angle_unit", &Derived::Unit::accessAngleUnit, return_value_policy<reference_existing_object>())
        // .def("access_angle_order", &Derived::Unit::accessAngleOrder, return_value_policy<reference_existing_object>())
        .def("to_string", &Derived::Unit::toString)
        .def("get_symbol", &Derived::Unit::getSymbol)

        .def("undefined", &Derived::Unit::Undefined).staticmethod("undefined")
        .def("square_meter", &Derived::Unit::SquareMeter).staticmethod("square_meter")
        .def("cubic_meter", &Derived::Unit::CubicMeter).staticmethod("cubic_meter")
        .def("hertz", &Derived::Unit::Hertz).staticmethod("hertz")
        .def("watt", &Derived::Unit::Watt).staticmethod("watt")
        .def("tesla", &Derived::Unit::Tesla).staticmethod("tesla")
        .def("velocity", &Derived::Unit::Velocity).staticmethod("velocity")
        .def("acceleration", &Derived::Unit::Acceleration).staticmethod("acceleration")
        .def("gravitational_parameter", &Derived::Unit::GravitationalParameter).staticmethod("gravitational_parameter")
        .def("angular_velocity", &Derived::Unit::AngularVelocity).staticmethod("angular_velocity")
        // .def("parse", &Derived::Unit::Parse).staticmethod("parse")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
