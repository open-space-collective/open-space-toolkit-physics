# Apache License 2.0

from ostk.physics.environment.object.celestial import Sun


class TestSun:
    def test_default_success(self):
        sun = Sun.default()

        assert sun is not None
        assert isinstance(sun, Sun)

    def test_spherical_success(self):
        sun = Sun.spherical()

        assert sun is not None
        assert isinstance(sun, Sun)
