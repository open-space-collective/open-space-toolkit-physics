################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/objects/celestial/test_moon.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

from ostk.physics.environment.objects.celestial_bodies import Moon

################################################################################################################################################################

class TestMoon:

    def test_default_success (self):

        moon = Moon.default()

        assert moon is not None
        assert isinstance(moon, Moon)

    def test_spherical_success (self):

        moon = Moon.spherical()

        assert moon is not None
        assert isinstance(moon, Moon)

################################################################################################################################################################
