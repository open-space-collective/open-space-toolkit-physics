# Apache License 2.0

import pytest

import numpy as np

from ostk.physics.time import Instant
from ostk.physics.time import DateTime
from ostk.physics.time import Scale
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate.frame.provider import iau
from ostk.physics.coordinate.frame.provider import Dynamic


@pytest.fixture
def epoch() -> Instant:
    return Instant.date_time(DateTime(2020, 1, 1, 0, 0, 0), Scale.UTC)


@pytest.fixture
def frame() -> Frame:
    return Frame.ITRF()


class TestFrame:
    def test_is_defined(self, frame: Frame):
        assert frame.is_defined() is True

    def test_is_quasi_inertial(self, frame: Frame):
        assert frame.is_quasi_inertial() is False

    def test_has_parent(self, frame: Frame):
        assert frame.has_parent() is True

    def test_access_parent(self, frame: Frame):
        assert frame.access_parent() is not None

    def test_access_ancestor(self, frame: Frame):
        assert frame.access_ancestor(ancestor_degree=1) is not None

    def test_access_provider(self, frame: Frame):
        assert frame.access_provider()

    def test_get_name(self, frame: Frame):
        assert frame.get_name() == "ITRF"

    def test_get_origin_in(self, epoch: Instant, frame: Frame):
        assert frame.get_origin_in(frame=frame, instant=epoch) is not None

    def test_get_velocity_in(self, epoch: Instant, frame: Frame):
        assert frame.get_velocity_in(frame=frame, instant=epoch) is not None

    def test_get_axes_in(self, epoch: Instant, frame: Frame):
        assert frame.get_axes_in(frame=frame, instant=epoch) is not None

    def test_get_transform_to(self, epoch: Instant, frame: Frame):
        assert frame.get_transform_to(frame=frame, instant=epoch) is not None

    def test_undefined(self):
        assert Frame.undefined() is not None

    def test_GCRF(self):
        assert Frame.GCRF() is not None

    def test_J2000(self):
        assert Frame.J2000(theory=iau.Theory.IAU_2006) is not None

    def test_MOD(self, epoch: Instant):
        assert Frame.MOD(epoch=epoch) is not None

    def test_TOD(self, epoch: Instant):
        assert Frame.TOD(epoch=epoch, theory=iau.Theory.IAU_2006) is not None

    def test_TEME(self):
        assert Frame.TEME() is not None

    def test_TEME_of_epoch(self, epoch: Instant):
        assert Frame.TEME_of_epoch(epoch=epoch) is not None

    def test_CIRF(self):
        assert Frame.CIRF() is not None

    def test_TIRF(self):
        assert Frame.TIRF() is not None

    def test_ITRF(self):
        assert Frame.ITRF() is not None

    def test_with_name(self, frame: Frame):
        assert Frame.with_name(name=frame.get_name()) is not None

    def test_exists(self, frame: Frame):
        assert Frame.exists(name=frame.get_name()) is True

    def test_construct_destruct(self, frame: Frame):
        custom_frame = Frame.construct(
            name="Custom Frame",
            is_quasi_inertial=True,
            parent_frame=frame,
            provider=Dynamic(lambda _: None),
        )

        assert custom_frame is not None

        Frame.destruct(custom_frame.get_name())

        assert Frame.exists(name="Custom Frame") is False
