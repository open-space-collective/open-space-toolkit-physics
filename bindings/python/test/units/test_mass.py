################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/units/test_mass.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.types import Real, String

import ostk.physics as physics

################################################################################################################################################################

Mass = physics.units.Mass
Unit = Mass.Unit

################################################################################################################################################################

def test_units_mass_unit ():

    enum_members = Unit.__members__

    list_keys = [
        'Undefined',
        'Kilogram',
        'Pound',
        'Tonne'
    ]

    list_values = [
        Unit.Undefined,
        Unit.Kilogram,
        Unit.Pound,
        Unit.Tonne
    ]

    assert enum_members is not None
    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values

################################################################################################################################################################

def test_units_mass_constructors ():

    mass: Mass = Mass(4.0, Unit.Kilogram)

    assert mass is not None
    assert isinstance(mass, Mass)
    assert mass.is_defined()

    mass: Mass = Mass(4.0, Unit.Pound)

    assert mass is not None
    assert isinstance(mass, Mass)
    assert mass.is_defined()

    mass: Mass = Mass(4.0, Unit.Tonne)

    assert mass is not None
    assert isinstance(mass, Mass)
    assert mass.is_defined()

################################################################################################################################################################

def test_units_mass_comparators ():

    mass_1: Mass = Mass(4.0, Unit.Kilogram)
    mass_2: Mass = Mass(3.5, Unit.Kilogram)

    assert mass_1 == mass_1
    assert mass_2 == mass_2
    assert mass_1 != mass_2

################################################################################################################################################################

def test_units_mass_is_defined ():

    mass: Mass = Mass(4.0, Unit.Kilogram)

    assert mass.is_defined() is True
    assert mass.undefined().is_defined() is False

################################################################################################################################################################

def test_units_mass_get_unit ():

    mass: Mass = Mass(4.0, Unit.Kilogram)
    unit: Unit = mass.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.Kilogram

    mass: Mass = Mass(4.0, Unit.Pound)
    unit: Unit = mass.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.Pound

    mass: Mass = Mass(4.0, Unit.Tonne)
    unit: Unit = mass.get_unit()

    assert unit is not None
    assert isinstance(unit, Unit)
    assert unit == Unit.Tonne

################################################################################################################################################################

def test_units_mass_in_unit ():

    mass: Mass = Mass(4.0, Unit.Kilogram)

    assert mass.in_unit(Unit.Kilogram) is not None
    assert mass.in_unit(Unit.Kilogram) == 4.0

    assert mass.in_unit(Unit.Pound) is not None

    assert mass.in_unit(Unit.Tonne) is not None

################################################################################################################################################################

def test_units_mass_in_kilograms ():

    mass: Mass = Mass(4000.0, Unit.Kilogram)

    assert mass.in_kilograms() is not None
    assert isinstance(mass.in_kilograms(), Real)
    assert mass.in_kilograms() == 4000.0

################################################################################################################################################################

def test_units_mass_to_string ():

    mass: Mass = Mass(4000.0, Unit.Kilogram)

    assert mass.to_string() is not None
    assert isinstance(mass.to_string(), String)
    assert mass.to_string() == '4000.0 [kg]'

################################################################################################################################################################

@pytest.mark.skip(reason = 'TBI')
def test_units_mass_parse ():
    pass

################################################################################################################################################################

def test_units_mass_string_from_unit ():

    string_0: Unit = Mass.string_from_unit(Unit.Kilogram)
    string_1: Unit = Mass.string_from_unit(Unit.Pound)
    string_2: Unit = Mass.string_from_unit(Unit.Tonne)

    assert string_0 is not None
    assert string_1 is not None
    assert string_2 is not None

    assert string_0 == 'Kilogram'
    assert string_1 == 'Pound'
    assert string_2 == 'Tonne'

################################################################################################################################################################

def test_units_mass_symbol_from_unit ():

    unit_0: Unit = Mass.symbol_from_unit(Unit.Kilogram)
    unit_1: Unit = Mass.symbol_from_unit(Unit.Pound)
    unit_2: Unit = Mass.symbol_from_unit(Unit.Tonne)

    assert unit_0 is not None
    assert unit_1 is not None
    assert unit_2 is not None

    assert unit_0 == 'kg'
    assert unit_1 == 'lb'
    assert unit_2 == 't'

################################################################################################################################################################
