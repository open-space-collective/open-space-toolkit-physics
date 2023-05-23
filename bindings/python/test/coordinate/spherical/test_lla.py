################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/coordinate/spherical/test_lla.py
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
LLA = physics.coordinate.spherical.LLA

################################################################################################################################################################

def test_coordinate_spherical_lla_constructors ():

    # Main Constructor
    latitude: Angle = Angle(30.0, Angle.Unit.Degree)
    longitude: Angle = Angle(30.0, Angle.Unit.Degree)
    altitude: Length = Length(1000.0, Length.Unit.Meter)

    # Construction with undefined static method

    lla: LLA = LLA(latitude, longitude, altitude)

    assert lla is not None
    assert isinstance(lla, LLA)

    # Construction with vector static method

    # ... with python list
    lla: LLA = LLA.vector([1.0, 1.0, 1.0])

    assert lla is not None
    assert isinstance(lla, LLA)

    # ... with python tuple
    lla: LLA = LLA.vector((1.0, 1.0, 1.0))

    assert lla is not None
    assert isinstance(lla, LLA)

    # ... with python numpy array
    lla: LLA = LLA.vector(np.array((1.0, 1.0, 1.0)))

    assert lla is not None
    assert isinstance(lla, LLA)

    # Construction with cartesian static method

    lla: LLA = LLA.cartesian([1.0, 1.0, 1.0], Length(1.0, Length.Unit.Meter), 0.001)

    assert lla is not None
    assert isinstance(lla, LLA)

    # Invalid latitude

    with pytest.raises(RuntimeError):

        lla: LLA = LLA.vector((95.0, 1.0, 1.0))

    # Invalid longitude

    with pytest.raises(RuntimeError):

        lla: LLA = LLA.vector((1.0, -181.0, 1.0))

    # Negative Altitude (Allowed)

    lla: LLA = LLA.vector((5.0, 1.0, -1.0))

    assert lla is not None
    assert isinstance(lla, LLA)

################################################################################################################################################################

def test_coordinate_spherical_lla_comparators ():

    # Main Constructor
    latitude: Angle = Angle(30.0, Angle.Unit.Degree)
    longitude: Angle = Angle(30.0, Angle.Unit.Degree)
    altitude: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    lla_1: LLA = LLA(latitude, longitude, altitude)
    lla_2: LLA = LLA(latitude, longitude, Length(10.0, Length.Unit.Meter))

    assert lla_1 == lla_1
    assert lla_2 == lla_2
    assert lla_1 != lla_2

################################################################################################################################################################

def test_coordinate_spherical_lla_is_defined ():

    # Main Constructor
    latitude: Angle = Angle(30.0, Angle.Unit.Degree)
    longitude: Angle = Angle(30.0, Angle.Unit.Degree)
    altitude: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    lla: LLA = LLA(latitude, longitude, altitude)

    assert lla.is_defined()
    assert LLA.undefined().is_defined() is False

################################################################################################################################################################

def test_coordinate_spherical_lla_getters ():

    # Main Constructor
    latitude: Angle = Angle(30.0, Angle.Unit.Degree)
    longitude: Angle = Angle(30.0, Angle.Unit.Degree)
    altitude: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    lla: LLA = LLA(latitude, longitude, altitude)

    # get_latitude
    lat = lla.get_latitude()

    assert lat is not None
    assert isinstance(lat, Angle)

    # get_longitude
    lon = lla.get_longitude()

    assert lon is not None
    assert isinstance(lon, Angle)

    # get_altitude
    alt = lla.get_altitude()

    assert alt is not None
    assert isinstance(alt, Length)

################################################################################################################################################################

def test_coordinate_spherical_lla_conversions ():

    # Main Constructor
    latitude: Angle = Angle(30.0, Angle.Unit.Degree)
    longitude: Angle = Angle(30.0, Angle.Unit.Degree)
    altitude: Length = Length(1000.0, Length.Unit.Meter)

    # Construction
    lla: LLA = LLA(latitude, longitude, altitude)

    # to_vector
    vector = LLA.to_vector(lla)

    assert vector is not None
    assert isinstance(vector, np.ndarray)

    # to_cartesian
    cartesian = LLA.to_cartesian(lla, Length(3.0, Length.Unit.Meter), 3.0)

    assert cartesian is not None
    assert isinstance(cartesian, np.ndarray)

    # to_string
    string = lla.to_string()

    assert string is not None
    assert isinstance(string, String)
    assert string == '[30.0 [deg], 30.0 [deg], 1000.0 [m]]'

################################################################################################################################################################
