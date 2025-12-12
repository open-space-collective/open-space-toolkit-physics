# Apache License 2.0

import pytest


from ostk.core.filesystem import Directory

from ostk.physics.coordinate import Frame
from ostk.physics.environment.ephemeris import Analytical
from ostk.physics.environment.ephemeris import SPICE
from ostk.physics.environment.object.celestial import Earth
from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel
from ostk.physics.environment.atmospheric import Earth as EarthAtmosphericModel
from ostk.physics.environment.magnetic import Earth as EarthMagneticModel


@pytest.fixture
def earth() -> Earth:
    return Earth.default()


@pytest.fixture
def earth_gravitational_model() -> EarthGravitationalModel:
    return EarthGravitationalModel(EarthGravitationalModel.Type.EGM96, 10, 10)


@pytest.fixture
def earth_atmospheric_model() -> EarthAtmosphericModel:
    return EarthAtmosphericModel(EarthAtmosphericModel.Type.Exponential)


@pytest.fixture
def earth_magnetic_model() -> EarthMagneticModel:
    return EarthMagneticModel(EarthMagneticModel.Type.Undefined)


class TestEarth:
    @pytest.mark.parametrize(
        "ephemeris",
        [Analytical(Frame.ITRF()), SPICE(SPICE.Object.Earth)],
    )
    def test_construct_with_ephemeris(
        self,
        ephemeris: Analytical | SPICE,
        earth_gravitational_model: EarthGravitationalModel,
        earth_atmospheric_model: EarthAtmosphericModel,
        earth_magnetic_model: EarthMagneticModel,
    ):
        earth = Earth(
            ephemeris=ephemeris,
            gravitational_model=earth_gravitational_model,
            atmospheric_model=earth_atmospheric_model,
            magnetic_model=earth_magnetic_model,
        )

        assert earth is not None

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
                    EarthGravitationalModel.Type.EGM2008,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.Type.Exponential,),
                (EarthMagneticModel.Type.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.Type.EGM96,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.Type.Exponential,),
                (EarthMagneticModel.Type.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.Type.EGM84,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.Type.Exponential,),
                (EarthMagneticModel.Type.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.Type.WGS84_EGM96,
                    Directory.undefined(),
                    20,
                    20,
                ),
                (EarthAtmosphericModel.Type.Exponential,),
                (EarthMagneticModel.Type.Dipole,),
            ),
            (
                (
                    EarthGravitationalModel.Type.WGS84,
                    Directory.undefined(),
                ),
                (EarthAtmosphericModel.Type.Exponential,),
                (EarthMagneticModel.Type.Dipole,),
            ),
            (
                (EarthGravitationalModel.Type.Spherical, Directory.undefined()),
                (EarthAtmosphericModel.Type.Exponential,),
                (EarthMagneticModel.Type.Dipole,),
            ),
        ),
    )
    def test_from_models(
        self,
        grav_model_parameters: tuple,
        atmos_model_parameters: tuple,
        mag_model_parameters: tuple,
    ):
        earth = Earth.from_models(
            EarthGravitationalModel(*grav_model_parameters),
            EarthMagneticModel(*mag_model_parameters),
            EarthAtmosphericModel(*atmos_model_parameters),
        )
        assert earth.is_defined()

    def test_singular_model_static_constructors(self):
        assert Earth.gravitational_only(
            EarthGravitationalModel(EarthGravitationalModel.Type.EGM2008)
        ).is_defined()
        assert Earth.atmospheric_only(
            EarthAtmosphericModel(
                EarthAtmosphericModel.Type.Exponential,
            )
        ).is_defined()
        assert Earth.magnetic_only(
            EarthMagneticModel(EarthMagneticModel.Type.WMM2010)
        ).is_defined()
