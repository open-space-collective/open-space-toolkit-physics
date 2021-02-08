################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/coordinate/test_velocity.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest
import numpy as np

from ostk.core.types import String
import ostk.physics as physics

################################################################################################################################################################

Scale = physics.time.Scale
DateTime = physics.time.DateTime
Instant = physics.time.Instant
Frame = physics.coordinate.Frame
Velocity = physics.coordinate.Velocity
Unit = Velocity.Unit

################################################################################################################################################################

def test_coordinate_position_constructors ():

    # Construct arbitrary frame
    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond

    # Construction with python lists
    vector = [1000.0, 0.0, 0.0]

    velocity: Velocity = Velocity(vector, unit, frame)

    assert velocity is not None
    assert isinstance(velocity, Velocity)
    assert velocity.is_defined()

    # Construction with python tuples
    vector = (1000.0, 0.0, 0.0)

    velocity: Velocity = Velocity(vector, unit, frame)

    assert velocity is not None
    assert isinstance(velocity, Velocity)
    assert velocity.is_defined()

    # Construction with python numpy arrays
    vector = np.array((1000.0, 0.0, 0.0))

    velocity: Velocity = Velocity(vector, unit, frame)

    assert velocity is not None
    assert isinstance(velocity, Velocity)
    assert velocity.is_defined()

    # Construction with meters static constructor
    velocity: Velocity = Velocity.meters_per_second(vector, frame)

    assert velocity is not None
    assert isinstance(velocity, Velocity)
    assert velocity.is_defined()

    # Construction with undefined static constructor
    velocity: Velocity = Velocity.undefined()

    assert velocity is not None
    assert isinstance(velocity, Velocity)
    assert velocity.is_defined() is False

################################################################################################################################################################

def test_coordinate_velocity_comparators ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector_1 = [1000.0, 0.0, 0.0]
    vector_2 = [-450.3, 234.9, -23.0]

    velocity_1: Velocity = Velocity(vector_1, unit, frame)
    velocity_2: Velocity = Velocity(vector_2, unit, frame)

    assert velocity_1 == velocity_1
    assert velocity_2 == velocity_2
    assert velocity_1 != velocity_2

################################################################################################################################################################

def test_coordinate_velocity_is_defined ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector = [1000.0, 0.0, 0.0]
    velocity: Velocity = Velocity(vector, unit, frame)

    assert velocity.is_defined()
    assert Velocity.undefined().is_defined() is False

################################################################################################################################################################

def test_coordinate_velocity_access_frame ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector = [1000.0, 0.0, 0.0]

    velocity: Velocity = Velocity(vector, unit, frame)

    ans_frame = velocity.access_frame()

    assert ans_frame is not None
    assert isinstance(ans_frame, Frame)
    assert ans_frame == frame

################################################################################################################################################################

def test_coordinate_velocity_get_coordinates ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector = [1000.0, 0.0, 0.0]

    velocity: Velocity = Velocity(vector, unit, frame)

    coordinates = velocity.get_coordinates()

    assert coordinates is not None
    assert isinstance(coordinates, np.ndarray)
    assert np.array_equal(coordinates, vector)

################################################################################################################################################################

def test_coordinate_velocity_get_unit ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector = [1000.0, 0.0, 0.0]

    velocity: Velocity = Velocity(vector, unit, frame)

    ans_unit = velocity.get_unit()

    assert ans_unit is not None
    assert isinstance(ans_unit, Unit)
    assert ans_unit == unit

################################################################################################################################################################

def test_coordinate_velocity_in_unit ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector = [1000.0, 0.0, 0.0]

    velocity: Velocity = Velocity(vector, unit, frame)

    new_velocity: Velocity = velocity.in_unit(Unit.MeterPerSecond)

    assert new_velocity is not None
    assert isinstance(new_velocity, Velocity)
    assert new_velocity == velocity

################################################################################################################################################################

@pytest.mark.skip
def test_coordinate_velocity_in_frame ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector = [1000.0, 0.0, 0.0]

    velocity: Velocity = Velocity(vector, unit, frame)

    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    new_velocity: Velocity = velocity.in_frame(frame, instant)

    assert new_velocity is not None
    assert isinstance(new_velocity, Velocity)
    assert new_velocity == velocity

################################################################################################################################################################

def test_coordinate_velocity_to_string ():

    frame: Frame = Frame.GCRF()
    unit: Unit = Unit.MeterPerSecond
    vector = [1000.0, 0.0, 0.0]

    velocity: Velocity = Velocity(vector, unit, frame)

    string: String = velocity.to_string()

    assert string is not None
    assert isinstance(string, String)
    assert string == '[1000.0, 0.0, 0.0] [m/s] @ GCRF'

################################################################################################################################################################

def test_coordinate_velocity_string_from_unit ():

    string: String = Velocity.string_from_unit(Unit.MeterPerSecond)

    assert string is not None
    assert isinstance(string, String)
    assert string == 'm/s'

################################################################################################################################################################
