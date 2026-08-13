# Apache License 2.0

from datetime import datetime

import pytest

from ostk.physics.time import Scale
from ostk.physics.time import Instant
from ostk.physics.coordinate import Transform
from ostk.physics.coordinate.frame.provider import CIRF


@pytest.fixture
def cirf() -> CIRF:
    return CIRF()


@pytest.fixture
def instant() -> Instant:
    return Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)


class TestCIRF:
    def test_constructor_success(self):
        assert isinstance(CIRF(), CIRF)

    def test_is_defined_success(self, cirf: CIRF):
        assert cirf.is_defined() is True

    def test_get_transform_at_success(self, cirf: CIRF, instant: Instant):
        assert isinstance(cirf.get_transform_at(instant), Transform)

    def test_compute_cip_coordinates_success(self, instant: Instant):
        modified_julian_date_tt: float = instant.get_modified_julian_date(Scale.TT)

        x, y, s = CIRF.compute_cip_coordinates(
            modified_julian_date_tt=modified_julian_date_tt,
            interpolate=True,
        )

        assert isinstance(x, float)
        assert isinstance(y, float)
        assert isinstance(s, float)

    def test_clear_xys_cache_success(self, instant: Instant):
        modified_julian_date_tt: float = instant.get_modified_julian_date(Scale.TT)

        CIRF.compute_cip_coordinates(
            modified_julian_date_tt=modified_julian_date_tt,
            interpolate=True,
        )

        assert CIRF.clear_xys_cache() is None

        x, y, s = CIRF.compute_cip_coordinates(
            modified_julian_date_tt=modified_julian_date_tt,
            interpolate=True,
        )

        assert isinstance(x, float)
        assert isinstance(y, float)
        assert isinstance(s, float)

    def test_xys_interpolation_enabled_success(self):
        initial: bool = CIRF.is_xys_interpolation_enabled()

        try:
            CIRF.set_xys_interpolation_enabled(interpolation_enabled=False)
            assert CIRF.is_xys_interpolation_enabled() is False

            CIRF.set_xys_interpolation_enabled(interpolation_enabled=True)
            assert CIRF.is_xys_interpolation_enabled() is True
        finally:
            CIRF.set_xys_interpolation_enabled(interpolation_enabled=initial)
