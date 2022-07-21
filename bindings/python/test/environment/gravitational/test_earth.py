################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/gravitational/test_earth.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest
import numpy as np

from ostk.core.filesystem import Directory

from ostk.physics.time import Instant
from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel

################################################################################################################################################################

def construct_earth ():

    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008)

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    return earth_gravitational_model

################################################################################################################################################################

def test_earth_constructors ():

    # Test constructor with enums
    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.WGS84)

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM96)

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM84)

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008)

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.spherical)

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    # Test constructor with directory
    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008, Directory.undefined())

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    # Test constructor with degree and order
    earth_gravitational_model: EarthGravitationalModel = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008, Directory.undefined(), 2, 2)

    assert earth_gravitational_model is not None
    assert isinstance(earth_gravitational_model, EarthGravitationalModel)

################################################################################################################################################################

def test_earth_get_type ():

    earth_gravitational_model = construct_earth()

    assert earth_gravitational_model.get_type() is not None
    assert earth_gravitational_model.get_type() == EarthGravitationalModel.EarthType.EGM2008

################################################################################################################################################################

def test_earth_get_field_value_at ():

    earth_gravitational_model = construct_earth()

    grav_acceleration = earth_gravitational_model.get_field_value_at(np.array([6400e3, 0.0, 0.0]), Instant.J2000())
    grav_acceleration_ref = np.array([-9.74722832e+00, -1.29220148e-05, -1.34173896e-05])
    assert all([round(grav_acceleration[i], -7) == round(grav_acceleration_ref[i], -7) for i in range(0, len(grav_acceleration_ref))])

################################################################################################################################################################
