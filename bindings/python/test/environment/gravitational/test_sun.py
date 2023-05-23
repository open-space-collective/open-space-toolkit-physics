################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/gravitational/test_sun.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

from ostk.core.filesystem import Directory

from ostk.physics.time import Instant
from ostk.physics.environment.gravitational import Sun as SunGravitationalModel

################################################################################################################################################################

@pytest.fixture
def sun_gravitational_model () -> SunGravitationalModel:

    return SunGravitationalModel(SunGravitationalModel.SunType.Spherical)

################################################################################################################################################################

class TestSun:

    def test_constructor_success_with_type (self):

        assert isinstance(SunGravitationalModel(SunGravitationalModel.SunType.Spherical), SunGravitationalModel)

    def test_constructor_success_with_directory (self):

        sun_gravitational_model = SunGravitationalModel(SunGravitationalModel.SunType.Spherical, Directory.undefined())

        assert isinstance(sun_gravitational_model, SunGravitationalModel)

    def test_get_type_success (self, sun_gravitational_model: SunGravitationalModel):

        assert sun_gravitational_model.get_type() == SunGravitationalModel.SunType.Spherical

    def test_get_field_value_at_success (self, sun_gravitational_model: SunGravitationalModel):

        grav_acceleration = sun_gravitational_model.get_field_value_at(np.array([150000e9, 0.0, 0.0]), Instant.J2000())
        grav_acceleration_ref = np.array([-0.00589833066746667, 0, 0])
        assert all([round(grav_acceleration[i], -7) == round(grav_acceleration_ref[i], -7) for i in range(0, len(grav_acceleration_ref))])

################################################################################################################################################################
