# Apache License 2.0

import pytest
import numpy as np

from ostk.core.type import String
import ostk.physics as physics

Scale = physics.time.Scale
DateTime = physics.time.DateTime
Instant = physics.time.Instant
Frame = physics.coordinate.Frame
Position = physics.coordinate.Position
Unit = physics.unit.Length.Unit


def test_coordinate_position_constructors():
    # Construct arbitrary frame
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter

    # Construction with python lists
    vector = [1000.0, 0.0, 0.0]

    position: Position = Position(vector, unit, frame)

    assert position is not None
    assert isinstance(position, Position)
    assert position.is_defined()

    # Construction with python tuples
    vector = (1000.0, 0.0, 0.0)

    position: Position = Position(vector, unit, frame)

    assert position is not None
    assert isinstance(position, Position)
    assert position.is_defined()

    # Construction with python numpy arrays
    vector = np.array((1000.0, 0.0, 0.0))

    position: Position = Position(vector, unit, frame)

    assert position is not None
    assert isinstance(position, Position)
    assert position.is_defined()

    # Construction with meters static constructor
    position: Position = Position.meters(vector, frame)

    assert position is not None
    assert isinstance(position, Position)
    assert position.is_defined()

    # Construction with undefined static constructor
    position: Position = Position.undefined()

    assert position is not None
    assert isinstance(position, Position)
    assert position.is_defined() is False


def test_coordinate_position_comparators():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector_1 = [1000.0, 0.0, 0.0]
    vector_2 = [-450.3, 234.9, -23.0]

    position_1: Position = Position(vector_1, unit, frame)
    position_2: Position = Position(vector_2, unit, frame)

    assert position_1 == position_1
    assert position_2 == position_2
    assert position_1 != position_2


def test_coordinate_position_is_defined():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]
    position: Position = Position(vector, unit, frame)

    assert position.is_defined()
    assert Position.undefined().is_defined() is False


@pytest.mark.skip
def test_coordinate_position_is_near():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter

    vector_1 = [1000.0, 0.0, 0.0]
    vector_2 = [1000.00001, 0.0001, 0.0]

    position_1: Position = Position(vector_1, unit, frame)
    position_2: Position = Position(vector_2, unit, frame)

    assert position_1.is_near(position_2, Unit.Meter)
    assert position_2.is_near(position_1, Unit.Meter)


def test_coordinate_position_access_frame():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]

    position: Position = Position(vector, unit, frame)

    ans_frame = position.access_frame()

    assert ans_frame is not None
    assert isinstance(ans_frame, Frame)
    assert ans_frame == frame


def test_coordinate_position_get_coordinates():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]

    position: Position = Position(vector, unit, frame)

    coordinates = position.get_coordinates()

    assert coordinates is not None
    assert isinstance(coordinates, np.ndarray)
    assert np.array_equal(coordinates, vector)


def test_coordinate_position_get_unit():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]

    position: Position = Position(vector, unit, frame)

    ans_unit = position.get_unit()

    assert ans_unit is not None
    assert isinstance(ans_unit, Unit)
    assert ans_unit == unit


def test_coordinate_position_in_unit():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]

    position: Position = Position(vector, unit, frame)

    new_position: Position = position.in_unit(Unit.Meter)

    assert new_position is not None
    assert isinstance(new_position, Position)
    assert new_position == position

    new_position: Position = position.in_unit(Unit.TerrestrialMile)

    assert new_position is not None
    assert isinstance(new_position, Position)
    # assert new_position == position


def test_coordinate_position_in_meters():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]

    position: Position = Position(vector, unit, frame)

    new_position: Position = position.in_meters()

    assert new_position is not None
    assert isinstance(new_position, Position)
    assert new_position == position


def test_coordinate_position_in_frame():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]

    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    position: Position = Position(vector, unit, frame)

    new_position: Position = position.in_frame(frame, instant)

    assert new_position is not None
    assert isinstance(new_position, Position)
    assert new_position == position


def test_coordinate_position_to_string():
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.Meter
    vector = [1000.0, 0.0, 0.0]

    position: Position = Position(vector, unit, frame)

    string: String = position.to_string()

    assert string is not None
    assert isinstance(string, String)
    assert string == "[1000.0, 0.0, 0.0] [m] @ GCRF"
