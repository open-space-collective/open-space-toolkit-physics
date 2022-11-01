################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           docker/development/debian/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

ARG BASE_IMAGE_VERSION=latest

FROM openspacecollective/open-space-toolkit-base:${BASE_IMAGE_VERSION}-debian

LABEL maintainer="lucas@loftorbital.com"

# Dependencies

## Zip

RUN apt-get update \
 && apt-get install -y unzip \
 && rm -rf /var/lib/apt/lists/*

## {fmt} [5.2.0]

RUN git clone --branch 5.2.0 --depth 1 https://github.com/fmtlib/fmt.git /tmp/fmt \
 && cd /tmp/fmt \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/fmt

## ordered-map [0.6.0]

RUN git clone --branch v0.6.0 --depth 1 https://github.com/Tessil/ordered-map.git /tmp/ordered-map \
 && cd /tmp/ordered-map \
 && cp -r ./include/tsl /usr/local/include \
 && rm -rf /tmp/ordered-map

## Eigen [3.3.7]

RUN mkdir /tmp/eigen \
 && cd /tmp/eigen \
 && wget --quiet https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz \
 && tar -xvf eigen-3.3.7.tar.gz \
 && cd eigen-3.3.7 \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make install \
 && rm -rf /tmp/eigen

## IAU SOFA [2018-01-30]

RUN mkdir -p /tmp/sofa \
 && cd /tmp/sofa \
 && wget --quiet http://www.iausofa.org/2018_0130_C/sofa_c-20180130.tar.gz \
 && tar -zxf sofa_c-20180130.tar.gz \
 && cd sofa/20180130/c/src/ \
 && pattern="CFLAGF = -c -pedantic -Wall -W -O" \
 && target="CFLAGF = -c -pedantic -Wall -W -O -fpic" \
 && sed -i -e 's,'"$pattern"','"$target"',g' makefile \
 && make -j $(nproc) \
 && mkdir /usr/local/include/sofa \
 && cp -r *.h /usr/local/include/sofa \
 && cp -r *.a /usr/local/lib \
 && rm -rf /tmp/sofa

## SPICE Toolkit [N0066]

RUN cd /tmp \
 && wget --quiet http://naif.jpl.nasa.gov/pub/naif/toolkit/C/PC_Linux_GCC_64bit/packages/cspice.tar.Z \
 && tar -xf cspice.tar.Z \
 && cd cspice \
 && apt-get update \
 && apt-get install -y csh \
 && ./makeall.csh > /dev/null \
 && mkdir -p /usr/local/include/cspice \
 && cp -r include/* /usr/local/include/cspice/ \
 && cp -r lib/* /usr/local/lib/ \
 && ln -s /usr/local/lib/cspice.a /usr/local/lib/libcspice.a \
 && rm -rf /tmp/cspice \
 && apt-get remove -y csh \
 && rm -rf /var/lib/apt/lists/*

# GeographicLib [1.52]

RUN git clone https://github.com/geographiclib/geographiclib /tmp/geographiclib \
 && cd /tmp/geographiclib \
 && git checkout tags/r1.52 \
 && mkdir build \
 && cd build \
 && apt-get update \
 && apt-get install -y libproj-dev \
 && cmake -DGEOGRAPHICLIB_LIB_TYPE=STATIC -DCMAKE_CXX_FLAGS="-fPIC" .. \
 && make -j $(nproc) \
 && make install \
 && rm -rf /tmp/geographiclib \
 && rm -rf /var/lib/apt/lists/*

## Open Space Toolkit ▸ Core

ARG OSTK_CORE_VERSION=0.4.5

RUN mkdir -p /tmp/open-space-toolkit-core \
 && cd /tmp/open-space-toolkit-core \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/${OSTK_CORE_VERSION}/open-space-toolkit-core-${OSTK_CORE_VERSION}-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/${OSTK_CORE_VERSION}/open-space-toolkit-core-${OSTK_CORE_VERSION}-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/open-space-toolkit-core

## Open Space Toolkit ▸ I/O

ARG OSTK_IO_VERSION=0.4.5

RUN mkdir -p /tmp/open-space-toolkit-io \
 && cd /tmp/open-space-toolkit-io \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-io/releases/download/${OSTK_IO_VERSION}/open-space-toolkit-io-${OSTK_IO_VERSION}-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-io/releases/download/${OSTK_IO_VERSION}/open-space-toolkit-io-${OSTK_IO_VERSION}-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/open-space-toolkit-io

## Open Space Toolkit ▸ Mathematics

ARG OSTK_MATHEMATICS_VERSION=0.5.1

RUN mkdir -p /tmp/open-space-toolkit-mathematics \
 && cd /tmp/open-space-toolkit-mathematics \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/${OSTK_MATHEMATICS_VERSION}/open-space-toolkit-mathematics-${OSTK_MATHEMATICS_VERSION}-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/${OSTK_MATHEMATICS_VERSION}/open-space-toolkit-mathematics-${OSTK_MATHEMATICS_VERSION}-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/open-space-toolkit-mathematics

# Install data

COPY --from=us.gcr.io/loft-orbital-public/software/open-space-toolkit/data:0.3.0 /open-space-toolkit/physics /usr/local/share/OpenSpaceToolkit/Physics

ENV OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY "/usr/local/share/OpenSpaceToolkit/Physics/coordinate/frame/providers/iers"
ENV OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY "/usr/local/share/OpenSpaceToolkit/Physics/environment/ephemerides/spice"
ENV OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY "/usr/local/share/OpenSpaceToolkit/Physics/environment/gravitational/earth"
ENV OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY "/usr/local/share/OpenSpaceToolkit/Physics/environment/magnetic/earth"

# Labels

ARG VERSION

ENV VERSION ${VERSION}

LABEL VERSION="${VERSION}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################
