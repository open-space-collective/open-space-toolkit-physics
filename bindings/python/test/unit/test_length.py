# Apache License 2.0

import pytest

from ostk.core.type import Real, String

import ostk.physics as physics

Length = physics.unit.Length
Unit = Length.Unit
Interval = physics.unit.Interval


def test_unit_length_unit():
    enum_members = Unit.__members__

    list_keys = [
        "Undefined",
        "Meter",
        "Foot",
        "TerrestrialMile",
        "NauticalMile",
        "AstronomicalUnit",
    ]

    list_values = [
        Unit.Undefined,
        Unit.Meter,
        Unit.Foot,
        Unit.TerrestrialMile,
        Unit.NauticalMile,
        Unit.AstronomicalUnit,
    ]

    assert enum_members is not None
    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values


def test_unit_length_constructors():
    length: Length = Length(4.0, Unit.Meter)

    assert length is not None
    assert isinstance(length, Length)
    assert length.is_defined()

    length: Length = Length(4.0, Unit.Foot)

    assert length is not None
    assert isinstance(length, Length)
    assert length.is_defined()

    length: Length = Length(4.0, Unit.TerrestrialMile)

    assert length is not None
    assert isinstance(length, Length)
    assert length.is_defined()

    length: Length = Length(4.0, Unit.NauticalMile)

    assert length is not None
    assert isinstance(length, Length)
    assert length.is_defined()

    length: Length = Length(4.0, Unit.AstronomicalUnit)

    assert length is not None
    assert isinstance(length, Length)
    assert length.is_defined()

    length: Length = Length(4.0, Unit.Undefined)

    assert length is not None
    assert isinstance(length, Length)
    assert length.is_defined() is False

    length: Length = Length(-1.0, Unit.Meter)

    assert length is not None
    assert isinstance(length, Length)
    assert length.is_defined() is True


def test_unit_length_comparators():
    length_1: Length = Length(4.0, Unit.Meter)
    length_2: Length = Length(3.5, Unit.Meter)

    assert length_1 == length_1
    assert length_2 == length_2
    assert length_1 != length_2

    assert length_1 <= length_1
    assert length_2 <= length_1
    assert length_2 <= length_2
    assert length_2 < length_1

    assert length_1 >= length_1
    assert length_1 >= length_2
    assert length_2 >= length_2
    assert length_1 > length_2


def test_unit_length_operators():
    length_1: Length = Length(4.0, Unit.Meter)
    length_2: Length = Length(3.5, Unit.Meter)

    sum_length: Length = length_1 + length_2
    diff_length: Length = length_1 - length_2
    mul_length: Length = length_1 * 2.0
    div_length: Length = length_1 / 2.0

    assert sum_length is not None
    assert isinstance(sum_length, Length)
    assert sum_length.is_defined()
    assert sum_length == Length(7.5, Unit.Meter)

    assert diff_length is not None
    assert isinstance(diff_length, Length)
    assert diff_length.is_defined()
    assert diff_length == Length(0.5, Unit.Meter)

    assert mul_length is not None
    assert isinstance(mul_length, Length)
    assert mul_length.is_defined()
    assert mul_length == Length(8.0, Unit.Meter)

    assert div_length is not None
    assert isinstance(div_length, Length)
    assert div_length.is_defined()
    assert div_length == Length(2.0, Unit.Meter)

    length_1 += length_2

    assert length_1 is not None
    assert isinstance(length_1, Length)
    assert length_1.is_defined()
    assert length_1 == Length(7.5, Unit.Meter)

    length_1 -= length_2

    assert length_1 is not None
    assert isinstance(length_1, Length)
    assert length_1.is_defined()
    assert length_1 == Length(4.0, Unit.Meter)

    length_1 *= 2.0

    assert length_1 is not None
    assert isinstance(length_1, Length)
    assert length_1.is_defined()
    assert length_1 == Length(8.0, Unit.Meter)

    length_1 /= 2.0

    assert length_1 is not None
    assert isinstance(length_1, Length)
    assert length_1.is_defined()
    assert length_1 == Length(4.0, Unit.Meter)


def test_unit_length_is_defined():
    length: Length = Length(4.0, Unit.Meter)

    assert length.is_defined() is True
    assert length.undefined().is_defined() is False


def test_unit_length_get_unit():
    length: Length = Length(4.0, Unit.Meter)
    unit: Unit = length.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.Meter

    length: Length = Length(4.0, Unit.Foot)
    unit: Unit = length.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.Foot

    length: Length = Length(4.0, Unit.TerrestrialMile)
    unit: Unit = length.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.TerrestrialMile

    length: Length = Length(4.0, Unit.NauticalMile)
    unit: Unit = length.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.NauticalMile

    length: Length = Length(4.0, Unit.AstronomicalUnit)
    unit: Unit = length.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.AstronomicalUnit


def test_unit_length_in_unit():
    length: Length = Length(4.0, Unit.Meter)

    assert length.in_unit(Unit.Meter) is not None
    assert length.in_unit(Unit.Meter) == 4.0

    assert length.in_unit(Unit.Foot) is not None
    # assert length.in_unit(Unit.Foot) == 4.0

    assert length.in_unit(Unit.TerrestrialMile) is not None
    # assert length.in_unit(Unit.TerrestrialMile) == 4.0

    assert length.in_unit(Unit.NauticalMile) is not None
    # assert length.in_unit(Unit.NauticalMile) == 4.0

    assert length.in_unit(Unit.AstronomicalUnit) is not None
    # assert length.in_unit(Unit.AstronomicalUnit) == 4.0


def test_unit_length_in_meters():
    length: Length = Length(4000.0, Unit.Meter)

    assert length.in_meters() is not None
    assert isinstance(length.in_meters(), Real)
    assert length.in_meters() == 4000.0


# def test_unit_length_millimeters ():

#     length: Length = Length(4000.0, Unit.Meter)

#     assert length.in_millimeters() is not None
#     assert isinstance(length.in_millimeters(), Real)
#     assert length.in_millimeters() == 4000000.0


def test_unit_length_kilometers():
    length: Length = Length(4000.0, Unit.Meter)

    assert length.in_kilometers() is not None
    assert isinstance(length.in_kilometers(), Real)
    assert length.in_kilometers() == 4.0


def test_unit_length_to_string():
    length: Length = Length(4000.0, Unit.Meter)

    assert length.to_string() is not None
    assert isinstance(length.to_string(), String)
    assert length.to_string() == "4000.0 [m]"


# def test_unit_length_parse ():


def test_unit_length_string_from_unit():
    string_0: Unit = Length.string_from_unit(Unit.Meter)
    string_1: Unit = Length.string_from_unit(Unit.Foot)
    string_2: Unit = Length.string_from_unit(Unit.TerrestrialMile)
    string_3: Unit = Length.string_from_unit(Unit.NauticalMile)
    string_4: Unit = Length.string_from_unit(Unit.AstronomicalUnit)

    assert string_0 is not None
    assert string_1 is not None
    assert string_2 is not None
    assert string_3 is not None
    assert string_4 is not None

    assert string_0 == "Meter"
    assert string_1 == "Foot"
    assert string_2 == "Terrestrial Mile"
    assert string_3 == "Nautical Mile"
    assert string_4 == "Astronomical Unit"


def test_unit_length_symbol_from_unit():
    unit_0: Unit = Length.symbol_from_unit(Unit.Meter)
    unit_1: Unit = Length.symbol_from_unit(Unit.Foot)
    unit_2: Unit = Length.symbol_from_unit(Unit.TerrestrialMile)
    unit_3: Unit = Length.symbol_from_unit(Unit.NauticalMile)
    unit_4: Unit = Length.symbol_from_unit(Unit.AstronomicalUnit)

    assert unit_0 is not None
    assert unit_1 is not None
    assert unit_2 is not None
    assert unit_3 is not None
    assert unit_4 is not None

    assert unit_0 == "m"
    assert unit_1 == "ft"
    assert unit_2 == "mi"
    assert unit_3 == "nmi"
    assert unit_4 == "AU"
