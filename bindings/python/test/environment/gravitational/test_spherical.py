################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/gravitational/test_spherical.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import numpy as np

from ostk.physics.time import Instant
from ostk.physics.environment.objects.celestial_bodies.earth.models import EGM2008
from ostk.physics.environment.gravitational import Spherical as SphericalGravitationalModel

################################################################################################################################################################

class TestSpherical:

    def test_constructor_success (self):

        spherical_gravitational_model = SphericalGravitationalModel(EGM2008.gravitational_parameter)

        assert isinstance(spherical_gravitational_model, SphericalGravitationalModel)

    def test_get_field_value_at_success (self):

        spherical_gravitational_model = SphericalGravitationalModel(EGM2008.gravitational_parameter)

        grav_acceleration = spherical_gravitational_model.get_field_value_at(np.array([6400e3, 0.0, 0.0]), Instant.J2000())
        grav_acceleration_ref = np.array([-9.73145609, 0, 0])
        assert all([round(grav_acceleration[i], -7) == round(grav_acceleration_ref[i], -7) for i in range(0, 2)])

################################################################################################################################################################
