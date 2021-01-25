################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/coordinate/test_axes.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest
import nunmpy as np

import ostk.physics as physics

################################################################################################################################################################

Frame = physics.coordinate.Frame
Axes = physics.coordinate.Axes

################################################################################################################################################################

def test_coordinate_axes_constructors ():

    # Construct arbitrary Frame
    frame: Frame = Frame.GCRF()

    # Construction using python lists
    vector_1 = [1.0, 0.0, 0.0]
    vector_2 = [0.0, 1.0, 0.0]
    vector_3 = [0.0, 0.0, 1.0]

    axes: Axes = Axes(vector_1, vector_2, vector_3, frame)

    assert axes is not None
    assert isinstance(axes, Axes)
    assert axes.is_defined() is True

    # Construction using python tuples
    vector_1 = (1.0, 0.0, 0.0)
    vector_2 = (0.0, 1.0, 0.0)
    vector_3 = (0.0, 0.0, 1.0)

    axes: Axes = Axes(vector_1, vector_2, vector_3, frame)

    assert axes is not None
    assert isinstance(axes, Axes)
    assert axes.is_defined() is True

    # Construction using python numpy arrays
    vector_1 = np.array(vector_1)
    vector_2 = np.array(vector_2)
    vector_3 = np.array(vector_3)

    axes: Axes = Axes(vector_1, vector_2, vector_3, frame)

    assert axes is not None
    assert isinstance(axes, Axes)
    assert axes.is_defined() is True

    # Construction using undefined method

    axes: Axes = Axes.undefined()

    assert axes is not None
    assert isinstance(axes, Axes)
    assert axes.is_defined() is False

################################################################################################################################################################

def test_coordinate_axes_xyz ():

    frame: Frame = Frame.GCRF()
    vector_1 = [1.0, 0.0, 0.0]
    vector_2 = [0.0, 1.0, 0.0]
    vector_3 = [0.0, 0.0, 1.0]

    axes: Axes = Axes(vector_1, vector_2, vector_3, frame)

    x = axes.x()
    y = axes.y()
    z = axes.z()

    assert x is not None
    assert isinstance(x, np.ndarray)
    assert np.array_equal(x, vector_1)

    assert y is not None
    assert isinstance(y, np.ndarray)
    assert np.array_equal(y, vector_2)

    assert z is not None
    assert isinstance(z, np.ndarray)
    assert np.array_equal(z, vector_3)

################################################################################################################################################################

def test_coordinate_axes_get_frame ():

    frame: Frame = Frame.GCRF()
    vector_1 = [1.0, 0.0, 0.0]
    vector_2 = [0.0, 1.0, 0.0]
    vector_3 = [0.0, 0.0, 1.0]

    axes: Axes = Axes(vector_1, vector_2, vector_3, frame)

    assert axes.get_frame() is not None
    assert isinstance(axes.get_frame(), Frame)
    assert axes.get_frame() == frame

################################################################################################################################################################

def test_coordinate_axes_in_frame ():

    frame: Frame = Frame.GCRF()
    vector_1 = [1.0, 0.0, 0.0]
    vector_2 = [0.0, 1.0, 0.0]
    vector_3 = [0.0, 0.0, 1.0]

    axes: Axes = Axes(vector_1, vector_2, vector_3, frame)

    assert axes.in_frame(Frame.GCRF) is not None
    assert isinstance(axes.in_frame(Frame.GCRF), Axes)
    assert axes.in_frame(Frame.GCRF) == axes

    assert axes.in_frame(Frame.TEME) is not None
    assert isinstance(axes.in_frame(Frame.TEME), Axes)
    assert axes.in_frame(Frame.TEME) != axes

################################################################################################################################################################
