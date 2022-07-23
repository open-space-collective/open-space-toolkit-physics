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

@pytest.fixture
def earth_gravitational_model () -> EarthGravitationalModel:

    return EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008)

################################################################################################################################################################

class TestEarth:

    def test_constructor_success_with_type (self):

        assert isinstance(EarthGravitationalModel(EarthGravitationalModel.EarthType.Spherical), EarthGravitationalModel)
        assert isinstance(EarthGravitationalModel(EarthGravitationalModel.EarthType.WGS84), EarthGravitationalModel)
        assert isinstance(EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM96), EarthGravitationalModel)
        assert isinstance(EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM84), EarthGravitationalModel)
        assert isinstance(EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008), EarthGravitationalModel)

    def test_constructor_success_with_directory (self):

        earth_gravitational_model = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008, Directory.undefined())

        assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    def test_constructor_success_with_degree_and_order (self):

        earth_gravitational_model = EarthGravitationalModel(EarthGravitationalModel.EarthType.EGM2008, Directory.undefined(), 2, 2)

        assert isinstance(earth_gravitational_model, EarthGravitationalModel)

    def test_get_type_success (self, earth_gravitational_model: EarthGravitationalModel):

        assert earth_gravitational_model.get_type() == EarthGravitationalModel.EarthType.EGM2008

    def test_get_field_value_at_success (self, earth_gravitational_model: EarthGravitationalModel):

        grav_acceleration = earth_gravitational_model.get_field_value_at(np.array([6400e3, 0.0, 0.0]), Instant.J2000())
        grav_acceleration_ref = np.array([-9.74722832e+00, -1.29220148e-05, -1.34173896e-05])
        assert all([round(grav_acceleration[i], -7) == round(grav_acceleration_ref[i], -7) for i in range(0, len(grav_acceleration_ref))])

################################################################################################################################################################
