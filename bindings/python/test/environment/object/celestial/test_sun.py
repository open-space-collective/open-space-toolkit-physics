# Apache License 2.0

from ostk.physics.coordinate import Position
from ostk.physics.environment.object.celestial import Sun
from ostk.physics.time import DateTime
from ostk.physics.time import Instant
from ostk.physics.time import Scale


class TestSun:
    def test_default_success(self):
        sun = Sun.default()

        assert sun is not None
        assert isinstance(sun, Sun)

    def test_spherical_success(self):
        sun = Sun.spherical()

        assert sun is not None
        assert isinstance(sun, Sun)

    def test_compute_analytical_position_success(self):
        sun = Sun.default()

        position = sun.compute_analytical_position(
            instant=Instant.date_time(DateTime(2024, 1, 1, 0, 0, 0), Scale.UTC)
        )

        assert position is not None
        assert isinstance(position, Position)
        assert position.is_defined()
