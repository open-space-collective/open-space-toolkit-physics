#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/testing/python/python-3.6/build.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

set -a
set -e

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
top_directory="${script_directory}/../../../.."

source "${script_directory}/.env"

pushd "${top_directory}" > /dev/null

docker build \
--tag="${python_test_image_repository}:${python_test_image_tag}" \
--file="${script_directory}/Dockerfile" \
.

popd > /dev/null

################################################################################################################################################################
