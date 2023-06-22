# Apache License 2.0

from datetime import datetime

from ostk.core.filesystem import File

from ostk.physics.time import Scale
from ostk.physics.time import Instant

from ostk.physics.environment.atmospheric.earth.weather import CSSISpaceWeather


class TestCSSISpaceWeather:
    def test_str_success(self, cssi_space_weather: CSSISpaceWeather):
        assert str(cssi_space_weather).startswith("-- CSSI Space Weather --")

    def test_repr_success(self, cssi_space_weather: CSSISpaceWeather):
        assert repr(cssi_space_weather).startswith("-- CSSI Space Weather --")

    def test_is_defined_success(self, cssi_space_weather: CSSISpaceWeather):
        assert cssi_space_weather.is_defined() is True

    def test_access_last_observation_date_success(self, cssi_space_weather: CSSISpaceWeather):
        assert cssi_space_weather.access_last_observation_date().to_string() == "2020-10-29"

    def test_access_observation_interval_success(self, cssi_space_weather: CSSISpaceWeather):
        assert cssi_space_weather.access_observation_interval().to_string()

    def test_access_observation_at_success(self, cssi_space_weather: CSSISpaceWeather):
        assert cssi_space_weather.access_observation_at() == Instant.date_time(
            datetime(2017, 1, 1, 0, 0, 0), Scale.UTC
        )

    def test_access_daily_prediction_interval_success(self, cssi_space_weather: CSSISpaceWeather):
        assert (
            cssi_space_weather.access_daily_prediction_interval().to_string()
            == "[2020-10-23 00:00:00 - 2020-10-29 00:00:00] [UTC]"
        )

    def test_access_daily_prediction_at_success(self, cssi_space_weather: CSSISpaceWeather):
        assert (
            cssi_space_weather.access_daily_prediction_at().to_string()
            == "[2020-10-30 00:00:00 - 2021-10-29 00:00:00] [UTC]"
        )

    def test_access_monthly_prediction_interval_success(self, cssi_space_weather: CSSISpaceWeather):
        assert (
            cssi_space_weather.access_daily_prediction_interval().to_string()
            == "[2020-10-23 00:00:00 - 2020-10-29 00:00:00] [UTC]"
        )

    def test_access_monthly_prediction_at_success(self, cssi_space_weather: CSSISpaceWeather):
        assert cssi_space_weather.access_monthly_prediction_at() == Instant.date_time(
            datetime(2017, 1, 1, 0, 0, 0), Scale.UTC
        )

    def test_undefined_success(self):
        assert CSSISpaceWeather.undefined() is not None

    def test_load_success(self, cssi_space_weather_file: File):
        assert CSSISpaceWeather.load(cssi_space_weather_file) is not None
