################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/environment/objects/celestial/test_earth.py
# @author         Antoine Paletta <antoine.paletta@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.physics.environment.objects.celestial_bodies import Earth

from ostk.physics.environment.objects.celestial_bodies.earth.models import EGM2008
from ostk.physics.environment.objects.celestial_bodies.earth.models import EGM96
from ostk.physics.environment.objects.celestial_bodies.earth.models import WGS84_EGM96
from ostk.physics.environment.objects.celestial_bodies.earth.models import EGM84
from ostk.physics.environment.objects.celestial_bodies.earth.models import WGS84
from ostk.physics.environment.objects.celestial_bodies.earth.models import Spherical

################################################################################################################################################################

def test_earth_static_default_constructor ():

    earth: Earth = Earth.default()

    assert earth is not None
    assert isinstance(earth, Earth)

################################################################################################################################################################

def test_earth_static_EGM2008_constructor ():

    earth: Earth = Earth.EGM2008()

    assert earth is not None
    assert isinstance(earth, Earth)

    earth_custom: Earth = Earth.EGM2008(2190, 2160)

    assert earth_custom is not None
    assert isinstance(earth_custom, Earth)

################################################################################################################################################################

def test_earth_static_EGM96_constructor ():

    earth: Earth = Earth.EGM96()

    assert earth is not None
    assert isinstance(earth, Earth)

    earth_custom: Earth = Earth.EGM96(360, 360)

    assert earth_custom is not None
    assert isinstance(earth_custom, Earth)

################################################################################################################################################################

def test_earth_static_EGM84_constructor ():

    earth: Earth = Earth.EGM84()

    assert earth is not None
    assert isinstance(earth, Earth)

    earth_custom: Earth = Earth.EGM84(180, 180)

    assert earth_custom is not None
    assert isinstance(earth_custom, Earth)

################################################################################################################################################################

def test_earth_static_WGS84_EGM96_constructor ():

    earth: Earth = Earth.WGS84_EGM96()

    assert earth is not None
    assert isinstance(earth, Earth)

    earth_custom: Earth = Earth.WGS84_EGM96(180, 180)

    assert earth_custom is not None
    assert isinstance(earth_custom, Earth)

################################################################################################################################################################

def test_earth_static_WGS84_constructor ():

    earth: Earth = Earth.WGS84()

    assert earth is not None
    assert isinstance(earth, Earth)

    earth_custom: Earth = Earth.WGS84(20, 0)

    assert earth is not None
    assert isinstance(earth_custom, Earth)

################################################################################################################################################################

def test_earth_static_spherical_constructor ():

    earth: Earth = Earth.spherical()

    assert earth is not None
    assert isinstance(earth, Earth)

################################################################################################################################################################

def test_earth_static_properties_EGM2008 ():

    assert EGM2008.gravitational_parameter is not None
    assert EGM2008.equatorial_radius is not None
    assert EGM2008.flattening is not None
    assert EGM2008.C20 is not None
    assert EGM2008.C40 is not None
    assert EGM2008.J2 is not None
    assert EGM2008.J4 is not None

    assert EGM2008.gravitational_parameter == Earth.gravitational_parameter
    assert EGM2008.equatorial_radius == Earth.equatorial_radius
    assert EGM2008.flattening == Earth.flattening
    assert EGM2008.C20 == Earth.C20
    assert EGM2008.C40 == Earth.C40
    assert EGM2008.J2 == Earth.J2
    assert EGM2008.J4 == Earth.J4

################################################################################################################################################################

def test_earth_static_properties_EGM96 ():

    assert EGM96.gravitational_parameter is not None
    assert EGM96.equatorial_radius is not None
    assert EGM96.flattening is not None
    assert EGM96.C20 is not None
    assert EGM96.C40 is not None
    assert EGM96.J2 is not None
    assert EGM96.J4 is not None

################################################################################################################################################################

def test_earth_static_properties_EGM96 ():

    assert EGM96.gravitational_parameter is not None
    assert EGM96.equatorial_radius is not None
    assert EGM96.flattening is not None
    assert EGM96.C20 is not None
    assert EGM96.C40 is not None
    assert EGM96.J2 is not None
    assert EGM96.J4 is not None

################################################################################################################################################################

def test_earth_static_properties_WGS84_EGM96 ():

    assert WGS84_EGM96.gravitational_parameter is not None
    assert WGS84_EGM96.equatorial_radius is not None
    assert WGS84_EGM96.flattening is not None
    assert WGS84_EGM96.C20 is not None
    assert WGS84_EGM96.C40 is not None
    assert WGS84_EGM96.J2 is not None
    assert WGS84_EGM96.J4 is not None

################################################################################################################################################################

def test_earth_static_properties_EGM84 ():

    assert EGM84.gravitational_parameter is not None
    assert EGM84.equatorial_radius is not None
    assert EGM84.flattening is not None
    assert EGM84.C20 is not None
    assert EGM84.C40 is not None
    assert EGM84.J2 is not None
    assert EGM84.J4 is not None

################################################################################################################################################################

def test_earth_static_properties_WGS84 ():

    assert WGS84.gravitational_parameter is not None
    assert WGS84.equatorial_radius is not None
    assert WGS84.flattening is not None
    assert WGS84.C20 is not None
    assert WGS84.C40 is not None
    assert WGS84.J2 is not None
    assert WGS84.J4 is not None

################################################################################################################################################################

def test_earth_static_properties_Spherical ():

    assert Spherical.gravitational_parameter is not None
    assert Spherical.equatorial_radius is not None
    assert Spherical.flattening is not None
    assert Spherical.C20 is not None
    assert Spherical.C40 is not None
    assert Spherical.J2 is not None
    assert Spherical.J4 is not None

################################################################################################################################################################
