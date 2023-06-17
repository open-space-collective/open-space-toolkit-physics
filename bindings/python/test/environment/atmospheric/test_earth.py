# Apache License 2.0

import pytest

import numpy as np

from ostk.core.filesystem import Directory

from ostk.physics.time import Instant
from ostk.physics.units import Length
from ostk.physics.units import Angle
from ostk.physics.coordinate import Position
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate.spherical import LLA
from ostk.physics.environment.atmospheric import Earth as EarthAtmosphericModel
from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel


@pytest.fixture
def earth_atmospheric_model() -> EarthAtmosphericModel:
    return EarthAtmosphericModel(EarthAtmosphericModel.Type.Exponential)


class TestEarth:
    def test_constructor_success_with_type(self):
        earth_atmospheric_model = EarthAtmosphericModel(
            type=EarthAtmosphericModel.Type.Exponential,
        )

        assert isinstance(earth_atmospheric_model, EarthAtmosphericModel)

    def test_constructor_success_with_directory(self):
        earth_atmospheric_model = EarthAtmosphericModel(
            type=EarthAtmosphericModel.Type.Exponential,
            directory=Directory.undefined(),
        )

        assert isinstance(earth_atmospheric_model, EarthAtmosphericModel)

    def test_get_type_success(self, earth_atmospheric_model: EarthAtmosphericModel):
        assert (
            earth_atmospheric_model.get_type() == EarthAtmosphericModel.Type.Exponential
        )

    def test_is_defined_success(self, earth_atmospheric_model: EarthAtmosphericModel):
        assert earth_atmospheric_model.is_defined() == True

    def test_get_density_at_success(self, earth_atmospheric_model: EarthAtmosphericModel):
        latitude = Angle.degrees(30.0)
        longitude = Angle.degrees(40.0)
        altitude = Length.kilometers(500.0)

        density = earth_atmospheric_model.get_density_at(
            position=Position.meters(
                coordinates=LLA(latitude, longitude, altitude).to_cartesian(
                    ellipsoid_equatorial_radius=EarthGravitationalModel.EGM2008.equatorial_radius,
                    ellipsoid_flattening=EarthGravitationalModel.EGM2008.flattening,
                ),
                frame=Frame.ITRF(),
            ),
            instant=Instant.J2000(),
        )

        assert density is not None
