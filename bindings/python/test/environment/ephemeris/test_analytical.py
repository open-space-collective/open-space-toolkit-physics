# Apache License 2.0

import pytest

from ostk.physics.coordinate import Frame
from ostk.physics.environment.ephemeris import Analytical


@pytest.fixture
def analytical():
    return Analytical(Frame.ITRF())


class TestAnalytical:
    def test_constructor_success(self, analytical: Analytical):
        assert analytical is not None

    def test_get_frame_success(self, analytical: Analytical):
        accessed_frame = analytical.get_frame()

        assert accessed_frame is not None
