# Apache License 2.0

import pytest
import numpy as np

from ostk.physics.time import Instant
from ostk.physics.time import DateTime
from ostk.physics.time import Scale
from ostk.physics.units import Length
from ostk.physics.units import Angle
from ostk.physics.coordinate import Position
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate.spherical import LLA

from ostk.physics.environment.atmospheric import Earth as EarthAtmosphericModel
from ostk.physics.environment.atmospheric.earth import Exponential


class TestExponential:
    def test_constructor_success(self):
        exponential_atmospheric_model = Exponential()

        assert isinstance(exponential_atmospheric_model, Exponential)

    def test_is_defined_success(self):
        exponential_atmospheric_model = Exponential()

        assert exponential_atmospheric_model.is_defined() is True

    def test_get_density_at_lla_success(self):
        exponential_atmospheric_model = Exponential()

        lla = LLA(Angle.degrees(0.0), Angle.degrees(0.0), Length.meters(500e3))

        density = exponential_atmospheric_model.get_density_at(
            lla, Instant.date_time(DateTime.parse("2021-01-01 00:00:00"), Scale.UTC)
        )

        # assert sensible number for density
        assert 1.0e-15 < density < 1.0e-12

    def test_get_density_at_position_success(self):
        exponential_atmospheric_model = Exponential()

        position = Position.meters(np.array([6878.1e3, 0, 0]), Frame.ITRF())

        density = exponential_atmospheric_model.get_density_at(
            position, Instant.date_time(DateTime.parse("2021-01-01 00:00:00"), Scale.UTC)
        )

        # assert sensible number for density
        assert 1.0e-15 < density < 1.0e-12