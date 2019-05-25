#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/ci/binaries.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

project_directory="${script_directory}/../.."
development_directory="${project_directory}/tools/development"

source "${project_directory}/tools/.env"

# Generate binaries

docker run \
--rm \
--env-file="${script_directory}/.env" \
--volume="${project_directory}:/app:rw" \
--volume="${project_directory}/share:/var/library-physics:rw" \
--volume="${development_directory}/helpers/build.sh:/app/build/build.sh:ro" \
--volume="${development_directory}/helpers/test.sh:/app/build/test.sh:ro" \
--workdir="/app/build" \
${image_repository}:${image_tag} \
/bin/bash -c "/app/build/build.sh && make package && mkdir -p /app/package && mv /app/build/*.rpm /app/package"

################################################################################################################################################################
