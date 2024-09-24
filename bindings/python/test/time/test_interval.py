# Apache License 2.0

import pytest

from datetime import datetime

from ostk.core.type import String

from ostk.physics.time import Scale
from ostk.physics.time import Instant
from ostk.physics.time import Duration
from ostk.physics.time import Interval


@pytest.fixture
def closed_interval() -> Interval:
    return Interval(
        Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed
    )


@pytest.fixture
def open_interval() -> Interval:
    return Interval(
        Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Open
    )


@pytest.fixture
def half_open_right_interval() -> Interval:
    return Interval(
        Instant.J2000(),
        Instant.J2000() + Duration.minutes(1.0),
        Interval.Type.HalfOpenRight,
    )


@pytest.fixture
def half_open_left_interval() -> Interval:
    return Interval(
        Instant.J2000(),
        Instant.J2000() + Duration.minutes(1.0),
        Interval.Type.HalfOpenLeft,
    )


@pytest.fixture
def interval_1(closed_interval: Interval) -> Interval:
    return closed_interval


@pytest.fixture
def interval_2() -> Interval:
    return Interval(
        Instant.J2000() - Duration.minutes(1.0), Instant.J2000(), Interval.Type.Closed
    )


@pytest.fixture
def interval_3() -> Interval:
    return Interval(
        Instant.J2000() - Duration.minutes(2.0),
        Instant.J2000() - Duration.minutes(1.0),
        Interval.Type.Closed,
    )


@pytest.fixture
def interval_4() -> Interval:
    return Interval(
        Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Open
    )


@pytest.fixture
def interval(interval_1: Interval) -> Interval:
    return interval_1


@pytest.fixture
def instant_1() -> Interval:
    return Instant.J2000()


@pytest.fixture
def instant_2() -> Interval:
    return Instant.J2000() + Duration.seconds(30.0)


@pytest.fixture
def instant_3() -> Interval:
    return Instant.J2000() + Duration.minutes(3.0)


class TestInterval:
    def test_interval_constructor(self):
        interval: Interval = Interval(
            Instant.J2000(), Instant.J2000() + Duration.minutes(1.0), Interval.Type.Closed
        )

        assert interval is not None
        assert isinstance(interval, Interval)

        with pytest.raises(RuntimeError):
            Interval(
                Instant.J2000() + Duration.seconds(1.0),
                Instant.J2000(),
                Interval.Type.Closed,
            )

    def test_interval_undefined(self):
        assert Interval.undefined() is not None
        assert isinstance(Interval.undefined(), Interval)

    def test_interval_constructor_closed(self):
        assert (
            Interval.closed(Instant.J2000(), Instant.J2000() + Duration.minutes(1.0))
            is not None
        )

    def test_interval_constructor_open(self):
        assert (
            Interval(
                Instant.J2000(),
                Instant.J2000() + Duration.minutes(1.0),
                Interval.Type.Open,
            )
            is not None
        )

    def test_interval_constructor_half_open_left(self):
        assert (
            Interval(
                Instant.J2000(),
                Instant.J2000() + Duration.minutes(1.0),
                Interval.Type.HalfOpenLeft,
            )
            is not None
        )

    def test_interval_constructor_half_open_right(self):
        assert (
            Interval(
                Instant.J2000(),
                Instant.J2000() + Duration.minutes(1.0),
                Interval.Type.HalfOpenRight,
            )
            is not None
        )

    def test_interval_constructor_centered(self):
        assert (
            Interval.centered(
                Instant.J2000(), Duration.minutes(1.0), Interval.Type.Closed
            )
            is not None
        )
        assert (
            Interval.centered(Instant.J2000(), Duration.minutes(1.0), Interval.Type.Open)
            is not None
        )
        assert (
            Interval.centered(
                Instant.J2000(), Duration.minutes(1.0), Interval.Type.HalfOpenLeft
            )
            is not None
        )
        assert (
            Interval.centered(
                Instant.J2000(), Duration.minutes(1.0), Interval.Type.HalfOpenRight
            )
            is not None
        )

    def test_interval_operator_equality(self, interval_1: Interval, interval_4: Interval):
        assert interval_1 == interval_1
        assert (interval_1 != interval_1) is False

        assert interval_1 != interval_4

    def test_interval_is_defined(self, interval: Interval):
        assert interval.is_defined()
        assert Interval.undefined().is_defined() is False

    def test_interval_is_degenerate(self, interval: Interval):
        assert interval.is_degenerate() is False
        assert Interval.closed(Instant.J2000(), Instant.J2000()).is_degenerate()

        with pytest.raises(Exception):
            Interval(Instant.J2000(), Instant.J2000(), Interval.Type.Open).is_degenerate()
            Interval.centered(
                Instant.J2000(), Duration.minutes(0.0), Interval.Type.Open
            ).is_degenerate()

    def test_interval_intersects(
        self,
        interval_1: Interval,
        interval_2: Interval,
        interval_3: Interval,
        interval_4: Interval,
    ):
        assert interval_1.intersects(interval_1)
        assert interval_1.intersects(interval_2)
        assert interval_1.intersects(interval_3) is False
        assert interval_1.intersects(interval_4)
        assert interval_3.intersects(interval_4) is False
        assert interval_3.intersects(interval_2)

    def test_interval_contains_instant(
        self,
        interval_1: Interval,
        interval_4: Interval,
        instant_1: Instant,
        instant_2: Instant,
        instant_3: Instant,
    ):
        assert interval_1.contains_instant(instant_1)
        assert interval_1.contains_instant(instant_2)
        assert interval_1.contains_instant(instant_3) is False

        assert interval_4.contains_instant(instant_1) is False
        assert interval_4.contains_instant(instant_2)
        assert interval_4.contains_instant(instant_3) is False

    def test_interval_contains_interval(
        self,
        interval_1: Interval,
        interval_2: Interval,
        interval_3: Interval,
        interval_4: Interval,
    ):
        assert interval_1.contains_interval(interval_1)
        assert interval_1.contains_interval(interval_2) is False
        assert interval_1.contains_interval(interval_3) is False
        assert interval_1.contains_interval(interval_4)
        assert interval_1.contains_interval(
            Interval.closed(
                Instant.J2000() + Duration.seconds(1.0),
                Instant.J2000() + Duration.seconds(2.0),
            )
        )

    def test_interval_get_properties(self, interval: Interval):
        assert interval.get_start() == Instant.J2000()
        assert interval.get_end() == Instant.J2000() + Duration.minutes(1.0)
        assert interval.get_duration() == Duration.minutes(1.0)
        assert interval.get_lower_bound() == interval.get_start()
        assert interval.get_upper_bound() == interval.get_end()
        assert interval.get_center() == Instant.J2000() + Duration.minutes(0.5)

    def test_interval_to_string(self, interval: Interval):
        assert interval.to_string() is not None
        assert isinstance(interval.to_string(), String)
        assert interval.to_string(Scale.UTC) is not None
        assert isinstance(interval.to_string(Scale.UTC), String)

    def test_interval_generate_grid(self, interval: Interval):
        grid: list = interval.generate_grid(Duration.seconds(1.0))

        assert grid is not None
        assert isinstance(grid, list)
        assert isinstance(grid[0], Instant)
        assert len(grid) == 61

    def test_to_datetime_span(self, interval: Interval):
        assert interval.to_datetime_span() is not None
        assert isinstance(interval.to_datetime_span(), tuple)
        assert isinstance(interval.to_datetime_span()[0], datetime)
        assert isinstance(interval.to_datetime_span()[1], datetime)
