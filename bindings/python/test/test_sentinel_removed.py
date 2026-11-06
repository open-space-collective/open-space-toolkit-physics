# Apache License 2.0

import pytest

import ostk.physics as physics

# `None` replaces the "undefined" value: the Undefined() / isDefined() sentinel pattern is gone from these classes.

SENTINEL_FREE_CLASSES = [
    physics.unit.Length,
    physics.unit.Interval,
    physics.unit.Mass,
    physics.unit.ElectricCurrent,
    physics.unit.Time,
    physics.unit.Angle,
    physics.unit.Derived,
    physics.unit.Derived.Unit,
    physics.time.Instant,
    physics.time.Interval,
    physics.time.Duration,
    physics.coordinate.Axes,
    physics.coordinate.Position,
    physics.coordinate.Velocity,
    physics.coordinate.Transform,
    physics.coordinate.Frame,
    physics.coordinate.spherical.LLA,
    physics.coordinate.spherical.AER,
    physics.coordinate.frame.provider.CIRF,
    physics.coordinate.frame.provider.iers.BulletinA,
    physics.coordinate.frame.provider.iers.Finals2000A,
    physics.data.Scalar,
    physics.data.Vector,
    physics.data.Direction,
    physics.data.Manifest,
    physics.Environment,
    physics.environment.object.Geometry,
    physics.environment.object.Celestial,
    physics.environment.ephemeris.Analytical,
    physics.environment.ephemeris.SPICE,
    physics.environment.ephemeris.spice.Kernel,
    physics.environment.gravitational.Model,
    physics.environment.gravitational.Earth,
    physics.environment.gravitational.Sun,
    physics.environment.gravitational.Moon,
    physics.environment.magnetic.Dipole,
    physics.environment.magnetic.Earth,
    physics.environment.atmospheric.Earth,
    physics.environment.atmospheric.earth.Exponential,
    physics.environment.atmospheric.earth.NRLMSISE00,
    physics.environment.atmospheric.earth.CSSISpaceWeather,
]

SENTINEL_FREE_ENUMS = [
    physics.Unit.Type,
    physics.time.Scale,
    physics.time.Interval.Type,
    physics.unit.Length.Unit,
    physics.unit.Mass.Unit,
    physics.unit.ElectricCurrent.Unit,
    physics.unit.Time.Unit,
    physics.unit.Angle.Unit,
    physics.coordinate.Transform.Type,
    physics.coordinate.Velocity.Unit,
    physics.environment.ephemeris.spice.Kernel.Type,
    physics.environment.object.Celestial.CelestialType,
    physics.environment.gravitational.Earth.Type,
    physics.environment.gravitational.Sun.Type,
    physics.environment.gravitational.Moon.Type,
    physics.environment.magnetic.Earth.Type,
    physics.environment.atmospheric.Earth.Type,
    physics.environment.atmospheric.Earth.InputDataType,
]


@pytest.mark.parametrize("cls", SENTINEL_FREE_CLASSES, ids=lambda cls: cls.__qualname__)
def test_sentinel_api_removed(cls):
    assert not hasattr(cls, "undefined")
    assert not hasattr(cls, "is_defined")


@pytest.mark.parametrize("enum", SENTINEL_FREE_ENUMS, ids=lambda enum: enum.__qualname__)
def test_undefined_enumerator_removed(enum):
    assert "Undefined" not in enum.__members__
    assert not hasattr(enum, "Undefined")


def test_kernel_type_from_file_extension_returns_none_for_unknown_extension():
    Kernel = physics.environment.ephemeris.spice.Kernel

    assert Kernel.type_from_file_extension("bsp") == Kernel.Type.SPK
    assert Kernel.type_from_file_extension("unknown") is None
