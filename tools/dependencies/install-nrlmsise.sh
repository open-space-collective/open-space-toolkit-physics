#!/usr/bin/env bash

# Apache License 2.0

# Build and install NRLMSISE-00 into ${INSTALL_PREFIX}.

set -euo pipefail

NRLMSISE00_MODEL_COMMIT="a5f81be"
prefix="${INSTALL_PREFIX:-/usr/local}"

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

git clone https://github.com/magnific0/nrlmsise-00.git "${source_dir}"
git -C "${source_dir}" checkout "${NRLMSISE00_MODEL_COMMIT}"

cmake -S "${source_dir}" -B "${source_dir}/build" \
    -DCMAKE_BUILD_TYPE=Release \
    -DNRLMSISE00_WITH_TESTS=OFF \
    -DCMAKE_C_FLAGS="-fPIC" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
cmake --build "${source_dir}/build" --parallel "$(getconf _NPROCESSORS_ONLN)"

mkdir -p "${prefix}/include/NRLMSISE-00" "${prefix}/lib"
cp "${source_dir}/nrlmsise-00.h" "${prefix}/include/NRLMSISE-00/"
cp "${source_dir}/lib/libnrlmsise00.a" "${prefix}/lib/"
