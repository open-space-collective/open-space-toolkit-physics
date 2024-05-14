# Apache License 2.0

import pytest

import numpy as np

from ostk.physics import Unit
from ostk.physics.data import Vector
from ostk.physics.unit import Length
from ostk.physics.time import Instant
from ostk.physics.coordinate import Frame


@pytest.fixture
def unit() -> Unit:
    return Unit.length(Length.Unit.Meter)


@pytest.fixture
def value() -> np.ndarray:
    return np.array([1.0, 2.0, 3.0])


@pytest.fixture
def frame() -> Frame:
    return Frame.GCRF()


@pytest.fixture
def vector(value: float, unit: Unit, frame: Frame) -> Vector:
    return Vector(
        value=value,
        unit=unit,
        frame=frame,
    )


class TestVector:
    def test_constructor(self, vector: Vector):
        assert vector is not None

    def test_equals(self, vector: Vector):
        assert vector == vector

    def test_not_equals(self, vector: Vector):
        assert (vector != vector) is False

    def test_is_defined(self, vector: Vector):
        assert vector.is_defined()

    def test_get_value(self, vector: Vector, value: float):
        assert np.all(vector.get_value() == value)

    def test_get_unit(self, vector: Vector):
        assert vector.get_unit().is_defined()

    def test_get_frame(self, vector: Vector, frame: Frame):
        assert vector.get_frame() == frame

    def test_in_unit(self, vector: Vector):
        assert vector.in_unit(Unit.length(Length.Unit.Foot)) is not None

    def test_in_frame(self, vector: Vector):
        assert vector.in_frame(Frame.ITRF(), Instant.J2000()) is not None

    def test_to_string(self, vector: Vector):
        assert vector.to_string() is not None

    def test_undefined(self):
        assert Vector.undefined() is not None
