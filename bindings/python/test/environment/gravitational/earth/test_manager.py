################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/gravitational/earth/test_manager.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import os

from ostk.core.filesystem import Path
from ostk.core.filesystem import Directory

from ostk.io import URL

from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel
from ostk.physics.environment.gravitational.earth import Manager as EarthGravitationalModelManager

################################################################################################################################################################

@pytest.fixture
def manager () -> EarthGravitationalModelManager:

    manager = EarthGravitationalModelManager.get()

    manager.set_remote_url(URL.parse('https://sourceforge.net/projects/geographiclib/files/gravity-distrib/'))
    manager.set_local_repository(Directory.path(Path.parse(os.environ.get('OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY'))))

    return manager

################################################################################################################################################################

class TestManager:

    def test_is_enabled_success (self, manager: EarthGravitationalModelManager):

        assert manager.is_enabled() == True

    def test_has_data_file_for_type_success (self, manager: EarthGravitationalModelManager):

        assert manager.has_data_file_for_type(EarthGravitationalModel.EarthType.WGS84) == True
        assert manager.has_data_file_for_type(EarthGravitationalModel.EarthType.EGM84) == True
        assert manager.has_data_file_for_type(EarthGravitationalModel.EarthType.EGM96) == True
        assert manager.has_data_file_for_type(EarthGravitationalModel.EarthType.EGM2008) == True

    def test_get_local_repository_success (self, manager: EarthGravitationalModelManager):

        assert isinstance(manager.get_local_repository(), Directory)
        assert manager.get_local_repository().to_string() == os.environ.get('OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY')

    def test_get_remote_url_success (self, manager: EarthGravitationalModelManager):

        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == 'https://sourceforge.net/projects/geographiclib/files/gravity-distrib/'

    def test_fetch_data_file_for_type_success (self, manager: EarthGravitationalModelManager):

        manager.fetch_data_file_for_type(EarthGravitationalModel.EarthType.WGS84)
        manager.fetch_data_file_for_type(EarthGravitationalModel.EarthType.EGM84)
        manager.fetch_data_file_for_type(EarthGravitationalModel.EarthType.EGM96)
        manager.fetch_data_file_for_type(EarthGravitationalModel.EarthType.EGM2008)

    def test_set_local_repository_success (self, manager: EarthGravitationalModelManager):

        manager.set_local_repository(Directory.path(Path.parse('./.open-space-toolkit/physics/environment/gravitational/earth2')))

        assert isinstance(manager.get_local_repository(), Directory)
        assert manager.get_local_repository().to_string() == './.open-space-toolkit/physics/environment/gravitational/earth2'

    def test_set_remote_url_success (self, manager: EarthGravitationalModelManager):

        manager.set_remote_url(URL.parse('https://sourceforge.net/projects/geographiclib/files/gravity-distrib/2'))

        assert isinstance(manager.get_remote_url(), URL)
        assert manager.get_remote_url().to_string() == 'https://sourceforge.net/projects/geographiclib/files/gravity-distrib/2'

    def test_enable_disable_success (self, manager: EarthGravitationalModelManager):

        manager.disable()
        assert manager.is_enabled() == False

        manager.enable()
        assert manager.is_enabled() == True

    def test_default_local_repository_success (self, manager: EarthGravitationalModelManager):

        assert isinstance(EarthGravitationalModelManager.default_local_repository(), Directory)
        assert manager.default_local_repository().to_string() == os.environ.get('OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY')

    def test_default_remote_url_success (self, manager: EarthGravitationalModelManager):

        assert isinstance(EarthGravitationalModelManager.default_remote_url(), URL)
        assert manager.default_remote_url().to_string() == 'https://sourceforge.net/projects/geographiclib/files/gravity-distrib/'

################################################################################################################################################################
