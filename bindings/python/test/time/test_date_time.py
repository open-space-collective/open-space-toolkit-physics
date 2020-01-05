################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/time/test_date_time.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import datetime
import pytest

from ostk.physics.time import Date
from ostk.physics.time import Time
from ostk.physics.time import DateTime

################################################################################################################################################################

def test_date_time_constructors ():

    assert DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0) is not None
    assert DateTime(2018, 1, 1, 0, 0, 0) is not None

    assert DateTime(Date(2018, 1, 1), Time(0, 0, 0)) is not None

################################################################################################################################################################

@pytest.mark.skip(reason = 'This is currently failing.')
def test_date_time_undefined ():

    assert DateTime.undefined() is not None

################################################################################################################################################################

def test_date_time_J2000 ():

    assert DateTime.J2000() is not None

################################################################################################################################################################

def test_date_time_GPS_epoch ():

    assert DateTime.GPS_epoch() is not None

################################################################################################################################################################

def test_date_time_unix_epoch ():

    assert DateTime.unix_epoch() is not None

################################################################################################################################################################

def test_date_time_modified_julian_date_epoch ():

    assert DateTime.modified_julian_date_epoch() is not None

################################################################################################################################################################

def test_date_time_julian_date ():

    assert DateTime.julian_date(2458119.5) is not None

################################################################################################################################################################

def test_date_time_modified_julian_date ():

    assert DateTime.modified_julian_date(58119.0) is not None

################################################################################################################################################################

def test_date_time_parse ():

    assert DateTime.parse('2018-01-01 00:00:00') is not None
    assert DateTime.parse('2018-01-01 00:00:00', DateTime.Format.Standard) is not None
    assert DateTime.parse('2018-01-01T00:00:00', DateTime.Format.ISO8601) is not None
    assert DateTime.parse('1 Jan 2018 00:00:00', DateTime.Format.STK) is not None

    assert (datetime.datetime.now() + datetime.timedelta(days = 1)) is not None

################################################################################################################################################################

def test_date_time_operators ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert (date_time == date_time) is not None
    assert (date_time != date_time) is not None

################################################################################################################################################################

def test_date_time_is_defined ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.is_defined()

################################################################################################################################################################

def test_date_time_get_date ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.get_date()

################################################################################################################################################################

def test_date_time_get_time ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.get_time()

################################################################################################################################################################

def test_date_time_get_julian_date ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.get_julian_date()

################################################################################################################################################################

def test_date_time_get_modified_julian_date ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.get_modified_julian_date()

################################################################################################################################################################

def test_date_time_to_string ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.to_string()
    assert date_time.to_string(DateTime.Format.Standard)
    assert date_time.to_string(DateTime.Format.ISO8601)
    assert date_time.to_string(DateTime.Format.STK)

################################################################################################################################################################
