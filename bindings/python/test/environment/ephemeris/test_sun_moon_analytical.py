# Apache License 2.0

import pytest

from ostk.physics.environment.ephemeris import SunMoonAnalytical


@pytest.fixture(
    params=[
        SunMoonAnalytical.Body.Sun,
        SunMoonAnalytical.Body.Moon,
    ]
)
def sun_moon_analytical(request) -> SunMoonAnalytical:
    return SunMoonAnalytical(request.param)


class TestSunMoonAnalytical:
    def test_constructor_success(self, sun_moon_analytical: SunMoonAnalytical):
        assert sun_moon_analytical is not None

    def test_is_defined_success(self, sun_moon_analytical: SunMoonAnalytical):
        assert sun_moon_analytical.is_defined() is True

    def test_access_frame_success(self, sun_moon_analytical: SunMoonAnalytical):
        accessed_frame = sun_moon_analytical.access_frame()

        assert accessed_frame is not None

    def test_get_body_success(self, sun_moon_analytical: SunMoonAnalytical):
        body = sun_moon_analytical.get_body()

        assert body in (SunMoonAnalytical.Body.Sun, SunMoonAnalytical.Body.Moon)

    def test_string_from_body_success(self):
        assert SunMoonAnalytical.string_from_body(SunMoonAnalytical.Body.Sun) == "Sun"
        assert SunMoonAnalytical.string_from_body(SunMoonAnalytical.Body.Moon) == "Moon"
