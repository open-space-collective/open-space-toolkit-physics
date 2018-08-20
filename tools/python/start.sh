#!/bin/bash

################################################################################################################################################################

# @project        Library/Physics
# @file           tools/python/start.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pushd "${script_directory}" > /dev/null

source ../.env

docker run \
--name="${container_name}-notebook" \
-it \
--rm \
--publish="8888:8888" \
--user="" \
--env="JUPYTER_LAB_ENABLE=yes" \
--env="LD_LIBRARY_PATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
--env="PYTHONPATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
--volume="$(pwd)/../../../library-core/lib:/opt/core:ro" \
--volume="$(pwd)/../../../library-mathematics/lib:/opt/mathematics:ro" \
--volume="$(pwd)/../../lib:/opt/lib:ro" \
--volume="$(pwd)/../../share/python/notebooks:/home/jovyan/notebooks" \
--volume="$(pwd)/../../share/data:/app/share/data" \
jupyter/scipy-notebook \
bash -c "mkdir -p /opt/conda/lib/python3.6/site-packages/Library/Physics \
&& ln -s /opt/lib/liblibrary-physics.so.0 /opt/conda/lib/python3.6/site-packages/Library/Physics/liblibrary-physics.so.0 \
&& ln -s /opt/lib/LibraryPhysicsPy.so /opt/conda/lib/python3.6/site-packages/Library/Physics/LibraryPhysicsPy.so \
&& echo 'from .LibraryPhysicsPy import *' > /opt/conda/lib/python3.6/site-packages/Library/Physics/__init__.py \
&& start-notebook.sh --NotebookApp.token=''"

popd

################################################################################################################################################################