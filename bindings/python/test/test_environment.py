# Apache License 2.0

import pytest

from ostk.physics.time import Instant, DateTime, Scale
from ostk.physics.coordinate import Frame, Position
from ostk.physics import Environment


@pytest.fixture
def environment() -> Environment:
    return Environment.default()


def test_environment_constructors():
    instant = Instant.date_time(DateTime(2019, 1, 1, 0, 0, 0), Scale.UTC)
    objects = []

    env: Environment = Environment(instant, objects)

    assert env is not None
    assert isinstance(env, Environment)


def test_environment_undefined():
    assert Environment.undefined() is not None
    assert Environment.undefined().is_defined() is False


def test_environment_default():
    assert Environment.default() is not None


def test_environment_isDefined(environment: Environment):
    assert environment.is_defined() is not None


def test_environment_has_object_with_name(environment: Environment):
    assert environment.has_object_with_name("Earth") is not None


@pytest.mark.skip
def test_environment_intersects(environment: Environment):
    assert environment.intersects() is not None


def test_environment_access_objects(environment: Environment):
    assert environment.access_objects() is not None


def test_environment_access_object_with_name(environment: Environment):
    assert environment.access_object_with_name("Earth") is not None


def test_environment_access_celestial_object_with_name(environment: Environment):
    assert environment.access_celestial_object_with_name("Earth") is not None


def test_environment_getInstant(environment: Environment):
    assert environment.get_instant() is not None


def test_environment_get_object_names(environment: Environment):
    assert environment.get_object_names() is not None


def test_environment_set_instant(environment: Environment):
    environment.set_instant(Instant.date_time(DateTime(2019, 1, 1, 0, 0, 0), Scale.UTC))


def test_environment_is_position_in_eclipse(environment: Environment):
    environment.set_instant(Instant.date_time(DateTime(2018, 1, 1, 0, 0, 0), Scale.UTC))

    assert environment.is_position_in_eclipse(
        Position.meters(
            [7000e3, 0.0, 0.0],
            Frame.ITRF(),
        )
    )
