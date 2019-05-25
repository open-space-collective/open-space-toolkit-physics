#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/development/docker/build.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Setup environment

source "${script_directory}/../../.env"

# Build Docker image

docker build \
--build-arg="VERSION=${image_tag}" \
--tag="${image_repository}:${image_tag}" \
--file="${script_directory}/Dockerfile" \
"${script_directory}"

# Tag Docker image

docker tag "${image_repository}:${image_tag}" "${image_repository}:latest"

################################################################################################################################################################
