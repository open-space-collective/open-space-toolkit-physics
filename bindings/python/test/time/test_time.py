# Apache License 2.0

import pytest
from ostk.core.type import String
from ostk.physics.time import Time


@pytest.fixture
def time() -> Time:
    return Time(0, 0, 0)


class TestTime:
    def test_constructors(self, time: Time) -> None:
        assert time is not None

    @pytest.mark.parametrize(
        "time_string, format",
        [
            ("00:00:00", None),
            ("00:00:00", Time.Format.Standard),
            ("00:00:00", Time.Format.ISO8601),
            (String("00:00:00"), None),
            (String("00:00:00"), Time.Format.Standard),
            (String("00:00:00"), Time.Format.ISO8601),
        ],
    )
    def test_parse(self, time_string, format) -> None:
        if format is None:
            time = Time.parse(time_string)
        else:
            time = Time.parse(time_string, format)

        assert time is not None
        assert isinstance(time, Time)
        assert time.is_defined()

    def test_operators(self, time: Time) -> None:
        assert (time == time) is not None
        assert (time != time) is not None

    def test_is_defined(self, time: Time) -> None:
        assert time.is_defined() is not None

    def test_get_hour(self, time: Time) -> None:
        assert time.get_hour() is not None

    def test_get_minute(self, time: Time) -> None:
        assert time.get_minute() is not None

    def test_get_second(self, time: Time) -> None:
        assert time.get_second() is not None

    def test_get_millisecond(self, time: Time) -> None:
        assert time.get_millisecond() is not None

    def test_get_microsecond(self, time: Time) -> None:
        assert time.get_microsecond() is not None

    def test_get_nanosecond(self, time: Time) -> None:
        assert time.get_nanosecond() is not None

    def test_get_floating_seconds(self, time: Time) -> None:
        assert time.get_floating_seconds() is not None

    def test_get_total_floating_seconds(self, time: Time) -> None:
        assert time.get_total_floating_seconds() is not None

    def test_get_total_floating_hours(self, time: Time) -> None:
        assert time.get_total_floating_hours() is not None

    def test_to_string(self, time: Time) -> None:
        assert time.to_string() is not None
        assert time.to_string(Time.Format.Standard) is not None
        assert time.to_string(Time.Format.ISO8601) is not None

    def test_set_hour(self, time: Time) -> None:
        time.set_hour(1)
        assert time.get_hour() == 1

    def test_set_minute(self, time: Time) -> None:
        time.set_minute(1)
        assert time.get_minute() == 1

    def test_set_second(self, time: Time) -> None:
        time.set_second(1)
        assert time.get_second() == 1

    def test_set_millisecond(self, time: Time) -> None:
        time.set_millisecond(1)
        assert time.get_millisecond() == 1

    def test_set_microsecond(self, time: Time) -> None:
        time.set_microsecond(1)
        assert time.get_microsecond() == 1

    def test_set_nanosecond(self, time: Time) -> None:
        time.set_nanosecond(1)
        assert time.get_nanosecond() == 1

    def test_undefined(self) -> None:
        assert Time.undefined() is not None

    def test_midnight(self) -> None:
        assert Time.midnight() is not None

    def test_noon(self) -> None:
        assert Time.noon() is not None

    def test_hours(self) -> None:
        assert Time.hours(12.0345) is not None

    def test_seconds(self) -> None:
        assert Time.seconds(1238.0345) is not None
