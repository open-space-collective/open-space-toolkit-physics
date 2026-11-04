# Apache License 2.0

"""Classes that define __eq__ without __hash__ are unhashable, as with the former pybind11 bindings."""

import pytest

from ostk.physics.coordinate import Frame
from ostk.physics.coordinate import Position
from ostk.physics.time import Date
from ostk.physics.time import Duration
from ostk.physics.time import Instant
from ostk.physics.time import Interval
from ostk.physics.time import Time
from ostk.physics.unit import Angle
from ostk.physics.unit import Length


@pytest.mark.parametrize(
    "value",
    [
        Frame.GCRF(),
        Position.meters([1.0, 2.0, 3.0], Frame.GCRF()),
        Date(2020, 1, 1),
        Time(0, 0, 0),
        Angle.degrees(1.0),
        Length.meters(1.0),
    ],
    ids=["Frame", "Position", "Date", "Time", "Angle", "Length"],
)
def test_value_types_are_unhashable(value):
    assert type(value).__hash__ is None

    with pytest.raises(TypeError):
        hash(value)


def test_types_with_a_hash_are_hashable():
    assert hash(Instant.J2000()) == hash(Instant.J2000())
    assert hash(Duration.seconds(1.0)) == hash(Duration.seconds(1.0))
    assert hash(Interval.closed(Instant.J2000(), Instant.J2000())) == hash(
        Interval.closed(Instant.J2000(), Instant.J2000())
    )
