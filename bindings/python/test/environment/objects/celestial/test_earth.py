# Apache License 2.0

import pytest

from ostk.core.filesystem import Directory

from ostk.physics.environment.objects.celestial_bodies import Earth

from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel
from ostk.physics.environment.atmospheric import Earth as EarthAtmosphericModel
from ostk.physics.environment.magnetic import Earth as EarthMagneticModel

@pytest.fixture
def earth():
    return Earth.default()

class TestEarth:
    def test_properties(self, earth):
        assert earth.get_gravitational_parameter() is not None
        assert earth.get_equatorial_radius() is not None
        assert earth.get_flattening() is not None
        assert earth.get_j2() is not None
        assert earth.get_j4() is not None


    def test_default_success(self, earth):
        assert earth is not None
        assert isinstance(earth, Earth)

    def test_EGM2008_success(self):
        earth = Earth.EGM2008()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.EGM2008(2190, 2160)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_WGS84_EGM96_success(self):
        earth = Earth.WGS84_EGM96()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.WGS84_EGM96(180, 180)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_EGM96_success(self):
        earth = Earth.EGM96()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.EGM96(360, 360)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_EGM84_success(self):
        earth = Earth.EGM84()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.EGM84(180, 180)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_WGS84_success(self):
        earth = Earth.WGS84()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.WGS84(20, 0)

        assert earth is not None
        assert isinstance(earth_custom, Earth)

    def test_spherical_success(self):
        earth = Earth.spherical()

        assert earth is not None
        assert isinstance(earth, Earth)

    @pytest.mark.parametrize(
        "grav_model_parameters,atmos_model_parameters,mag_model_parameters",
        (
            (
                (
                    EarthGravitationalModel.EarthType.EGM2008,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.EarthAtmosphericType.Exponential,),
                (EarthMagneticModel.EarthMagneticType.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.EarthType.EGM96,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.EarthAtmosphericType.Exponential,),
                (EarthMagneticModel.EarthMagneticType.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.EarthType.EGM84,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.EarthAtmosphericType.Exponential,),
                (EarthMagneticModel.EarthMagneticType.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.EarthType.WGS84_EGM96,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.EarthAtmosphericType.Exponential,),
                (EarthMagneticModel.EarthMagneticType.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.EarthType.WGS84,
                    Directory.undefined(),
                ),
                (EarthAtmosphericModel.EarthAtmosphericType.Exponential,),
                (EarthMagneticModel.EarthMagneticType.Dipole,),
            ),
            (
                (EarthGravitationalModel.EarthType.Spherical, Directory.undefined()),
                (EarthAtmosphericModel.EarthAtmosphericType.Exponential,),
                (EarthMagneticModel.EarthMagneticType.Dipole,),
            ),
        ),
    )
    def test_from_models(
        self, grav_model_parameters: tuple, atmos_model_parameters, mag_model_parameters
    ):
        earth = Earth.from_models(
            EarthGravitationalModel(*grav_model_parameters),
            EarthMagneticModel(*mag_model_parameters),
            EarthAtmosphericModel(*atmos_model_parameters),
        )
        assert earth.is_defined()
