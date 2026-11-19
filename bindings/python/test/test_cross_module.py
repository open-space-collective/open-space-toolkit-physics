# Apache License 2.0

"""Types bound by ostk.core, ostk.io and ostk.mathematics crossing into and out of ostk.physics.

All the extension modules must use the same nanobind version and ABI for these to resolve.
"""

import sys

import numpy as np

import ostk.core as core
from ostk.core.filesystem import Directory
from ostk.core.filesystem import File
from ostk.core.filesystem import Path
from ostk.core.type import String

import ostk.io as io
from ostk.io import URL

import ostk.mathematics as mathematics
from ostk.mathematics.geometry import Angle as MathAngle
from ostk.mathematics.geometry.d3.object import Composite
from ostk.mathematics.geometry.d3.object import Point
from ostk.mathematics.geometry.d3.object import Sphere
from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion
from ostk.mathematics.geometry.d3.transformation.rotation import RotationVector
from ostk.mathematics.object import RealInterval

import ostk.physics as physics
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate import Position
from ostk.physics.coordinate.spherical import LLA
from ostk.physics.data import Manager as DataManager
from ostk.physics.environment.ephemeris.spice import Kernel
from ostk.physics.environment.object import Geometry
from ostk.physics.time import Instant
from ostk.physics.time import Interval
from ostk.physics.unit import Angle
from ostk.physics.unit import Length


def test_upstream_modules_are_imported_by_physics():
    # ostk/physics/__init__.py imports ostk.io and ostk.mathematics (which import ostk.core) first,
    # so their types are registered before ostk.physics uses them.
    assert "ostk.core" in sys.modules
    assert "ostk.io" in sys.modules
    assert "ostk.mathematics" in sys.modules
    assert physics.time.Instant is Instant


def test_core_string_argument_and_return_value():
    frame = Frame.with_name(String("GCRF"))

    name = frame.get_name()

    assert type(name) is String
    assert name == String("GCRF")
    assert String("Frame: ") + name == String("Frame: GCRF")


def test_str_argument_converts_implicitly_to_core_string():
    # The str -> String implicit conversion is registered by ostk.core, and applies in ostk.physics.
    assert Frame.exists("GCRF")
    assert Frame.with_name("GCRF") == Frame.GCRF()


def test_core_filesystem_arguments_and_return_values():
    kernel = Kernel.file(File.path(Path.parse("/tmp/kernel.bsp")))

    assert kernel.get_type() == Kernel.Type.SPK

    file = kernel.get_file()

    assert type(file) is File
    assert file.get_path() == Path.parse("/tmp/kernel.bsp")

    local_repository = DataManager.get().get_local_repository()

    assert type(local_repository) is Directory


def test_io_url_argument_and_return_value():
    manager = DataManager.get()

    remote_url = manager.get_remote_url()

    assert type(remote_url) is URL

    try:
        manager.set_remote_url(URL.parse("https://example.com/data"))

        assert manager.get_remote_url() == URL.parse("https://example.com/data")
    finally:
        manager.set_remote_url(remote_url)


def test_mathematics_composite_argument_and_return_value():
    sphere = Sphere(Point(0.0, 0.0, 0.0), 1.0)

    geometry = Geometry(sphere, Frame.GCRF())

    composite = geometry.get_composite()

    assert type(composite) is Composite
    assert composite.get_object_count() == 1
    assert composite.get_object_at(0).is_sphere()


def test_mathematics_quaternion_return_value():
    transform = Frame.GCRF().get_transform_to(Frame.GCRF(), Instant.J2000())

    orientation = transform.get_orientation()

    assert type(orientation) is Quaternion
    assert orientation == Quaternion.unit()


def test_vector_list_argument_and_ndarray_return_value():
    position = Position.meters([7000e3, 0.0, 0.0], Frame.GCRF())

    coordinates = position.get_coordinates()

    assert isinstance(coordinates, np.ndarray)
    assert coordinates.dtype == np.float64
    assert coordinates.shape == (3,)
    assert np.array_equal(coordinates, [7000e3, 0.0, 0.0])


def test_physics_angle_and_mathematics_angle_convert_both_ways():
    physics_angle = Angle.degrees(90.0)

    # Constructor that ostk.physics adds to ostk.mathematics' Angle
    math_angle = MathAngle(physics_angle)

    assert type(math_angle) is MathAngle
    assert math_angle.in_degrees() == 90.0

    # physics Angle -> mathematics Angle (implicit conversion)
    rotation_vector = RotationVector([0.0, 0.0, 1.0], physics_angle)

    assert rotation_vector.get_angle().in_degrees() == 90.0

    # mathematics Angle -> physics Angle (implicit conversion)
    lla = LLA(MathAngle.degrees(10.0), MathAngle.degrees(20.0), Length.meters(30.0))

    assert lla.get_latitude().in_degrees() == 10.0
    assert lla.get_longitude().in_degrees() == 20.0


def test_interval_type_is_the_mathematics_interval_type():
    # Interval.Type is mathematics' IntervalBase::Type (bound once, by ostk.mathematics).
    assert Interval.Type is RealInterval.Type

    interval = Interval(Instant.J2000(), Instant.J2000(), RealInterval.Type.Closed)

    assert interval.get_type() == Interval.Type.Closed
