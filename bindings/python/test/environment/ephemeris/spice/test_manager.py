# Apache License 2.0

import pytest

from ostk.core.filesystem import Path
from ostk.core.filesystem import File


from ostk.physics.environment.ephemeris.spice import Manager
from ostk.physics.environment.ephemeris.spice import Kernel


@pytest.fixture
def manager() -> Manager:
    manager = Manager.get()

    yield manager

    manager.reset()


class TestManager:
    def test_get_success(self):
        manager = Manager.get()

        assert manager is not None

    def test_fetch_kernel_success(self, manager: Manager):
        manager.fetch_kernel(
            kernel=Kernel.file(
                file=File.path(
                    path=Path.parse("de430.bsp"),
                ),
            )
        )

    def test_fetch_matching_kernels_success(self, manager: Manager):
        kernels: list[Kernel] = manager.fetch_matching_kernels(".*\\.bsp$")

        assert kernels is not None

    def test_find_kernel_paths_success(self, manager: Manager):
        paths: list[Path] = manager.find_kernel_paths(".*\\.bsp$")

        assert paths is not None
        assert isinstance(paths, list)

    def test_find_kernel_success(self, manager: Manager):
        kernel: Kernel = manager.find_kernel("de430.bsp")

        assert kernel is not None
