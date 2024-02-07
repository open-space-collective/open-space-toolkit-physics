# Apache License 2.0

from ostk.physics.environment.object.celestial import Earth


class TestCelestial:
    def test_model_is_defined_success(self):
        earth = Earth.spherical()

        assert earth.gravitational_model_is_defined() is True
        assert earth.magnetic_model_is_defined() is False
        assert earth.atmospheric_model_is_defined() is False
