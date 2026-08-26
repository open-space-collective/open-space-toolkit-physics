# Apache License 2.0

from ostk.physics.coordinate import Position
from ostk.physics.environment.object.celestial import Moon
from ostk.physics.time import DateTime
from ostk.physics.time import Instant
from ostk.physics.time import Scale


class TestMoon:
    def test_default_success(self):
        moon = Moon.default()

        assert moon is not None
        assert isinstance(moon, Moon)

    def test_spherical_success(self):
        moon = Moon.spherical()

        assert moon is not None
        assert isinstance(moon, Moon)

    def test_compute_analytical_position_success(self):
        moon = Moon.spherical()

        position = moon.compute_analytical_position(
            instant=Instant.date_time(DateTime(2024, 1, 1, 0, 0, 0), Scale.UTC)
        )

        assert position is not None
        assert isinstance(position, Position)
        assert position.is_defined()
