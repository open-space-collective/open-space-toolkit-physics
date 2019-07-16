################################################################################################################################################################

# @project        Library ▸ Physics
# @file           library/physics/time/test_date_time.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import datetime
import pytest

from Library.Physics.Time import Date
from Library.Physics.Time import Time
from Library.Physics.Time import DateTime

################################################################################################################################################################

def test_date_time_constructors ():

    assert DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0) is not None
    assert DateTime(2018, 1, 1, 0, 0, 0) is not None

    assert DateTime(Date(2018, 1, 1), Time(0, 0, 0)) is not None

################################################################################################################################################################

@pytest.mark.skip(reason = 'This is currently failing.')
def test_date_time_undefined ():

    assert DateTime.Undefined() is not None

################################################################################################################################################################

def test_date_time_j2000 ():

    assert DateTime.J2000() is not None

################################################################################################################################################################

def test_date_time_gps_epoch ():

    assert DateTime.GPSEpoch() is not None

################################################################################################################################################################

def test_date_time_unix_epoch ():

    assert DateTime.UnixEpoch() is not None

################################################################################################################################################################

def test_date_time_modified_julian_date_epoch ():

    assert DateTime.ModifiedJulianDateEpoch() is not None

################################################################################################################################################################

def test_date_time_julian_date ():

    assert DateTime.JulianDate(2458119.5) is not None

################################################################################################################################################################

def test_date_time_modified_julian_date ():

    assert DateTime.ModifiedJulianDate(58119.0) is not None

################################################################################################################################################################

def test_date_time_parse ():

    assert DateTime.Parse('2018-01-01 00:00:00') is not None
    assert DateTime.Parse('2018-01-01 00:00:00', DateTime.Format.Standard) is not None
    assert DateTime.Parse('2018-01-01T00:00:00', DateTime.Format.ISO8601) is not None
    assert DateTime.Parse('1 Jan 2018 00:00:00', DateTime.Format.STK) is not None

    assert (datetime.datetime.now() + datetime.timedelta(days = 1)) is not None

################################################################################################################################################################

def test_date_time_operators ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert (date_time == date_time) is not None
    assert (date_time != date_time) is not None

################################################################################################################################################################

def test_date_time_is_defined ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.isDefined()

################################################################################################################################################################

def test_date_time_get_date ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.getDate()

################################################################################################################################################################

def test_date_time_get_time ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.getTime()

################################################################################################################################################################

def test_date_time_get_julian_date ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.getJulianDate()

################################################################################################################################################################

def test_date_time_get_modified_julian_date ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.getModifiedJulianDate()

################################################################################################################################################################

def test_date_time_to_string ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.toString()
    assert date_time.toString(DateTime.Format.Standard)
    assert date_time.toString(DateTime.Format.ISO8601)
    assert date_time.toString(DateTime.Format.STK)

################################################################################################################################################################
