# Apache License 2.0

import pytest

from ostk.physics.environment.ephemeris import SPICE


@pytest.fixture
def spice() -> SPICE:
    return SPICE(SPICE.Object.Earth)


class TestSPICE:
    def test_constructor_success(self):
        spice = SPICE(SPICE.Object.Earth)

        assert spice is not None
        assert spice.is_defined() is True

    def test_is_defined_success(self, spice: SPICE):
        assert spice.is_defined() is True

    def test_access_frame_success(self, spice: SPICE):
        frame = spice.access_frame()

        assert frame is not None

    def test_string_from_object_success(self):
        assert SPICE.string_from_object(SPICE.Object.Sun) == "Sun"
        assert SPICE.string_from_object(SPICE.Object.Earth) == "Earth"
        assert SPICE.string_from_object(SPICE.Object.Moon) == "Moon"
        assert SPICE.string_from_object(SPICE.Object.Mars) == "Mars"
