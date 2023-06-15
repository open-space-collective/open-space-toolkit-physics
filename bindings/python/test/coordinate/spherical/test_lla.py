# Apache License 2.0

import pytest
import numpy as np

from ostk.core.types import String

import ostk.physics as physics

Angle = physics.units.Angle
Length = physics.units.Length
LLA = physics.coordinate.spherical.LLA
Spherical = physics.environment.objects.celestial_bodies.earth.models.Spherical
WGS84_EGM96 = physics.environment.objects.celestial_bodies.earth.models.WGS84_EGM96

@pytest.fixture
def latitude_float() -> float:
    return 30.0

@pytest.fixture
def longitude_float() -> float:
    return 30.0

@pytest.fixture
def altitude_float() -> float:
    return 1000.0

@pytest.fixture
def latitude(latitude_float: float) -> Angle:
    return Angle(latitude_float, Angle.Unit.Degree)

@pytest.fixture
def longitude(longitude_float: float) -> Angle:
    return Angle(longitude_float, Angle.Unit.Degree)

@pytest.fixture
def altitude(altitude_float: float) -> Length:
    return Length(altitude_float, Length.Unit.Meter)

@pytest.fixture
def lla(latitude: Angle, longitude: Angle, altitude: Length) -> LLA:
    return LLA(latitude, longitude, altitude)

@pytest.fixture
def lla_point_equator_1() -> LLA:
    return LLA(
        Angle(0.0, Angle.Unit.Degree),
        Angle(0.0, Angle.Unit.Degree),
        Length(1.0, Length.Unit.Meter)
    )

@pytest.fixture
def lla_point_equator_2() -> LLA:
    return LLA(
        Angle(0.0, Angle.Unit.Degree),
        Angle(90.0, Angle.Unit.Degree),
        Length(1.0, Length.Unit.Meter)
    )

@pytest.fixture
def lla_point_equator_3() -> LLA:
    return LLA(
        Angle(0.0, Angle.Unit.Degree),
        Angle(180.0, Angle.Unit.Degree),
        Length(1.0, Length.Unit.Meter)
    )

@pytest.fixture
def lla_north_pole() -> LLA:
    return LLA(
        Angle(90.0, Angle.Unit.Degree),
        Angle(0.0, Angle.Unit.Degree),
        Length(1.0, Length.Unit.Meter)
    )

@pytest.fixture
def lla_south_pole() -> LLA:
    return LLA(
        Angle(-90.0, Angle.Unit.Degree),
        Angle(0.0, Angle.Unit.Degree),
        Length(1.0, Length.Unit.Meter)
    )


class TestLLA:
    def test_constructor_list_success(self,
                                      latitude_float: float,
                                      longitude_float: float,
                                      altitude_float: float):

        lla: LLA = LLA.vector([latitude_float, longitude_float, altitude_float])
        assert lla is not None

    def test_constructor_tuple_success(self,
                                       latitude_float: float,
                                       longitude_float: float,
                                       altitude_float: float):

        lla: LLA = LLA.vector((latitude_float, longitude_float, altitude_float))
        assert lla is not None

    def test_constructor_numpy_array_success(self,
                                             latitude_float: float,
                                             longitude_float: float,
                                             altitude_float: float):

        lla: LLA = LLA.vector(np.array((latitude_float, longitude_float, altitude_float)))
        assert lla is not None

    def test_constructor_vector_failure_latitude(self):

        with pytest.raises(RuntimeError):
            lla: LLA = LLA.vector((95.0, 1.0, 1.0))

    def test_constructor_vector_failure_longitude(self):

        with pytest.raises(RuntimeError):
            lla: LLA = LLA.vector((1.0, -181.0, 1.0))

    def test_constructor_vector_success_altitude_negative(self):

        lla: LLA = LLA.vector((5.0, 1.0, -1.0))
        assert lla is not None

    def test_constructor_cartesian_success(self):

        lla: LLA = LLA.cartesian([1.0, 1.0, 1.0], Length(1.0, Length.Unit.Meter), 0.001)
        assert lla is not None

    def test_comparator(self,
                        lla_point_equator_1: LLA,
                        lla_point_equator_2: LLA):

        assert lla_point_equator_1 == lla_point_equator_1
        assert lla_point_equator_2 == lla_point_equator_2
        assert lla_point_equator_1 != lla_point_equator_2

    def test_is_defined(self,
                        lla: LLA):

        assert lla.is_defined()
        assert lla.undefined().is_defined() is False

    def test_getters(self,
                     latitude: Angle,
                     longitude: Angle,
                     altitude: Length,
                     lla: LLA):

        assert lla.get_latitude() == latitude
        assert lla.get_longitude() == longitude
        assert lla.get_altitude() == altitude

    def test_conversion_vector(self,
                               latitude_float: float,
                               longitude_float: float,
                               altitude_float: float,
                               lla: LLA):

        vector: np.ndarray = lla.to_vector()

        assert vector[0] == latitude_float
        assert vector[1] == longitude_float
        assert vector[2] == altitude_float

    def test_conversion_cartesian(self,
                                  lla: LLA):

        cartesian: np.ndarray = LLA.to_cartesian(lla, Length(3.0, Length.Unit.Meter), 3.0)
        assert cartesian is not None

    def test_conversion_string(self,
                               latitude_float: float,
                               longitude_float: float,
                               altitude_float: float,
                               lla: LLA):

        lla_string: String = lla.to_string()

        assert lla_string is not None
        assert isinstance(lla_string, String)
        assert lla_string == f"[{latitude_float} [deg], {longitude_float} [deg], {altitude_float} [m]]"

    def test_distance_between(self,
                              lla_point_equator_1: LLA,
                              lla_point_equator_2: LLA,
                              lla_point_equator_3: LLA,
                              lla_north_pole: LLA,
                              lla_south_pole: LLA):

        zero_distance_spherical: Length = LLA.distance_between(lla_point_equator_1, lla_point_equator_1, Spherical.equatorial_radius, Spherical.flattening)
        assert zero_distance_spherical is not None
        assert zero_distance_spherical.in_meters() == 0.0

        distance_spherical_equatorial_1_2: Length = LLA.distance_between(lla_point_equator_1, lla_point_equator_2, Spherical.equatorial_radius, Spherical.flattening)
        distance_spherical_equatorial_2_1: Length = LLA.distance_between(lla_point_equator_2, lla_point_equator_1, Spherical.equatorial_radius, Spherical.flattening)
        assert distance_spherical_equatorial_1_2.in_meters() == Spherical.equatorial_radius.in_meters() * np.pi / 2
        assert distance_spherical_equatorial_2_1.in_meters() == Spherical.equatorial_radius.in_meters() * np.pi / 2

        distance_spherical_equatorial_1_3: Length = LLA.distance_between(lla_point_equator_1, lla_point_equator_3, Spherical.equatorial_radius, Spherical.flattening)
        distance_spherical_equatorial_3_1: Length = LLA.distance_between(lla_point_equator_3, lla_point_equator_1, Spherical.equatorial_radius, Spherical.flattening)
        assert distance_spherical_equatorial_1_3.in_meters() == Spherical.equatorial_radius.in_meters() * np.pi
        assert distance_spherical_equatorial_3_1.in_meters() == Spherical.equatorial_radius.in_meters() * np.pi

        distance_spherical_poles: Length = LLA.distance_between(lla_north_pole, lla_south_pole, Spherical.equatorial_radius, Spherical.flattening)
        assert distance_spherical_poles == distance_spherical_equatorial_1_3

        distance_wgs84_poles: Length = LLA.distance_between(lla_north_pole, lla_south_pole, WGS84_EGM96.equatorial_radius, WGS84_EGM96.flattening)
        distance_wgs84_equatorial_1_2: Length = LLA.distance_between(lla_point_equator_1, lla_point_equator_2, WGS84_EGM96.equatorial_radius, WGS84_EGM96.flattening)
        assert distance_wgs84_equatorial_1_2 == distance_spherical_equatorial_1_2  # on equator

        distance_wgs84_equatorial_1_3: Length = LLA.distance_between(lla_point_equator_1, lla_point_equator_3, WGS84_EGM96.equatorial_radius, WGS84_EGM96.flattening)  # through the poles
        distance_wgs84_equatorial_3_1: Length = LLA.distance_between(lla_point_equator_3, lla_point_equator_1, WGS84_EGM96.equatorial_radius, WGS84_EGM96.flattening)  # through the poles
        distance_wgs84_equatorial_2_3: Length = LLA.distance_between(lla_point_equator_2, lla_point_equator_3, WGS84_EGM96.equatorial_radius, WGS84_EGM96.flattening)

        assert distance_wgs84_equatorial_3_1 == distance_wgs84_equatorial_1_3
        assert distance_wgs84_equatorial_1_3 < distance_wgs84_equatorial_1_2 + distance_wgs84_equatorial_2_3

        distance_wgs84_1_north_pole: Length = LLA.distance_between(lla_point_equator_1, lla_north_pole, WGS84_EGM96.equatorial_radius, WGS84_EGM96.flattening)
        assert distance_wgs84_1_north_pole < distance_wgs84_equatorial_1_2  # flattened surface at poles
        assert distance_wgs84_1_north_pole < distance_spherical_equatorial_1_2
