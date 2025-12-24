# Apache License 2.0

import pathlib

import pytest

from ostk.core.filesystem import Path
from ostk.core.filesystem import File
from ostk.physics.time import Instant
from ostk.physics.time import DateTime
from ostk.physics.time import Scale
from ostk.physics.unit import Length
from ostk.physics.unit import Angle
from ostk.physics.coordinate import Position
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate.spherical import LLA
from ostk.physics.environment.atmospheric import Earth as EarthAtmosphericModel
from ostk.physics.environment.atmospheric.earth import CSSISpaceWeather
from ostk.physics.environment.gravitational import Earth as EarthGravitationalModel
from ostk.physics.environment.object.celestial import Sun
from ostk.physics.environment.atmospheric.earth import Manager


@pytest.fixture
def cssi_space_weather() -> CSSISpaceWeather:
    return CSSISpaceWeather.load(
        File.path(
            Path.parse(
                f"{pathlib.Path(__file__).parent.absolute()}/earth/data/SW-Last5Years.test.csv"
            )
        )
    )


@pytest.fixture
def manager() -> Manager:
    manager = Manager.get()

    yield manager

    manager.reset()
    manager.clear_local_repository()


@pytest.fixture
def manager_with_cssi_space_weather(cssi_space_weather: CSSISpaceWeather) -> Manager:
    manager = Manager.get()
    manager.load_cssi_space_weather(cssi_space_weather)

    yield manager

    manager.reset()
    manager.clear_local_repository()


@pytest.fixture
def earth_atmospheric_model_exponential() -> EarthAtmosphericModel:
    return EarthAtmosphericModel(EarthAtmosphericModel.Type.Exponential)


@pytest.fixture
def earth_atmospheric_model_nrlmsise() -> EarthAtmosphericModel:
    return EarthAtmosphericModel(EarthAtmosphericModel.Type.NRLMSISE00)


class TestEarth:
    def test_constructor_success_with_type(self):
        earth_atmospheric_model = EarthAtmosphericModel(
            type=EarthAtmosphericModel.Type.Exponential,
            input_data_type=EarthAtmosphericModel.InputDataType.Undefined,
        )

        assert isinstance(earth_atmospheric_model, EarthAtmosphericModel)

    def test_constructor_success_exponential_with_params(self):
        earth_atmospheric_model = EarthAtmosphericModel(
            type=EarthAtmosphericModel.Type.Exponential,
            input_data_type=EarthAtmosphericModel.InputDataType.Undefined,
            f107_constant_value=160.0,
            f107_average_constant_value=160.0,
            kp_constant_value=4.0,
            earth_frame=Frame.ITRF(),
            earth_radius=EarthGravitationalModel.WGS84.equatorial_radius,
            earth_flattening=EarthGravitationalModel.WGS84.flattening,
            sun_celestial=Sun.default(),
        )

        assert isinstance(earth_atmospheric_model, EarthAtmosphericModel)

    def test_constructor_success_nrlmsise_file_with_params(self):
        earth_atmospheric_model = EarthAtmosphericModel(
            type=EarthAtmosphericModel.Type.NRLMSISE00,
            input_data_type=EarthAtmosphericModel.InputDataType.CSSISpaceWeatherFile,
            earth_frame=Frame.ITRF(),
            earth_radius=EarthGravitationalModel.WGS84.equatorial_radius,
            earth_flattening=EarthGravitationalModel.WGS84.flattening,
        )

        assert isinstance(earth_atmospheric_model, EarthAtmosphericModel)

    def test_constructor_success_nrlmsise_constant_with_params(self):
        earth_atmospheric_model = EarthAtmosphericModel(
            type=EarthAtmosphericModel.Type.NRLMSISE00,
            input_data_type=EarthAtmosphericModel.InputDataType.ConstantFluxAndGeoMag,
            f107_constant_value=160.0,
            f107_average_constant_value=160.0,
            kp_constant_value=4.0,
            earth_frame=Frame.ITRF(),
            earth_radius=EarthGravitationalModel.WGS84.equatorial_radius,
            earth_flattening=EarthGravitationalModel.WGS84.flattening,
            sun_celestial=Sun.default(),
        )

        assert isinstance(earth_atmospheric_model, EarthAtmosphericModel)

    def test_get_type_success(
        self, earth_atmospheric_model_exponential: EarthAtmosphericModel
    ):
        assert (
            earth_atmospheric_model_exponential.get_type()
            == EarthAtmosphericModel.Type.Exponential
        )

    def test_get_input_data_type_success(
        self, earth_atmospheric_model_exponential: EarthAtmosphericModel
    ):
        assert (
            earth_atmospheric_model_exponential.get_input_data_type()
            == EarthAtmosphericModel.InputDataType.Undefined
        )

    def test_is_defined_success(
        self,
        earth_atmospheric_model_exponential: EarthAtmosphericModel,
    ):
        assert earth_atmospheric_model_exponential.is_defined()

    def test_get_density_at_exponential_success(
        self, earth_atmospheric_model_exponential: EarthAtmosphericModel
    ):
        latitude = Angle.degrees(30.0)
        longitude = Angle.degrees(40.0)
        altitude = Length.kilometers(500.0)

        density = earth_atmospheric_model_exponential.get_density_at(
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

    def test_get_density_at_nrlmsise_success(
        self,
        earth_atmospheric_model_nrlmsise: EarthAtmosphericModel,
        manager_with_cssi_space_weather: Manager,
    ):
        latitude = Angle.degrees(30.0)
        longitude = Angle.degrees(40.0)
        altitude = Length.kilometers(500.0)

        density = earth_atmospheric_model_nrlmsise.get_density_at(
            position=Position.meters(
                coordinates=LLA(latitude, longitude, altitude).to_cartesian(
                    ellipsoid_equatorial_radius=EarthGravitationalModel.EGM2008.equatorial_radius,
                    ellipsoid_flattening=EarthGravitationalModel.EGM2008.flattening,
                ),
                frame=Frame.ITRF(),
            ),
            instant=Instant.date_time(DateTime.parse("2021-01-01 00:00:00"), Scale.UTC),
        )

        assert density is not None

    def test_exponential_static_method_success(self):
        assert isinstance(EarthAtmosphericModel.exponential(), EarthAtmosphericModel)

    def test_nrlmsise00_with_cssi_static_method_success(self):
        assert isinstance(EarthAtmosphericModel.nrlmsise00_with_cssi(), EarthAtmosphericModel)

    def test_nrlmsise00_with_cssi_static_method_with_sun_success(self):
        assert isinstance(EarthAtmosphericModel.nrlmsise00_with_cssi(sun_celestial=Sun.default()), EarthAtmosphericModel)
        assert isinstance(EarthAtmosphericModel.nrlmsise00_with_cssi(), EarthAtmosphericModel)

    def test_nrlmsise00_with_constant_flux_static_method_success(self):
        assert isinstance(EarthAtmosphericModel.nrlmsise00_with_constant_flux(f107_constant_value=150.0, f107_average_constant_value=150.0, kp_constant_value=3.0), EarthAtmosphericModel)
