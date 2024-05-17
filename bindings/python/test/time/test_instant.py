# Apache License 2.0

import datetime
import pytest

from ostk.physics.time import Scale
from ostk.physics.time import Instant
from ostk.physics.time import Duration
from ostk.physics.time import DateTime


def test_instant_undefined():
    assert Instant.undefined() is not None


def test_instant_now():
    assert Instant.now() is not None


def test_instant_J2000():
    assert Instant.J2000() is not None


def test_instant_GPS_epock():
    assert Instant.GPS_epoch() is not None


def test_instant_datetime():
    assert (
        Instant.date_time(DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0), Scale.UTC) is not None
    )

    assert Instant.date_time(datetime.datetime.now(), Scale.UTC)


def test_instant_julian_date():
    assert Instant.julian_date(2458119.5, Scale.UTC) is not None


def test_instant_modified_julian_date():
    assert Instant.modified_julian_date(58119.0, Scale.UTC) is not None


def test_instant_parse():
    assert Instant.parse("2024-01-01 00:01:02.000", Scale.UTC) is not None
    assert (
        Instant.parse("2024-01-01 00:01:02.000", Scale.UTC, DateTime.Format.Standard)
        is not None
    )
    assert (
        Instant.parse("2024-01-01T00:01:02.000", Scale.UTC, DateTime.Format.ISO8601)
        is not None
    )


def test_instant_operators():
    instant = Instant.J2000()

    assert (instant == instant) is not None
    assert (instant != instant) is not None

    assert (instant < instant) is not None
    assert (instant <= instant) is not None
    assert (instant > instant) is not None
    assert (instant >= instant) is not None

    assert (instant + Duration.seconds(1.0)) is not None
    assert (instant - Duration.seconds(1.0)) is not None

    assert (instant - instant) is not None

    instant += Duration.seconds(1.0)
    instant -= Duration.seconds(1.0)


def test_instant_is_defined():
    assert Instant.J2000().is_defined() is not None


def test_instant_is_post_epoch():
    assert Instant.J2000().is_post_epoch() is not None


def test_instant_is_near():
    assert Instant.J2000().is_near(Instant.J2000(), Duration.zero()) is not None


def test_instant_get_date_time():
    assert Instant.J2000().get_date_time(Scale.UTC) is not None


def test_instant_get_julian_date():
    assert Instant.J2000().get_julian_date(Scale.UTC) is not None


def test_instant_get_modified_julian_date():
    assert Instant.J2000().get_modified_julian_date(Scale.UTC) is not None


def test_instant_to_string():
    assert Instant.J2000().to_string() is not None
    assert Instant.J2000().to_string(Scale.UTC) is not None
    assert Instant.J2000().to_string(Scale.UTC, DateTime.Format.ISO8601) is not None
