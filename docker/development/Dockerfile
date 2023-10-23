# Apache License 2.0

ARG BASE_IMAGE_VERSION="latest"

FROM openspacecollective/open-space-toolkit-base:${BASE_IMAGE_VERSION}

LABEL maintainer="lucas@loftorbital.com"

# Dependencies

## Zip, jq, and git-lfs

RUN apt-get update \
 && apt-get install -y unzip jq git-lfs \
 && rm -rf /var/lib/apt/lists/*

## {fmt}

ARG FMT_VERSION="5.2.0"

RUN git clone --branch ${FMT_VERSION} --depth 1 https://github.com/fmtlib/fmt.git /tmp/fmt \
 && cd /tmp/fmt \
 && mkdir build \
 && cd build \
 && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE .. \
 && make --silent -j $(nproc) \
 && make install \
 && rm -rf /tmp/fmt

## ordered-map

ARG ORDERED_MAP_VERSION="0.6.0"

RUN git clone --branch v${ORDERED_MAP_VERSION} --depth 1 https://github.com/Tessil/ordered-map.git /tmp/ordered-map \
 && cd /tmp/ordered-map \
 && cp -r ./include/tsl /usr/local/include \
 && rm -rf /tmp/ordered-map

# NRLMSISE00 Model

ARG NRLMSISE00_MODEL_COMMIT="a5f81be"

RUN git clone https://github.com/magnific0/nrlmsise-00.git /tmp/nrlmsise \
 && cd /tmp/nrlmsise \
 && git checkout ${NRLMSISE00_MODEL_COMMIT} \
 && mkdir build \
 && cd build \
 && cmake -DNRLMSISE00_WITH_TESTS="OFF" -DCMAKE_C_FLAGS="-fPIC" .. \
 && make -j $(nproc) \
 && mkdir /usr/local/include/NRLMSISE-00 \
 && cp ../nrlmsise-00.h /usr/local/include/NRLMSISE-00 \
 && cp ../lib/libnrlmsise00.a /usr/local/lib \
 && rm -rf /tmp/nrlmsise

## Eigen

ARG EIGEN_VERSION="3.4.0"

RUN mkdir /tmp/eigen \
 && cd /tmp/eigen \
 && wget --quiet https://gitlab.com/libeigen/eigen/-/archive/${EIGEN_VERSION}/eigen-${EIGEN_VERSION}.tar.gz \
 && tar -xvf eigen-${EIGEN_VERSION}.tar.gz \
 && cd eigen-${EIGEN_VERSION} \
 && mkdir build \
 && cd build \
 && cmake .. \
 && make install \
 && rm -rf /tmp/eigen

## IAU SOFA

ARG IAU_SOFA_RELEASE="2018_0130_C"
ARG IAU_SOFA_VERSION="20180130"

RUN mkdir -p /tmp/sofa \
 && cd /tmp/sofa \
 && wget --quiet http://www.iausofa.org/${IAU_SOFA_RELEASE}/sofa_c-${IAU_SOFA_VERSION}.tar.gz \
 && tar -zxf sofa_c-${IAU_SOFA_VERSION}.tar.gz \
 && cd sofa/${IAU_SOFA_VERSION}/c/src/ \
 && pattern="CFLAGF = -c -pedantic -Wall -W -O" \
 && target="CFLAGF = -c -pedantic -Wall -W -O -fpic" \
 && sed -i -e 's,'"$pattern"','"$target"',g' makefile \
 && make -j $(nproc) \
 && mkdir /usr/local/include/sofa \
 && cp -r *.h /usr/local/include/sofa \
 && cp -r *.a /usr/local/lib \
 && rm -rf /tmp/sofa

## SPICE Toolkit

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

# GeographicLib

ARG GEOGRAPHIC_LIB="1.52"

RUN git clone https://github.com/geographiclib/geographiclib /tmp/geographiclib \
 && cd /tmp/geographiclib \
 && git checkout tags/r${GEOGRAPHIC_LIB} \
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

ARG OSTK_CORE_MAJOR="0"
ARG OSTK_CORE_MINOR="7"

## Force an image rebuild when new Core patch versions are detected
ADD https://api.github.com/repos/open-space-collective/open-space-toolkit-core/git/matching-refs/tags/${OSTK_CORE_MAJOR}.${OSTK_CORE_MINOR} /tmp/open-space-toolkit-core/versions.json

RUN mkdir -p /tmp/open-space-toolkit-core \
 && cd /tmp/open-space-toolkit-core \
 && export LATEST_PATCH_OF_MINOR=$(jq -r .[-1].ref versions.json | cut -d "/" -f3) \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-core-${LATEST_PATCH_OF_MINOR}-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-core-${LATEST_PATCH_OF_MINOR}-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/open-space-toolkit-core

 ## Open Space Toolkit ▸ I/O

ARG OSTK_IO_MAJOR="0"
ARG OSTK_IO_MINOR="7"

## Force an image rebuild when new IO patch versions are detected
ADD https://api.github.com/repos/open-space-collective/open-space-toolkit-io/git/matching-refs/tags/${OSTK_IO_MAJOR}.${OSTK_IO_MINOR} /tmp/open-space-toolkit-io/versions.json

RUN mkdir -p /tmp/open-space-toolkit-io \
 && cd /tmp/open-space-toolkit-io \
 && export LATEST_PATCH_OF_MINOR=$(jq -r .[-1].ref versions.json | cut -d "/" -f3) \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-io/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-io-${LATEST_PATCH_OF_MINOR}-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-io/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-io-${LATEST_PATCH_OF_MINOR}-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/open-space-toolkit-io

 ## Open Space Toolkit ▸ Mathematics

ARG OSTK_MATHEMATICS_MAJOR="0"
ARG OSTK_MATHEMATICS_MINOR="7"

## Force an image rebuild when new Math patch versions are detected
ADD https://api.github.com/repos/open-space-collective/open-space-toolkit-mathematics/git/matching-refs/tags/${OSTK_MATHEMATICS_MAJOR}.${OSTK_MATHEMATICS_MINOR} /tmp/open-space-toolkit-mathematics/versions.json

RUN mkdir -p /tmp/open-space-toolkit-mathematics \
 && cd /tmp/open-space-toolkit-mathematics \
 && export LATEST_PATCH_OF_MINOR=$(jq -r .[-1].ref versions.json | cut -d "/" -f3) \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-mathematics-${LATEST_PATCH_OF_MINOR}-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-mathematics-${LATEST_PATCH_OF_MINOR}-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/open-space-toolkit-mathematics

# Install seed data

RUN git clone --branch main --single-branch --depth=1 https://github.com/open-space-collective/open-space-toolkit-data.git /var/cache/open-space-toolkit-data

ENV OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY="/var/cache/open-space-toolkit-data/data/coordinate/frame/providers/iers"
ENV OSTK_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY="/var/cache/open-space-toolkit-data/data/environment/ephemerides/spice"
ENV OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY="/var/cache/open-space-toolkit-data/data/environment/gravitational/earth"
ENV OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY="/var/cache/open-space-toolkit-data/data/environment/magnetic/earth"
ENV OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY="/var/cache/open-space-toolkit-data/data/environment/atmospheric/earth"
ENV OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY="/var/cache/open-space-toolkit-data/data"

# Labels

ARG VERSION
ENV VERSION="${VERSION}"
LABEL VERSION="${VERSION}"

# Execution

CMD [ "/bin/bash" ]
