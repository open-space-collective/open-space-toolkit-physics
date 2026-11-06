# Apache License 2.0

from ostk.physics.environment.object import Celestial
from ostk.physics.environment.object.celestial import Earth


class TestCelestial:
    def test_model_is_defined_success(self):
        earth = Earth.spherical()

        assert earth.gravitational_model_is_defined() is True
        assert earth.magnetic_model_is_defined() is False
        assert earth.atmospheric_model_is_defined() is False

    def test_frame_type_has_no_undefined(self):
        assert Celestial.string_from_frame_type(Celestial.FrameType.NED) == "NED"
        assert not hasattr(Celestial.FrameType, "Undefined")
