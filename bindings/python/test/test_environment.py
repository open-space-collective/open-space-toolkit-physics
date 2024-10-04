# Apache License 2.0

import pytest

from ostk.physics.time import Instant, DateTime, Scale
from ostk.physics.coordinate import Frame, Position
from ostk.physics import Environment


@pytest.fixture
def environment() -> Environment:
    return Environment.default()


class TestEnvironment:

    def test_constructors(self):
        instant = Instant.date_time(DateTime(2019, 1, 1, 0, 0, 0), Scale.UTC)
        objects = []

        env: Environment = Environment(instant, objects)

        assert env is not None
        assert isinstance(env, Environment)

        env = Environment(instant, objects, set_global_instance=True)

        assert env is not None
        assert isinstance(env, Environment)

    def test_undefined(self):
        assert Environment.undefined() is not None
        assert Environment.undefined().is_defined() is False

    def test_default(self):
        assert Environment.default() is not None
        assert Environment.default(set_global_instance=True) is not None

    def test_is_defined(self, environment: Environment):
        assert environment.is_defined() is not None

    def test_has_object_with_name(self, environment: Environment):
        assert environment.has_object_with_name("Earth") is not None

    @pytest.mark.skip
    def test_intersects(self, environment: Environment):
        assert environment.intersects() is not None

    def test_access_objects(self, environment: Environment):
        assert environment.access_objects() is not None

    def test_access_object_with_name(self, environment: Environment):
        assert environment.access_object_with_name("Earth") is not None

    def test_access_celestial_object_with_name(self, environment: Environment):
        assert environment.access_celestial_object_with_name("Earth") is not None

    def test_get_instant(self, environment: Environment):
        assert environment.get_instant() is not None

    def test_get_object_names(self, environment: Environment):
        assert environment.get_object_names() is not None

    def test_set_instant(self, environment: Environment):
        environment.set_instant(
            Instant.date_time(DateTime(2019, 1, 1, 0, 0, 0), Scale.UTC)
        )

    def test_is_position_in_eclipse(self, environment: Environment):
        environment.set_instant(
            Instant.date_time(DateTime(2018, 1, 1, 0, 0, 0), Scale.UTC)
        )

        assert environment.is_position_in_eclipse(
            Position.meters(
                [7000e3, 0.0, 0.0],
                Frame.ITRF(),
            )
        )

    def test_access_global_instance(self):
        with pytest.raises(RuntimeError):
            Environment.access_global_instance()

        Environment.default(set_global_instance=True)

        assert Environment.access_global_instance() is not None

    def test_has_global_instance(self):
        assert Environment.has_global_instance() is False

        Environment.default(set_global_instance=True)

        assert Environment.has_global_instance() is True

    def teardown_method(self, method):
        Environment.reset_global_instance()
