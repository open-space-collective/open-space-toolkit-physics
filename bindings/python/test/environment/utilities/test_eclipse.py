# Apache License 2.0

import pytest

from ostk.physics import Environment
from ostk.physics.coordinate import Frame, Position
from ostk.physics.environment.object import Celestial
from ostk.physics.environment.object.celestial import Earth, Sun
from ostk.physics.environment.utility import (
    Eclipse,
    EclipsePhase,
    eclipse_intervals_at_position,
    montenbruck_gill_shadow_function,
)
from ostk.physics.time import Scale, Instant, Duration, Interval, DateTime


@pytest.fixture
def interval() -> Interval:
    return Interval.closed(
        Instant.date_time(DateTime(2025, 1, 1, 0, 0, 0), Scale.UTC),
        Instant.date_time(DateTime(2025, 1, 1, 0, 10, 0), Scale.UTC),
    )


@pytest.fixture
def intervals(
    interval: Interval,
) -> list[Interval]:
    return [
        interval,
        Interval.closed(
            Instant.date_time(DateTime(2025, 1, 1, 0, 10, 0), Scale.UTC),
            Instant.date_time(DateTime(2025, 1, 1, 0, 12, 0), Scale.UTC),
        ),
    ]


@pytest.fixture
def region() -> EclipsePhase.Region:
    return EclipsePhase.Region.Umbra


@pytest.fixture
def regions(
    region: EclipsePhase.Region,
) -> list[EclipsePhase.Region]:
    return [
        region,
        EclipsePhase.Region.Penumbra,
    ]


@pytest.fixture
def is_complete() -> bool:
    return True


@pytest.fixture
def eclipse_phase(
    interval: Interval,
    region: EclipsePhase.Region,
    is_complete: bool,
) -> EclipsePhase:
    return EclipsePhase(
        region=region,
        interval=interval,
        is_complete=is_complete,
    )


@pytest.fixture
def eclipse_phases(
    intervals: list[Interval],
    regions: list[EclipsePhase.Region],
) -> list[EclipsePhase]:
    return [
        EclipsePhase(
            region=region,
            interval=interval,
            is_complete=True,
        )
        for region, interval in zip(regions, intervals)
    ]


@pytest.fixture
def sun() -> Celestial:
    return Sun.default()


@pytest.fixture
def earth() -> Celestial:
    return Earth.default()


@pytest.fixture
def eclipse(
    sun: Celestial,
    earth: Celestial,
    eclipse_phase: EclipsePhase,
) -> Eclipse:
    return Eclipse(
        occulted_celestial_object=sun,
        occulting_celestial_object=earth,
        phases=[eclipse_phase],
    )


@pytest.fixture
def environment() -> Environment:
    return Environment.default()


class TestEclipsePhase:
    def test_constructor_and_properties_success(
        self,
        interval: Interval,
        region: EclipsePhase.Region,
        is_complete: bool,
    ):
        eclipse_phase: EclipsePhase = EclipsePhase(
            region=region,
            interval=interval,
            is_complete=is_complete,
        )

        assert isinstance(eclipse_phase, EclipsePhase)
        assert eclipse_phase.get_region() == region
        assert eclipse_phase.get_interval() == interval
        assert eclipse_phase.is_complete() == is_complete
        assert isinstance(str(eclipse_phase), str)
        assert isinstance(repr(eclipse_phase), str)


class TestEclipse:
    def test_constructor_and_properties_success(
        self,
        sun: Celestial,
        earth: Celestial,
        eclipse_phases: list[EclipsePhase],
    ):
        eclipse: Eclipse = Eclipse(
            occulted_celestial_object=sun,
            occulting_celestial_object=earth,
            phases=eclipse_phases,
        )

        assert isinstance(eclipse, Eclipse)
        assert eclipse.get_occulted_celestial_object().get_type() == sun.get_type()
        assert eclipse.get_occulting_celestial_object().get_type() == earth.get_type()
        assert eclipse.get_phases() == eclipse_phases
        assert eclipse.get_duration(include_penumbra=True) == Duration.minutes(12.0)
        assert eclipse.get_duration(include_penumbra=False) == Duration.minutes(10.0)
        assert eclipse.get_interval(include_penumbra=True) == Interval.closed(
            Instant.date_time(DateTime(2025, 1, 1, 0, 0, 0), Scale.UTC),
            Instant.date_time(DateTime(2025, 1, 1, 0, 12, 0), Scale.UTC),
        )
        assert eclipse.get_interval(include_penumbra=False) == Interval.closed(
            Instant.date_time(DateTime(2025, 1, 1, 0, 0, 0), Scale.UTC),
            Instant.date_time(DateTime(2025, 1, 1, 0, 10, 0), Scale.UTC),
        )
        assert isinstance(str(eclipse), str)
        assert isinstance(repr(eclipse), str)


class TestEclipseUtilityFunctions:
    def test_eclipse_intervals_at_position_basic(
        self,
        environment: Environment,
    ):
        eclipse_intervals = eclipse_intervals_at_position(
            analysis_interval=Interval.closed(
                Instant.date_time(DateTime(2025, 1, 1, 0, 0, 0), Scale.UTC),
                Instant.date_time(DateTime(2025, 1, 3, 0, 0, 0), Scale.UTC),
            ),
            position=Position.meters([1000.0, 0.0, 0.0], Frame.ITRF()),
            environment=environment,
        )

        assert eclipse_intervals is not None
        assert isinstance(eclipse_intervals, list)
        assert len(eclipse_intervals) > 0
        for interval in eclipse_intervals:
            assert isinstance(interval, Interval)
            assert interval.is_defined()

    def test_montenbruck_gill_shadow_function_various_positions(
        self,
        sun: Celestial,
        earth: Celestial,
    ):
        shadow_function_value_in_eclipse: float = montenbruck_gill_shadow_function(
            instant=Instant.date_time(DateTime(2025, 1, 1, 0, 0, 0), Scale.UTC),
            position=Position.meters([1000.0, 0.0, 0.0], Frame.ITRF()),
            occulted_celestial_object=sun,
            occulting_celestial_object=earth,
        )

        assert shadow_function_value_in_eclipse == 0.0

        shadow_function_value_in_sunlight: float = montenbruck_gill_shadow_function(
            instant=Instant.date_time(DateTime(2025, 1, 1, 12, 0, 0), Scale.UTC),
            position=Position.meters([1000.0, 0.0, 0.0], Frame.ITRF()),
            occulted_celestial_object=sun,
            occulting_celestial_object=earth,
        )

        assert shadow_function_value_in_sunlight == 1.0
