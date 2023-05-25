# Apache License 2.0

import pytest

from ostk.physics.time import Scale


def test_scale():
    assert Scale.UTC is not None
    assert Scale.TAI is not None
    assert Scale.GPST is not None
