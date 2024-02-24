# Apache License 2.0

import pytest

import numpy as np

from ostk.physics.data import Direction
from ostk.physics.coordinate import Frame


@pytest.fixture
def value() -> np.ndarray:
    return np.array([1.0, 0.0, 0.0])


@pytest.fixture
def frame() -> Frame:
    return Frame.GCRF()


@pytest.fixture
def direction(value: float, frame: Frame) -> Direction:
    return Direction(
        value=value,
        frame=frame,
    )


class TestDirection:
    def test_constructor(self, direction: Direction):
        assert direction is not None

    def test_equals(self, direction: Direction):
        assert direction == direction

    def test_not_equals(self, direction: Direction):
        assert (direction != direction) is False

    def test_undefined(self):
        assert Direction.undefined() is not None
