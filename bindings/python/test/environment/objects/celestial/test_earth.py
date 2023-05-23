# Apache License 2.0

from ostk.physics.environment.objects.celestial_bodies import Earth

from ostk.physics.environment.objects.celestial_bodies.earth.models import EGM2008
from ostk.physics.environment.objects.celestial_bodies.earth.models import EGM96
from ostk.physics.environment.objects.celestial_bodies.earth.models import WGS84_EGM96
from ostk.physics.environment.objects.celestial_bodies.earth.models import EGM84
from ostk.physics.environment.objects.celestial_bodies.earth.models import WGS84
from ostk.physics.environment.objects.celestial_bodies.earth.models import Spherical

################################################################################################################################################################

class TestEarth:

    def test_properties_EGM2008 (self):

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

    def test_properties_WGS84_EGM96 (self):

        assert WGS84_EGM96.gravitational_parameter is not None
        assert WGS84_EGM96.equatorial_radius is not None
        assert WGS84_EGM96.flattening is not None
        assert WGS84_EGM96.C20 is not None
        assert WGS84_EGM96.C40 is not None
        assert WGS84_EGM96.J2 is not None
        assert WGS84_EGM96.J4 is not None

    def test_properties_EGM96 (self):

        assert EGM96.gravitational_parameter is not None
        assert EGM96.equatorial_radius is not None
        assert EGM96.flattening is not None
        assert EGM96.C20 is not None
        assert EGM96.C40 is not None
        assert EGM96.J2 is not None
        assert EGM96.J4 is not None

    def test_properties_EGM84 (self):

        assert EGM84.gravitational_parameter is not None
        assert EGM84.equatorial_radius is not None
        assert EGM84.flattening is not None
        assert EGM84.C20 is not None
        assert EGM84.C40 is not None
        assert EGM84.J2 is not None
        assert EGM84.J4 is not None

    def test_properties_WGS84 (self):

        assert WGS84.gravitational_parameter is not None
        assert WGS84.equatorial_radius is not None
        assert WGS84.flattening is not None
        assert WGS84.C20 is not None
        assert WGS84.C40 is not None
        assert WGS84.J2 is not None
        assert WGS84.J4 is not None

    def test_properties_spherical (self):

        assert Spherical.gravitational_parameter is not None
        assert Spherical.equatorial_radius is not None
        assert Spherical.flattening is not None
        assert Spherical.C20 is not None
        assert Spherical.C40 is not None
        assert Spherical.J2 is not None
        assert Spherical.J4 is not None

    def test_default_success (self):

        earth = Earth.default()

        assert earth is not None
        assert isinstance(earth, Earth)

    def test_EGM2008_success (self):

        earth = Earth.EGM2008()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.EGM2008(2190, 2160)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_WGS84_EGM96_success (self):

        earth = Earth.WGS84_EGM96()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.WGS84_EGM96(180, 180)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_EGM96_success (self):

        earth = Earth.EGM96()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.EGM96(360, 360)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_EGM84_success (self):

        earth = Earth.EGM84()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.EGM84(180, 180)

        assert earth_custom is not None
        assert isinstance(earth_custom, Earth)

    def test_WGS84_success (self):

        earth = Earth.WGS84()

        assert earth is not None
        assert isinstance(earth, Earth)

        earth_custom: Earth = Earth.WGS84(20, 0)

        assert earth is not None
        assert isinstance(earth_custom, Earth)

    def test_spherical_success (self):

        earth = Earth.spherical()

        assert earth is not None
        assert isinstance(earth, Earth)

################################################################################################################################################################
