# Apache License 2.0

import pytest
import numpy as np

from ostk.physics.time import Instant
from ostk.physics.time import DateTime
from ostk.physics.time import Scale
from ostk.physics.unit import Length
from ostk.physics.unit import Angle
from ostk.physics.coordinate import Position
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate.spherical import LLA

from ostk.physics.environment.atmospheric import Earth as EarthAtmosphericModel
from ostk.physics.environment.atmospheric.earth import NRLMSISE00


class TestNRLMSISE00:
    def test_constructor_success(self, nrlmsise00_model):
        assert isinstance(nrlmsise00_model, NRLMSISE00)

    def test_is_defined_success(self, nrlmsise00_model):
        assert nrlmsise00_model.is_defined() is True

    def test_get_density_at_lla_no_sun_success(self, nrlmsise00_model):
        lla = LLA(Angle.degrees(0.0), Angle.degrees(0.0), Length.meters(500e3))

        density = nrlmsise00_model.get_density_at(
            lla, Instant.date_time(DateTime.parse("2021-01-01 00:00:00"), Scale.UTC)
        )

        # assert sensible number for density
        assert 1.0e-15 < density < 1.0e-12
