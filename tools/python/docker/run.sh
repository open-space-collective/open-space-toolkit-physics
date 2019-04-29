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
--name="${python_container_name}" \
-it \
--rm \
"${python_image_repository}:${python_image_tag}" \
/bin/bash

popd > /dev/null

################################################################################################################################################################