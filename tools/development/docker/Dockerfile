################################################################################################################################################################

# @project        Library/Physics
# @file           tools/development/docker/Dockerfile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

FROM openspacecollective/library-mathematics:0.1.10

LABEL maintainer="lucas@loftorbital.com"

# Arguments

ARG cpu_count=1

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
 && make -j ${cpu_count} \
 && mkdir /usr/local/include/sofa \
 && cp -r *.h /usr/local/include/sofa \
 && cp -r *.a /usr/local/lib \
 && rm -rf /tmp/sofa \
 && popd > /dev/null

## Library :: Mathematics [0.1.10]

RUN mkdir -p /tmp/library-mathematics \
 && pushd /tmp/library-mathematics > /dev/null \
 && wget --quiet https://github.com/open-space-collective/library-mathematics/releases/download/0.1.10/library-mathematics-0.1.10-1.x86_64-runtime.rpm \
 && wget --quiet https://github.com/open-space-collective/library-mathematics/releases/download/0.1.10/library-mathematics-0.1.10-1.x86_64-devel.rpm \
 && dnf install -y ./*.rpm \
 && rm -rf /tmp/library-mathematics \
 && popd > /dev/null

# Labels

ARG version

ENV version ${version}

LABEL version="${version}"

# Execution

CMD ["/bin/bash"]

################################################################################################################################################################