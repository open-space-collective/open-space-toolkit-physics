# Apache License 2.0

import pytest

from ostk.core.filesystem import Path, Directory, PermissionSet

from ostk.physics.environment.magnetic import Earth as EarthMagneticModel
from ostk.physics.environment.magnetic.earth import (
    Manager as EarthMagneticModelManager,
)


@pytest.fixture
def manager() -> EarthMagneticModelManager:
    manager = EarthMagneticModelManager.get()

    yield manager

    # This reset is important so that other test modules are not affected
    manager.reset()


class TestManager:
    def test_get_mode_success(self, manager: EarthMagneticModelManager):
        assert manager.get_mode() == EarthMagneticModelManager.Mode.Automatic

    def test_has_data_files_for_type_success(self, manager: EarthMagneticModelManager):
        assert manager.has_data_files_for_type(EarthMagneticModel.Type.EMM2010) == True

    def test_get_local_repository_success(self, manager: EarthMagneticModelManager):
        assert isinstance(manager.get_local_repository(), Directory)
        assert len(str(manager.get_local_repository().to_string())) > 0

    def test_fetch_data_files_for_type_success(self, manager: EarthMagneticModelManager):
        test_directory = Directory.path(
            manager.get_local_repository().get_path() + Path.parse("/test")
        )
        if test_directory.exists():
            test_directory.remove()

        test_directory.create(PermissionSet.rw(), PermissionSet.r(), PermissionSet.r())
        manager.set_local_repository(test_directory)

        manager.fetch_data_files_for_type(EarthMagneticModel.Type.EMM2010)

    def test_set_mode_success(self, manager: EarthMagneticModelManager):
        assert manager.get_mode() == EarthMagneticModelManager.Mode.Automatic

        manager.set_mode(EarthMagneticModelManager.Mode.Manual)

        assert manager.get_mode() == EarthMagneticModelManager.Mode.Manual

    def test_set_local_repository_success(self, manager: EarthMagneticModelManager):
        manager.set_local_repository(
            Directory.path(
                Path.parse("./.open-space-toolkit/physics/environment/magnetic/earth2")
            )
        )

        assert isinstance(manager.get_local_repository(), Directory)
        assert (
            manager.get_local_repository().to_string()
            == "./.open-space-toolkit/physics/environment/magnetic/earth2"
        )
