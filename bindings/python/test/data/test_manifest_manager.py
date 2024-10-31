# Apache License 2.0

import pytest
from datetime import datetime
from ostk.core.filesystem import Directory
from ostk.core.filesystem import File
from ostk.core.filesystem import Path

from ostk.io import URL

from ostk.physics.time import Instant
from ostk.physics.data import Manager
from ostk.physics.data import Manifest


class TestManager:
    def test_get_last_update_timestamp_for_success(self, manager: Manager):
        assert isinstance(manager.get_last_update_timestamp_for("manifest"), Instant)

    def test_get_remote_url_success(self, manager: Manager):
        assert isinstance(manager.get_remote_url(), URL)

    def test_get_local_repository_success(self, manager: Manager):
        assert isinstance(manager.get_local_repository(), Directory)

    def test_get_remote_data_urls_success(self, manager: Manager):
        assert isinstance(manager.get_remote_data_urls("data_name"), list)

    def test_get_manifest_success(self, manager: Manager):
        assert isinstance(manager.get_manifest(), Manifest)

    def test_set_remote_url_success(self, manager: Manager):
        manager.set_remote_url(URL.parse("http://example.com"))
        assert manager.get_remote_url() == URL.parse("http://example.com")

    def test_set_local_repository_success(self, manager: Manager):
        directory = Directory.path(Path.parse("./test_directory"))
        manager.set_local_repository(directory)
        assert manager.get_local_repository() == directory

    def test_find_remote_data_urls_success(self, manager: Manager):
        assert isinstance(manager.find_remote_data_urls(".*"), list)

    def test_load_manifest_success(self, manager: Manager, manifest: Manifest):
        manager.load_manifest(manifest)
        assert manager.get_manifest().is_defined()

    def test_manifest_file_exists_success(self, manager: Manager):
        assert isinstance(manager.manifest_file_exists(), bool)

    def test_reset_success(self, manager: Manager, manifest: Manifest):
        manager.load_manifest(manifest)
        assert manager.get_manifest().is_defined()

        manager.reset()
        assert not manager.get_manifest().is_defined()

    def test_get_success(self):
        assert isinstance(Manager.get(), Manager)

    def test_default_remote_url_success(self, manager: Manager):
        assert isinstance(manager.default_remote_url(), URL)
