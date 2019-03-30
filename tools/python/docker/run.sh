#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/docker/run.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

source "../../.env"

docker run \
--name="${container_name}-python" \
-it \
--rm \
"${image_name}-python:${image_version}" \
/bin/bash

popd > /dev/null

################################################################################################################################################################