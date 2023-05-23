################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/coordinate/spherical/test_aer.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest
import numpy as np

from ostk.core.types import String

import ostk.physics as physics

################################################################################################################################################################

Angle = physics.units.Angle
Length = physics.units.Length
AER = physics.coordinate.spherical.AER

################################################################################################################################################################

def test_coordinate_spherical_aer_constructors ():

    # Main Constructor
    azimuth: Angle = Angle(30.0, Angle.Unit.Degree)
    elevation: Angle = Angle(30.0, Angle.Unit.Degree)
    aer_range: Length = Length(1000.0, Length.Unit.Meter)

    # Construction with undefined static method

    aer: AER = AER(azimuth, elevation, aer_range)

    assert aer is not None
    assert isinstance(aer, AER)

    # Construction with vector static method

    # ... with python list
    aer: AER = AER.vector([1.0, 1.0, 1.0])

    assert aer is not None
    assert isinstance(aer, AER)

    # ... with python tuple
    aer: AER = AER.vector((1.0, 1.0, 1.0))

    assert aer is not None
    assert isinstance(aer, AER)

    # ... with python numpy array
    aer: AER = AER.vector(np.array((1.0, 1.0, 1.0)))

    assert aer is not None
    assert isinstance(aer, AER)

    # Invalid azimuth

    with pytest.raises(RuntimeError):

        aer: AER = AER.vector((400.0, 1.0, 1.0))

    # Invalid elevation

    with pytest.raises(RuntimeError):

        aer: AER = AER.vector((1.0, 181.0, 1.0))

    # Negative Range

    with pytest.raises(RuntimeError):

        aer: AER = AER.vector((1.0, 2.0, -1.0))

################################################################################################################################################################

def test_coordinate_spherical_aer_comparators ():

    # Main Constructor
    azimuth: Angle = Angle(30.0, Angle.Unit.Degree)
    elevation: Angle = Angle(30.0, Angle.Unit.Degree)
    aer_range: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    aer_1: AER = AER(azimuth, elevation, aer_range)
    aer_2: AER = AER(azimuth, elevation, Length(10.0, Length.Unit.Meter))

    assert aer_1 == aer_1
    assert aer_2 == aer_2
    assert aer_1 != aer_2

################################################################################################################################################################

def test_coordinate_spherical_aer_is_defined ():

    # Main Constructor
    azimuth: Angle = Angle(30.0, Angle.Unit.Degree)
    elevation: Angle = Angle(30.0, Angle.Unit.Degree)
    aer_range: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    aer: AER = AER(azimuth, elevation, aer_range)

    assert aer.is_defined()
    assert AER.undefined().is_defined() is False

################################################################################################################################################################

def test_coordinate_spherical_aer_getters ():

    # Main Constructor
    azimuth: Angle = Angle(30.0, Angle.Unit.Degree)
    elevation: Angle = Angle(30.0, Angle.Unit.Degree)
    aer_range: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    aer: AER = AER(azimuth, elevation, aer_range)

    # get_azimuth
    lat = aer.get_azimuth()

    assert lat is not None
    assert isinstance(lat, Angle)

    # get_elevation
    lon = aer.get_elevation()

    assert lon is not None
    assert isinstance(lon, Angle)

    # get_range
    alt = aer.get_range()

    assert alt is not None
    assert isinstance(alt, Length)

################################################################################################################################################################

def test_coordinate_spherical_aer_conversions ():

    # Main Constructor
    azimuth: Angle = Angle(30.0, Angle.Unit.Degree)
    elevation: Angle = Angle(30.0, Angle.Unit.Degree)
    aer_range: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    aer: AER = AER(azimuth, elevation, aer_range)

    # to_vector
    vector = AER.to_vector(aer)

    assert vector is not None
    assert isinstance(vector, np.ndarray)

    # to_string
    string = aer.to_string()

    assert string is not None
    assert isinstance(string, String)
    assert string == '[30.0 [deg], 30.0 [deg], 1000.0 [m]]'

################################################################################################################################################################

# def test_coordinate_spherical_aer_from_position_to_position ():

################################################################################################################################################################
