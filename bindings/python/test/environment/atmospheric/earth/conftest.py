# Apache License 2.0

import pytest

import pathlib

from ostk.core.filesystem import Path
from ostk.core.filesystem import File

from ostk.io import URL

from ostk.physics.coordinate import Frame
from ostk.physics.environment.object.celestial import Sun
from ostk.physics.environment.atmospheric.earth import Manager
from ostk.physics.environment.atmospheric.earth import CSSISpaceWeather
from ostk.physics.environment.atmospheric.earth import Exponential
from ostk.physics.environment.atmospheric.earth import NRLMSISE00
from ostk.physics.environment.gravitational import Earth as EarthGravityModel


@pytest.fixture
def data_directory_path() -> str:
    return f"{pathlib.Path(__file__).parent.absolute()}/data"


@pytest.fixture
def cssi_space_weather_file(data_directory_path: str) -> File:
    return File.path(Path.parse(f"{data_directory_path}/SW-Last5Years.test.csv"))


@pytest.fixture
def cssi_space_weather_legacy_file(data_directory_path: str) -> File:
    return File.path(Path.parse(f"{data_directory_path}/SpaceWeather-All-v1.2.test.txt"))


@pytest.fixture
def cssi_space_weather(cssi_space_weather_file: File) -> CSSISpaceWeather:
    return CSSISpaceWeather.load(cssi_space_weather_file)


@pytest.fixture
def manager() -> Manager:
    manager = Manager.get()

    yield manager

    manager.reset()
    manager.clear_local_repository()


@pytest.fixture
def exponential_model() -> Exponential:
    return Exponential()


@pytest.fixture
def nrlmsise00_model() -> NRLMSISE00:
    return NRLMSISE00(
        NRLMSISE00.InputDataType.CSSISpaceWeatherFile,
        160.0,
        160.0,
        3.0,
        Frame.ITRF(),
        EarthGravityModel.WGS84.equatorial_radius,
        EarthGravityModel.WGS84.flattening,
        Sun.spherical(),
    )
