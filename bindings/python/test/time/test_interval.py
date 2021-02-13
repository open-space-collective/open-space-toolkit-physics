################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/time/test_interval.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.physics.time import Scale
from ostk.physics.time import Instant
from ostk.physics.time import Duration
from ostk.physics.time import Interval

################################################################################################################################################################

def test_interval_constructors ():

    assert Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed) is not None

################################################################################################################################################################

def test_interval_undefined ():

    assert Interval.undefined() is not None

################################################################################################################################################################

def test_interval_closed ():

    assert Interval.closed(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0)) is not None

################################################################################################################################################################

def test_interval_operators ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert (interval == interval) is not None
    assert (interval != interval) is not None

################################################################################################################################################################

def test_interval_is_defined ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.is_defined() is not None

################################################################################################################################################################

def test_interval_is_degenerate ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.is_degenerate() is not None

################################################################################################################################################################

@pytest.mark.skip
def test_interval_intersects ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.intersects(interval) is not None

################################################################################################################################################################

def test_interval_contains_instant ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.contains_instant(Instant.J2000()) is not None

################################################################################################################################################################

def test_interval_contains_interval ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.contains_interval(interval) is not None

################################################################################################################################################################

def test_interval_get_start ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.get_start() is not None

################################################################################################################################################################

def test_interval_get_end ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.get_end() is not None

################################################################################################################################################################

def test_interval_get_duration ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.get_duration() is not None

################################################################################################################################################################

def test_interval_get_center ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.get_center() is not None

################################################################################################################################################################

def test_interval_to_string ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    assert interval.to_string() is not None
    assert interval.to_string(Scale.UTC) is not None

################################################################################################################################################################

def test_interval_generate_grid ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed)

    grid = interval.generate_grid(Duration.seconds(1.0))

    assert grid is not None
    assert isinstance(grid, list)
    assert isinstance(grid[0], Instant)

################################################################################################################################################################
