/// Apache License 2.0

#include <pybind11/stl.h>

#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

inline void OpenSpaceToolkitPhysicsPy_Unit_Derived(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::physics::unit::Angle;
    using ostk::physics::unit::Derived;
    using ostk::physics::unit::ElectricCurrent;
    using ostk::physics::unit::Length;
    using ostk::physics::unit::Mass;
    using ostk::physics::unit::Time;

    class_<Derived> derived_class(
        aModule,
        "Derived",
        R"doc(
            Derived unit.

            :reference: https://en.wikipedia.org/wiki/SI_derived_unit
        )doc"
    );

    derived_class
        .def(
            init<double, Derived::Unit>(),
            R"doc(
                Constructor.

                Args:
                    aValue (float): Value
                    aUnit (Unit): Unit
            )doc"
        )

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

        .def(
            "get_unit",
            &Derived::getUnit,
            R"doc(
                Get unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def(
            "in_unit",
            &Derived::in,
            R"doc(
                Convert to unit.

                Returns:
                    float: Value in unit.
            )doc"
        )
        .def(
            "to_string",
            &Derived::toString,
            "aPrecision"_a = -1,
            R"doc(
                Convert to string.

                Args:
                    aPrecision (int): Precision

                Returns:
                    str: String representation.
            )doc"
        )

        // .def_static("parse", &Derived::Parse)
        .def_static(
            "string_from_unit",
            &Derived::StringFromUnit,
            R"doc(
                Get string from unit.

                Args:
                    aUnit (Unit): Unit.

                Returns:
                    str: String.
            )doc"
        )
        .def_static(
            "symbol_from_unit",
            &Derived::SymbolFromUnit,
            R"doc(
                Get symbol from unit.

                Args:
                    aUnit (Unit): Unit.

                Returns:
                    str: Symbol.
            )doc"
        )

        ;

    class_<Derived::Order>(
        derived_class,
        "Order",
        R"doc(
            SI unit order.

        )doc"
    )

        .def(
            init<int>(),
            R"doc(
                Constructor.

                Args:
                    aValue (int): Value.
            )doc"
        )

        .def(
            init<int, int>(),
            R"doc(
                Constructor.

                Args:
                    aNumerator (int): Numerator.
                    aDenominator (int): Denominator.
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def(
            "is_zero",
            &Derived::Order::isZero,
            R"doc(
                Check if the order is zero.

                Returns:
                    bool: True if zero.
            )doc"
        )
        .def(
            "is_unity",
            &Derived::Order::isUnity,
            R"doc(
                Check if the order is unity.

                Returns:
                    bool: True if unity.
            )doc"
        )

        .def(
            "get_numerator",
            &Derived::Order::getNumerator,
            R"doc(
                Get numerator.

                Returns:
                    int: Numerator.
            )doc"
        )
        .def(
            "get_denominator",
            &Derived::Order::getDenominator,
            R"doc(
                Get denominator.

                Returns:
                    int: Denominator.
            )doc"
        )
        .def(
            "get_value",
            &Derived::Order::getValue,
            R"doc(
                Get value.

                Returns:
                    float: Value.
            )doc"
        )
        .def(
            "to_string",
            &Derived::Order::toString,
            R"doc(
                Convert to string.

                Returns:
                    str: String representation.
            )doc"
        )

        .def_static(
            "zero",
            &Derived::Order::Zero,
            R"doc(
                Create a zero order.

                Returns:
                    Order: Order.
            )doc"
        )
        .def_static(
            "one",
            &Derived::Order::One,
            R"doc(
                Create a unity order.

                Returns:
                    Order: Order.
            )doc"
        )
        .def_static(
            "two",
            &Derived::Order::Two,
            R"doc(
                Create a two order.

                Returns:
                    Order: Order.
            )doc"
        )

        ;

    class_<Derived::Unit>(
        derived_class,
        "Unit",
        R"doc(
            Unit
        )doc"
    )

        .def(
            init<
                const std::optional<Length::Unit>&,
                const Derived::Order&,
                const std::optional<Mass::Unit>&,
                const Derived::Order&,
                const std::optional<Time::Unit>&,
                const Derived::Order&,
                const std::optional<ElectricCurrent::Unit>&,
                const Derived::Order&,
                const std::optional<Angle::Unit>&,
                const Derived::Order&>(),
            arg("length_unit"),
            arg("length_order"),
            arg("mass_unit"),
            arg("mass_order"),
            arg("time_unit"),
            arg("time_order"),
            arg("electric_current_unit"),
            arg("electric_current_order"),
            arg("angle_unit"),
            arg("angle_order"),
            R"doc(
                Constructor.

                A dimension that is absent from the unit has a unit of None and an order of zero.

                Args:
                    length_unit (Length.Unit | None): Length unit.
                    length_order (Derived.Order): Length order.
                    mass_unit (Mass.Unit | None): Mass unit.
                    mass_order (Derived.Order): Mass order.
                    time_unit (Time.Unit | None): Time unit.
                    time_order (Derived.Order): Time order.
                    electric_current_unit (ElectricCurrent.Unit | None): Electric current unit.
                    electric_current_order (Derived.Order): Electric current order.
                    angle_unit (Angle.Unit | None): Angle unit.
                    angle_order (Derived.Order): Angle order.
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("is_compatible_with", &Derived::Unit::isCompatibleWith)

        // .def("access_length_unit", &Derived::Unit::accessLengthUnit, return_value_policy::reference)
        // .def("access_length_order", &Derived::Unit::accessLengthOrder, return_value_policy::reference)
        // .def("access_mass_unit", &Derived::Unit::accessMassUnit, return_value_policy::reference)
        // .def("access_mass_order", &Derived::Unit::accessMassOrder, return_value_policy::reference)
        // .def("access_time_unit", &Derived::Unit::accessTimeUnit, return_value_policy::reference)
        // .def("access_time_order", &Derived::Unit::accessTimeOrder, return_value_policy::reference)
        // .def("access_angle_unit", &Derived::Unit::accessAngleUnit, return_value_policy::reference)
        // .def("access_angle_order", &Derived::Unit::accessAngleOrder, return_value_policy::reference)
        .def(
            "to_string",
            &Derived::Unit::toString,
            R"doc(
                Convert to string.

                Returns:
                    str: String representation.
            )doc"
        )
        .def(
            "get_symbol",
            &Derived::Unit::getSymbol,
            R"doc(
                Get symbol.

                Returns:
                    str: Symbol.
            )doc"
        )

        // Static constructors for specifying actual named S.I. units
        .def_static(
            "square_meter",
            &Derived::Unit::SquareMeter,
            R"doc(
                Create a square meter unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "cubic_meter",
            &Derived::Unit::CubicMeter,
            R"doc(
                Create a cubic meter unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "hertz",
            &Derived::Unit::Hertz,
            R"doc(
                Create a hertz unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "watt",
            &Derived::Unit::Watt,
            R"doc(
                Create a watt unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "tesla",
            &Derived::Unit::Tesla,
            R"doc(
                Create a tesla unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "newton",
            &Derived::Unit::Newton,
            R"doc(
                Create a newton unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "kilogram_per_second",
            &Derived::Unit::KilogramPerSecond,
            R"doc(
                Create a kilogram per second unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "meter_per_second",
            &Derived::Unit::MeterPerSecond,
            R"doc(
                Create a meter per second unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "meter_per_second_squared",
            &Derived::Unit::MeterPerSecondSquared,
            R"doc(
                Create a meter per second squared unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "meter_cubed_per_second_squared",
            &Derived::Unit::MeterCubedPerSecondSquared,
            R"doc(
                Create a meter cubed per second squared unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "radian_per_second",
            &Derived::Unit::RadianPerSecond,
            R"doc(
                Create a radian per second unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "revolution_per_day",
            &Derived::Unit::RevolutionPerDay,
            R"doc(
                Create a revolution per day unit.

                Returns:
                    Unit: Unit.
            )doc"
        )

        // Static constructors for specifying derived (non-base) quantities
        .def_static(
            "velocity",
            &Derived::Unit::Velocity,
            arg("length"),
            arg("time"),
            R"doc(
                Create a velocity unit.

                Args:
                    length (Length::Unit): Length unit.
                    time (Time::Unit): Time unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "acceleration",
            &Derived::Unit::Acceleration,
            arg("length"),
            arg("time"),
            R"doc(
                Create an acceleration unit.

                Args:
                    length (Length::Unit): Length unit.
                    time (Time::Unit): Time unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "angular_velocity",
            &Derived::Unit::AngularVelocity,
            arg("angle"),
            arg("time"),
            R"doc(
                Create an angular velocity unit.

                Args:
                    angle (Angle::Unit): Angle unit.
                    time (Time::Unit): Time unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "gravitational_parameter",
            &Derived::Unit::GravitationalParameter,
            arg("length"),
            arg("time"),
            R"doc(
                Create a gravitational parameter unit.

                Args:
                    length (Length::Unit): Length unit.
                    time (Time::Unit): Time unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "force",
            &Derived::Unit::Force,
            arg("mass"),
            arg("length"),
            arg("time"),
            R"doc(
                Create a force unit.

                Args:
                    mass (Mass::Unit): Mass unit.
                    length (Length::Unit): Length unit.
                    time (Time::Unit): Time unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "mass_flow_rate",
            &Derived::Unit::MassFlowRate,
            arg("mass"),
            arg("time"),
            R"doc(
                Create a mass flow rate unit.

                Args:
                    mass (Mass::Unit): Mass unit.
                    time (Time::Unit): Time unit.

                Returns:
                    Unit: Unit.
            )doc"
        )
        .def_static(
            "mass_density",
            &Derived::Unit::MassDensity,
            arg("mass"),
            arg("length"),
            R"doc(
                Create a mass density unit.

                Args:
                    mass (Mass::Unit): Mass unit.
                    length (Length::Unit): Length unit.

                Returns:
                    Unit: Unit.
            )doc"
        )

        // .def_static("parse", &Derived::Unit::Parse)

        ;
}
