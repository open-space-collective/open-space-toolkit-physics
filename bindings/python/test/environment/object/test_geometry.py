# Apache License 2.0

import gc

import pytest

from ostk.mathematics.geometry.d3.object import Composite
from ostk.mathematics.geometry.d3.object import Point
from ostk.mathematics.geometry.d3.object import Sphere

from ostk.physics.coordinate import Frame
from ostk.physics.environment.object import Geometry


@pytest.fixture
def composite() -> Composite:
    return Composite(Sphere(Point(0.0, 0.0, 0.0), 1.0))


@pytest.fixture
def geometry(composite: Composite) -> Geometry:
    return Geometry(composite, Frame.GCRF())


class TestGeometry:
    def test_access_composite_success(self, geometry: Geometry, composite: Composite):
        assert geometry.access_composite() == composite

    def test_access_composite_outlives_temporary_parent_success(
        self,
        composite: Composite,
    ):
        """`access_composite` must keep its parent geometry alive.

        Several accessors hand back a geometry *by value*, so binding
        `access_composite` with a bare `return_value_policy::reference` leaves the
        returned composite pointing into an object Python is free to collect as soon as
        the expression ends. A regression shows up here as garbage data or a segfault.
        """

        accessed = Geometry(composite, Frame.GCRF()).access_composite()

        gc.collect()

        # Churn the heap, so that freed storage is likely to have been reused.
        ballast = [bytearray(4096) for _ in range(2000)]
        del ballast

        assert accessed.get_object_count() == 1
        assert accessed.access_object_at(0).is_sphere()
