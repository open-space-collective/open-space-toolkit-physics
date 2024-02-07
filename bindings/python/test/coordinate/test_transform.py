# Apache License 2.0

import pytest
import numpy as np

from ostk.core.type import String
import ostk.physics as physics

import ostk.mathematics as mathematics

Scale = physics.time.Scale
DateTime = physics.time.DateTime
Instant = physics.time.Instant
Quaternion = mathematics.geometry.d3.transformation.rotation.Quaternion
Transform = physics.coordinate.Transform
Type = Transform.Type


def test_coordinate_transform_type():
    enum_members = Type.__members__

    list_keys = ["Undefined", "Active", "Passive"]
    list_values = [Type.Undefined, Type.Active, Type.Passive]

    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values


def test_coordinate_transform_constructors():
    # Construct arbitrary Instant
    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    # Construct arbitrary Orientation
    quaternion: Quaternion = Quaternion([0.0, 0.0, 0.0], 1.0)

    # Construct Transform Type
    transform_type: Type = Type.Passive

    # Construction using python lists
    translation = [1.0, 0.0, 0.0]
    velocity = [0.01, 0.0, 0.0]
    angular_velocity = [0.01, 0.01, 0.01]

    transform: Transform = Transform(
        instant, translation, velocity, quaternion, angular_velocity, transform_type
    )

    assert transform is not None
    assert isinstance(transform, Transform)

    # Construction using python tuples
    translation = (1.0, 0.0, 0.0)
    velocity = (0.01, 0.0, 0.0)
    angular_velocity = (0.01, 0.01, 0.01)

    transform: Transform = Transform(
        instant, translation, velocity, quaternion, angular_velocity, transform_type
    )

    assert transform is not None
    assert isinstance(transform, Transform)

    # Construction using python numpy arrays
    translation = np.array(translation)
    velocity = np.array(velocity)
    angular_velocity = np.array(angular_velocity)

    transform: Transform = Transform(
        instant, translation, velocity, quaternion, angular_velocity, transform_type
    )

    assert transform is not None
    assert isinstance(transform, Transform)

    # Construct using identity static constructor

    transform: Transform = Transform.identity(instant)

    assert transform is not None
    assert isinstance(transform, Transform)

    # Construct using active static constructor

    transform: Transform = Transform.active(
        instant, translation, velocity, quaternion, angular_velocity
    )

    assert transform is not None
    assert isinstance(transform, Transform)

    # Construct using passive static constructor

    transform: Transform = Transform.passive(
        instant, translation, velocity, quaternion, angular_velocity
    )

    assert transform is not None
    assert isinstance(transform, Transform)


def test_coordinate_transform_comparators():
    # Construct arbitrary Instant
    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    # Construct arbitrary Orientation
    quaternion: Quaternion = Quaternion([0.0, 0.0, 0.0], 1.0)

    # Construct Transform Type
    transform_type: Type = Type.Passive

    # Construction using python lists
    translation_1 = [1.0, 0.0, 0.0]
    translation_2 = [0.0, 0.0, 0.0]
    velocity = [0.01, 0.0, 0.0]
    angular_velocity = [0.01, 0.01, 0.01]

    transform_1: Transform = Transform(
        instant, translation_1, velocity, quaternion, angular_velocity, transform_type
    )
    transform_2: Transform = Transform(
        instant, translation_2, velocity, quaternion, angular_velocity, transform_type
    )

    assert transform_1 == transform_1
    assert transform_2 == transform_2
    assert transform_1 != transform_2


def test_coordinate_transform_operators():
    # Construct arbitrary Instant
    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    # Construct arbitrary Orientation
    quaternion: Quaternion = Quaternion([0.0, 0.0, 0.0], 1.0)

    # Construct Transform Type
    transform_type: Type = Type.Passive

    # Construction using python lists
    translation = [1.0, 0.0, 0.0]
    velocity = [0.01, 0.0, 0.0]
    angular_velocity = [0.01, 0.01, 0.01]

    transform: Transform = Transform(
        instant, translation, velocity, quaternion, angular_velocity, transform_type
    )

    mul_transform = transform * transform

    assert mul_transform is not None
    assert isinstance(mul_transform, Transform)
    assert mul_transform.is_defined()

    transform *= transform

    assert transform is not None
    assert isinstance(transform, Transform)
    assert transform.is_defined()


def test_coordinate_transform_is_defined():
    # Construct arbitrary Instant
    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    # Construct arbitrary Orientation
    quaternion: Quaternion = Quaternion([0.0, 0.0, 0.0], 1.0)

    # Construct Transform Type
    transform_type: Type = Type.Passive

    # Construction using python lists
    translation = [1.0, 0.0, 0.0]
    velocity = [0.01, 0.0, 0.0]
    angular_velocity = [0.01, 0.01, 0.01]

    transform: Transform = Transform(
        instant, translation, velocity, quaternion, angular_velocity, transform_type
    )

    assert transform.is_defined()
    assert transform.undefined().is_defined() is False


def test_coordinate_transform_is_identity():
    # Construct arbitrary Instant
    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    # Construct arbitrary Orientation
    quaternion: Quaternion = Quaternion([0.0, 0.0, 0.0], 1.0)

    # Construct Transform Type
    transform_type: Type = Type.Passive

    # Construction using python lists
    translation = [0.0, 0.0, 0.0]
    velocity = [0.00, 0.0, 0.0]
    angular_velocity = [0.00, 0.00, 0.00]

    transform: Transform = Transform(
        instant, translation, velocity, quaternion, angular_velocity, transform_type
    )

    assert transform.is_defined()
    assert transform.is_identity()
    assert transform.identity(instant).is_identity()


# def test_coordinate_transform_accesses ():

# access_instant


# access_translation


# access_velocity


# access_orientation


# access_angular_velocity


def test_coordinate_transform_getters():
    # Construct arbitrary Instant
    instant: Instant = Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)

    # Construct arbitrary Orientation
    quaternion: Quaternion = Quaternion([0.0, 0.0, 0.0], 1.0)

    # Construct Transform Type
    transform_type: Type = Type.Passive

    # Construction using python lists
    translation = [1.0, 0.0, 0.0]
    velocity = [0.01, 0.0, 0.0]
    angular_velocity = [0.01, 0.01, 0.01]

    transform: Transform = Transform(
        instant, translation, velocity, quaternion, angular_velocity, transform_type
    )

    # get_instant
    ans_instant: Instant = transform.get_instant()

    assert ans_instant is not None
    assert isinstance(ans_instant, Instant)
    assert ans_instant == instant

    # get_translation
    ans_translation = transform.get_translation()

    assert ans_translation is not None
    assert isinstance(ans_translation, np.ndarray)
    assert np.array_equal(ans_translation, translation)

    # get_velocity
    ans_velocity = transform.get_velocity()

    assert ans_velocity is not None
    assert isinstance(ans_velocity, np.ndarray)
    assert np.array_equal(ans_velocity, velocity)

    # get_orientation
    ans_quaternion = transform.get_orientation()

    assert ans_quaternion is not None
    assert isinstance(ans_quaternion, Quaternion)
    assert ans_quaternion == quaternion

    # get_angular_velocity
    ans_angular_velocity = transform.get_angular_velocity()

    assert ans_angular_velocity is not None
    assert isinstance(ans_angular_velocity, np.ndarray)
    assert np.array_equal(ans_angular_velocity, angular_velocity)

    # get_inverse
    inverse: Transform = transform.get_inverse()

    assert inverse is not None
    assert isinstance(inverse, Transform)


# def test_coordinate_transform_apply_to_position ():

# ################################################################################################################################################################

# def test_coordinate_transform_apply_to_velocity ():

# ################################################################################################################################################################

# def test_coordinate_transform_apply_to_vector ():
