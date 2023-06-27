# Apache License 2.0

import pytest

import pathlib

from ostk.core.filesystem import Path
from ostk.core.filesystem import File

from ostk.io import URL

from ostk.physics.environment.atmospheric.earth import Manager
from ostk.physics.environment.atmospheric.earth import CSSISpaceWeather


@pytest.fixture
def data_directory_path() -> str:
    return f"{pathlib.Path(__file__).parent.absolute()}/data"


@pytest.fixture
def cssi_space_weather_file(data_directory_path: str) -> File:
    return File.path(Path.parse(f"{data_directory_path}/SW-Last5Years.test.csv"))


@pytest.fixture
def cssi_space_weather(cssi_space_weather_file: File) -> CSSISpaceWeather:
    return CSSISpaceWeather.load(cssi_space_weather_file)


@pytest.fixture
def manager() -> Manager:
    manager = Manager.get()

    manager.set_mode(Manager.Mode.Automatic)
    manager.set_remote_url(
        URL.parse("https://celestrak.org/SpaceData/")
    )  # SW-Last5Years.csv

    yield manager

    manager.reset()
    manager.clear_local_repository()
