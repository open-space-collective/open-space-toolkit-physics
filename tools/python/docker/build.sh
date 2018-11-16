#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/docker/build.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd ${script_directory} > /dev/null

source "../../.env"

docker build \
--tag="${image_name}-python:${image_version}" \
.

docker build \
--tag="${image_name}-python-debug:${image_version}" \
--file="Dockerfile.debug" \
--build-arg="image_name=${image_name}" \
--build-arg="image_version=${image_version}" \
.

popd > /dev/null

################################################################################################################################################################