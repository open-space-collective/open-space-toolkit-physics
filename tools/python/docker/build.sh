#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/docker/build.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

source "../../.env"

docker build \
--tag="${python_image_repository}:${python_image_tag}" \
.

# docker build \
# --tag="${image_name}-python-debug:${image_tag}" \
# --file="Dockerfile.debug" \
# --build-arg="image_repository=${python_image_repository}" \
# --build-arg="image_tag=${python_image_tag}" \
# .

popd > /dev/null

################################################################################################################################################################