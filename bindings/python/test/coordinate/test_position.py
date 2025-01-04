# Apache License 2.0

import pytest
import numpy as np

from ostk.core.type import String

from ostk.physics import Environment
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate import Position
from ostk.physics.coordinate.spherical import LLA
from ostk.physics.time import Instant
from ostk.physics.time import Scale
from ostk.physics.time import DateTime
from ostk.physics.unit import Length


@pytest.fixture
def unit() -> Length.Unit:
    return Length.Unit.Meter


@pytest.fixture
def frame() -> Frame:
    return Frame.GCRF()


@pytest.fixture
def earth():
    return Environment.default().access_celestial_object_with_name("Earth")


@pytest.fixture
def lla() -> LLA:
    return LLA.vector([0.0, 0.0, 0.0])


class TestPosition:

    def test_constructors(self, unit: Length.Unit, frame: Frame):
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

    def test_comparators(self, unit: Length.Unit, frame: Frame):
        vector_1 = [1000.0, 0.0, 0.0]
        vector_2 = [-450.3, 234.9, -23.0]

        position_1: Position = Position(vector_1, unit, frame)
        position_2: Position = Position(vector_2, unit, frame)

        assert position_1 == position_1
        assert position_2 == position_2
        assert position_1 != position_2

    def test_is_defined(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]
        position: Position = Position(vector, unit, frame)

        assert position.is_defined()
        assert Position.undefined().is_defined() is False

    @pytest.mark.skip
    def test_is_near(self, unit: Length.Unit, frame: Frame):

        vector_1 = [1000.0, 0.0, 0.0]
        vector_2 = [1000.00001, 0.0001, 0.0]

        position_1: Position = Position(vector_1, unit, frame)
        position_2: Position = Position(vector_2, unit, frame)

        assert position_1.is_near(position_2, Length.Unit.Meter)
        assert position_2.is_near(position_1, Length.Unit.Meter)

    def test_access_frame(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]

        position: Position = Position(vector, unit, frame)

        ans_frame = position.access_frame()

        assert ans_frame is not None
        assert isinstance(ans_frame, Frame)
        assert ans_frame == frame

    def test_get_coordinates(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]

        position: Position = Position(vector, unit, frame)

        coordinates = position.get_coordinates()

        assert coordinates is not None
        assert isinstance(coordinates, np.ndarray)
        assert np.array_equal(coordinates, vector)

    def test_get_unit(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]

        position: Position = Position(vector, unit, frame)

        ans_unit = position.get_unit()

        assert ans_unit is not None
        assert isinstance(ans_unit, Length.Unit)
        assert ans_unit == unit

    def test_in_unit(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]

        position: Position = Position(vector, unit, frame)

        new_position: Position = position.in_unit(Length.Unit.Meter)

        assert new_position is not None
        assert isinstance(new_position, Position)
        assert new_position == position

        new_position: Position = position.in_unit(Length.Unit.TerrestrialMile)

        assert new_position is not None
        assert isinstance(new_position, Position)
        # assert new_position == position

    def test_in_meters(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]

        position: Position = Position(vector, unit, frame)

        new_position: Position = position.in_meters()

        assert new_position is not None
        assert isinstance(new_position, Position)
        assert new_position == position

    def test_in_frame(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]

        instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

        position: Position = Position(vector, unit, frame)

        new_position: Position = position.in_frame(frame, instant)

        assert new_position is not None
        assert isinstance(new_position, Position)
        assert new_position == position

    def test_to_string(self, unit: Length.Unit, frame: Frame):
        vector = [1000.0, 0.0, 0.0]

        position: Position = Position(vector, unit, frame)

        string: String = position.to_string()

        assert string is not None
        assert isinstance(string, String)
        assert string == "[1000.0, 0.0, 0.0] [m] @ GCRF"

    def test_from_lla(self, lla: LLA, earth):
        assert Position.from_lla(lla, earth) is not None

        Environment.default(True)
        assert Position.from_lla(lla) is not None
