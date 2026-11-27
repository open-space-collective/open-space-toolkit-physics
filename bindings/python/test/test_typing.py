# Apache License 2.0

"""Calls that the bindings accept, and that the generated type stubs must accept too.

The bindings convert some Python values implicitly, for example a `datetime.datetime` where
a `DateTime` is declared, or a list of floats where a vector is declared. Each test makes
such a call. `test_stubs_accept_these_calls` type-checks this file with mypy against the
generated stubs, so a stub that rejects one of these calls fails.
"""

from datetime import datetime
from pathlib import Path

import numpy as np
import pytest

import ostk.physics
from ostk.mathematics.geometry import Angle as MathematicsAngle
from ostk.physics.coordinate import Frame
from ostk.physics.coordinate import Position
from ostk.physics.time import DateTime
from ostk.physics.time import Instant
from ostk.physics.time import Scale
from ostk.physics.unit import Angle


def test_date_time_parameter_accepts_datetime() -> None:
    instant: Instant = Instant.date_time(datetime(2024, 1, 2, 3, 4, 5), Scale.UTC)

    assert instant == Instant.date_time(DateTime(2024, 1, 2, 3, 4, 5), Scale.UTC)


def test_date_time_return_value_is_datetime() -> None:
    instant = Instant.date_time(datetime(2024, 1, 2, 3, 4, 5), Scale.UTC)

    date_time: datetime = instant.get_date_time(Scale.UTC)

    assert date_time.year == 2024
    assert DateTime.J2000().year == 2000


def test_vector_parameter_accepts_list() -> None:
    position: Position = Position.meters([1.0, 2.0, 3.0], Frame.GCRF())
    coordinates: np.ndarray = position.get_coordinates()

    assert coordinates.tolist() == [1.0, 2.0, 3.0]


def test_string_parameter_accepts_str() -> None:
    gcrf: Frame = Frame.GCRF()

    assert Frame.with_name("GCRF") == gcrf
    assert isinstance(Instant.parse("2024-01-02 03:04:05.000", Scale.UTC), Instant)


def test_angle_parameter_accepts_mathematics_angle() -> None:
    angle: Angle = Angle.between(
        MathematicsAngle.degrees(10.0), MathematicsAngle.degrees(30.0)
    )

    assert isinstance(angle, Angle)


def test_stubs_accept_these_calls(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    mypy_api = pytest.importorskip("mypy.api")

    # In the CMake build tree, the package is a directory next to `test`, not an installed
    # distribution: mypy only finds it through MYPYPATH.
    package_root: Path = Path(ostk.physics.__file__).resolve().parents[2]

    if package_root.name != "site-packages":
        monkeypatch.setenv("MYPYPATH", str(package_root))

    # Report the errors in the calls of this file only: the stubs themselves are not checked,
    # as for an installed package.
    config: Path = tmp_path / "mypy.ini"
    config.write_text("[mypy]\n[mypy-ostk.*]\nignore_errors = True\n")

    stdout, stderr, exit_status = mypy_api.run(
        [
            __file__,
            "--config-file",
            str(config),
            "--cache-dir",
            str(tmp_path / "mypy_cache"),
        ]
    )

    assert exit_status == 0, stdout + stderr
