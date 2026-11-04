# Apache License 2.0

import pytest
from ostk.core.type import String
from ostk.physics.time import Date


def test_date_constructors():
    assert Date(2018, 1, 1) is not None


def test_date_J2000():
    assert Date.J2000() is not None


def test_date_GPS_epoch():
    assert Date.GPS_epoch() is not None


def test_date_unix_epoch():
    assert Date.unix_epoch() is not None


def test_date_modified_julian_date_epoch():
    assert Date.modified_julian_date_epoch() is not None


def test_date_parse():
    ## Using python strings

    # Testing with default format argument (None, which detects the format)
    date: Date = Date.parse("2018-01-01")

    assert date is not None
    assert isinstance(date, Date)

    # Testing with Date.Format.Standard
    date: Date = Date.parse("2018-01-01", Date.Format.Standard)

    assert date is not None
    assert isinstance(date, Date)

    # Testing with Date.Format.STK
    date: Date = Date.parse("2 Jan 2019", Date.Format.STK)

    assert date is not None
    assert isinstance(date, Date)

    ## Using String class

    # Testing with default format argument (None, which detects the format)
    date: Date = Date.parse(String("2018-01-01"))

    assert date is not None
    assert isinstance(date, Date)

    # Testing with Date.Format.Standard
    date: Date = Date.parse(String("2018-01-01"), Date.Format.Standard)

    assert date is not None
    assert isinstance(date, Date)

    # Testing with Date.Format.STK
    date: Date = Date.parse(String("2 Jan 2019"), Date.Format.STK)

    assert date is not None
    assert isinstance(date, Date)


def test_date_parse_without_format():
    assert Date.parse("2018-01-02") == Date.parse("2018-01-02", Date.Format.Standard)
    assert Date.parse("2018-01-02", None) == Date.parse(
        "2018-01-02", Date.Format.Standard
    )
    assert Date.parse("2 Jan 2018", None) == Date.parse("2 Jan 2018", Date.Format.STK)

    with pytest.raises(RuntimeError):
        Date.parse("abc", None)


def test_date_format_has_no_undefined():
    assert not hasattr(Date.Format, "Undefined")


def test_date_operators():
    date = Date(2018, 1, 1)

    assert (date == date) is not None
    assert (date != date) is not None


def test_date_has_no_undefined():
    assert not hasattr(Date, "undefined")
    assert not hasattr(Date, "is_defined")


def test_date_get_year():
    date = Date(2018, 1, 1)

    assert date.get_year() is not None


def test_date_get_day():
    date = Date(2018, 1, 1)

    assert date.get_day() is not None


def test_date_get_month():
    date = Date(2018, 1, 1)

    assert date.get_month() is not None


def test_date_to_string():
    date = Date(2018, 1, 1)

    date.to_string()
    date.to_string(Date.Format.Standard)
    date.to_string(Date.Format.STK)


def test_date_replace():
    date = Date(2018, 1, 2)

    assert date.replace() == date
    assert date.replace(year=2019) == Date(2019, 1, 2)
    assert date.replace(month=6) == Date(2018, 6, 2)
    assert date.replace(day=15) == Date(2018, 1, 15)
    assert date.replace(2019, 6, 15) == Date(2019, 6, 15)
    assert date.replace(None, 6, None) == Date(2018, 6, 2)

    # Original date is left untouched
    assert date == Date(2018, 1, 2)


def test_date_set_year():
    date = Date(2018, 1, 1)

    with pytest.warns(DeprecationWarning):
        date.set_year(2019)


def test_date_set_month():
    date = Date(2018, 1, 1)

    with pytest.warns(DeprecationWarning):
        date.set_month(2)


def test_date_set_day():
    date = Date(2018, 1, 1)

    with pytest.warns(DeprecationWarning):
        date.set_day(2)
