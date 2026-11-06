#!/usr/bin/env bash

# Apache License 2.0

# Build and install IAU SOFA into ${INSTALL_PREFIX}.

set -euo pipefail

IAU_SOFA_VERSION="20231011"
prefix="${INSTALL_PREFIX:-/usr/local}"

source_dir="$(mktemp -d)"
trap 'rm -rf "${source_dir}"' EXIT

archive="${source_dir}/sofa.tar.gz"
url="http://www.iausofa.org/s/sofa_c-${IAU_SOFA_VERSION}tar.gz"
if command -v curl >/dev/null 2>&1; then
    curl -fsSL "${url}" -o "${archive}"
elif command -v wget >/dev/null 2>&1; then
    wget --quiet "${url}" -O "${archive}"
else
    echo "curl or wget is required to download SOFA."
    exit 1
fi
tar -xzf "${archive}" -C "${source_dir}"

sofa_src="${source_dir}/sofa/${IAU_SOFA_VERSION}/c/src"
python3 - "${sofa_src}/makefile" <<'PY'
import pathlib, sys
path = pathlib.Path(sys.argv[1])
text = path.read_text()
old = "CFLAGF = -c -pedantic -Wall -O"
new = "CFLAGF = -c -pedantic -Wall -O -fPIC"
if old not in text:
    raise SystemExit(f"Could not find SOFA compile flags in {path}")
path.write_text(text.replace(old, new, 1))
PY
make -C "${sofa_src}" --jobs "$(getconf _NPROCESSORS_ONLN)"

mkdir -p "${prefix}/include/sofa" "${prefix}/lib"
cp "${sofa_src}/"*.h "${prefix}/include/sofa/"
cp "${sofa_src}/"*.a "${prefix}/lib/"
