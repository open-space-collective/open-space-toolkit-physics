# Apache License 2.0


from datetime import datetime

import pytest

from ostk.core.filesystem import File

from ostk.physics.time import Scale
from ostk.physics.time import Instant
from ostk.physics.coordinate.frame.provider.iers import Finals2000A


class TestFinals2000A:
    def test_str_success(self, finals_2000a: Finals2000A):
        assert str(finals_2000a).startswith("-- Finals 2000A --")

    def test_repr_success(self, finals_2000a: Finals2000A):
        assert repr(finals_2000a).startswith("-- Finals 2000A --")

    def test_get_interval_success(self, finals_2000a: Finals2000A):
        assert (
            finals_2000a.get_interval().to_string()
            == "[1992-01-01 00:00:00 - 2021-12-26 00:00:00] [UTC]"
        )

    def test_get_polar_motion_at_success(self, finals_2000a: Finals2000A):
        assert list(
            finals_2000a.get_polar_motion_at(
                Instant.date_time(datetime(2020, 10, 31, 0, 0, 0), Scale.UTC)
            )
        ) == [0.160621, 0.297128]

    def test_get_polar_motion_at_not_tabulated_returns_none(
        self, finals_2000a: Finals2000A
    ):
        # The test file has rows without any value after 2021-11-06 (until 2021-12-26)
        assert (
            finals_2000a.get_polar_motion_at(
                Instant.date_time(datetime(2021, 11, 20, 0, 0, 0), Scale.UTC)
            )
            is None
        )

    def test_get_polar_motion_at_outside_the_data_raises(self, finals_2000a: Finals2000A):
        with pytest.raises(RuntimeError):
            finals_2000a.get_polar_motion_at(
                Instant.date_time(datetime(2030, 1, 1, 0, 0, 0), Scale.UTC)
            )

    def test_get_ut1_minus_utc_at_success(self, finals_2000a: Finals2000A):
        assert (
            finals_2000a.get_ut1_minus_utc_at(
                Instant.date_time(datetime(2020, 10, 31, 0, 0, 0), Scale.UTC)
            )
            == -0.17524010000000001
        )

    def test_get_lod_at_success(self, finals_2000a: Finals2000A):
        assert (
            finals_2000a.get_lod_at(
                Instant.date_time(datetime(2015, 10, 31, 0, 0, 0), Scale.UTC)
            )
            == 1.5646
        )
        assert (
            finals_2000a.get_lod_at(
                Instant.date_time(datetime(2020, 10, 31, 0, 0, 0), Scale.UTC)
            )
            is None
        )

    def test_get_data_at_success(self, finals_2000a: Finals2000A):
        data: Finals2000A.Data = finals_2000a.get_data_at(
            Instant.date_time(datetime(2020, 10, 31, 0, 0, 0), Scale.UTC)
        )

        assert isinstance(data, Finals2000A.Data)

        assert data.year == 20
        assert data.month == 10
        assert data.day == 30
        assert data.mjd == 59153.0
        assert data.polar_motionflag == "P"
        assert data.x_a == 0.16062100000000001
        assert data.x_error_a == 0.000892
        assert data.y_a == 0.297128
        assert data.y_error_a == 0.00066399999999999999
        assert data.ut1_minus_utc_flag == "P"
        assert data.ut1_minus_utc_a == -0.17524010000000001
        assert data.ut1_minus_utc_error_a == 0.0002041
        assert data.lod_a is None
        assert data.lod_error_a is None
        assert data.nutation_flag == "P"
        assert data.dx_a == 0.021999999999999999
        assert data.dx_error_a == 0.128
        assert data.dy_a == 0.17899999999999999
        assert data.dy_error_a == 0.16
        assert data.x_b is None
        assert data.y_b is None
        assert data.ut1_minus_utc_b is None
        assert data.dx_b is None
        assert data.dy_b is None

    def test_load_success(self, finals_2000a_file: File):
        assert Finals2000A.load(finals_2000a_file) is not None
