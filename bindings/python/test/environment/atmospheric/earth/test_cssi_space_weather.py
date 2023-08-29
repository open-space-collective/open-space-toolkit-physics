# Apache License 2.0

import pytest

from datetime import datetime

from ostk.core.filesystem import File

from ostk.physics.time import Scale
from ostk.physics.time import Instant

from ostk.physics.environment.atmospheric.earth import CSSISpaceWeather


class TestCSSISpaceWeather:
    def test_str_success(self, cssi_space_weather: CSSISpaceWeather):
        assert str(cssi_space_weather).startswith("-- CSSI Space Weather --")

    def test_repr_success(self, cssi_space_weather: CSSISpaceWeather):
        assert repr(cssi_space_weather).startswith("-- CSSI Space Weather --")

    def test_is_defined_success(self, cssi_space_weather: CSSISpaceWeather):
        assert cssi_space_weather.is_defined() is True

    def test_access_last_observation_date_success(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        assert (
            cssi_space_weather.access_last_observation_date().to_string() == "2023-06-19"
        )

    def test_access_observation_interval_success(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        assert (
            cssi_space_weather.access_observation_interval().to_string()
            == "[2018-01-01 00:00:00 - 2023-06-20 00:00:00[ [UTC]"
        )

    def test_access_observation_at_success(self, cssi_space_weather: CSSISpaceWeather):
        observation: Observation = cssi_space_weather.access_observation_at(
            Instant.date_time(datetime(2023, 6, 19, 0, 0, 0), Scale.UTC)
        )

        assert observation.date.to_string() == "2023-06-19"
        assert observation.kp_sum == 177
        assert observation.f107_obs == pytest.approx(168.8)
        assert observation.f107_obs_center_81 == pytest.approx(160.1)

    def test_access_daily_prediction_interval_success(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        assert (
            cssi_space_weather.access_daily_prediction_interval().to_string()
            == "[2023-06-20 00:00:00 - 2023-08-04 00:00:00[ [UTC]"
        )

    def test_access_daily_prediction_at_success(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        prediction: Reading = cssi_space_weather.access_daily_prediction_at(
            Instant.date_time(datetime(2023, 8, 3, 0, 0, 0), Scale.UTC)
        )

        assert prediction.date.to_string() == "2023-08-03"
        assert prediction.kp_sum == 104
        assert prediction.f107_obs == pytest.approx(165.1)
        assert prediction.f107_obs_center_81 == pytest.approx(157.4)

    def test_access_monthly_prediction_interval_success(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        assert (
            cssi_space_weather.access_monthly_prediction_interval().to_string()
            == "[2023-08-01 00:00:00 - 2029-01-01 00:00:00] [UTC]"
        )

    def test_access_monthly_prediction_at_success(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        prediction: Reading = cssi_space_weather.access_monthly_prediction_at(
            Instant.date_time(datetime(2029, 1, 1, 0, 0, 0), Scale.UTC)
        )

        assert prediction.date.to_string() == "2029-01-01"
        assert prediction.f107_obs == pytest.approx(83.5)
        assert prediction.f107_obs_center_81 == pytest.approx(83.6)

    def test_access_reading_at_success(self, cssi_space_weather: CSSISpaceWeather):
        reading: Reading = cssi_space_weather.access_reading_at(
            Instant.date_time(datetime(2029, 1, 1, 0, 0, 0), Scale.UTC)
        )

        assert reading.date.to_string() == "2029-01-01"
        assert reading.f107_obs == pytest.approx(83.5)
        assert reading.f107_obs_center_81 == pytest.approx(83.6)
        assert reading.f107_data_type == "PRM"

    def test_access_last_reading_where_success(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        reading: Reading = cssi_space_weather.access_last_reading_where(
            lambda reading: reading.f107_data_type == "PRD",
            Instant.date_time(datetime(2023, 12, 1, 0, 0, 0), Scale.UTC),
        )

        assert reading.date.to_string() == "2023-08-03"
        assert reading.f107_data_type == "PRD"

    def test_access_last_reading_where_failure(
        self, cssi_space_weather: CSSISpaceWeather
    ):
        with pytest.raises(RuntimeError):
            cssi_space_weather.access_last_reading_where(
                lambda reading: reading.f107_data_type == "FAKE",
                Instant.date_time(datetime(2029, 1, 1, 0, 0, 0), Scale.UTC),
            )

    def test_undefined_success(self):
        assert CSSISpaceWeather.undefined() is not None

    def test_load_success(self, cssi_space_weather_file: File):
        assert CSSISpaceWeather.load(cssi_space_weather_file) is not None

    def test_load_legacy_success(self, cssi_space_weather_legacy_file: File):
        assert CSSISpaceWeather.load_legacy(cssi_space_weather_legacy_file) is not None
