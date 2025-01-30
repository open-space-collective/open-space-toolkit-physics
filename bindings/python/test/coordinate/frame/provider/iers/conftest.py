# Apache License 2.0

import pytest

import pathlib

from ostk.core.filesystem import Path
from ostk.core.filesystem import File
from ostk.physics.coordinate.frame.provider.iers import BulletinA
from ostk.physics.coordinate.frame.provider.iers import Finals2000A


@pytest.fixture
def data_directory_path() -> str:
    return f"{pathlib.Path(__file__).parent.absolute()}/data"


@pytest.fixture
def bulletin_a_file(data_directory_path: str) -> File:
    return File.path(Path.parse(f"{data_directory_path}/ser7.dat"))


@pytest.fixture
def bulletin_a(bulletin_a_file: File) -> BulletinA:
    return BulletinA.load(bulletin_a_file)


@pytest.fixture
def finals_2000a_file(data_directory_path: str) -> File:
    return File.path(Path.parse(f"{data_directory_path}/finals2000A.data"))


@pytest.fixture
def finals_2000a(finals_2000a_file: File) -> Finals2000A:
    return Finals2000A.load(finals_2000a_file)
