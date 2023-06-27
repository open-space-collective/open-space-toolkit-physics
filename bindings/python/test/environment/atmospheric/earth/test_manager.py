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
        assert manager.get_local_repository().to_string() == os.environ.get(
            "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY"
        )

    def test_get_cssi_space_weather_directory_success(self, manager: Manager):
        assert isinstance(manager.get_cssi_space_weather_directory(), Directory)
        assert (
            manager.get_cssi_space_weather_directory().to_string()
            == str(
                os.environ.get(
                    "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY"
                )
            )
            + "/CSSISpaceWeather"
        )

    def test_get_remote_url_success(self, manager: Manager):
        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == "https://celestrak.org/SpaceData/"

    def test_get_cssi_space_weather_array_success(self, manager: Manager):
        assert isinstance(manager.get_cssi_space_weather_array(), list)
        assert len(manager.get_cssi_space_weather_array()) == 0

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

    def test_get_kp_3_hour_solar_indices_at_success(self, manager: Manager):
        kp_indices = manager.get_kp_3_hour_solar_indices_at(
            Instant.date_time(datetime(2023, 6, 18, 12, 34, 56), Scale.UTC)
        )

        assert kp_indices == [27, 20, 13, 20, 17, 17, 27, 20]

    def test_get_ap_3_hour_solar_indices_at_success(self, manager: Manager):
        ap_indices = manager.get_ap_3_hour_solar_indices_at(
            Instant.date_time(datetime(2023, 6, 18, 12, 34, 56), Scale.UTC)
        )

        assert ap_indices == [12, 7, 5, 7, 6, 6, 12, 7, 8]

    def test_get_f107_solar_flux_at_success(self, manager: Manager):
        flux = manager.get_f107_solar_flux_at(
            Instant.date_time(datetime(2023, 6, 18, 12, 34, 56), Scale.UTC)
        )

        assert flux == pytest.approx(164.1)

    def test_get_f107_solar_flux_81_day_avg_at_success(self, manager: Manager):
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
        assert manager.get_local_repository().to_string() == os.environ.get(
            "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY"
        )

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

    def test_set_remote_url_success(self, manager: Manager):
        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == "https://celestrak.org/SpaceData/"

        manager.set_remote_url(URL.parse("https://celestrak.org/SpaceData/"))

        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == "https://celestrak.org/SpaceData/"

    def test_load_cssi_space_weather_success(
        self, manager: Manager, cssi_space_weather: CSSISpaceWeather
    ):
        assert len(manager.get_cssi_space_weather_array()) == 0

        manager.load_cssi_space_weather(cssi_space_weather)

        assert len(manager.get_cssi_space_weather_array()) == 1

    def test_fetch_latest_cssi_space_weather_success(self, manager: Manager):
        file: File = manager.fetch_latest_cssi_space_weather()

        assert isinstance(file, File)
        assert file.exists()

        file.remove()

    def test_reset_success(self, manager: Manager, cssi_space_weather: CSSISpaceWeather):
        manager.load_cssi_space_weather(cssi_space_weather)

        assert len(manager.get_cssi_space_weather_array()) == 1

        manager.reset()

        assert len(manager.get_cssi_space_weather_array()) == 0

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
        assert manager.default_local_repository().to_string() == os.environ.get(
            "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY"
        )

    def test_default_local_repository_lock_timeout_success(self, manager: Manager):
        assert isinstance(manager.default_local_repository_lock_timeout(), Duration)
        assert manager.default_local_repository_lock_timeout().in_seconds() == 60.0

    def test_default_remote_url_success(self, manager: Manager):
        assert isinstance(manager.default_remote_url(), URL)
        assert (
            manager.default_remote_url().to_string() == "https://celestrak.org/SpaceData/"
        )
