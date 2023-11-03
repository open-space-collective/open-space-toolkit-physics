# Apache License 2.0

import pytest

import os

from ostk.core.filesystem import Path, Directory, PermissionSet

from ostk.io import URL

from ostk.physics.time import Duration
from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel
from ostk.physics.environment.gravitational.earth import (
    Manager as EarthGravitationalModelManager,
)


@pytest.fixture
def manager() -> EarthGravitationalModelManager:
    manager = EarthGravitationalModelManager.get()

    manager.set_local_repository(
        EarthGravitationalModelManager.default_local_repository()
    )

    yield manager

    # This reset is important so that other test modules are not affected
    manager.reset()


class TestManager:
    def test_get_mode_success(self, manager: EarthGravitationalModelManager):
        assert manager.get_mode() == EarthGravitationalModelManager.Mode.Automatic

    def test_has_data_files_for_type_success(
        self, manager: EarthGravitationalModelManager
    ):
        assert manager.has_data_files_for_type(EarthGravitationalModel.Type.WGS84) == True
        assert manager.has_data_files_for_type(EarthGravitationalModel.Type.EGM84) == True
        assert manager.has_data_files_for_type(EarthGravitationalModel.Type.EGM96) == True
        assert (
            manager.has_data_files_for_type(EarthGravitationalModel.Type.EGM2008) == True
        )

    def test_get_local_repository_success(self, manager: EarthGravitationalModelManager):
        assert isinstance(manager.get_local_repository(), Directory)
        assert len(str(manager.get_local_repository().to_string())) > 0

    def test_fetch_data_files_for_type_success(
        self, manager: EarthGravitationalModelManager
    ):
        test_directory = Directory.path(
            manager.get_local_repository().get_path() + Path.parse("/test")
        )
        if test_directory.exists():
            test_directory.remove()

        test_directory.create(PermissionSet.rw(), PermissionSet.r(), PermissionSet.r())
        manager.set_local_repository(test_directory)

        manager.fetch_data_files_for_type(EarthGravitationalModel.Type.WGS84)

    def test_set_mode_success(self, manager: EarthGravitationalModelManager):
        assert manager.get_mode() == EarthGravitationalModelManager.Mode.Automatic

        manager.set_mode(EarthGravitationalModelManager.Mode.Manual)

        assert manager.get_mode() == EarthGravitationalModelManager.Mode.Manual

    def test_set_local_repository_success(self, manager: EarthGravitationalModelManager):
        manager.set_local_repository(
            Directory.path(
                Path.parse(
                    "./.open-space-toolkit/physics/environment/gravitational/earth2"
                )
            )
        )

        assert isinstance(manager.get_local_repository(), Directory)
        assert (
            manager.get_local_repository().to_string()
            == "./.open-space-toolkit/physics/environment/gravitational/earth2"
        )

    def test_default_local_repository_success(
        self, manager: EarthGravitationalModelManager
    ):
        assert isinstance(
            EarthGravitationalModelManager.default_local_repository(), Directory
        )
        assert len(str(manager.default_local_repository().to_string())) > 0

    def test_default_mode_success(self, manager: EarthGravitationalModelManager):
        assert manager.default_mode() == EarthGravitationalModelManager.Mode.Automatic

    def test_default_local_repository_lock_timeout_success(
        self, manager: EarthGravitationalModelManager
    ):
        assert isinstance(manager.default_local_repository_lock_timeout(), Duration)
        assert manager.default_local_repository_lock_timeout().in_seconds() == 60.0
