################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/coordinate/frame/providers/iers/test_bulletin_a.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

from datetime import datetime

from ostk.core.filesystem import File

from ostk.physics.time import Scale
from ostk.physics.time import Instant

import ostk.physics as physics

################################################################################################################################################################

BulletinA = physics.coordinate.frame.providers.iers.BulletinA

################################################################################################################################################################

class TestBulletinA:

    def test_str_success (self, bulletin_a: BulletinA):

        assert str(bulletin_a).startswith('-- Bulletin A --')

    def test_repr_success (self, bulletin_a: BulletinA):

        assert repr(bulletin_a).startswith('-- Bulletin A --')

    def test_is_defined_success (self, bulletin_a: BulletinA):

        assert bulletin_a.is_defined() is True

    def test_access_release_date_success (self, bulletin_a: BulletinA):

        assert bulletin_a.access_release_date().to_string() == '2020-10-29'

    def test_access_tai_minus_utc_success (self, bulletin_a: BulletinA):

        assert bulletin_a.access_tai_minus_utc().to_string() == '37.000.000.000'

    def test_access_tai_minus_utc_epoch_success (self, bulletin_a: BulletinA):

        assert bulletin_a.access_tai_minus_utc_epoch() == Instant.date_time(datetime(2017, 1, 1, 0, 0, 0), Scale.UTC)

    def test_access_observation_interval_success (self, bulletin_a: BulletinA):

        assert bulletin_a.access_observation_interval().to_string() == '[2020-10-23 00:00:00 - 2020-10-29 00:00:00] [UTC]'

    def test_access_prediction_interval_success (self, bulletin_a: BulletinA):

        assert bulletin_a.access_prediction_interval().to_string() == '[2020-10-30 00:00:00 - 2021-10-29 00:00:00] [UTC]'

    def test_get_release_date_success (self, bulletin_a: BulletinA):

        assert bulletin_a.get_release_date().to_string() == '2020-10-29'

    def test_get_tai_minus_utc_success (self, bulletin_a: BulletinA):

        assert bulletin_a.get_tai_minus_utc().to_string() == '37.000.000.000'

    def test_get_tai_minus_utc_epoch_success (self, bulletin_a: BulletinA):

        assert bulletin_a.get_tai_minus_utc_epoch() == Instant.date_time(datetime(2017, 1, 1, 0, 0, 0), Scale.UTC)

    def test_get_observation_interval_success (self, bulletin_a: BulletinA):

        assert bulletin_a.get_observation_interval().to_string() == '[2020-10-23 00:00:00 - 2020-10-29 00:00:00] [UTC]'

    def test_get_observation_at_success (self, bulletin_a: BulletinA):

        observation: BulletinA.Observation = bulletin_a.get_observation_at(Instant.date_time(datetime(2020, 10, 24, 0, 0, 0), Scale.UTC))

        assert isinstance(observation, BulletinA.Observation)

        assert observation.year == 2020
        assert observation.month == 10
        assert observation.day == 24
        assert observation.mjd == 59146.0
        assert observation.x == 0.17091999999999999
        assert observation.x_error == 9.0000000000000006e-05
        assert observation.y == 0.3024
        assert observation.y_error == 9.0000000000000006e-05
        assert observation.ut1_minus_utc == -0.17319599999999999
        assert observation.ut1_minus_utc_error == 1.2999999999999999e-05

    def test_get_prediction_interval_success (self, bulletin_a: BulletinA):

        assert bulletin_a.get_prediction_interval().to_string() == '[2020-10-30 00:00:00 - 2021-10-29 00:00:00] [UTC]'

    def test_get_prediction_at_success (self, bulletin_a: BulletinA):

        prediction: BulletinA.Prediction = bulletin_a.get_prediction_at(Instant.date_time(datetime(2020, 10, 31, 0, 0, 0), Scale.UTC))

        assert isinstance(prediction, BulletinA.Prediction)

        assert prediction.year == 2020
        assert prediction.month == 10
        assert prediction.day == 31
        assert prediction.mjd == 59153.0
        assert prediction.x == 0.16059999999999999
        assert prediction.y == 0.29709999999999998
        assert prediction.ut1_minus_utc == -0.17524000000000001

    def test_undefined_success (self):

        assert BulletinA.undefined() is not None

    def test_load_success (self, bulletin_a_file: File):

        assert BulletinA.load(bulletin_a_file) is not None

################################################################################################################################################################
