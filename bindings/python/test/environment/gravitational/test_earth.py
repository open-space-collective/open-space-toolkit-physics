# Apache License 2.0

import pytest

import numpy as np

from ostk.core.filesystem import Directory

from ostk.physics.time import Instant
from ostk.physics.environment.gravitational import Model as GravitationalModel
from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel


@pytest.fixture
def earth_gravitational_model() -> EarthGravitationalModel:
    return EarthGravitationalModel(EarthGravitationalModel.Type.EGM2008)


class TestEarth:
    def test_constructor_success_with_type(self):
        assert isinstance(
            EarthGravitationalModel(EarthGravitationalModel.Type.Spherical),
            EarthGravitationalModel,
        )
        assert isinstance(
            EarthGravitationalModel(EarthGravitationalModel.Type.WGS84),
            EarthGravitationalModel,
        )
        assert isinstance(
            EarthGravitationalModel(EarthGravitationalModel.Type.EGM96),
            EarthGravitationalModel,
        )
        assert isinstance(
            EarthGravitationalModel(EarthGravitationalModel.Type.EGM84),
            EarthGravitationalModel,
        )
        assert isinstance(
            EarthGravitationalModel(EarthGravitationalModel.Type.EGM2008),
            EarthGravitationalModel,
        )

    def test_constructor_success_with_directory(self):
        earth_gravitational_model = EarthGravitationalModel(
            EarthGravitationalModel.Type.EGM2008, Directory.undefined()
        )

        assert isinstance(earth_gravitational_model, EarthGravitationalModel)
        assert isinstance(earth_gravitational_model, GravitationalModel)

    def test_constructor_success_with_degree_and_order(self):
        earth_gravitational_model = EarthGravitationalModel(
            EarthGravitationalModel.Type.EGM2008, Directory.undefined(), 2, 2
        )

        assert isinstance(earth_gravitational_model, EarthGravitationalModel)
        assert isinstance(earth_gravitational_model, GravitationalModel)

    def test_constructor_success_without_directory_with_degree_and_order(self):
        earth_gravitational_model = EarthGravitationalModel(
            EarthGravitationalModel.Type.EGM2008, 2, 2
        )

        assert isinstance(earth_gravitational_model, EarthGravitationalModel)
        assert isinstance(earth_gravitational_model, GravitationalModel)

    def test_get_type_success(self, earth_gravitational_model: EarthGravitationalModel):
        assert (
            earth_gravitational_model.get_type() == EarthGravitationalModel.Type.EGM2008
        )

    def test_get_degree_order_success(self):
        egm_earth_gravitational_model = EarthGravitationalModel(
            EarthGravitationalModel.Type.EGM2008, Directory.undefined(), 51, 50
        )

        assert egm_earth_gravitational_model.get_degree() == 51
        assert egm_earth_gravitational_model.get_order() == 50

        spherical_earth_gravitational_model = EarthGravitationalModel(
            EarthGravitationalModel.Type.Spherical
        )

        assert spherical_earth_gravitational_model.get_degree().is_defined() is False
        assert spherical_earth_gravitational_model.get_order().is_defined() is False

    def test_get_field_value_at_success(
        self, earth_gravitational_model: EarthGravitationalModel
    ):
        grav_acceleration = earth_gravitational_model.get_field_value_at(
            np.array([6400e3, 0.0, 0.0]), Instant.J2000()
        )
        grav_acceleration_ref = np.array(
            [-9.74722832e00, -1.29220148e-05, -1.34173896e-05]
        )
        assert all(
            [
                round(grav_acceleration[i], -7) == round(grav_acceleration_ref[i], -7)
                for i in range(0, len(grav_acceleration_ref))
            ]
        )

    def test_gravity_constant(self):
        assert EarthGravitationalModel.gravity_constant is not None
