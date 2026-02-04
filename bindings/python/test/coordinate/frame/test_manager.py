# Apache License 2.0

import pytest

from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion

from ostk.physics.time import Instant
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate import Transform
from ostk.physics.coordinate.frame import Manager
from ostk.physics.coordinate.frame.provider import Static


@pytest.fixture
def manager() -> Manager:
    manager = Manager.get()

    yield manager

    # Clean up any test frames created during tests
    for name in ["TestFrame", "TestFrame1", "TestFrame2", "TestFrame3"]:
        if Frame.exists(name):
            Frame.destruct(name)


@pytest.fixture
def static_provider() -> Static:
    return Static(
        Transform.passive(
            Instant.J2000(),
            [1.0, 0.0, 0.0],
            [0.0, 0.0, 0.0],
            Quaternion.unit(),
            [0.0, 0.0, 0.0],
        )
    )


class TestManager:
    def test_get_success(
        self,
    ):
        manager = Manager.get()
        assert manager is not None

    def test_get_singleton(
        self,
    ):
        manager1 = Manager.get()
        manager2 = Manager.get()
        assert manager1 is manager2

    def test_has_frame_with_name_success(
        self,
        manager: Manager,
    ):
        # GCRF always exists
        assert manager.has_frame_with_name("GCRF") is True

    def test_has_frame_with_name_not_found(
        self,
        manager: Manager,
    ):
        assert manager.has_frame_with_name("NonExistentFrame") is False

    def test_has_frame_with_name_custom_frame(
        self,
        manager: Manager,
        static_provider: Static,
    ):
        Frame.construct("TestFrame", True, Frame.GCRF(), static_provider)

        assert manager.has_frame_with_name("TestFrame") is True

        Frame.destruct("TestFrame")

        assert manager.has_frame_with_name("TestFrame") is False

    def test_access_frame_with_name_success(self, manager: Manager):
        gcrf = manager.access_frame_with_name("GCRF")

        assert gcrf is not None
        assert gcrf.get_name() == "GCRF"

    def test_access_frame_with_name_not_found(self, manager: Manager):
        frame = manager.access_frame_with_name("NonExistentFrame")

        assert frame is None

    def test_access_frame_with_name_custom_frame(
        self, manager: Manager, static_provider: Static
    ):
        Frame.construct("TestFrame", True, Frame.GCRF(), static_provider)

        accessed_frame = manager.access_frame_with_name("TestFrame")

        assert accessed_frame is not None
        assert accessed_frame.get_name() == "TestFrame"

    def test_get_all_frame_names_success(
        self,
        manager: Manager,
        static_provider: Static,
    ):
        Frame.construct("TestFrame1", True, Frame.GCRF(), static_provider)
        Frame.construct("TestFrame2", True, Frame.GCRF(), static_provider)

        frame_names = manager.get_all_frame_names()

        assert "TestFrame1" in frame_names
        assert "TestFrame2" in frame_names

    def test_remove_frame_with_name_success(
        self,
        manager: Manager,
        static_provider: Static,
    ):
        Frame.construct("TestFrame", True, Frame.GCRF(), static_provider)

        assert manager.has_frame_with_name("TestFrame") is True

        manager.remove_frame_with_name("TestFrame")

        assert manager.has_frame_with_name("TestFrame") is False

    def test_remove_frame_with_name_not_found(
        self,
        manager: Manager,
    ):
        with pytest.raises(Exception):
            manager.remove_frame_with_name("NonExistentFrame")

    def test_clear_all_frames_success(
        self,
        manager: Manager,
        static_provider: Static,
    ):
        Frame.construct("TestFrame1", True, Frame.GCRF(), static_provider)
        Frame.construct("TestFrame2", True, Frame.GCRF(), static_provider)

        assert manager.has_frame_with_name("TestFrame1") is True
        assert manager.has_frame_with_name("TestFrame2") is True

        manager.clear_all_frames()

        assert manager.has_frame_with_name("TestFrame1") is False
        assert manager.has_frame_with_name("TestFrame2") is False

    def test_access_cached_transform_not_found(
        self,
        manager: Manager,
    ):
        gcrf = Frame.GCRF()
        itrf = Frame.ITRF()
        instant = Instant.J2000()

        transform = manager.access_cached_transform(gcrf, itrf, instant)

        # Should return undefined transform when not cached
        assert transform.is_defined() is False

    def test_add_and_access_cached_transform_success(
        self,
        manager: Manager,
        static_provider: Static,
    ):
        frame1 = Frame.construct("TestFrame1", True, Frame.GCRF(), static_provider)
        frame2 = Frame.construct("TestFrame2", True, Frame.GCRF(), static_provider)
        instant = Instant.J2000()

        transform = Transform.passive(
            instant,
            [1.0, 2.0, 3.0],
            [0.0, 0.0, 0.0],
            Quaternion.unit(),
            [0.0, 0.0, 0.0],
        )

        manager.add_cached_transform(frame1, frame2, instant, transform)

        cached_forward = manager.access_cached_transform(frame1, frame2, instant)
        assert cached_forward.is_defined() is True

        # Reverse transform should also be cached (eager caching)
        cached_reverse = manager.access_cached_transform(frame2, frame1, instant)
        assert cached_reverse.is_defined() is True
