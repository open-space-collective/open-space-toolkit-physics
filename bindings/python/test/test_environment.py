################################################################################################################################################################

# @project        Library ▸ Physics
# @file           bindings/python/test/test_environment.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from Library.Physics.Time import Scale
from Library.Physics.Time import Instant
from Library.Physics.Time import DateTime
from Library.Physics import Environment

################################################################################################################################################################

def test_environment_constructors ():

    instant = Instant.DateTime(DateTime(2019, 1, 1, 0, 0, 0), Scale.UTC)
    objects = []

    assert Environment(instant, objects) is not None

################################################################################################################################################################

def test_environment_undefined ():

    assert Environment.Undefined() is not None

################################################################################################################################################################

def test_environment_default ():

    assert Environment.Default() is not None

################################################################################################################################################################

def test_environment_isDefined ():

    environment = Environment.Default()

    assert environment.isDefined() is not None

################################################################################################################################################################

def test_environment_hasObjectWithName ():

    environment = Environment.Default()

    assert environment.hasObjectWithName('Earth') is not None

################################################################################################################################################################

@pytest.mark.skip
def test_environment_intersects ():

    environment = Environment.Default()

    assert environment.intersects() is not None

################################################################################################################################################################

@pytest.mark.skip
def test_environment_accessObjects ():

    environment = Environment.Default()

    assert environment.accessObjects() is not None

################################################################################################################################################################

def test_environment_accessObjectWithName ():

    environment = Environment.Default()

    assert environment.accessObjectWithName('Earth') is not None

################################################################################################################################################################

def test_environment_accessCelestialObjectWithName ():

    environment = Environment.Default()

    assert environment.accessCelestialObjectWithName('Earth') is not None

################################################################################################################################################################

def test_environment_getInstant ():

    environment = Environment.Default()

    assert environment.getInstant() is not None

################################################################################################################################################################

def test_environment_getObjectNames ():

    environment = Environment.Default()

    assert environment.getObjectNames() is not None

################################################################################################################################################################

def test_environment_setInstant ():

    environment = Environment.Default()

    environment.setInstant(Instant.DateTime(DateTime(2019, 1, 1, 0, 0, 0), Scale.UTC))

################################################################################################################################################################
