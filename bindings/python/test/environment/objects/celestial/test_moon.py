################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/objects/celestial/test_moon.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.physics.environment.objects.celestial_bodies import Moon

################################################################################################################################################################

def test_moon_static_default_constructor ():

    moon: Moon = Moon.default()

    assert moon is not None
    assert isinstance(moon, Moon)

################################################################################################################################################################
