# Apache License 2.0

import pytest

from ostk.core.filesystem import Path
from ostk.core.filesystem import File

from ostk.physics.environment.ephemeris import SPICE
from ostk.physics.environment.ephemeris.spice import Kernel
from ostk.physics.environment.ephemeris.spice import Engine


@pytest.fixture
def engine() -> Engine:
    engine = Engine.get()

    yield engine

    # Reset engine after test to not affect other tests
    engine.reset()


class TestEngine:
    def test_get_singleton_success(self):
        engine = Engine.get()

        assert engine is not None

    def test_reset_success(self, engine: Engine):
        engine.reset()

    def test_get_frame_of_success(self, engine: Engine):
        frame = engine.get_frame_of(SPICE.Object.Earth)

        assert frame is not None

    def test_get_kernels_success(self, engine: Engine):
        kernels = engine.get_kernels()

        assert kernels is not None

    def test_is_kernel_loaded_success(self, engine: Engine):
        assert not engine.is_kernel_loaded(
            Kernel.file(
                file=File.path(
                    path=Path.parse("de430.bsp"),
                ),
            )
        )

    def test_unload_kernel_success(self, engine: Engine):
        kernels = engine.get_kernels()
        engine.unload_kernel(kernels[0])

    def test_load_kernel_success(self, engine: Engine):
        kernel = engine.get_kernels()[0]
        engine.unload_kernel(kernel)

        assert not engine.is_kernel_loaded(kernel)
        engine.load_kernel(kernel)
        assert engine.is_kernel_loaded(kernel)

    def unload_all_kernels_success(self, engine: Engine):
        engine.unload_all_kernels()

    def test_default_kernels_success(self):
        kernels = Engine.default_kernels()

        assert kernels is not None
        assert isinstance(kernels, list)
