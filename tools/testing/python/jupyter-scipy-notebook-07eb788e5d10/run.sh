#!/bin/bash

# Apache License 2.0

set -a
set -e

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
tools_directory="${script_directory}/../../.."

# Setup environment

source "${tools_directory}/.env"
source "${script_directory}/.env"

image_repository=${python_test_image_repository}
image_tag=${python_test_image_tag}

container_name=${python_test_container_name}

# Build Docker image if it does not exist already

pull_image ()
{

    echo "Pulling Docker image [${image_repository}:${image_tag}]..."

    {
        docker pull "${image_repository}:${image_tag}" 2> /dev/null && pull_result=1
    } || {
        echo "Cannot pull Docker image [${image_repository}:${image_tag}]." && pull_result=0
    }

}

build_image ()
{

    echo "Building Docker image [${image_repository}:${image_tag}]..."

    pushd "${script_directory}" > /dev/null

    ./build.sh

    popd > /dev/null

}

pull_or_build_image ()
{

    if [[ "$(docker images -q ${image_repository}:${image_tag} 2> /dev/null)" == "" ]]; then

        pull_image

        if [[ ${pull_result} -eq 0 ]]; then
            build_image
        fi

    fi

}

# Run Docker container

run_container ()
{

    echo "Running Docker image [${image_repository}:${image_tag}]..."

    docker run \
    --name=${container_name} \
    -it \
    --rm \
    --env-file="${script_directory}/.env" \
    --volume="${project_directory}/lib/libopen-space-toolkit-physics.so:/opt/conda/lib/python3.6/site-packages/OpenSpaceToolkit/Physics/libopen-space-toolkit-physics.so:ro" \
    --volume="${project_directory}/lib/libopen-space-toolkit-physics.so.0:/opt/conda/lib/python3.6/site-packages/OpenSpaceToolkit/Physics/libopen-space-toolkit-physics.so.0:ro" \
    --volume="${project_directory}/lib/OpenSpaceToolkitPhysicsPy.so:/opt/conda/lib/python3.6/site-packages/OpenSpaceToolkit/Physics/OpenSpaceToolkitPhysicsPy.so:ro" \
    --volume="${project_directory}/bindings/python/docs:/home/jovyan/open-space-toolkit/physics/docs:ro" \
    --volume="${project_directory}/bindings/python/test:/home/jovyan/open-space-toolkit/physics/test:ro" \
    --volume="${project_directory}/share:/home/jovyan/open-space-toolkit/physics/data" \
    ${image_repository}:${image_tag} \
    ${@}

}

pull_or_build_image
run_container ${@}
