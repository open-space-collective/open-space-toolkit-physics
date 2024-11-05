# Apache License 2.0

import pytest

from datetime import datetime
import pathlib

from ostk.core.filesystem import Path
from ostk.core.filesystem import File
from ostk.core.filesystem import Directory

from ostk.physics.time import Scale
from ostk.physics.time import Instant
from ostk.physics.time import Duration

from ostk.physics.coordinate.frame.provider.iers import Manager
from ostk.physics.coordinate.frame.provider.iers import BulletinA
from ostk.physics.coordinate.frame.provider.iers import Finals2000A


@pytest.fixture
def manager(bulletin_a) -> Manager:
    manager = Manager.get()

    manager.set_mode(Manager.Mode.Automatic)

    manager.load_bulletin_a(bulletin_a)

    yield manager

    manager.reset()
    manager.clear_local_repository()


class TestManager:
    def test_get_mode_success(self, manager: Manager):
        assert manager.get_mode() == Manager.Mode.Automatic

    def test_get_local_repository_success(self, manager: Manager):
        assert isinstance(manager.get_local_repository(), Directory)
        assert len(str(manager.get_local_repository().to_string())) > 0

    def test_get_bulletin_a_directory_success(self, manager: Manager):
        assert isinstance(manager.get_bulletin_a_directory(), Directory)
        assert len(str(manager.get_bulletin_a_directory().to_string())) > 0

    def test_get_finals_2000a_directory_success(self, manager: Manager):
        assert isinstance(manager.get_finals_2000a_directory(), Directory)
        assert len(str(manager.get_finals_2000a_directory().to_string())) > 0

    def test_get_bulletin_a_success(self, manager: Manager):
        bulletin_a: BulletinA = manager.get_bulletin_a()

        assert isinstance(bulletin_a, BulletinA)

    def test_get_finals_2000a_success(self, manager: Manager):
        finals_2000a: Finals2000A = manager.get_finals_2000a()

        assert isinstance(finals_2000a, Finals2000A)

    def test_get_polar_motion_at_success(self, manager: Manager):
        assert list(
            manager.get_polar_motion_at(
                Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)
            )
        ) == [0.076577, 0.282336]

    @pytest.mark.skip(reason="Flaky external dependency.")
    def test_get_polar_motion_at_success_2(self, manager: Manager):
        assert len(manager.get_bulletin_a_array()) == 0
        assert len(manager.get_finals_2000a_array()) == 0

        assert manager.get_polar_motion_at(Instant.now() - Duration.days(7.0)) is not None

        assert len(manager.get_bulletin_a_array()) == 1
        assert len(manager.get_finals_2000a_array()) == 0

        assert (
            manager.get_polar_motion_at(
                Instant.date_time(datetime(2000, 1, 1, 0, 0, 0), Scale.UTC)
            )
            is not None
        )
        assert (
            manager.get_polar_motion_at(
                Instant.date_time(datetime(2010, 1, 1, 0, 0, 0), Scale.UTC)
            )
            is not None
        )
        assert (
            manager.get_polar_motion_at(
                Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)
            )
            is not None
        )
        assert (
            manager.get_polar_motion_at(
                Instant.date_time(datetime(2023, 7, 16, 0, 0, 0), Scale.UTC)
            )
            is not None
        )

        assert len(manager.get_bulletin_a_array()) == 1
        assert len(manager.get_finals_2000a_array()) == 1

    def test_get_ut1_minus_utc_at_success(self, manager: Manager):
        assert (
            manager.get_ut1_minus_utc_at(
                Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)
            )
            == -0.17715539999999999
        )

    def test_get_lod_at_success(self, manager: Manager):
        assert (
            manager.get_lod_at(
                Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)
            )
            == 0.43790000000000001
        )

    def test_set_mode_success(self, manager: Manager):
        assert manager.get_mode() == Manager.Mode.Automatic

        manager.set_mode(Manager.Mode.Manual)

        assert manager.get_mode() == Manager.Mode.Manual

    def test_set_local_repository_success(self, manager: Manager):
        assert isinstance(manager.get_local_repository(), Directory)
        assert len(str(manager.get_local_repository().to_string())) > 0

        manager.set_local_repository(
            Directory.path(
                Path.parse(
                    "./.open-space-toolkit/physics/coordinate/frame/provider/iers2"
                )
            )
        )

        assert isinstance(manager.get_local_repository(), Directory)
        assert (
            manager.get_local_repository().to_string()
            == "./.open-space-toolkit/physics/coordinate/frame/provider/iers2"
        )

    def test_load_bulletin_a_success(self, manager: Manager, bulletin_a: BulletinA):
        manager.load_bulletin_a(bulletin_a)

        assert manager.get_bulletin_a().is_defined()

    def test_load_finals_2000a_success(self, manager: Manager, finals_2000a: Finals2000A):
        manager.load_finals_2000a(finals_2000a)

        assert manager.get_finals_2000a().is_defined()

    def test_fetch_latest_bulletin_a_success(self, manager: Manager):
        file: File = manager.fetch_latest_bulletin_a()

        assert isinstance(file, File)
        assert file.exists()

        file.remove()

    def test_fetch_latest_finals_2000a_success(self, manager: Manager):
        file: File = manager.fetch_latest_finals_2000a()

        assert isinstance(file, File)
        assert file.exists()

        file.remove()

    def test_reset_success(self, manager: Manager, bulletin_a: BulletinA):
        assert manager.get_bulletin_a().is_defined()

        manager.reset()

        # The get methods automatically load things if they are not loaded, so we set to manual
        manager.set_mode(manager.Mode.Manual)

        with pytest.raises(Exception):
            manager.get_bulletin_a()

        manager.set_mode(manager.Mode.Automatic)

    def test_clear_local_repository_success(self, manager: Manager):
        assert manager.get_local_repository().exists()
        assert manager.get_bulletin_a_directory().exists()
        assert manager.get_finals_2000a_directory().exists()
        pathlib.Path(
            str(manager.get_bulletin_a_directory().get_path().to_string()) + "/toto"
        ).touch()
        pathlib.Path(
            str(manager.get_finals_2000a_directory().get_path().to_string()) + "/toto"
        ).touch()
        assert not manager.get_local_repository().is_empty()

        manager.clear_local_repository()

        assert manager.get_local_repository().exists()
        assert manager.get_bulletin_a_directory().is_empty()
        assert manager.get_finals_2000a_directory().is_empty()

    def test_get_success(self):
        assert isinstance(Manager.get(), Manager)
