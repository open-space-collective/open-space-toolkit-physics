# Apache License 2.0

import pytest
from datetime import datetime
from ostk.core.filesystem import Directory, File
from ostk.physics.time import Instant
from ostk.physics.data import Manager, Manifest

class TestManager:
    def test_get_last_update_timestamp_for_success(self, manager: Manager):
        assert isinstance(manager.get_last_update_timestamp_for("manifest"), datetime)

    def test_get_remote_url_success(self, manager: Manager):
        assert isinstance(manager.get_remote_url(), str)

    def test_get_manifest_repository_success(self, manager: Manager):
        assert isinstance(manager.get_manifest_repository(), Directory)

    def test_get_remote_data_urls_success(self, manager: Manager):
        assert isinstance(manager.get_remote_data_urls("data_name"), list)

    def test_get_manifest_success(self, manager: Manager):
        assert isinstance(manager.get_manifest(), dict)

    def test_set_remote_url_success(self, manager: Manager):
        manager.set_remote_url("http://example.com")
        assert manager.get_remote_url() == "http://example.com"

    def test_set_manifest_repository_success(self, manager: Manager):
        directory = Directory.path("./test_directory")
        manager.set_manifest_repository(directory)
        assert manager.get_manifest_repository() == directory

    def test_find_remote_data_urls_success(self, manager: Manager):
        assert isinstance(manager.find_remote_data_urls(".*"), list)

    def test_load_manifest_success(self, manager: Manager, manifest_file: File):

        manifest = Manifest.load(manifest_file)

        manager.load_manifest(manifest)
        assert manager.get_manifest() == manifest

    def test_manifest_file_exists_success(self, manager: Manager):
        assert isinstance(manager.manifest_file_exists(), bool)

    def test_reset_success(self, manager: Manager):
        manager.reset()
        assert manager.get_manifest() == {}

    def test_get_success(self):
        assert isinstance(Manager.get(), Manager)

    def test_default_remote_url_success(self, manager: Manager):
        assert isinstance(manager.default_remote_url(), str)

    def test_default_manifest_repository_success(self, manager: Manager):
        assert isinstance(manager.default_manifest_repository(), Directory)
