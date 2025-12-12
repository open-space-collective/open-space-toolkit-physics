# Apache License 2.0

import pytest

from ostk.core.filesystem import File, Path

from ostk.physics.environment.ephemeris.spice import Kernel


@pytest.fixture
def kernel() -> Kernel:
    return Kernel(Kernel.Type.SPK, File.path(Path.parse("de430.bsp")))


class TestKernel:
    def test_undefined_success(self):
        kernel = Kernel.undefined()

        assert kernel is not None
        assert kernel.is_defined() is False

    def test_string_from_type_success(self):
        assert Kernel.string_from_type(Kernel.Type.SPK) == "SPK"
        assert Kernel.string_from_type(Kernel.Type.LSK) == "LSK"
        assert Kernel.string_from_type(Kernel.Type.PCK) == "PCK"

    def test_type_from_string_success(self):
        assert Kernel.type_from_string("SPK") == Kernel.Type.SPK
        assert Kernel.type_from_string("LSK") == Kernel.Type.LSK
        assert Kernel.type_from_string("PCK") == Kernel.Type.PCK

    def test_type_from_file_extension_success(self):
        assert Kernel.type_from_file_extension("bsp") == Kernel.Type.SPK
        assert Kernel.type_from_file_extension("tls") == Kernel.Type.LSK
        assert Kernel.type_from_file_extension("tpc") == Kernel.Type.PCK

    def test_constructor_success(self):
        assert Kernel(Kernel.Type.SPK, File.path(Path.parse("de430.bsp"))) is not None

    def test_get_type_success(self, kernel: Kernel):
        assert kernel.get_type() == Kernel.Type.SPK
