#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/development/helpers/test.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# make test

export LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE="Automatic"
export LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY="/app/share/coordinate/frame/providers/iers"

export LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_ENGINE_MODE="Automatic"
export LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY="/app/share/environment/ephemerides/spice"

export LIBRARY_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_ENABLED="true"
export LIBRARY_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY="/app/share/environment/gravitational/earth"

if [[ -z ${1} ]]; then
    ${script_directory}/../bin/*.test
else
    ${script_directory}/../bin/*.test --gtest_filter=${1}
fi

################################################################################################################################################################