#!/bin/bash

################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           tools/development/helpers/test-python.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

PYTHON_VERSION="3.11"

################################################################################################################################################################

project_directory="$(git rev-parse --show-toplevel)"
test_directory="${project_directory}/bindings/python/test"

pushd "${test_directory}" > /dev/null

python${PYTHON_VERSION} -m pytest -svx ${@}

popd > /dev/null

################################################################################################################################################################