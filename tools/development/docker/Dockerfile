################################################################################################################################################################

# @project        Library/Physics
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

FROM openspacecollective/library-mathematics:0.1.14

LABEL maintainer="lucas@loftorbital.com"

# Dependencies

## IAU SOFA [2018-01-30]

RUN pushd /tmp > /dev/null \
 && mkdir sofa \
 && cd sofa \
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
 && rm -rf /tmp/sofa \
 && popd > /dev/null

## SPICE Toolkit [N0066]

RUN pushd /tmp > /dev/null \
 && wget --quiet http://naif.jpl.nasa.gov/pub/naif/toolkit/C/PC_Linux_GCC_64bit/packages/cspice.tar.Z \
 && tar -xf cspice.tar.Z \
 && cd cspice \
 && dnf install -y csh \
 && ./makeall.csh \
 && mkdir -p /usr/local/include/cspice \
 && cp -r include/* /usr/local/include/cspice/ \
 && cp -r lib/* /usr/local/lib/ \
 && ln -s /usr/local/lib/cspice.a /usr/local/lib/libcspice.a \
 && rm -rf /tmp/cspice \
 && dnf remove -y csh \
 && dnf clean all \
 && popd > /dev/null

## GeographicLib [1.49]

RUN git clone git://git.code.sf.net/p/geographiclib/code /tmp/geographiclib \
 && pushd /tmp/geographiclib > /dev/null \
 && git checkout tags/r1.49 \
 && mkdir build \
 && cd build \
 && dnf install -y proj-devel \
 && cmake -DGEOGRAPHICLIB_LIB_TYPE=STATIC -DCMAKE_CXX_FLAGS="-fPIC" .. \
 && make -j $(nproc) \
 && make install \
 && popd > /dev/null \
 && rm -rf /tmp/geographiclib \
 && dnf clean all

## Library ▸ I/O [0.2.0]

RUN mkdir -p /tmp/library-io \
 && pushd /tmp/library-io > /dev/null \
 && wget --quiet https://github.com/open-space-collective/library-io/releases/download/0.2.0/library-io-0.2.0-1.x86_64-runtime.rpm \
 && wget --quiet https://github.com/open-space-collective/library-io/releases/download/0.2.0/library-io-0.2.0-1.x86_64-devel.rpm \
 && dnf install -y ./*.rpm \
 && rm -rf /tmp/library-io \
 && popd > /dev/null

## Library ▸ Mathematics [0.2.0]

RUN mkdir -p /tmp/library-mathematics \
 && pushd /tmp/library-mathematics > /dev/null \
 && wget --quiet https://github.com/open-space-collective/library-mathematics/releases/download/0.2.0/library-mathematics-0.2.0-1.x86_64-runtime.rpm \
 && wget --quiet https://github.com/open-space-collective/library-mathematics/releases/download/0.2.0/library-mathematics-0.2.0-1.x86_64-devel.rpm \
 && dnf install -y ./*.rpm \
 && rm -rf /tmp/library-mathematics \
 && popd > /dev/null

# Labels

ARG VERSION

ENV VERSION ${VERSION}

LABEL VERSION="${VERSION}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################