# Apache License 2.0

import math

import pytest

from ostk.mathematics.geometry import Angle as AngleMathematics
from ostk.physics.unit import Angle as AnglePhysics

Unit = AnglePhysics.Unit


def test_angle_conversion():
    angle_physics: AnglePhysics = AnglePhysics(30.0, AnglePhysics.Unit.Degree)
    angle_mathematics: AngleMathematics = AngleMathematics(
        30.0, AngleMathematics.Unit.Degree
    )

    assert angle_physics is not None
    assert angle_mathematics is not None
    assert angle_physics == angle_mathematics


def test_angle_unit():
    enum_members = Unit.__members__

    list_keys = ["Undefined", "Radian", "Degree", "Arcminute", "Arcsecond", "Revolution"]

    list_values = [
        Unit.Undefined,
        Unit.Radian,
        Unit.Degree,
        Unit.Arcminute,
        Unit.Arcsecond,
        Unit.Revolution,
    ]

    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values


def test_angle_default_constructor():
    # Default constructor with Degree Unit
    angle: AnglePhysics = AnglePhysics(12.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_degrees() == 12.34

    angle: AnglePhysics = AnglePhysics(-12.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_degrees() == -12.34

    angle: AnglePhysics = AnglePhysics(365.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_degrees() == 365.34

    angle: AnglePhysics = AnglePhysics(-4000.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_degrees() == -4000.34

    # Default constructor with Radian Unit
    angle: AnglePhysics = AnglePhysics(3.4, Unit.Radian)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_radians() == 3.4

    # Default constructor with Arcminute Unit
    angle: AnglePhysics = AnglePhysics(3600.0, Unit.Arcminute)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_arcminutes() == 3600.0

    # Default constructor with Arcsecond Unit
    angle: AnglePhysics = AnglePhysics(3600.0, Unit.Arcsecond)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_arcseconds() == 3600.0

    # Default constructor with Revolution Unit
    angle: AnglePhysics = AnglePhysics(18.0, Unit.Revolution)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.in_revolutions() == 18.0

    # Invalid construction
    with pytest.raises(TypeError):
        angle: AnglePhysics = AnglePhysics(45, Unit.Degree)


def test_angle_undefined_constructor():
    angle: AnglePhysics = AnglePhysics.undefined()

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined() is False


def test_angle_zero_constructor():
    angle: AnglePhysics = AnglePhysics.zero()

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined() is True
    assert angle.get_unit() == Unit.Radian
    assert angle.is_zero() is True
    assert angle.in_radians() == 0.0
    assert angle.in_degrees() == 0.0
    assert angle.in_arcminutes() == 0.0
    assert angle.in_arcseconds() == 0.0
    assert angle.in_revolutions() == 0.0


def test_angle_pi_constructors():
    angle: AnglePhysics = AnglePhysics.half_pi()

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == math.pi / 2

    angle: AnglePhysics = AnglePhysics.pi()

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == math.pi

    angle: AnglePhysics = AnglePhysics.two_pi()

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == 2 * math.pi


def test_angle_unit_constructors():
    # Radian
    angle: AnglePhysics = AnglePhysics.radians(3.4)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == 3.4

    # Degree
    angle: AnglePhysics = AnglePhysics.degrees(-45.0)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Degree
    assert angle.in_degrees() == -45.0

    # Arcminutes
    angle: AnglePhysics = AnglePhysics.arcminutes(60.5)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Arcminute
    assert angle.in_arcminutes() == 60.5

    # Arcseconds
    angle: AnglePhysics = AnglePhysics.arcseconds(60.5)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Arcsecond
    assert angle.in_arcseconds() == 60.5

    # Revolutions
    angle: AnglePhysics = AnglePhysics.revolutions(3.9)

    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Revolution
    assert angle.in_revolutions() == 3.9


def test_angle_unit_conversion():
    angle: AnglePhysics = AnglePhysics(60.0, Unit.Degree)

    assert angle.in_degrees() == 60.0
    assert angle.in_radians() == (math.pi * 60.0 / 180.0)
    assert angle.in_arcminutes() == 60.0 * 60.0
    assert (angle.in_arcseconds() - 60.0 * 3600.0) <= 1e-10


def test_angle_comparators():
    angle_deg: AnglePhysics = AnglePhysics(60.0, Unit.Degree)
    angle_rad: AnglePhysics = AnglePhysics(60.0 * math.pi / 180.0, Unit.Radian)

    assert angle_deg == angle_deg
    assert angle_rad == angle_rad
    assert angle_deg == angle_rad
    assert angle_deg != AnglePhysics(59.0, Unit.Degree)


def test_angle_operators():
    angle: AnglePhysics = AnglePhysics(30.0, Unit.Degree)
    half_angle: AnglePhysics = angle / 2.0
    double_angle: AnglePhysics = angle * 2.0
    sum_angle: AnglePhysics = angle + angle
    diff_angle: AnglePhysics = angle - angle
    positive_angle: AnglePhysics = +angle
    negative_angle: AnglePhysics = -angle

    assert half_angle is not None
    assert isinstance(half_angle, AnglePhysics)
    assert double_angle is not None
    assert isinstance(double_angle, AnglePhysics)
    assert sum_angle is not None
    assert isinstance(sum_angle, AnglePhysics)
    assert diff_angle is not None
    assert isinstance(diff_angle, AnglePhysics)
    assert positive_angle is not None
    assert isinstance(positive_angle, AnglePhysics)
    assert negative_angle is not None
    assert isinstance(negative_angle, AnglePhysics)

    assert half_angle.in_degrees() == 15.0
    assert double_angle.in_degrees() == 60.0
    assert sum_angle.in_degrees() == 60.0
    assert diff_angle.in_degrees() == 0.0
    assert diff_angle.is_zero()
    assert positive_angle.in_degrees() == +30.0
    assert negative_angle.in_degrees() == -30.0

    angle_deg: AnglePhysics = AnglePhysics(90.0, Unit.Degree)
    angle_rad: AnglePhysics = AnglePhysics(math.pi / 2, Unit.Radian)

    sum_angle: AnglePhysics = angle_rad + angle_deg
    assert sum_angle is not None
    assert isinstance(sum_angle, AnglePhysics)
    assert (sum_angle.in_degrees() - 180.0) <= 1e-10

    angle: AnglePhysics = AnglePhysics(90.0, Unit.Degree)

    angle *= 3.0
    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.get_unit() == Unit.Degree
    assert angle.in_degrees() == 270.0

    angle /= 3.0
    assert angle is not None
    assert isinstance(angle, AnglePhysics)
    assert angle.get_unit() == Unit.Degree
    assert angle.in_degrees() == 90.0


def test_angle_string_from_unit():
    assert AnglePhysics.string_from_unit(Unit.Degree) == "Degree"
    assert AnglePhysics.string_from_unit(Unit.Radian) == "Radian"
    assert AnglePhysics.string_from_unit(Unit.Arcminute) == "Arcminute"
    assert AnglePhysics.string_from_unit(Unit.Arcsecond) == "Arcsecond"
    assert AnglePhysics.string_from_unit(Unit.Revolution) == "Revolution"


def test_angle_string_symbol_from_unit():
    assert AnglePhysics.symbol_from_unit(Unit.Degree) == "deg"
    assert AnglePhysics.symbol_from_unit(Unit.Radian) == "rad"
    assert AnglePhysics.symbol_from_unit(Unit.Arcminute) == "amin"
    assert AnglePhysics.symbol_from_unit(Unit.Arcsecond) == "asec"
    assert AnglePhysics.symbol_from_unit(Unit.Revolution) == "rev"


def test_angle_in_radians_reduction():
    angle: AnglePhysics = AnglePhysics(math.pi * 3 / 2, Unit.Radian)
    assert angle.in_radians(lower_bound=-math.pi, upper_bound=math.pi) == -math.pi / 2

    angle: AnglePhysics = AnglePhysics(math.pi / 2, Unit.Radian)
    assert angle.in_radians(lower_bound=-math.pi, upper_bound=math.pi) == math.pi / 2

    angle: AnglePhysics = AnglePhysics(-math.pi, Unit.Radian)
    assert angle.in_radians(-math.pi, math.pi) == -math.pi

    angle: AnglePhysics = AnglePhysics(math.pi, Unit.Radian)
    assert angle.in_radians(-math.pi, math.pi) == -math.pi


def test_angle_in_degrees_reduction():
    angle: AnglePhysics = AnglePhysics(359.0, Unit.Degree)
    assert angle.in_degrees(lower_bound=-180.0, upper_bound=180.0) == -1.0

    angle: AnglePhysics = AnglePhysics(1.0, Unit.Degree)
    assert angle.in_degrees(lower_bound=-180.0, upper_bound=180.0) == 1.0

    angle: AnglePhysics = AnglePhysics(-180.0, Unit.Degree)
    assert angle.in_degrees(-180.0, 180.0) == -180.0

    angle: AnglePhysics = AnglePhysics(180.0, Unit.Degree)
    assert angle.in_degrees(-180.0, 180.0) == -180.0


def test_angle_in_arcminutes_reduction():
    angle: AnglePhysics = AnglePhysics(359.0 * 60.0, Unit.Arcminute)
    assert (
        angle.in_arcminutes(lower_bound=-180.0 * 60.0, upper_bound=180.0 * 60.0) == -60.0
    )

    angle: AnglePhysics = AnglePhysics(60.0, Unit.Arcminute)
    assert (
        angle.in_arcminutes(lower_bound=-180.0 * 60.0, upper_bound=180.0 * 60.0) == 60.0
    )

    angle: AnglePhysics = AnglePhysics(-180.0 * 60.0, Unit.Arcminute)
    assert angle.in_arcminutes(-180.0 * 60.0, 180.0 * 60.0) == -180.0 * 60.0

    angle: AnglePhysics = AnglePhysics(180.0 * 60.0, Unit.Arcminute)
    assert angle.in_arcminutes(-180.0 * 60.0, 180.0 * 60.0) == -180.0 * 60.0


def test_angle_in_arcseconds_reduction():
    angle: AnglePhysics = AnglePhysics(359.0 * 3600.0, Unit.Arcsecond)
    assert (
        angle.in_arcseconds(lower_bound=-180.0 * 3600.0, upper_bound=180.0 * 3600.0)
        == -3600.0
    )

    angle: AnglePhysics = AnglePhysics(3600.0, Unit.Arcsecond)
    assert (
        angle.in_arcseconds(lower_bound=-180.0 * 3600.0, upper_bound=180.0 * 3600.0)
        == 3600.0
    )

    angle: AnglePhysics = AnglePhysics(-180 * 3600.0, Unit.Arcsecond)
    assert angle.in_arcseconds(-180.0 * 3600.0, 180.0 * 3600.0) == -180.0 * 3600.0

    angle: AnglePhysics = AnglePhysics(180.0 * 3600.0, Unit.Arcsecond)
    assert angle.in_arcseconds(-180.0 * 3600.0, 180.0 * 3600.0) == -180.0 * 3600.0


def test_parse():
    angle: AnglePhysics = AnglePhysics.parse(string="3.14 [rad]")
    assert angle == AnglePhysics(3.14, Unit.Radian)

    angle: AnglePhysics = AnglePhysics.parse(string="60 [deg]")
    assert angle == AnglePhysics(60.0, Unit.Degree)

    angle: AnglePhysics = AnglePhysics.parse("60 [amin]")
    assert angle == AnglePhysics(60.0, Unit.Arcminute)

    angle: AnglePhysics = AnglePhysics.parse("3600 [asec]")
    assert angle == AnglePhysics(3600.0, Unit.Arcsecond)


def test_to_string():
    angle: AnglePhysics = AnglePhysics(3.141592653589793, Unit.Radian)
    assert angle.to_string() == "3.1415926535897931 [rad]"
    assert angle.to_string(precision=1) == "3.1 [rad]"
