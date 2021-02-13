################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/units/test_derived.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import ostk.physics as physics

################################################################################################################################################################

Length = physics.units.Length
Time = physics.units.Time
Angle = physics.units.Angle
Derived = physics.units.Derived

################################################################################################################################################################

def test_units_derived_unit_constructors ():

    # square_meter
    derived_unit: Derived.Unit = Derived.Unit.square_meter()

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # cubic_meter
    derived_unit: Derived.Unit = Derived.Unit.cubic_meter()

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # hertz
    derived_unit: Derived.Unit = Derived.Unit.hertz()

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # watt
    derived_unit: Derived.Unit = Derived.Unit.watt()

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # tesla
    derived_unit: Derived.Unit = Derived.Unit.tesla()

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # velocity
    derived_unit: Derived.Unit = Derived.Unit.velocity(Length.Unit.Meter, Time.Unit.Second)

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # acceleration
    derived_unit: Derived.Unit = Derived.Unit.acceleration(Length.Unit.Meter, Time.Unit.Second)

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # gravitational_parameter
    derived_unit: Derived.Unit = Derived.Unit.gravitational_parameter(Length.Unit.Meter, Time.Unit.Second)

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

    # angular_velocity
    derived_unit: Derived.Unit = Derived.Unit.angular_velocity(Angle.Unit.Revolution, Time.Unit.Day)

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)

################################################################################################################################################################

def test_units_derived_unit_undefined ():

    derived_unit: Derived.Unit = Derived.Unit.undefined()

    assert derived_unit is not None
    assert isinstance(derived_unit, Derived.Unit)
    assert derived_unit.is_defined() is False

################################################################################################################################################################

def test_units_derived_unit_comparators ():

    derived_unit: Derived.Unit = Derived.Unit.square_meter()

    assert derived_unit == derived_unit
    assert (derived_unit != derived_unit) is False

################################################################################################################################################################

def test_units_derived_unit_is_compatible_with ():

    pass

################################################################################################################################################################

def test_units_derived_unit_to_string ():

    pass

################################################################################################################################################################

def test_units_derived_unit_get_symbol ():

    pass

################################################################################################################################################################
