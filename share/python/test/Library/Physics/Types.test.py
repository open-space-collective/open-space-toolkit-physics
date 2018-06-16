# coding=utf-8

################################################################################################################################################################

# @project        Library/Physics
# @file           Library/Physics/LibraryMathematicsPy/Types.test.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

# Types

from LibraryMathematicsPy import Types

## Integer

assert Types.Integer(0) == 0
assert Types.Integer(123) == 123
assert Types.Integer(+123) == +123
assert Types.Integer(-123) == -123

assert Types.Integer(0).getString() == "0"
assert Types.Integer(123).getString() == "123"
assert Types.Integer(+123).getString() == "123"
assert Types.Integer(-123).getString() == "-123"

## Real

################################################################################################################################################################