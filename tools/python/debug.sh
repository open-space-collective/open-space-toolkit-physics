#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/debug.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

source ../.env

if [[ ! -z $1 ]] && [[ $1 == "--link" ]]; then

    docker run \
    --name="${container_name}-python-debug" \
    -it \
    --rm \
    --privileged \
    --user="" \
    --env="LD_LIBRARY_PATH=/usr/local/lib:/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --env="PYTHONPATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --volume="$(pwd)/../../../library-core/lib:/opt/library-core:ro" \
    --volume="$(pwd)/../../../library-mathematics/lib:/opt/library-mathematics:ro" \
    --volume="$(pwd)/../../lib:/opt/lib:ro" \
    --volume="$(pwd)/../../share/python/notebooks:/home/jovyan/notebooks" \
    --volume="$(pwd)/helpers:/home/jovyan/notebooks/helpers:ro" \
    --volume="$(pwd)/../../share/data:/app/share/data" \
    --workdir="/home/jovyan/notebooks" \
    "${repository_name}/${project_name}-python-debug" \
    bash -c "mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Core \
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
    && /bin/bash"

else

    docker run \
    --name="${container_name}-python-debug" \
    -it \
    --rm \
    --privileged \
    --user="" \
    --env="LD_LIBRARY_PATH=/usr/local/lib:/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --env="PYTHONPATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
    --volume="$(pwd)/../../lib:/opt/lib:ro" \
    --volume="$(pwd)/../../share/python/notebooks:/home/jovyan/notebooks" \
    --volume="$(pwd)/helpers:/home/jovyan/notebooks/helpers:ro" \
    --volume="$(pwd)/../../share/data:/app/share/data" \
    --workdir="/home/jovyan/notebooks" \
    "${repository_name}/${project_name}-python-debug" \
    bash -c "mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Physics \
    && ln -s /opt/lib/liblibrary-physics.so.0 /opt/conda/lib/python3.6/site-packages/Library/Physics/liblibrary-physics.so.0 \
    && ln -s /opt/lib/LibraryPhysicsPy.so /opt/conda/lib/python3.6/site-packages/Library/Physics/LibraryPhysicsPy.so \
    && echo 'from .LibraryPhysicsPy import *' > /opt/conda/lib/python3.6/site-packages/Library/Physics/__init__.py \
    && /bin/bash"

fi

popd > /dev/null

################################################################################################################################################################