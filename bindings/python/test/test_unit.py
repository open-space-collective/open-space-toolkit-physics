# Apache License 2.0

from ostk.physics import Unit
from ostk.physics.unit import Length


class TestUnit:
    def test_none(self):
        unit: Unit = Unit.none()

        assert unit.is_none()
        assert unit.get_type() == Unit.Type.None_
        assert unit.to_string() == "-"

    def test_length(self):
        unit: Unit = Unit.length(Length.Unit.Meter)

        assert not unit.is_none()
        assert unit.get_type() == Unit.Type.Length
        assert unit.to_string() == "m"
        assert unit == Unit.length(Length.Unit.Meter)
        assert unit != Unit.none()

    def test_has_no_undefined(self):
        assert not hasattr(Unit, "undefined")
        assert not hasattr(Unit, "is_defined")
        assert not hasattr(Unit.Type, "Undefined")
