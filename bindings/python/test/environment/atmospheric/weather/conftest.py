# Apache License 2.0

import pytest

import pathlib

from ostk.core.filesystem import Path
from ostk.core.filesystem import File

from ostk.physics.environment.atmospheric.earth.weather import CSSISpaceWeather


@pytest.fixture
def data_directory_path() -> str:
    return f"{pathlib.Path(__file__).parent.absolute()}/data"


@pytest.fixture
def cssi_space_weather_file(data_directory_path: str) -> File:
    return File.path(Path.parse(f"{data_directory_path}/SW-Last5Years.test.csv"))


@pytest.fixture
def cssi_space_weather(cssi_space_weather_file: File) -> CSSISpaceWeather:
    return CSSISpaceWeather.load(cssi_space_weather_file)
