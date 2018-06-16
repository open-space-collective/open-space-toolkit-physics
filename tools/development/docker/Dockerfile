################################################################################################################################################################

# @project        Library/Physics
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

FROM openspacecollective/library-mathematics:latest

LABEL maintainer="lucas@loftorbital.com"

# Arguments

ARG version
ARG cpu_count=1

# Dependencies

## Library :: Mathematics [master]

RUN pushd /tmp > /dev/null \
    && git clone https://github.com/open-space-collective/library-mathematics.git \
    && cd library-mathematics \
    && mkdir build \
    && cd build \
    && cmake -DBUILD_UNIT_TESTS=OFF .. \
    && make -j ${cpu_count} \
    && make install \
    && rm -rf /tmp/library-mathematics \
    && popd > /dev/null

## NumPy

RUN pip install --upgrade pip \
    && pip install numpy

# Labels

ENV version ${version}

LABEL version="${version}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################