# Apache License 2.0

"""Round trips of the Eigen types (Vector2d, Vector3d) that cross the Python boundary.

ostk.physics binds Vector2d (arguments) and Vector3d (arguments and return values). These tests pin how
arrays, lists and tuples are converted, so that they behave like the former pybind11 bindings.
"""

import numpy as np
import pytest

from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion

from ostk.physics.coordinate import Frame
from ostk.physics.coordinate import Position
from ostk.physics.coordinate import Transform
from ostk.physics.time import Instant
from ostk.physics.unit import Angle


@pytest.fixture
def transform() -> Transform:
    return Transform.active(
        Instant.J2000(),
        [1.0, 2.0, 3.0],
        [4.0, 5.0, 6.0],
        Quaternion.unit(),
        [7.0, 8.0, 9.0],
    )


class TestVector3dArgument:
    @pytest.mark.parametrize(
        "coordinates",
        [
            [1.0, 2.0, 3.0],
            (1.0, 2.0, 3.0),
            [1, 2, 3],
            np.array([1.0, 2.0, 3.0]),
            np.array([1, 2, 3]),
            np.array([1.0, 2.0, 3.0], dtype=np.float32),
            np.array([[1.0], [2.0], [3.0]]),
            np.array([1.0, 2.0, 3.0], order="F"),
            np.array([1.0, 0.0, 2.0, 0.0, 3.0, 0.0])[::2],
        ],
        ids=[
            "list",
            "tuple",
            "int list",
            "ndarray",
            "int ndarray",
            "float32 ndarray",
            "column ndarray",
            "fortran ndarray",
            "strided ndarray",
        ],
    )
    def test_accepted(self, coordinates):
        position = Position.meters(coordinates, Frame.GCRF())

        assert np.array_equal(position.get_coordinates(), [1.0, 2.0, 3.0])

    def test_read_only_ndarray(self):
        coordinates = np.array([1.0, 2.0, 3.0])
        coordinates.flags.writeable = False

        position = Position.meters(coordinates, Frame.GCRF())

        assert np.array_equal(position.get_coordinates(), [1.0, 2.0, 3.0])

    def test_input_is_copied(self):
        coordinates = np.array([1.0, 2.0, 3.0])

        position = Position.meters(coordinates, Frame.GCRF())

        coordinates[0] = 100.0

        assert np.array_equal(position.get_coordinates(), [1.0, 2.0, 3.0])

    @pytest.mark.parametrize(
        "coordinates",
        [
            [1.0, 2.0],
            [1.0, 2.0, 3.0, 4.0],
            np.array([[1.0, 2.0, 3.0]]),
            np.eye(3),
            ["a", "b", "c"],
            "abc",
            [[1.0], [2.0, 3.0], [4.0]],
        ],
        ids=[
            "too short",
            "too long",
            "row ndarray",
            "matrix",
            "list of str",
            "str",
            "ragged",
        ],
    )
    def test_rejected(self, coordinates):
        with pytest.raises(TypeError):
            Position.meters(coordinates, Frame.GCRF())


class TestVector3dReturnValue:
    def test_values_dtype_and_shape(self):
        coordinates = Position.meters([1.0, 2.0, 3.0], Frame.GCRF()).get_coordinates()

        assert isinstance(coordinates, np.ndarray)
        assert coordinates.dtype == np.float64
        assert coordinates.shape == (3,)
        assert np.array_equal(coordinates, [1.0, 2.0, 3.0])

    def test_member_getters(self, transform: Transform):
        for getter in (
            transform.get_translation,
            transform.get_velocity,
            transform.get_angular_velocity,
        ):
            value = getter()

            assert isinstance(value, np.ndarray)
            assert value.dtype == np.float64
            assert value.shape == (3,)
            assert np.array_equal(value, getter())

    def test_is_an_independent_writeable_copy(self, transform: Transform):
        translation = transform.get_translation()
        expected = translation.copy()

        assert translation.flags.writeable

        translation[0] = 100.0

        assert np.array_equal(transform.get_translation(), expected)
        assert transform.get_translation() is not transform.get_translation()

    def test_outlives_its_source(self):
        coordinates = Position.meters([1.0, 2.0, 3.0], Frame.GCRF()).get_coordinates()

        assert np.array_equal(coordinates, [1.0, 2.0, 3.0])

    def test_round_trip(self):
        transform = Transform.identity(Instant.J2000())

        vector = np.array([1.0, -2.0, 3.5])

        assert np.array_equal(transform.apply_to_vector(vector), vector)
        assert np.array_equal(transform.apply_to_position(vector), vector)
        assert np.array_equal(transform.apply_to_vector([1.0, -2.0, 3.5]), vector)


class TestVector2dArgument:
    @pytest.mark.parametrize(
        "first, second",
        [
            ([1.0, 0.0], [0.0, 1.0]),
            ((1.0, 0.0), (0.0, 1.0)),
            (np.array([1.0, 0.0]), np.array([0.0, 1.0])),
            (np.array([[1.0], [0.0]]), np.array([[0.0], [1.0]])),
        ],
        ids=["list", "tuple", "ndarray", "column ndarray"],
    )
    def test_accepted(self, first, second):
        assert Angle.between(first, second).in_degrees() == pytest.approx(90.0)

    def test_rejected(self):
        with pytest.raises(TypeError):
            Angle.between([1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0])
