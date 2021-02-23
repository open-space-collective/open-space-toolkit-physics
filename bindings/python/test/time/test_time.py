################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/time/test_time.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.types import String

from ostk.physics.time import Time

################################################################################################################################################################

def test_time_constructors ():

    assert Time(0, 0, 0) is not None

################################################################################################################################################################

def test_time_undefined ():

    assert Time.undefined() is not None

################################################################################################################################################################

def test_time_midnight ():

    assert Time.midnight() is not None

################################################################################################################################################################

def test_time_noon ():

    assert Time.noon() is not None

################################################################################################################################################################

def test_time_parse ():

    ## Using python strings

    # Testing with default format argument (Time::Format::Undefined)
    time: Time = Time.parse('00:00:00')

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    # Testing with Time.Format.Standard
    time: Time = Time.parse('00:00:00', Time.Format.Standard)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    # Testing with Time.Format.ISO8601
    time: Time = Time.parse('00:00:00', Time.Format.ISO8601)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    ## Using String class

    # Testing with default format argument (Time::Format::Undefined)
    time: Time = Time.parse(String('00:00:00'))

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    # Testing with Time.Format.Standard
    time: Time = Time.parse(String('00:00:00'), Time.Format.Standard)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

    # Testing with Time.Format.ISO8601
    time: Time = Time.parse(String('00:00:00'), Time.Format.ISO8601)

    assert time is not None
    assert isinstance(time, Time)
    assert time.is_defined()

################################################################################################################################################################

def test_time_operators ():

    time = Time(0, 0, 0)

    assert (time == time) is not None
    assert (time != time) is not None

################################################################################################################################################################

def test_time_is_defined ():

    time = Time(0, 0, 0)

    assert time.is_defined() is not None

################################################################################################################################################################

def test_time_get_hour ():

    time = Time(0, 0, 0)

    assert time.get_hour() is not None

################################################################################################################################################################

def test_time_get_minute ():

    time = Time(0, 0, 0)

    assert time.get_minute() is not None

################################################################################################################################################################

def test_time_get_second ():

    time = Time(0, 0, 0)

    assert time.get_second() is not None

################################################################################################################################################################

def test_time_get_millisecond ():

    time = Time(0, 0, 0)

    assert time.get_millisecond() is not None

################################################################################################################################################################

def test_time_get_microsecond ():

    time = Time(0, 0, 0)

    assert time.get_microsecond() is not None

################################################################################################################################################################

def test_time_get_nanosecond ():

    time = Time(0, 0, 0)

    assert time.get_nanosecond() is not None

################################################################################################################################################################

def test_time_get_floating_seconds ():

    time = Time(0, 0, 0)

    assert time.get_floating_seconds() is not None

################################################################################################################################################################

def test_time_to_string ():

    time = Time(0, 0, 0)

    assert time.to_string() is not None
    assert time.to_string(Time.Format.Standard) is not None
    assert time.to_string(Time.Format.ISO8601) is not None

################################################################################################################################################################

def test_time_set_hour ():

    time = Time(0, 0, 0)

    time.set_hour(1)

################################################################################################################################################################

def test_time_set_minute ():

    time = Time(0, 0, 0)

    time.set_minute(1)

################################################################################################################################################################

def test_time_set_second ():

    time = Time(0, 0, 0)

    time.set_second(1)

################################################################################################################################################################

def test_time_set_millisecond ():

    time = Time(0, 0, 0)

    time.set_millisecond(1)

################################################################################################################################################################

def test_time_set_microsecond ():

    time = Time(0, 0, 0)

    time.set_microsecond(1)

################################################################################################################################################################

def test_time_set_nanosecond ():

    time = Time(0, 0, 0)

    time.set_nanosecond(1)

################################################################################################################################################################
