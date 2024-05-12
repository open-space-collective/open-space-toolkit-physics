# Apache License 2.0

import pytest

import pathlib

from ostk.core.filesystem import Path
from ostk.core.filesystem import File

from ostk.physics.data import Manager, Manifest


@pytest.fixture
def data_directory_path() -> str:
    return f"{pathlib.Path(__file__).parent.absolute()}/data"


@pytest.fixture
def manifest_file(data_directory_path: str) -> File:
    return File.path(Path.parse(f"{data_directory_path}/manifest.json"))


@pytest.fixture
def manifest(manifest_file: File) -> Manifest:
    return Manifest.load(manifest_file)


@pytest.fixture
def manager() -> Manager:
    manager = Manager.get()

    yield manager

    manager.reset()
