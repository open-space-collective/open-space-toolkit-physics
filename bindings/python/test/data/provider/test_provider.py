# Apache License 2.0

import pytest

from ostk.physics import Environment
from ostk.physics.environment.object import Celestial
from ostk.physics.coordinate import Position
from ostk.physics.coordinate import Frame
from ostk.physics.data import provider


@pytest.fixture
def environment() -> Environment:
    return Environment.default()


@pytest.fixture
def celestial(environment: Environment) -> Celestial:
    return environment.access_celestial_object_with_name("Earth")


@pytest.fixture
def position():
    return Position.meters([6671000.0, 0.0, 0.0], Frame.ITRF())


class TestProvider:
    def test_nadir(
        self,
        celestial: Celestial,
        position: Position,
        environment: Environment,
    ):
        assert provider.nadir(position, celestial, environment) is not None
