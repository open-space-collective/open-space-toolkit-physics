# Apache License 2.0

ARG BASE_IMAGE_VERSION="latest"

# General purpose development image (root user)

FROM openspacecollective/open-space-toolkit-base-development:${BASE_IMAGE_VERSION} AS root-user

LABEL maintainer="lucas@loftorbital.com"

# Dependencies

## Zip, jq, and git-lfs

RUN apt-get update \
    && apt-get install -y unzip jq git-lfs \
    && rm -rf /var/lib/apt/lists/*

## fmt

ARG FMT_VERSION="5.2.0"

RUN cd /tmp \
    && git clone --branch ${FMT_VERSION} --depth 1 https://github.com/fmtlib/fmt.git \
    && cd fmt \
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

ARG TARGETPLATFORM

RUN cd /tmp \
    && export PACKAGE_PLATFORM=$(if [ ${TARGETPLATFORM} = "linux/amd64" ]; then echo "PC_Linux_GCC_64bit"; elif [ ${TARGETPLATFORM} = "linux/arm64" ]; then echo "MacM1_OSX_clang_64bit"; else echo "Unknown platform" && exit 1; fi;) \
    && wget --quiet http://naif.jpl.nasa.gov/pub/naif/toolkit/C/${PACKAGE_PLATFORM}/packages/cspice.tar.Z \
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

ARG TARGETPLATFORM
ARG OSTK_CORE_MAJOR="5"

## Force an image rebuild when new Core minor or patch versions are detected
ADD https://api.github.com/repos/open-space-collective/open-space-toolkit-core/git/matching-refs/tags/${OSTK_CORE_MAJOR} /tmp/open-space-toolkit-core/versions.json

RUN mkdir -p /tmp/open-space-toolkit-core \
    && cd /tmp/open-space-toolkit-core \
    && export LATEST_PATCH_OF_MINOR=$(jq -r .[-1].ref versions.json | cut -d "/" -f3) \
    && export PACKAGE_PLATFORM=$(if [ ${TARGETPLATFORM} = "linux/amd64" ]; then echo "x86_64"; elif [ ${TARGETPLATFORM} = "linux/arm64" ]; then echo "aarch64"; else echo "Unknown platform" && exit 1; fi;) \
    && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-core-${LATEST_PATCH_OF_MINOR}-1.${PACKAGE_PLATFORM}-runtime.deb \
    && wget --quiet https://github.com/open-space-collective/open-space-toolkit-core/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-core-${LATEST_PATCH_OF_MINOR}-1.${PACKAGE_PLATFORM}-devel.deb \
    && apt-get install -y ./*.deb \
    && rm -rf /tmp/open-space-toolkit-core

## Open Space Toolkit ▸ I/O

ARG TARGETPLATFORM
ARG OSTK_IO_MAJOR="4"

## Force an image rebuild when new IO minor or patch versions are detected
ADD https://api.github.com/repos/open-space-collective/open-space-toolkit-io/git/matching-refs/tags/${OSTK_IO_MAJOR} /tmp/open-space-toolkit-io/versions.json

RUN mkdir -p /tmp/open-space-toolkit-io \
    && cd /tmp/open-space-toolkit-io \
    && export LATEST_PATCH_OF_MINOR=$(jq -r .[-1].ref versions.json | cut -d "/" -f3) \
    && export PACKAGE_PLATFORM=$(if [ ${TARGETPLATFORM} = "linux/amd64" ]; then echo "x86_64"; elif [ ${TARGETPLATFORM} = "linux/arm64" ]; then echo "aarch64"; else echo "Unknown platform" && exit 1; fi;) \
    && wget --quiet https://github.com/open-space-collective/open-space-toolkit-io/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-io-${LATEST_PATCH_OF_MINOR}-1.${PACKAGE_PLATFORM}-runtime.deb \
    && wget --quiet https://github.com/open-space-collective/open-space-toolkit-io/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-io-${LATEST_PATCH_OF_MINOR}-1.${PACKAGE_PLATFORM}-devel.deb \
    && apt-get install -y ./*.deb \
    && rm -rf /tmp/open-space-toolkit-io

## Open Space Toolkit ▸ Mathematics

ARG TARGETPLATFORM
ARG OSTK_MATHEMATICS_MAJOR="4"

## Force an image rebuild when new Math minor or patch versions are detected
ADD https://api.github.com/repos/open-space-collective/open-space-toolkit-mathematics/git/matching-refs/tags/${OSTK_MATHEMATICS_MAJOR} /tmp/open-space-toolkit-mathematics/versions.json

RUN mkdir -p /tmp/open-space-toolkit-mathematics \
    && cd /tmp/open-space-toolkit-mathematics \
    && export LATEST_PATCH_OF_MINOR=$(jq -r .[-1].ref versions.json | cut -d "/" -f3) \
    && export PACKAGE_PLATFORM=$(if [ ${TARGETPLATFORM} = "linux/amd64" ]; then echo "x86_64"; elif [ ${TARGETPLATFORM} = "linux/arm64" ]; then echo "aarch64"; else echo "Unknown platform" && exit 1; fi;) \
    && wget --quiet https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-mathematics-${LATEST_PATCH_OF_MINOR}-1.${PACKAGE_PLATFORM}-runtime.deb \
    && wget --quiet https://github.com/open-space-collective/open-space-toolkit-mathematics/releases/download/${LATEST_PATCH_OF_MINOR}/open-space-toolkit-mathematics-${LATEST_PATCH_OF_MINOR}-1.${PACKAGE_PLATFORM}-devel.deb \
    && apt-get install -y ./*.deb \
    && rm -rf /tmp/open-space-toolkit-mathematics

# Install OSTk data

ARG OSTK_DATA_LOCAL_CACHE="/var/cache/open-space-toolkit-data"
ENV OSTK_PHYSICS_DATA_LOCAL_REPOSITORY="${OSTK_DATA_LOCAL_CACHE}/data"

RUN git clone --branch v1 --single-branch --depth=1 https://github.com/open-space-collective/open-space-toolkit-data.git ${OSTK_DATA_LOCAL_CACHE} && chmod -R g+w ${OSTK_DATA_LOCAL_CACHE}

# Labels

ARG VERSION
ENV VERSION="${VERSION}"
LABEL VERSION="${VERSION}"

# Development image for humans (non-root user)

FROM root-user AS non-root-user

# Install dev utilities

RUN apt-get update \
    && apt-get install -y zsh sudo \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user and group

ARG USERNAME="developer"
ARG USER_UID="1000"
ARG USER_GID=${USER_UID}
RUN groupadd --gid ${USER_GID} ${USERNAME} || true \
    && adduser --uid ${USER_UID} --gid ${USER_GID} ${USERNAME} \
    && echo "${USERNAME} ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers.d/${USERNAME}

# Change ownership of OSTK_DATA_LOCAL_CACHE

RUN chown -R ${USERNAME}:${USERNAME} ${OSTK_DATA_LOCAL_CACHE}

# Use non-root user

USER ${USERNAME}

# Install shell utilities

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" \
    && git clone https://github.com/bhilburn/powerlevel9k.git /home/${USERNAME}/.oh-my-zsh/custom/themes/powerlevel9k \
    && git clone https://github.com/zsh-users/zsh-autosuggestions /home/${USERNAME}/.oh-my-zsh/custom/plugins/zsh-autosuggestions \
    && git clone https://github.com/zsh-users/zsh-syntax-highlighting.git /home/${USERNAME}/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting \
    && mkdir -p /home/${USERNAME}/.vscode-server/extensions /home/${USERNAME}/.vscode-server-insiders/extensions

## Configure environment

ENV PATH="/home/${USERNAME}/.local/bin:${PATH}"

# Entrypoint

CMD [ "/bin/bash" ]
