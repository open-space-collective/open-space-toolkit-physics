################################################################################################################################################################

# @project        Library ▸ Physics
# @file           library/physics/time/test_interval.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from Library.Physics.Time import Scale
from Library.Physics.Time import Instant
from Library.Physics.Time import Duration
from Library.Physics.Time import Interval

################################################################################################################################################################

def test_interval_constructors ():

    assert Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed) is not None

################################################################################################################################################################

def test_interval_undefined ():

    assert Interval.Undefined() is not None

################################################################################################################################################################

def test_interval_closed ():

    assert Interval.Closed(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0)) is not None

################################################################################################################################################################

def test_interval_operators ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert (interval == interval) is not None
    assert (interval != interval) is not None

################################################################################################################################################################

def test_interval_is_defined ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.isDefined() is not None

################################################################################################################################################################

def test_interval_is_degenerate ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.isDegenerate() is not None

################################################################################################################################################################

def test_interval_intersects ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.intersects(interval) is not None

################################################################################################################################################################

def test_interval_contains_instant ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.containsInstant(Instant.J2000()) is not None

################################################################################################################################################################

def test_interval_contains_interval ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.containsInterval(interval) is not None

################################################################################################################################################################

def test_interval_get_start ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.getStart() is not None

################################################################################################################################################################

def test_interval_get_end ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.getEnd() is not None

################################################################################################################################################################

def test_interval_get_duration ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.getDuration() is not None

################################################################################################################################################################

def test_interval_get_center ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.getCenter() is not None

################################################################################################################################################################

def test_interval_to_string ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.toString() is not None
    assert interval.toString(Scale.UTC) is not None

################################################################################################################################################################

def test_interval_generate_grid ():

    interval = Interval(Instant.J2000(), Instant.J2000() + Duration.Minutes(1.0), Interval.Type.Closed)

    assert interval.generateGrid(Duration.Seconds(1.0)) is not None

################################################################################################################################################################
