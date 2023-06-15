# Apache License 2.0

import pytest

import numpy as np

from ostk.core.filesystem import Directory

from ostk.physics.time import Instant
from ostk.physics.environment.gravitational import Model as GravitationalModel
from ostk.physics.environment.gravitational import Moon as MoonGravitationalModel


@pytest.fixture
def moon_gravitational_model() -> MoonGravitationalModel:
    return MoonGravitationalModel(MoonGravitationalModel.Type.Spherical)


class TestMoon:
    def test_constructor_success_with_type(self):
        assert isinstance(
            MoonGravitationalModel(MoonGravitationalModel.Type.Spherical),
            MoonGravitationalModel,
        )
        assert isinstance(
            MoonGravitationalModel(MoonGravitationalModel.Type.Spherical),
            GravitationalModel,
        )

    def test_constructor_success_with_directory(self):
        moon_gravitational_model = MoonGravitationalModel(
            MoonGravitationalModel.Type.Spherical, Directory.undefined()
        )

        assert isinstance(moon_gravitational_model, MoonGravitationalModel)
        assert isinstance(moon_gravitational_model, GravitationalModel)

    def test_get_type_success(self, moon_gravitational_model: MoonGravitationalModel):
        assert (
            moon_gravitational_model.get_type() == MoonGravitationalModel.Type.Spherical
        )

    def test_get_field_value_at_success(
        self, moon_gravitational_model: MoonGravitationalModel
    ):
        grav_acceleration = moon_gravitational_model.get_field_value_at(
            np.array([160000e3, 0.0, 0.0]), Instant.J2000()
        )
        grav_acceleration_ref = np.array([-0.000191515625, 0, 0])
        assert all(
            [
                round(grav_acceleration[i], -7) == round(grav_acceleration_ref[i], -7)
                for i in range(0, len(grav_acceleration_ref))
            ]
        )
