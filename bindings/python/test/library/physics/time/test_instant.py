################################################################################################################################################################

# @project        Library ▸ Physics
# @file           library/physics/time/test_instant.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import datetime
import pytest

from Library.Physics.Time import Scale
from Library.Physics.Time import Instant
from Library.Physics.Time import Duration
from Library.Physics.Time import DateTime

################################################################################################################################################################

def test_instant_undefined ():

    assert Instant.Undefined() is not None

################################################################################################################################################################

def test_instant_now ():

    assert Instant.Now() is not None

################################################################################################################################################################

def test_instant_j2000 ():

    assert Instant.J2000() is not None

################################################################################################################################################################

def test_instant_datetime ():

    assert Instant.DateTime(DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0), Scale.UTC) is not None

    assert Instant.DateTime(datetime.datetime.now(), Scale.UTC)

################################################################################################################################################################

def test_instant_julian_date ():

    assert Instant.JulianDate(2458119.5, Scale.UTC) is not None

################################################################################################################################################################

def test_instant_modified_julian_date ():

    assert Instant.ModifiedJulianDate(58119.0, Scale.UTC) is not None

################################################################################################################################################################

def test_instant_operators ():

    instant = Instant.J2000()

    assert (instant == instant) is not None
    assert (instant != instant) is not None


    assert (instant < instant) is not None
    assert (instant <= instant) is not None
    assert (instant > instant) is not None
    assert (instant >= instant) is not None

    assert (instant + Duration.Seconds(1.0)) is not None
    assert (instant - Duration.Seconds(1.0)) is not None

    assert (instant - instant) is not None

    instant += Duration.Seconds(1.0)
    instant -= Duration.Seconds(1.0)

################################################################################################################################################################

def test_instant_is_defined ():

    assert Instant.J2000().isDefined() is not None

################################################################################################################################################################

def test_instant_is_post_epoch ():

    assert Instant.J2000().isPostEpoch() is not None

################################################################################################################################################################

def test_instant_is_near ():

    assert Instant.J2000().isNear(Instant.J2000(), Duration.Zero()) is not None

################################################################################################################################################################

def test_instant_get_date_time ():

    assert Instant.J2000().getDateTime(Scale.UTC) is not None

################################################################################################################################################################

def test_instant_get_julian_date ():

    assert Instant.J2000().getJulianDate(Scale.UTC) is not None

################################################################################################################################################################

def test_instant_get_modified_julian_date ():

    assert Instant.J2000().getModifiedJulianDate(Scale.UTC) is not None

################################################################################################################################################################

def test_instant_to_string ():

    assert Instant.J2000().toString() is not None
    assert Instant.J2000().toString(Scale.UTC) is not None

################################################################################################################################################################
