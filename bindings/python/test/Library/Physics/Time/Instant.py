# coding=utf-8

################################################################################################################################################################

# @project        Library ▸ Physics
# @file           LibraryPhysicsPy/Time/Instant.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import unittest

from Library.Core import Types

from LibraryPhysicsPy import Time

################################################################################################################################################################

Scale = Time.Scale
Instant = Time.Instant
DateTime = Time.DateTime

class TestLibraryPhysicsTimeInstant (unittest.TestCase):

    def setUp (self):

        self.instant = Instant.DateTime(DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0), Scale.UTC)

    def runTest (self):

        self.assertTrue(self.instant == self.instant)
        self.assertFalse(self.instant != self.instant)

        self.assertTrue(self.instant.isDefined())
        self.assertTrue(self.instant.isPostEpoch())

        self.assertEqual(self.instant.getDateTime(Scale.UTC), DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0))
        self.assertEqual(self.instant.getJulianDate(Scale.UTC), 2458119.5)
        self.assertEqual(self.instant.getModifiedJulianDate(Scale.UTC), 58119.0)
        self.assertEqual(self.instant.toString(Scale.UTC), "2018-01-01 00:00:00 [UTC]")

        self.assertFalse(Instant.Undefined().isDefined())
        self.assertTrue(Instant.Now().isDefined())
        self.assertTrue(Instant.J2000().isDefined())
        self.assertEqual(Instant.DateTime(DateTime(2018, 1, 1, 0, 0, 0, 0, 0, 0), Scale.UTC), self.instant)
        self.assertEqual(Instant.JulianDate(2458119.5, Scale.UTC), self.instant)
        self.assertEqual(Instant.ModifiedJulianDate(58119.0, Scale.UTC), self.instant)

suite = unittest.TestLoader().loadTestsFromTestCase(TestLibraryPhysicsTimeInstant)
unittest.TextTestRunner(verbosity=2).run(suite)

################################################################################################################################################################
