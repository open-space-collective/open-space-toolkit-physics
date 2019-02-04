#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/start.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

source "../.env"

# Build Docker image if it does not exist already

if [[ "$(docker images -q ${image_name}-python:${image_version} 2> /dev/null)" == "" ]]; then

    pushd "${script_directory}/docker" > /dev/null

    ./build.sh

    popd

fi

options=""
command="/bin/bash"

if [[ ! -z $1 ]] && [[ $1 == "--link" ]]; then

    options="${options} \
    --volume=${library_core_directory}/lib:/opt/library-core:ro \
    --volume=${library_mathematics_directory}/lib:/opt/library-mathematics:ro"

    command=" \
    mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Core \
    && ln -s /opt/library-core/liblibrary-core.so.0 /opt/conda/lib/python3.6/site-packages/Library/Core/liblibrary-core.so.0 \
    && ln -s /opt/library-core/LibraryCorePy.so /opt/conda/lib/python3.6/site-packages/Library/Core/LibraryCorePy.so \
    && echo 'from .LibraryCorePy import *' > /opt/conda/lib/python3.6/site-packages/Library/Core/__init__.py \
    && mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Mathematics \
    && ln -s /opt/library-mathematics/liblibrary-mathematics.so.0 /opt/conda/lib/python3.6/site-packages/Library/Mathematics/liblibrary-mathematics.so.0 \
    && ln -s /opt/library-mathematics/LibraryMathematicsPy.so /opt/conda/lib/python3.6/site-packages/Library/Mathematics/LibraryMathematicsPy.so \
    && echo 'from .LibraryMathematicsPy import *' > /opt/conda/lib/python3.6/site-packages/Library/Mathematics/__init__.py \
    && mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Physics \
    && ln -s /opt/lib/liblibrary-physics.so.0 /opt/conda/lib/python3.6/site-packages/Library/Physics/liblibrary-physics.so.0 \
    && ln -s /opt/lib/LibraryPhysicsPy.so /opt/conda/lib/python3.6/site-packages/Library/Physics/LibraryPhysicsPy.so \
    && echo 'from .LibraryPhysicsPy import *' > /opt/conda/lib/python3.6/site-packages/Library/Physics/__init__.py \
    && start-notebook.sh --NotebookApp.token=''"

else

    command=" \
    pip install --quiet LibraryIOPy LibraryMathematicsPy \
    && mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Physics \
    && ln -s /opt/lib/liblibrary-physics.so.0 /opt/conda/lib/python3.6/site-packages/Library/Physics/liblibrary-physics.so.0 \
    && ln -s /opt/lib/LibraryPhysicsPy.so /opt/conda/lib/python3.6/site-packages/Library/Physics/LibraryPhysicsPy.so \
    && echo -e 'from Library.IO import *' | tee -a /opt/conda/lib/python3.6/site-packages/Library/Physics/__init__.py \
    && echo -e 'from Library.Mathematics import *' | tee -a /opt/conda/lib/python3.6/site-packages/Library/Physics/__init__.py \
    && echo -e 'from .LibraryPhysicsPy import *' | tee -a /opt/conda/lib/python3.6/site-packages/Library/Physics/__init__.py \
    && start-notebook.sh --NotebookApp.token=''"

fi

# Run Docker container

docker run \
--name="${container_name}-notebook" \
-it \
--rm \
--publish="${python_port}:8888" \
--env-file="${script_directory}/.env" \
--volume="${project_directory}/lib:/opt/lib:ro" \
--volume="${project_directory}/bindings/python/docs:/home/jovyan/docs" \
--volume="${project_directory}/tutorials/python/notebooks:/home/jovyan/tutorials" \
--volume="${project_directory}/share:/home/jovyan/.library/physics" \
--workdir="/home/jovyan" \
${options} \
"${image_name}-python:${image_version}" \
/bin/bash -c "${command}"

popd > /dev/null

################################################################################################################################################################