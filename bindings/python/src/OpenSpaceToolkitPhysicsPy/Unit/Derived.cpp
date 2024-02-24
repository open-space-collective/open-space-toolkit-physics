/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Derived(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;

    using ostk::physics::unit::Length;
    using ostk::physics::unit::Mass;
    using ostk::physics::unit::Time;
    using ostk::physics::unit::ElectricCurrent;
    using ostk::physics::unit::Angle;
    using ostk::physics::unit::Derived;

    class_<Derived> derived_class(aModule, "Derived");

    derived_class
        .def(init<Real, Derived::Unit>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Derived>))
        .def(
            "__repr__",
            +[](const Derived& aDerived) -> std::string
            {
                return aDerived.toString();
            }
        )

        .def("is_defined", &Derived::isDefined)

        .def("get_unit", &Derived::getUnit)
        .def("in_unit", &Derived::in)
        .def("to_string", &Derived::toString, "aPrecision"_a = Integer::Undefined())

        .def_static("undefined", &Derived::Undefined)
        // .def_static("parse", &Derived::Parse)
        .def_static("string_from_unit", &Derived::StringFromUnit)
        .def_static("symbol_from_unit", &Derived::SymbolFromUnit)

        ;

    class_<Derived::Order>(derived_class, "Order")

        .def(init<int>())

        .def(init<int, int>())

        .def(self == self)
        .def(self != self)

        .def("is_zero", &Derived::Order::isZero)
        .def("is_unity", &Derived::Order::isUnity)

        .def("get_numerator", &Derived::Order::getNumerator)
        .def("get_denominator", &Derived::Order::getDenominator)
        .def("get_value", &Derived::Order::getValue)
        .def("to_string", &Derived::Order::toString)

        .def_static("zero", &Derived::Order::Zero)
        .def_static("one", &Derived::Order::One)
        .def_static("two", &Derived::Order::Two)

        ;

    class_<Derived::Unit>(derived_class, "Unit")

        .def(init<
             const Length::Unit&,
             const Derived::Order&,
             const Mass::Unit&,
             const Derived::Order&,
             const Time::Unit&,
             const Derived::Order&,
             const ElectricCurrent::Unit&,
             const Derived::Order&,
             const Angle::Unit&,
             const Derived::Order&>())

        .def(self == self)
        .def(self != self)

        .def("is_defined", &Derived::Unit::isDefined)
        .def("is_compatible_with", &Derived::Unit::isCompatibleWith)

        // .def("access_length_unit", &Derived::Unit::accessLengthUnit, return_value_policy::reference)
        // .def("access_length_order", &Derived::Unit::accessLengthOrder, return_value_policy::reference)
        // .def("access_mass_unit", &Derived::Unit::accessMassUnit, return_value_policy::reference)
        // .def("access_mass_order", &Derived::Unit::accessMassOrder, return_value_policy::reference)
        // .def("access_time_unit", &Derived::Unit::accessTimeUnit, return_value_policy::reference)
        // .def("access_time_order", &Derived::Unit::accessTimeOrder, return_value_policy::reference)
        // .def("access_angle_unit", &Derived::Unit::accessAngleUnit, return_value_policy::reference)
        // .def("access_angle_order", &Derived::Unit::accessAngleOrder, return_value_policy::reference)
        .def("to_string", &Derived::Unit::toString)
        .def("get_symbol", &Derived::Unit::getSymbol)

        // Static constructors for specifying actual named S.I. units
        .def_static("square_meter", &Derived::Unit::SquareMeter)
        .def_static("cubic_meter", &Derived::Unit::CubicMeter)
        .def_static("hertz", &Derived::Unit::Hertz)
        .def_static("watt", &Derived::Unit::Watt)
        .def_static("tesla", &Derived::Unit::Tesla)
        .def_static("newton", &Derived::Unit::Newton)
        .def_static("kilogram_per_second", &Derived::Unit::KilogramPerSecond)

        // Static constructors for specifying derived (non-base) quantities
        .def_static("velocity", &Derived::Unit::Velocity, arg("length"), arg("time"))
        .def_static("acceleration", &Derived::Unit::Acceleration, arg("length"), arg("time"))
        .def_static("angular_velocity", &Derived::Unit::AngularVelocity, arg("angle"), arg("time"))
        .def_static("gravitational_parameter", &Derived::Unit::GravitationalParameter, arg("length"), arg("time"))
        .def_static("force", &Derived::Unit::Force, arg("mass"), arg("length"), arg("time"))
        .def_static("mass_flow_rate", &Derived::Unit::MassFlowRate, arg("mass"), arg("time"))
        .def_static("mass_density", &Derived::Unit::MassDensity, arg("mass"), arg("length"))

        .def_static("undefined", &Derived::Unit::Undefined)

        // .def_static("parse", &Derived::Unit::Parse)

        ;
}
