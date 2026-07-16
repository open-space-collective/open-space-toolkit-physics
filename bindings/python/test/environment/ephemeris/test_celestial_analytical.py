# Apache License 2.0

import pytest

from ostk.physics.environment.ephemeris import CelestialAnalytical
from ostk.physics.environment.object import Celestial


@pytest.fixture(
    params=[
        Celestial.CelestialType.Sun,
        Celestial.CelestialType.Moon,
    ]
)
def celestial_analytical(request) -> CelestialAnalytical:
    return CelestialAnalytical(request.param)


class TestCelestialAnalytical:
    def test_constructor_success(self, celestial_analytical: CelestialAnalytical):
        assert celestial_analytical is not None

    def test_constructor_unsupported_type_failure(self):
        with pytest.raises(Exception):
            CelestialAnalytical(Celestial.CelestialType.Earth)

    def test_is_defined_success(self, celestial_analytical: CelestialAnalytical):
        assert celestial_analytical.is_defined() is True

    def test_access_frame_success(self, celestial_analytical: CelestialAnalytical):
        accessed_frame = celestial_analytical.access_frame()

        assert accessed_frame is not None

    def test_get_type_success(self, celestial_analytical: CelestialAnalytical):
        type = celestial_analytical.get_type()

        assert type in (Celestial.CelestialType.Sun, Celestial.CelestialType.Moon)
