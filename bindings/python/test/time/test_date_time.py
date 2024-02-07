# Apache License 2.0

import datetime

from ostk.core.type import String

from ostk.physics.time import Date
from ostk.physics.time import Time
from ostk.physics.time import DateTime


class TestDateTime:
    def test_constructor_success_full(self):
        date_time = DateTime(
            year=2020,
            month=1,
            day=1,
            hour=0,
            minute=0,
            second=0,
            millisecond=0,
            microsecond=0,
            nanosecond=0,
        )

        assert date_time is not None
        assert isinstance(date_time, DateTime)
        assert date_time.is_defined()

    def test_constructor_success_partial(self):
        date_time = DateTime(
            year=2020,
            month=1,
            day=1,
            hour=0,
            minute=0,
            second=0,
        )

        assert date_time is not None
        assert isinstance(date_time, DateTime)
        assert date_time.is_defined()

    def test_constructor_success_date_time(self):
        date_time = DateTime(
            date=Date(2020, 1, 1),
            time=Time(0, 0, 0),
        )

        assert date_time is not None
        assert isinstance(date_time, DateTime)
        assert date_time.is_defined()

    # def test_constructor_success_python_datetime (self):

    #     # date_time = DateTime(
    #     #     datetime.datetime(2020, 1, 2, 3, 4, 5),
    #     # )

    #     # assert date_time is not None
    #     # assert isinstance(date_time, DateTime)
    #     # assert date_time.is_defined()

    #     print(type(DateTime(2020, 1, 1)))
    #     print(type(DateTime.J2000()))
    #     print(type(DateTime(datetime.datetime.now())))

    # datetime.datetime(date_time)

    def test_comparators_success(self):
        date_time_1 = DateTime(2020, 1, 1, 0, 0, 0, 0, 0, 0)
        date_time_2 = DateTime(2020, 1, 1, 0, 0, 0, 0, 0, 1)
        date_time_3 = DateTime(2020, 1, 1, 0, 0, 1, 0, 0, 0)

        assert date_time_1 == date_time_1
        assert date_time_2 == date_time_2
        assert date_time_3 == date_time_3
        assert date_time_1 != date_time_2
        assert date_time_1 != date_time_3

        date_time_1 = DateTime(2020, 1, 2, 3, 4, 5)
        date_time_2 = datetime.datetime(2020, 1, 2, 3, 4, 5)

        assert date_time_1 == date_time_1
        assert date_time_1 == date_time_2
        assert date_time_2 == date_time_2
        assert (date_time_1 != date_time_1) is False

    def test_is_defined_success(self):
        date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

        assert date_time is not None
        assert date_time.is_defined()

    def test_get_date_success(self):
        date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

        assert date_time.get_date() is not None
        assert date_time.get_date() == Date(2018, 1, 1)

    def test_get_time_success(self):
        date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

        assert date_time.get_time() is not None
        assert date_time.get_time() == Time(0, 0, 0, 0, 0, 0)

    def test_get_julian_date_success(self):
        date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

        assert date_time.get_julian_date()

    def test_get_modified_julian_date_success(self):
        date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

        assert date_time.get_modified_julian_date()

    def test_to_string_success(self):
        date_time = DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0)

        assert date_time.to_string()
        assert date_time.to_string(DateTime.Format.Standard)
        assert date_time.to_string(DateTime.Format.ISO8601)
        assert date_time.to_string(DateTime.Format.STK)

    def test_undefined_success(self):
        assert DateTime.undefined() is None

    def test_J2000_success(self):
        date_time = DateTime.J2000()

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)

    def test_GPS_epoch_success(self):
        date_time = DateTime.GPS_epoch()

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)

    def test_unix_epoch_success(self):
        date_time = DateTime.unix_epoch()

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)

    def test_modified_julian_date_epoch_success(self):
        date_time = DateTime.modified_julian_date_epoch()

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)

    def test_julian_date_success(self):
        date_time = DateTime.julian_date(2458119.5)

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)

    def test_modified_julian_date_success(self):
        date_time = DateTime.modified_julian_date(58119.0)

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)

    def test_parse_success_str_format_undefined(self):
        date_time = DateTime.parse("2018-01-01 00:00:00")

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    def test_parse_success_str_format_standard(self):
        date_time = DateTime.parse("2018-01-01 00:00:00", DateTime.Format.Standard)

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    def test_parse_success_str_format_iso8601(self):
        date_time = DateTime.parse("2018-01-01T00:00:00", DateTime.Format.ISO8601)

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    def test_parse_success_str_format_stk(self):
        date_time = DateTime.parse("1 Jan 2018 00:00:00", DateTime.Format.STK)

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    def test_parse_success_string_format_undefined(self):
        date_time = DateTime.parse(String("2018-01-01 00:00:00"))

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    def test_parse_success_string_format_standard(self):
        date_time = DateTime.parse(
            String("2018-01-01 00:00:00"), DateTime.Format.Standard
        )

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    def test_parse_success_string_format_iso8601(self):
        date_time = DateTime.parse(String("2018-01-01T00:00:00"), DateTime.Format.ISO8601)

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

    def test_parse_success_string_format_stk(self):
        date_time = DateTime.parse(String("1 Jan 2018 00:00:00"), DateTime.Format.STK)

        assert date_time is not None
        assert isinstance(date_time, datetime.datetime)
        assert date_time == datetime.datetime(2018, 1, 1, 0, 0)
        assert date_time == DateTime(2018, 1, 1, 0, 0, 0)

        assert (datetime.datetime.now() + datetime.timedelta(days=1)) is not None
