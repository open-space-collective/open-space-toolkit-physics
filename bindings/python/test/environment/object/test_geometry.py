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

        accessed = Geometry(composite, Frame.GCRF()).access_composite()

        gc.collect()

        # Churn the heap, so that freed storage is likely to have been reused.
        ballast = [bytearray(4096) for _ in range(2000)]
        del ballast

        assert accessed.get_object_count() == 1
        assert accessed.access_object_at(0).is_sphere()
