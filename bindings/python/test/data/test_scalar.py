# Apache License 2.0

import pytest

from ostk.physics import Unit
from ostk.physics.data import Scalar
from ostk.physics.unit import Length


@pytest.fixture
def unit() -> Unit:
    return Unit.length(Length.Unit.Meter)


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
    def test_constructor(self, scalar: Scalar):
        assert scalar is not None

    def test_equals(self, scalar: Scalar):
        assert scalar == scalar

    def test_not_equals(self, scalar: Scalar):
        assert (scalar != scalar) is False

    def test_is_defined(self, scalar: Scalar):
        assert scalar.is_defined()

    def test_get_value(self, scalar: Scalar, value: float):
        assert scalar.get_value() == value

    def test_get_unit(self, scalar: Scalar):
        assert scalar.get_unit().is_defined()

    def test_in_unit(self, scalar: Scalar):
        assert scalar.in_unit(Unit.length(Length.Unit.Foot)) is not None

    def test_to_string(self, scalar: Scalar):
        assert scalar.to_string() is not None

    def test_undefined(self):
        assert Scalar.undefined() is not None
