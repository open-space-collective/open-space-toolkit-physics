################################################################################################################################################################

# @project        Library ▸ Physics
# @file           tools/testing/python/python-3.6/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM python:3.6

LABEL maintainer="lucas@loftorbital.com"

RUN pip install pytest>=5.0.1

COPY bindings/python/requirements.txt /requirements.txt

RUN pip install -r /requirements.txt

ENV LD_LIBRARY_PATH /usr/local/lib:/usr/local/lib/python3.6/site-packages:/library/physics/lib
ENV PYTHONPATH /usr/local/lib/python3.6/site-packages:/library/physics/lib

COPY bindings/python/tools/python/Library/Physics /usr/local/lib/python3.6/site-packages/Library/Physics

RUN mkdir -p /library \
 && mkdir -p /library/physics

WORKDIR /library/physics/test

ENTRYPOINT [ "pytest", "-sv" ]

################################################################################################################################################################
