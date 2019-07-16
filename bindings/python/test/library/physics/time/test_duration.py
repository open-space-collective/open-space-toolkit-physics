################################################################################################################################################################

# @project        Library ▸ Physics
# @file           library/physics/time/test_duration.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from Library.Physics.Units import Time
from Library.Physics.Time import Instant
from Library.Physics.Time import Duration

################################################################################################################################################################

def test_duration_undefined ():

    assert Duration.Undefined() is not None

################################################################################################################################################################

def test_duration_zero ():

    assert Duration.Zero() is not None

################################################################################################################################################################

def test_duration_nanoseconds ():

    assert Duration.Nanoseconds(123.456) is not None

################################################################################################################################################################

def test_duration_microseconds ():

    assert Duration.Microseconds(123.456) is not None

################################################################################################################################################################

def test_duration_milliseconds ():

    assert Duration.Milliseconds(123.456) is not None

################################################################################################################################################################

def test_duration_seconds ():

    assert Duration.Seconds(123.456) is not None

################################################################################################################################################################

def test_duration_minutes ():

    assert Duration.Minutes(123.456) is not None

################################################################################################################################################################

def test_duration_hours ():

    assert Duration.Hours(123.456) is not None

################################################################################################################################################################

def test_duration_days ():

    assert Duration.Days(123.456) is not None

################################################################################################################################################################

def test_duration_weeks ():

    assert Duration.Weeks(123.456) is not None

################################################################################################################################################################

def test_duration_between ():

    assert Duration.Between(Instant.Now(), Instant.Now()) is not None

################################################################################################################################################################

def test_duration_parse ():

    assert Duration.Parse('02:03.456.000.000') is not None
    assert Duration.Parse('02:03.456.000.000', Duration.Format.Standard) is not None
    assert Duration.Parse('PT2M3.456S', Duration.Format.ISO8601) is not None

################################################################################################################################################################

def test_duration_operators ():

    duration_A = Duration.Seconds(123)
    duration_B = Duration.Seconds(456)

    assert (duration_A == duration_B) is not None
    assert (duration_A != duration_B) is not None

    assert (duration_A < duration_B) is not None
    assert (duration_A <= duration_B) is not None
    assert (duration_A > duration_B) is not None
    assert (duration_A >= duration_B) is not None

    assert (duration_A + duration_B) is not None
    assert (duration_A - duration_B) is not None

    assert (duration_A * 2.0) is not None
    assert (duration_A / 2.0) is not None

    duration_A += duration_B
    duration_A -= duration_B

    duration_A *= 2.0
    duration_A /= 2.0

################################################################################################################################################################

def test_duration_is_defined ():

    assert Duration.Seconds(123).isDefined() is not None

################################################################################################################################################################

def test_duration_is_zero ():

    assert Duration.Seconds(123).isZero() is not None

################################################################################################################################################################

def test_duration_is_positive ():

    assert Duration.Seconds(123).isPositive() is not None

################################################################################################################################################################

def test_duration_is_strictly_positive ():

    assert Duration.Seconds(123).isStrictlyPositive() is not None

################################################################################################################################################################

def test_duration_is_near ():

    assert Duration.Seconds(123).isNear(Duration.Seconds(123), Duration.Zero()) is not None

################################################################################################################################################################

def test_duration_get_nanoseconds ():

    assert Duration.Seconds(123).getNanoseconds() is not None

################################################################################################################################################################

def test_duration_get_microseconds ():

    assert Duration.Seconds(123).getMicroseconds() is not None

################################################################################################################################################################

def test_duration_get_milliseconds ():

    assert Duration.Seconds(123).getMilliseconds() is not None

################################################################################################################################################################

def test_duration_get_seconds ():

    assert Duration.Seconds(123).getSeconds() is not None

################################################################################################################################################################

def test_duration_get_minutes ():

    assert Duration.Seconds(123).getMinutes() is not None

################################################################################################################################################################

def test_duration_get_hours ():

    assert Duration.Seconds(123).getHours() is not None

################################################################################################################################################################

def test_duration_get_days ():

    assert Duration.Seconds(123).getDays() is not None

################################################################################################################################################################

def test_duration_get_weeks ():

    assert Duration.Seconds(123).getWeeks() is not None

################################################################################################################################################################

def test_duration_in_nanoseconds ():

    assert Duration.Seconds(123).inNanoseconds() is not None

################################################################################################################################################################

def test_duration_in_microseconds ():

    assert Duration.Seconds(123).inMicroseconds() is not None

################################################################################################################################################################

def test_duration_in_milliseconds ():

    assert Duration.Seconds(123).inMilliseconds() is not None

################################################################################################################################################################

def test_duration_in_seconds ():

    assert Duration.Seconds(123).inSeconds() is not None

################################################################################################################################################################

def test_duration_in_minutes ():

    assert Duration.Seconds(123).inMinutes() is not None

################################################################################################################################################################

def test_duration_in_hours ():

    assert Duration.Seconds(123).inHours() is not None

################################################################################################################################################################

def test_duration_in_days ():

    assert Duration.Seconds(123).inDays() is not None

################################################################################################################################################################

def test_duration_in_weeks ():

    assert Duration.Seconds(123).inWeeks() is not None

################################################################################################################################################################

def test_duration_in_unit ():

    assert Duration.Seconds(123).inUnit(Time.Unit.Second) is not None

################################################################################################################################################################

def test_duration_get_absolute ():

    assert Duration.Seconds(123).getAbsolute() is not None

################################################################################################################################################################

def test_duration_to_string ():

    assert Duration.Seconds(123).toString() is not None
    assert Duration.Seconds(123).toString(Duration.Format.Standard)
    assert Duration.Seconds(123).toString(Duration.Format.ISO8601)

################################################################################################################################################################
