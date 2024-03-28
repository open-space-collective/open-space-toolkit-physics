# Apache License 2.0

import pytest

from datetime import datetime
import pathlib
import os

from ostk.core.filesystem import Path
from ostk.core.filesystem import File
from ostk.core.filesystem import Directory

from ostk.io import URL

from ostk.physics.time import Scale
from ostk.physics.time import Instant
from ostk.physics.time import Duration

from ostk.physics.environment.atmospheric.earth import Manager
from ostk.physics.environment.atmospheric.earth import CSSISpaceWeather


class TestManager:
    def test_get_mode_success(self, manager: Manager):
        assert manager.get_mode() == Manager.Mode.Automatic

    def test_get_local_repository_success(self, manager: Manager):
        assert isinstance(manager.get_local_repository(), Directory)
        assert len(str(manager.get_local_repository().to_string())) > 0

    def test_get_cssi_space_weather_directory_success(self, manager: Manager):
        assert isinstance(manager.get_cssi_space_weather_directory(), Directory)
        assert len(str(manager.get_cssi_space_weather_directory().to_string())) > 0

    def test_get_loaded_cssi_space_weather_success(self, manager: Manager):
        assert isinstance(manager.get_loaded_cssi_space_weather(), CSSISpaceWeather)
        assert not manager.get_loaded_cssi_space_weather().is_defined()

    def test_get_cssi_space_weather_at_success(self, manager: Manager):
        try:
            cssi_space_weather: CSSISpaceWeather = manager.get_cssi_space_weather_at(
                Instant.now() - Duration.days(8.0)
            )
        except RuntimeError:
            manager.reset()
            manager.clear_local_repository()
            cssi_space_weather: CSSISpaceWeather = manager.get_cssi_space_weather_at(
                Instant.now() - Duration.days(5.0)
            )

        assert isinstance(cssi_space_weather, CSSISpaceWeather)

    def test_get_kp_3_hour_solar_indices_at_success(
        self, manager: Manager, cssi_space_weather: CSSISpaceWeather
    ):
        # load test file data for comparison
        manager.load_cssi_space_weather(cssi_space_weather)

        kp_indices = manager.get_kp_3_hour_solar_indices_at(
            Instant.date_time(datetime(2023, 6, 18, 12, 34, 56), Scale.UTC)
        )

        assert kp_indices == [27, 20, 13, 20, 17, 17, 27, 20]

    def test_get_ap_3_hour_solar_indices_at_success(
        self, manager: Manager, cssi_space_weather: CSSISpaceWeather
    ):
        # load test file data for comparison
        manager.load_cssi_space_weather(cssi_space_weather)

        ap_indices = manager.get_ap_3_hour_solar_indices_at(
            Instant.date_time(datetime(2023, 6, 18, 12, 34, 56), Scale.UTC)
        )

        assert ap_indices == [12, 7, 5, 7, 6, 6, 12, 7]

    def test_get_ap_daily_index_at_success(
        self, manager: Manager, cssi_space_weather: CSSISpaceWeather
    ):
        # load test file data for comparison
        manager.load_cssi_space_weather(cssi_space_weather)

        ap_index = manager.get_ap_daily_index_at(
            Instant.date_time(datetime(2023, 6, 18, 12, 34, 56), Scale.UTC)
        )

        assert ap_index == 8

    def test_get_f107_solar_flux_at_success(
        self, manager: Manager, cssi_space_weather: CSSISpaceWeather
    ):
        # load test file data for comparison
        manager.load_cssi_space_weather(cssi_space_weather)

        flux = manager.get_f107_solar_flux_at(
            Instant.date_time(datetime(2023, 6, 18, 12, 34, 56), Scale.UTC)
        )

        assert flux == pytest.approx(164.1)

    def test_get_f107_solar_flux_81_day_avg_at_success(
        self, manager: Manager, cssi_space_weather: CSSISpaceWeather
    ):
        # load test file data for comparison
        manager.load_cssi_space_weather(cssi_space_weather)

        flux_avg = manager.get_f107_solar_flux_81_day_avg_at(
            Instant.date_time(datetime(2018, 1, 1, 12, 34, 56), Scale.UTC)
        )

        assert flux_avg == pytest.approx(71.4)

    def test_set_mode_success(self, manager: Manager):
        assert manager.get_mode() == Manager.Mode.Automatic

        manager.set_mode(Manager.Mode.Manual)

        assert manager.get_mode() == Manager.Mode.Manual

    def test_set_local_repository_success(self, manager: Manager):
        assert isinstance(manager.get_local_repository(), Directory)

        manager.set_local_repository(
            Directory.path(
                Path.parse("./.open-space-toolkit/physics/environment/atmospheric/earth")
            )
        )

        assert isinstance(manager.get_local_repository(), Directory)
        assert (
            manager.get_local_repository().to_string()
            == "./.open-space-toolkit/physics/environment/atmospheric/earth"
        )

    def test_load_cssi_space_weather_success(
        self, manager: Manager, cssi_space_weather: CSSISpaceWeather
    ):
        assert not manager.get_loaded_cssi_space_weather().is_defined()

        manager.load_cssi_space_weather(cssi_space_weather)

        assert manager.get_loaded_cssi_space_weather().is_defined()

    def test_fetch_latest_cssi_space_weather_success(self, manager: Manager):
        file: File = manager.fetch_latest_cssi_space_weather()

        assert isinstance(file, File)
        assert file.exists()

        file.remove()

    def test_reset_success(self, manager: Manager, cssi_space_weather: CSSISpaceWeather):
        manager.load_cssi_space_weather(cssi_space_weather)

        assert manager.get_loaded_cssi_space_weather().is_defined()

        manager.reset()

        assert not manager.get_loaded_cssi_space_weather().is_defined()

    def test_clear_local_repository_success(self, manager: Manager):
        assert manager.get_local_repository().exists()
        assert manager.get_cssi_space_weather_directory().exists()
        pathlib.Path(
            str(manager.get_cssi_space_weather_directory().get_path().to_string())
            + "/toto"
        ).touch()
        assert not manager.get_local_repository().is_empty()

        manager.clear_local_repository()

        assert manager.get_local_repository().exists()
        assert manager.get_cssi_space_weather_directory().is_empty()

    def test_get_success(self):
        assert isinstance(Manager.get(), Manager)

    def test_default_mode_success(self, manager: Manager):
        assert manager.default_mode() == Manager.Mode.Automatic

    def test_default_local_repository_success(self, manager: Manager):
        assert isinstance(manager.default_local_repository(), Directory)
        assert len(str(manager.default_local_repository().to_string())) > 0

    def test_default_local_repository_lock_timeout_success(self, manager: Manager):
        assert isinstance(manager.default_local_repository_lock_timeout(), Duration)
        assert manager.default_local_repository_lock_timeout().in_seconds() == 60.0
