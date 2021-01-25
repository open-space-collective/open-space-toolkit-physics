################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           docker/release/fedora/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

ARG VERSION

FROM openspacecollective/open-space-toolkit-physics-development:${VERSION}-fedora as cpp-builder

RUN mkdir -p /app/bin /app/build /app/lib

WORKDIR /app/build

COPY ./bindings /app/bindings
COPY ./docs /app/docs
COPY ./include /app/include
COPY ./share /app/share
COPY ./src /app/src
COPY ./test /app/test
COPY ./thirdparty /app/thirdparty
COPY ./tools /app/tools
COPY CMakeLists.txt /app/CMakeLists.txt
COPY LICENSE /app/LICENSE
COPY README.md /app/README.md
COPY .git /app/.git

RUN cmake .. \
 && make -j $(nproc) \
 && make install

################################################################################################################################################################

FROM fedora:30 as cpp-release

ENV LD_LIBRARY_PATH /usr/local/lib

COPY --from=cpp-builder /usr/local/include/OpenSpaceToolkit /usr/local/include/OpenSpaceToolkit
COPY --from=cpp-builder /usr/local/lib/libopen-space-toolkit-physics.* /usr/local/lib/
COPY --from=cpp-builder /usr/local/share/OpenSpaceToolkit /usr/local/share/OpenSpaceToolkit
COPY --from=cpp-builder /usr/local/test/OpenSpaceToolkit /usr/local/test/OpenSpaceToolkit

ENTRYPOINT ["/usr/local/test/OpenSpaceToolkit/Physics/open-space-toolkit-physics.test"]

################################################################################################################################################################

FROM fedora:30 as python-builder

COPY --from=cpp-builder /app/build/bindings/python/dist /dist

RUN pip3 install /dist/*.whl

################################################################################################################################################################

FROM fedora:30 as python-release

LABEL maintainer="lucas@loftorbital.com"

RUN ln -s /usr/bin/pip3 /usr/bin/pip

RUN dnf update -y \
 && dnf install -y wget libcurl-devel openssl-devel unzip \
 && dnf clean all

RUN pip install ipython numpy

COPY --from=python-builder /usr/local/lib/python3.8/site-packages/ostk /usr/local/lib/python3.8/site-packages/ostk

ENTRYPOINT ["ipython"]

################################################################################################################################################################
