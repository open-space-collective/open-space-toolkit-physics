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
--env="JUPYTER_LAB_ENABLE=yes" \
--env="LD_LIBRARY_PATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
--env="PYTHONPATH=/opt/conda/lib/python3.6/site-packages:/home/jovyan/lib" \
--volume=$(pwd)/../../lib:/home/jovyan/lib:ro \
--volume=$(pwd)/notebooks:/home/jovyan/notebooks \
jupyter/scipy-notebook \
start-notebook.sh --NotebookApp.token=''

popd

################################################################################################################################################################