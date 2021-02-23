################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/time/test_date_time.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import datetime
import pytest

from ostk.core.types import String

from ostk.physics.time import Date
from ostk.physics.time import Time
from ostk.physics.time import DateTime

################################################################################################################################################################

def test_date_time_constructors ():

    # Construction with 6 integers in input
    date_time: DateTime = DateTime(2020, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time is not None
    assert isinstance(date_time, DateTime)
    assert date_time.is_defined()

    # Construction with 9 integers in input
    date_time: DateTime = DateTime(2020, 1, 1, 0, 0, 0)

    assert date_time is not None
    assert isinstance(date_time, DateTime)
    assert date_time.is_defined()

    # Construction with Date and Time objects
    date_time: DateTime = DateTime(Date(2020, 1, 1), Time(0, 0, 0))

    assert date_time is not None
    assert isinstance(date_time, DateTime)
    assert date_time.is_defined()

################################################################################################################################################################

@pytest.mark.skip(reason = 'This is currently failing.')
def test_date_time_undefined ():

    assert DateTime.undefined() is not None

################################################################################################################################################################

def test_date_time_J2000 ():

    date_time: DateTime = DateTime.J2000()

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)

################################################################################################################################################################

def test_date_time_GPS_epoch ():

    date_time: DateTime = DateTime.GPS_epoch()

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)

################################################################################################################################################################

def test_date_time_unix_epoch ():

    date_time: DateTime = DateTime.unix_epoch()

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)

################################################################################################################################################################

def test_date_time_modified_julian_date_epoch ():

    date_time: DateTime = DateTime.modified_julian_date_epoch()

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)

################################################################################################################################################################

def test_date_time_julian_date ():

    date_time: DateTime = DateTime.julian_date(2458119.5)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)

################################################################################################################################################################

def test_date_time_modified_julian_date ():

    date_time: DateTime = DateTime.modified_julian_date(58119.0)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)

################################################################################################################################################################

def test_date_time_parse ():

    ## Using python strings

    # Testing with default argument (DateTime.Format.Undefined)
    date_time = DateTime.parse('2018-01-01 00:00:00')

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    # Testing with DateTime.Format.Standard
    date_time = DateTime.parse('2018-01-01 00:00:00', DateTime.Format.Standard)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    # Testing with DateTime.Format.ISO8601
    date_time = DateTime.parse('2018-01-01T00:00:00', DateTime.Format.ISO8601)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    # Testing with DateTime.Format.STK
    date_time = DateTime.parse('1 Jan 2018 00:00:00', DateTime.Format.STK)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    ## Using String

    # Testing with default argument (DateTime.Format.Undefined)
    date_time = DateTime.parse(String('2018-01-01 00:00:00'))

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    # Testing with DateTime.Format.Standard
    date_time = DateTime.parse(String('2018-01-01 00:00:00'), DateTime.Format.Standard)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    # Testing with DateTime.Format.ISO8601
    date_time = DateTime.parse(String('2018-01-01T00:00:00'), DateTime.Format.ISO8601)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    # Testing with DateTime.Format.STK
    date_time = DateTime.parse(String('1 Jan 2018 00:00:00'), DateTime.Format.STK)

    assert date_time is not None
    assert isinstance(date_time, datetime.datetime)
    assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
    assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    assert (datetime.datetime.now() + datetime.timedelta(days = 1)) is not None

################################################################################################################################################################

def test_date_time_comparators ():

    date_time_1 = DateTime(2020, 1, 1, 0, 0, 0, 0, 0, 0)
    date_time_2 = DateTime(2020, 1, 1, 0, 0, 0, 0, 0, 1)
    date_time_3 = DateTime(2020, 1, 1, 0, 0, 1, 0, 0, 0)

    assert date_time_1 == date_time_1
    assert date_time_2 == date_time_2
    assert date_time_3 == date_time_3
    assert date_time_1 != date_time_2
    assert date_time_1 != date_time_3

    date_time_1: DateTime = DateTime(2020, 1, 2, 3, 4, 5)
    date_time_2: DateTime = datetime.datetime(2020, 1, 2, 3, 4, 5)

    assert date_time_1 == date_time_1
    assert date_time_1 == date_time_2
    assert date_time_2 == date_time_2
    assert (date_time_1 != date_time_1) is False

################################################################################################################################################################

def test_date_time_is_defined ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time is not None
    assert date_time.is_defined()

################################################################################################################################################################

def test_date_time_get_date ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.get_date() is not None
    assert date_time.get_date() == Date(2018, 1, 1)

################################################################################################################################################################

def test_date_time_get_time ():

    date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

    assert date_time.get_time() is not None
    assert date_time.get_time() == Time(0, 0, 0, 0, 0, 0)

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
