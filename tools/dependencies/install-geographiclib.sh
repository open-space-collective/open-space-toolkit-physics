#!/usr/bin/env bash

# Apache License 2.0

# Build and install GeographicLib as a static library into ${INSTALL_PREFIX}.

set -euo pipefail

GEOGRAPHIC_LIB_VERSION="1.52"
prefix="${INSTALL_PREFIX:-/usr/local}"

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

if command -v apt-get >/dev/null 2>&1; then
    apt-get update
    apt-get install -y libproj-dev
    rm -rf /var/lib/apt/lists/*
fi

git clone --branch "r${GEOGRAPHIC_LIB_VERSION}" --depth 1 https://github.com/geographiclib/geographiclib.git "${source_dir}"

cmake -S "${source_dir}" -B "${source_dir}/build" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX="${prefix}" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DGEOGRAPHICLIB_LIB_TYPE=STATIC
cmake --build "${source_dir}/build" --parallel "$(getconf _NPROCESSORS_ONLN)"
cmake --install "${source_dir}/build"
