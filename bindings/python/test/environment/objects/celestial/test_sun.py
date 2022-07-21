################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/objects/celestial/test_sun.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.physics.environment.objects.celestial_bodies import Sun

################################################################################################################################################################

def test_sun_static_default_constructor ():

    sun: Sun = Sun.default()

    assert sun is not None
    assert isinstance(sun, Sun)

################################################################################################################################################################
