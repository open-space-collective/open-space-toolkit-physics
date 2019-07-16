#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/testing/python/run.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

set -a
set -e

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

# Python - 3.6

./python-3.6/run.sh

# Jupyter SciPy Notebook - 07eb788e5d10

./jupyter-scipy-notebook-07eb788e5d10/run.sh

popd > /dev/null

################################################################################################################################################################
