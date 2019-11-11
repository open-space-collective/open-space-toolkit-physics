################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/testing/python/jupyter-scipy-notebook-07eb788e5d10/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM jupyter/scipy-notebook:07eb788e5d10

LABEL maintainer="lucas@loftorbital.com"

RUN pip install pytest>=5.0.1

COPY bindings/python/requirements.txt /requirements.txt

RUN pip install -r /requirements.txt

ENV LD_LIBRARY_PATH /usr/local/lib:/opt/conda/lib/python3.6/site-packages:/home/jovyan/library/physics/lib
ENV PYTHONPATH /opt/conda/lib/python3.6/site-packages:/home/jovyan/library/physics/lib

COPY bindings/python/tools/python/Library/Physics /opt/conda/lib/python3.6/site-packages/Library/Physics

RUN mkdir -p /home/jovyan/library \
 && mkdir -p /home/jovyan/library/physics

WORKDIR /home/jovyan/library/physics/test

CMD [ "pytest", "-sv" ]

################################################################################################################################################################
