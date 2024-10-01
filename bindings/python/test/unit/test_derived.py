# Apache License 2.0

from ostk.physics.unit import Length
from ostk.physics.unit import Time
from ostk.physics.unit import Angle
from ostk.physics.unit import Mass
from ostk.physics.unit import Derived


class TestDerived:
    def test_derived_square_meter(self):
        derived_unit: Derived.Unit = Derived.Unit.square_meter()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_cubic_meter(self):
        derived_unit: Derived.Unit = Derived.Unit.cubic_meter()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_hertz(self):
        derived_unit: Derived.Unit = Derived.Unit.hertz()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_watt(self):
        derived_unit: Derived.Unit = Derived.Unit.watt()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_tesla(self):
        derived_unit: Derived.Unit = Derived.Unit.tesla()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_newton(self):
        derived_unit: Derived.Unit = Derived.Unit.newton()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_kilogram_per_second(self):
        derived_unit: Derived.Unit = Derived.Unit.kilogram_per_second()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_meter_per_second(self):
        derived_unit: Derived.Unit = Derived.Unit.meter_per_second()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_meter_per_second_squared(self):
        derived_unit: Derived.Unit = Derived.Unit.meter_per_second_squared()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_meter_cubed_per_second_squared(self):
        derived_unit: Derived.Unit = Derived.Unit.meter_cubed_per_second_squared()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_radian_per_second(self):
        derived_unit: Derived.Unit = Derived.Unit.radian_per_second()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_revolution_per_day(self):
        derived_unit: Derived.Unit = Derived.Unit.revolution_per_day()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_velocity(self):
        derived_unit: Derived.Unit = Derived.Unit.velocity(
            Length.Unit.Meter, Time.Unit.Second
        )

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_acceleration(self):
        derived_unit: Derived.Unit = Derived.Unit.acceleration(
            Length.Unit.Meter, Time.Unit.Second
        )

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_angular_velocity(self):
        derived_unit: Derived.Unit = Derived.Unit.angular_velocity(
            Angle.Unit.Revolution, Time.Unit.Day
        )

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_gravitational_parameter(self):
        derived_unit: Derived.Unit = Derived.Unit.gravitational_parameter(
            Length.Unit.Meter, Time.Unit.Second
        )

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_force(self):
        derived_unit: Derived.Unit = Derived.Unit.force(
            Mass.Unit.Kilogram, Length.Unit.Meter, Time.Unit.Second
        )

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_derived_mass_flow_rate(self):
        derived_unit: Derived.Unit = Derived.Unit.mass_flow_rate(
            Mass.Unit.Kilogram, Time.Unit.Second
        )

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)

    def test_unit_derived_unit_undefined(self):
        derived_unit: Derived.Unit = Derived.Unit.undefined()

        assert derived_unit is not None
        assert isinstance(derived_unit, Derived.Unit)
        assert derived_unit.is_defined() is False

    def test_unit_derived_unit_comparators(self):
        derived_unit: Derived.Unit = Derived.Unit.square_meter()

        assert derived_unit == derived_unit
        assert (derived_unit != derived_unit) is False

    # TBI: add these tests
    # def test_unit_derived_unit_is_compatible_with(self):
    #     pass

    # def test_unit_derived_unit_to_string(self):
    #     pass

    # def test_unit_derived_unit_get_symbol(self):
    #     pass
