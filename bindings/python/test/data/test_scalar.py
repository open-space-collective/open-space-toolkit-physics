# Apache License 2.0

import pytest

from ostk.physics.data import Scalar
from ostk.physics.unit import Unit
from ostk.physics.unit import Length


@pytest.fixture
def unit() -> Unit:
    return Length.Unit.Meter


@pytest.fixture
def value() -> float:
    return 5.0


@pytest.fixture
def scalar(value: float, unit: Unit) -> Scalar:
    return Scalar(
        value=value,
        unit=unit,
    )


class TestScalar:
    def test_equals(self, scalar: Scalar):
        assert scalar == scalar

    def test_not_equals(self, scalar: Scalar):
        assert (scalar != scalar) is False

    def test_is_defined(self, scalar: Scalar):
        assert scalar.is_defined()

    def test_get_value(self, scalar: Scalar, value: float):
        assert scalar.get_value() == value

    def test_get_unit(self, scalar: Scalar, unit: Unit):
        assert scalar.get_unit() == unit

    def test_in_unit(self, scalar: Scalar):
        assert scalar.in_unit(Length.Unit.Kilometer) is not None

    def test_to_string(self, scalar: Scalar):
        assert scalar.to_string() is not None
