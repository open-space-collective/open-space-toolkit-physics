# Apache License 2.0

from ostk.physics.environment.object.celestial import Moon


class TestMoon:
    def test_default_success(self):
        moon = Moon.default()

        assert moon is not None
        assert isinstance(moon, Moon)

    def test_spherical_success(self):
        moon = Moon.spherical()

        assert moon is not None
        assert isinstance(moon, Moon)
