# Apache License 2.0

import pytest
from datetime import datetime

from ostk.core.filesystem import File
from ostk.core.filesystem import Path

from ostk.io import URL

from ostk.physics.data import Manifest
from ostk.physics.time import Instant


class TestManifest:
    def test_is_defined_success(self, manifest: Manifest):
        assert manifest.is_defined() == True

    def test_get_last_modified_timestamp_success(self, manifest: Manifest):
        assert isinstance(manifest.get_last_modified_timestamp(), Instant)

    def test_get_last_update_timestamp_for_success(self, manifest: Manifest):
        assert isinstance(manifest.get_last_update_timestamp_for("manifest"), Instant)

    def test_get_next_update_check_timestamp_for_success(self, manifest: Manifest):
        assert isinstance(
            manifest.get_next_update_check_timestamp_for("manifest"), Instant
        )

    def test_get_remote_data_urls_success(self, manifest: Manifest):
        test_url: URL = URL.parse("http://test.com")
        assert isinstance(manifest.get_remote_data_urls(test_url, "manifest"), list)

    def test_find_remote_data_urls_success(self, manifest: Manifest):
        test_url: URL = URL.parse("http://test.com")
        assert isinstance(manifest.find_remote_data_urls(test_url, ".*"), list)

    def test_undefined_success(self):
        assert isinstance(Manifest.undefined(), Manifest)

    def test_load_success(self, manifest_file: File):
        manifest = Manifest.load(manifest_file)
        assert isinstance(manifest, Manifest)
