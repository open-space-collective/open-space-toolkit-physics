////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           LibraryPhysicsPy/Units/Derived.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Units/Derived.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryPhysicsPy_Units_Derived_toString_overloads, library::physics::units::Derived::toString, 0, 1)

inline void                     LibraryPhysicsPy_Units_Derived              ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::physics::units::Length ;
    using library::physics::units::Mass ;
    using library::physics::units::Time ;
    using library::physics::units::Angle ;
    using library::physics::units::Derived ;

    scope in_Derived = class_<Derived>("Derived", init<Real, Derived::Unit>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Derived& aDerived) -> std::string { return aDerived.toString() ; })

        .def("isDefined", &Derived::isDefined)
        
        .def("getUnit", &Derived::getUnit)
        .def("inUnit", &Derived::in)
        .def("toString", &Derived::toString, LibraryPhysicsPy_Units_Derived_toString_overloads())
        
        .def("Undefined", &Derived::Undefined).staticmethod("Undefined")
        // .def("Parse", &Derived::Parse).staticmethod("Undefined")
        .def("StringFromUnit", &Derived::StringFromUnit).staticmethod("StringFromUnit")
        .def("SymbolFromUnit", &Derived::SymbolFromUnit).staticmethod("SymbolFromUnit")

    ;

    class_<Derived::Order>("Order", init<int>())

        .def(init<int, int>())

        .def(self == self)
        .def(self != self)

        .def("isZero", &Derived::Order::isZero)
        .def("isUnity", &Derived::Order::isUnity)
        
        .def("getNumerator", &Derived::Order::getNumerator)
        .def("getDenominator", &Derived::Order::getDenominator)
        .def("getValue", &Derived::Order::getValue)
        .def("toString", &Derived::Order::toString)
        
        .def("Zero", &Derived::Order::Zero).staticmethod("Zero")
        .def("One", &Derived::Order::One).staticmethod("One")
        .def("Two", &Derived::Order::Two).staticmethod("Two")

    ;

    class_<Derived::Unit>("Unit", init<const Length::Unit&, const Derived::Order&, const Mass::Unit&, const Derived::Order&, const Time::Unit&, const Derived::Order&, const Angle::Unit&, const Derived::Order&>())

        .def(self == self)
        .def(self != self)

        .def("isDefined", &Derived::Unit::isDefined)
        .def("isCompatibleWith", &Derived::Unit::isCompatibleWith)

        // .def("accessLengthUnit", &Derived::Unit::accessLengthUnit, return_value_policy<reference_existing_object>())
        // .def("accessLengthOrder", &Derived::Unit::accessLengthOrder, return_value_policy<reference_existing_object>())
        // .def("accessMassUnit", &Derived::Unit::accessMassUnit, return_value_policy<reference_existing_object>())
        // .def("accessMassOrder", &Derived::Unit::accessMassOrder, return_value_policy<reference_existing_object>())
        // .def("accessTimeUnit", &Derived::Unit::accessTimeUnit, return_value_policy<reference_existing_object>())
        // .def("accessTimeOrder", &Derived::Unit::accessTimeOrder, return_value_policy<reference_existing_object>())
        // .def("accessAngleUnit", &Derived::Unit::accessAngleUnit, return_value_policy<reference_existing_object>())
        // .def("accessAngleOrder", &Derived::Unit::accessAngleOrder, return_value_policy<reference_existing_object>())
        .def("toString", &Derived::Unit::toString)
        .def("getSymbol", &Derived::Unit::getSymbol)
        
        .def("Undefined", &Derived::Unit::Undefined).staticmethod("Undefined")
        .def("SquareMeter", &Derived::Unit::SquareMeter).staticmethod("SquareMeter")
        .def("CubicMeter", &Derived::Unit::CubicMeter).staticmethod("CubicMeter")
        .def("Hertz", &Derived::Unit::Hertz).staticmethod("Hertz")
        .def("Watt", &Derived::Unit::Watt).staticmethod("Watt")
        .def("Velocity", &Derived::Unit::Velocity).staticmethod("Velocity")
        .def("AngularVelocity", &Derived::Unit::AngularVelocity).staticmethod("AngularVelocity")
        // .def("Parse", &Derived::Unit::Parse).staticmethod("Parse")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////