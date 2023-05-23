################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/test_import.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import ostk.mathematics as mathematics
import ostk.physics as physics

################################################################################################################################################################

def test_import ():

    Point = mathematics.geometry.d3.objects.Point
    Segment = mathematics.geometry.d3.objects.Segment

    Scale = physics.time.Scale
    Instant = physics.time.Instant
    Duration = physics.time.Duration
    Interval = physics.time.Interval
    Date = physics.time.Date
    Time = physics.time.Time
    DateTime = physics.time.DateTime
    Frame = physics.coordinate.Frame
    Environment = physics.Environment
    Object = physics.environment.Object
    Geometry = physics.environment.object.Geometry
    Celestial = physics.environment.objects.Celestial
    Earth = physics.environment.objects.celestial_bodies.Earth

################################################################################################################################################################
