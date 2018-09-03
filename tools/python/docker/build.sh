#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/docker/build.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd ${script_directory} > /dev/null

source "../../.env"

docker build \
--tag="${repository_name}/${project_name}-python" \
.

docker build \
--tag="${repository_name}/${project_name}-python-debug" \
--file="Dockerfile.debug" \
--build-arg="repository_name=${repository_name}" \
--build-arg="project_name=${project_name}" \
.

popd > /dev/null

################################################################################################################################################################