################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           bindings/python/test/units/derived/test_angle.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.mathematics.geometry import Angle as AngleMathematics
from ostk.physics.units import Angle as AnglePhysics

################################################################################################################################################################

def test_angle_conversion ():

    angle_physics: AnglePhysics = AnglePhysics(30.0, AnglePhysics.Unit.Degree)
    angle_mathematics: AngleMathematics = AngleMathematics(30.0, AngleMathematics.Unit.Degree)

    assert angle_physics is not None
    assert angle_mathematics is not None
    # assert angle_physics == angle_mathematics

################################################################################################################################################################
