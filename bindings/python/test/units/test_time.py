################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/units/test_time.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import ostk.physics as physics

################################################################################################################################################################

Time = physics.units.Time
Unit = Time.Unit

################################################################################################################################################################

def test_units_time_unit ():

    enum_members = Unit.__members__

    list_keys = [
        "Undefined",
        "Nanosecond",
        "Microsecond",
        "Millisecond",
        "Second",
        "Minute",
        "Hour",
        "Day",
        "Week"
    ]

    list_values = [
       Unit.Undefined,
       Unit.Nanosecond,
       Unit.Microsecond,
       Unit.Millisecond,
       Unit.Second,
       Unit.Minute,
       Unit.Hour,
       Unit.Day,
       Unit.Week
    ]

    assert enum_members is not None
    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values

################################################################################################################################################################

def test_units_time_constructors ():

    time: Time = Time(3.2, Unit.Nanosecond)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Microsecond)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Millisecond)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Second)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Minute)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Hour)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Day)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Week)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    time: Time = Time(3.2, Unit.Undefined)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined() is False

################################################################################################################################################################

def test_units_time_is_defined():

    assert Time(2.0, Unit.Second).is_defined()
    assert Time.undefined().is_defined() is False

################################################################################################################################################################
