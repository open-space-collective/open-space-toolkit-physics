#!/bin/bash

################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/development/stop.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

# Setup environment

source "../.env"

# Stop Docker container

docker rm -f ${container_name}

popd > /dev/null

################################################################################################################################################################
