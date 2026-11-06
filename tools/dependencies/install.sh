#!/usr/bin/env bash

# Apache License 2.0

# Install all dependencies into ${INSTALL_PREFIX}.

set -euo pipefail

dependencies_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

"${dependencies_dir}/install-fmt.sh"
"${dependencies_dir}/install-ordered-map.sh"
"${dependencies_dir}/install-nrlmsise.sh"
"${dependencies_dir}/install-eigen.sh"
"${dependencies_dir}/install-sofa.sh"
"${dependencies_dir}/install-cspice.sh"
"${dependencies_dir}/install-geographiclib.sh"
