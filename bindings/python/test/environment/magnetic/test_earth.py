# Apache License 2.0

import pytest

import numpy as np

from ostk.core.filesystem import Directory

from ostk.physics.environment.magnetic import Earth as EarthMagneticModel
from ostk.physics.environment.object.celestial import Earth


@pytest.fixture
def earth_magnetic_model() -> EarthMagneticModel:
    return EarthMagneticModel(EarthMagneticModel.Type.EMM2010)


class TestEarth:
    def test_constructor_success_with_type(self):
        earth_magnetic_model = EarthMagneticModel(
            EarthMagneticModel.Type.EMM2010,
        )

        assert isinstance(earth_magnetic_model, EarthMagneticModel)

    def test_constructor_success_with_directory(self):
        earth_magnetic_model = EarthMagneticModel(
            EarthMagneticModel.Type.EMM2010,
            Directory.undefined(),
        )

        assert isinstance(earth_magnetic_model, EarthMagneticModel)

    def test_get_type_success(self, earth_magnetic_model: EarthMagneticModel):
        assert earth_magnetic_model.get_type() == EarthMagneticModel.Type.EMM2010

    def test_is_defined_success(self, earth_magnetic_model: EarthMagneticModel):
        assert earth_magnetic_model.is_defined() == True
