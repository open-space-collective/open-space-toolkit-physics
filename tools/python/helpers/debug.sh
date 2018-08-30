#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/helpers/debug.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

gdb `which python`

# gdb `which python` --args /home/jovyan/notebooks/A.py

# set args /home/jovyan/notebooks/A.py

popd > /dev/null

################################################################################################################################################################