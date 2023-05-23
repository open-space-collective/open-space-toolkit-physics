################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/coordinate/frame/providers/iers/test_manager.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

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

from ostk.physics.coordinate.frame.providers.iers import Manager
from ostk.physics.coordinate.frame.providers.iers import BulletinA
from ostk.physics.coordinate.frame.providers.iers import Finals2000A

################################################################################################################################################################

@pytest.fixture
def manager () -> Manager:

    manager = Manager.get()

    manager.set_mode(Manager.Mode.Automatic)
    manager.set_remote_url(URL.parse('https://maia.usno.navy.mil/ser7/'))

    yield manager

    manager.reset()
    manager.clear_local_repository()

################################################################################################################################################################

class TestManager:

    def test_get_mode_success (self, manager: Manager):

        assert manager.get_mode() == Manager.Mode.Automatic

    def test_get_local_repository_success (self, manager: Manager):

        assert isinstance(manager.get_local_repository(), Directory)
        assert manager.get_local_repository().to_string() == os.environ.get('OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY')

    def test_get_bulletin_a_directory_success (self, manager: Manager):

        assert isinstance(manager.get_bulletin_a_directory(), Directory)
        assert manager.get_bulletin_a_directory().to_string() == str(os.environ.get('OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY')) + '/bulletin-A'

    def test_get_finals_2000a_directory_success (self, manager: Manager):

        assert isinstance(manager.get_finals_2000a_directory(), Directory)
        assert manager.get_finals_2000a_directory().to_string() == str(os.environ.get('OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY')) + '/finals-2000A'

    def test_get_remote_url_success (self, manager: Manager):

        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == 'https://maia.usno.navy.mil/ser7/'

    def test_get_bulletin_a_array_success (self, manager: Manager):

        assert isinstance(manager.get_bulletin_a_array(), list)
        assert len(manager.get_bulletin_a_array()) == 0

    def test_get_bulletin_a_at_success (self, manager: Manager):

        try:
            bulletin_a: BulletinA = manager.get_bulletin_a_at(Instant.now() - Duration.days(8.0))
        except RuntimeError:
            manager.reset()
            manager.clear_local_repository()
            bulletin_a: BulletinA = manager.get_bulletin_a_at(Instant.now() - Duration.days(5.0))

        assert isinstance(bulletin_a, BulletinA)

    def test_get_finals_2000a_array_success (self, manager: Manager):

        assert isinstance(manager.get_finals_2000a_array(), list)
        assert len(manager.get_finals_2000a_array()) == 0

    def test_get_finals_2000a_at_success (self, manager: Manager):

        finals_2000a: Finals2000A = manager.get_finals_2000a_at(Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC))

        assert isinstance(finals_2000a, Finals2000A)

    def test_get_polar_motion_at_success (self, manager: Manager):

        assert list(manager.get_polar_motion_at(Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC))) == [0.076577, 0.282336]

    def test_get_polar_motion_at_success_2 (self, manager: Manager):

        assert len(manager.get_bulletin_a_array()) == 0
        assert len(manager.get_finals_2000a_array()) == 0

        assert manager.get_polar_motion_at(Instant.now() - Duration.days(7.0)) is not None

        assert len(manager.get_bulletin_a_array()) == 1
        assert len(manager.get_finals_2000a_array()) == 0

        assert manager.get_polar_motion_at(Instant.date_time(datetime(2000, 1, 1, 0, 0, 0), Scale.UTC)) is not None
        assert manager.get_polar_motion_at(Instant.date_time(datetime(2010, 1, 1, 0, 0, 0), Scale.UTC)) is not None
        assert manager.get_polar_motion_at(Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)) is not None
        assert manager.get_polar_motion_at(Instant.date_time(datetime(2023, 7, 16, 0, 0, 0), Scale.UTC)) is not None

        assert len(manager.get_bulletin_a_array()) == 1
        assert len(manager.get_finals_2000a_array()) == 1

    def test_get_ut1_minus_utc_at_success (self, manager: Manager):

        assert manager.get_ut1_minus_utc_at(Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)) == -0.17715539999999999

    def test_get_lod_at_success (self, manager: Manager):

        assert manager.get_lod_at(Instant.date_time(datetime(2020, 1, 1, 0, 0, 0), Scale.UTC)) == 0.43790000000000001

    def test_set_mode_success (self, manager: Manager):

        assert manager.get_mode() == Manager.Mode.Automatic

        manager.set_mode(Manager.Mode.Manual)

        assert manager.get_mode() == Manager.Mode.Manual

    def test_set_local_repository_success (self, manager: Manager):

        assert isinstance(manager.get_local_repository(), Directory)
        assert manager.get_local_repository().to_string() == os.environ.get('OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY')

        manager.set_local_repository(Directory.path(Path.parse('./.open-space-toolkit/physics/coordinate/frame/providers/iers2')))

        assert isinstance(manager.get_local_repository(), Directory)
        assert manager.get_local_repository().to_string() == './.open-space-toolkit/physics/coordinate/frame/providers/iers2'

    def test_set_remote_url_success (self, manager: Manager):

        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == 'https://maia.usno.navy.mil/ser7/'

        manager.set_remote_url(URL.parse('https://maia.usno.navy.mil/ser7/2'))

        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == 'https://maia.usno.navy.mil/ser7/2'

    def test_load_bulletin_a_success (self, manager: Manager, bulletin_a: BulletinA):

        assert len(manager.get_bulletin_a_array()) == 0

        manager.load_bulletin_a(bulletin_a)

        assert len(manager.get_bulletin_a_array()) == 1

    def test_load_finals_2000a_success (self, manager: Manager, finals_2000a: Finals2000A):

        assert len(manager.get_finals_2000a_array()) == 0

        manager.load_finals_2000a(finals_2000a)

        assert len(manager.get_finals_2000a_array()) == 1

    def test_fetch_latest_bulletin_a_success (self, manager: Manager):

        file: File = manager.fetch_latest_bulletin_a()

        assert isinstance(file, File)
        assert file.exists()

        file.remove()

    def test_fetch_latest_finals_2000a_success (self, manager: Manager):

        file: File = manager.fetch_latest_finals_2000a()

        assert isinstance(file, File)
        assert file.exists()

        file.remove()

    def test_reset_success (self, manager: Manager, bulletin_a: BulletinA):

        manager.load_bulletin_a(bulletin_a)

        assert len(manager.get_bulletin_a_array()) == 1

        manager.reset()

        assert len(manager.get_bulletin_a_array()) == 0

    def test_clear_local_repository_success (self, manager: Manager):

        assert manager.get_local_repository().exists()
        assert manager.get_bulletin_a_directory().exists()
        assert manager.get_finals_2000a_directory().exists()
        pathlib.Path(str(manager.get_bulletin_a_directory().get_path().to_string()) + '/toto').touch()
        pathlib.Path(str(manager.get_finals_2000a_directory().get_path().to_string()) + '/toto').touch()
        assert not manager.get_local_repository().is_empty()

        manager.clear_local_repository()

        assert manager.get_local_repository().exists()
        assert manager.get_bulletin_a_directory().is_empty()
        assert manager.get_finals_2000a_directory().is_empty()

    def test_get_success (self):

        assert isinstance(Manager.get(), Manager)

    def test_default_mode_success (self, manager: Manager):

        assert manager.default_mode() == Manager.Mode.Automatic

    def test_default_local_repository_success (self, manager: Manager):

        assert isinstance(manager.default_local_repository(), Directory)
        assert manager.default_local_repository().to_string() == os.environ.get('OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY')

    def test_default_local_repository_lock_timeout_success (self, manager: Manager):

        assert isinstance(manager.default_local_repository_lock_timeout(), Duration)
        assert manager.default_local_repository_lock_timeout().in_seconds() == 60.0

    def test_default_remote_url_success (self, manager: Manager):

        assert isinstance(manager.default_remote_url(), URL)
        assert manager.default_remote_url().to_string() == 'https://maia.usno.navy.mil/ser7/'

################################################################################################################################################################
