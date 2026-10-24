#!/usr/bin/env bash

# Apache License 2.0

# Install the CSPICE toolkit into ${INSTALL_PREFIX}.

set -euo pipefail

prefix="${INSTALL_PREFIX:-/usr/local}"

if [[ -n "${TARGETPLATFORM:-}" ]]; then
    case "${TARGETPLATFORM}" in
        linux/amd64) package_platform="PC_Linux_GCC_64bit" ;;
        linux/arm64) package_platform="MacM1_OSX_clang_64bit" ;;
        *)
            echo "Unsupported TARGETPLATFORM for CSPICE: ${TARGETPLATFORM}"
            exit 1
            ;;
    esac
else
    case "$(uname -s)-$(uname -m)" in
        Darwin-arm64) package_platform="MacM1_OSX_clang_64bit" ;;
        Linux-x86_64) package_platform="PC_Linux_GCC_64bit" ;;
        Linux-aarch64) package_platform="MacM1_OSX_clang_64bit" ;;
        *)
            echo "Unsupported platform for CSPICE: $(uname -s) $(uname -m)"
            exit 1
            ;;
    esac
fi

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

archive="${source_dir}/cspice.tar.Z"
url="https://naif.jpl.nasa.gov/pub/naif/toolkit/C/${package_platform}/packages/cspice.tar.Z"
curl -fsSL "${url}" -o "${archive}"
tar -xf "${archive}" -C "${source_dir}"

if [[ "$(uname -s)" != "Darwin" ]]; then
    extra_packages=""
    if [[ "${package_platform}" == "MacM1_OSX_clang_64bit" ]]; then
        extra_packages="clang-18"
    fi
    apt-get update
    apt-get install -y csh ${extra_packages}
    if [[ -n "${extra_packages}" ]]; then
        ln -sfn /usr/bin/clang-18 /usr/local/bin/clang
    fi
    (cd "${source_dir}/cspice" && ./makeall.csh >/dev/null)
    apt-get remove -y csh ${extra_packages}
    rm -rf /var/lib/apt/lists/*
fi

mkdir -p "${prefix}/include/cspice" "${prefix}/lib"
cp -R "${source_dir}/cspice/include/." "${prefix}/include/cspice/"
cp -R "${source_dir}/cspice/lib/." "${prefix}/lib/"
ln -sfn cspice.a "${prefix}/lib/libcspice.a"
