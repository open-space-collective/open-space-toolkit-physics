################################################################################################################################################################

# @project        Open Space Toolkit ▸ Physics
# @file           docker/development/debian/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

ARG BASE_IMAGE_VERSION=latest

FROM openspacecollective/library-base:${BASE_IMAGE_VERSION}-debian

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
 && wget --quiet http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz \
 && tar -xvf 3.3.7.tar.gz \
 && cd eigen-eigen-323c052e1731 \
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

# GeographicLib [1.49]

RUN git clone git://git.code.sf.net/p/geographiclib/code /tmp/geographiclib \
 && cd /tmp/geographiclib \
 && git checkout tags/r1.49 \
 && mkdir build \
 && cd build \
 && apt-get update \
 && apt-get install -y libproj-dev \
 && cmake -DGEOGRAPHICLIB_LIB_TYPE=STATIC -DCMAKE_CXX_FLAGS="-fPIC" .. \
 && make -j $(nproc) \
 && make install \
 && rm -rf /tmp/geographiclib \
 && rm -rf /var/lib/apt/lists/*

## Library ▸ Core [0.2.5]

RUN mkdir -p /tmp/library-core \
 && cd /tmp/library-core \
 && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.2.5/library-core-0.2.5-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/library-core/releases/download/0.2.5/library-core-0.2.5-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/library-core

## Library ▸ I/O [0.2.4]

RUN mkdir -p /tmp/library-io \
 && cd /tmp/library-io \
 && wget --quiet https://github.com/open-space-collective/library-io/releases/download/0.2.4/library-io-0.2.4-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/library-io/releases/download/0.2.4/library-io-0.2.4-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/library-io

## Library ▸ Mathematics [0.2.6]

RUN mkdir -p /tmp/library-mathematics \
 && cd /tmp/library-mathematics \
 && wget --quiet https://github.com/open-space-collective/library-mathematics/releases/download/0.2.6/library-mathematics-0.2.6-1.x86_64-runtime.deb \
 && wget --quiet https://github.com/open-space-collective/library-mathematics/releases/download/0.2.6/library-mathematics-0.2.6-1.x86_64-devel.deb \
 && apt-get install -y ./*.deb \
 && rm -rf /tmp/library-mathematics

# Labels

ARG VERSION

ENV VERSION ${VERSION}

LABEL VERSION="${VERSION}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################
