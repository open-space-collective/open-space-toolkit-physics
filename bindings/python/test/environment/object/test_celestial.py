# Apache License 2.0

import pytest

from ostk.physics.coordinate import Frame
from ostk.physics.environment.ephemeris import Analytical
from ostk.physics.environment.object import Celestial
from ostk.physics.environment.object.celestial import Earth
from ostk.physics.unit import Length


class TestCelestial:
    def test_model_is_defined_success(self):
        earth = Earth.spherical()

        assert earth.gravitational_model_is_defined() is True
        assert earth.magnetic_model_is_defined() is False
        assert earth.atmospheric_model_is_defined() is False

    def test_frame_type_has_no_undefined(self):
        assert Celestial.string_from_frame_type(Celestial.FrameType.NED) == "NED"
        assert not hasattr(Celestial.FrameType, "Undefined")

    def test_get_frame_success(self):
        earth = Earth.spherical()

        assert earth.get_frame() is not None

    def test_constructor_without_gravitational_constants(self):
        celestial = Celestial(
            "Some Planet",
            Celestial.CelestialType.Earth,
            None,
            Length.kilometers(1000.0),
            0.1,
            None,
            None,
            Analytical(Frame.ITRF()),
            None,
            None,
            None,
        )

        assert celestial.get_equatorial_radius() == Length.kilometers(1000.0)
        assert celestial.get_flattening() == pytest.approx(0.1)

        with pytest.raises(RuntimeError):
            celestial.get_gravitational_parameter()

        with pytest.raises(RuntimeError):
            celestial.get_j2()

        with pytest.raises(RuntimeError):
            celestial.get_j4()
