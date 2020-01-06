# Open Space Toolkit ▸ Physics

[![Build Status](https://travis-ci.com/open-space-collective/open-space-toolkit-physics.svg?branch=master)](https://travis-ci.com/open-space-collective/open-space-toolkit-physics)
[![Code Coverage](https://codecov.io/gh/open-space-collective/open-space-toolkit-physics/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/open-space-toolkit-physics)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/open-space-toolkit-physics)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-physics.svg)](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-physics)
[![PyPI version](https://badge.fury.io/py/open-space-toolkit-physics.svg)](https://badge.fury.io/py/open-space-toolkit-physics)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Physical units, time, reference frames, environment modeling.

## Warning

*⚠ This component is under development.*

## Installation

### C++

The binary packages are hosted using [GitHub Releases](https://github.com/open-space-collective/open-space-toolkit-physics/releases).

*Note: Don't forget to set the desired version number in the URLs!*

#### Debian / Ubuntu

```bash
# Download .deb packages

wget https://github.com/open-space-collective/open-space-toolkit-physics/releases/download/0.4.0/open-space-toolkit-physics-0.4.0-1.x86_64-runtime.deb
wget https://github.com/open-space-collective/open-space-toolkit-physics/releases/download/0.4.0/open-space-toolkit-physics-0.4.0-1.x86_64-devel.deb

# Install .deb packages

apt install -y open-space-toolkit-physics-0.4.0-*.deb
```

#### Fedora / CentOS

```bash
# Download .rpm packages

wget https://github.com/open-space-collective/open-space-toolkit-physics/releases/download/0.4.0/open-space-toolkit-physics-0.4.0-1.x86_64-runtime.rpm
wget https://github.com/open-space-collective/open-space-toolkit-physics/releases/download/0.4.0/open-space-toolkit-physics-0.4.0-1.x86_64-devel.rpm

# Install .rpm packages

dnf install -y open-space-toolkit-physics-0.4.0-*.rpm
```

### Python

The binary packages are hosted on [PyPI](https://pypi.org/project/open-space-toolkit-physics/):

```bash
pip install open-space-toolkit-physics
```

## Getting Started

Want to quickly get started? It's pretty simple.

Install [Docker](https://www.docker.com/) and try this:

```bash
docker run -it openspacecollective/open-space-toolkit-physics-python
```

This will start an [iPython](https://ipython.org/) shell within a container where the OSTk Physics component is already installed.

Once the shell is up and running, playing with it is easy:

```py
from ostk.physics import Environment # Environment modeling class
from ostk.physics.time import Instant # Instant class
from ostk.physics.coordinate import Frame # Reference frame class

environment = Environment.default() # Bootstrap a default environment

moon = environment.access_object_with_name('Moon') # Access Moon

environment.set_instant(Instant.now()) # Set environment to present time

moon.get_position_in(Frame.ITRF()) # Position of the Moon in ITRF
moon.get_axes_in(Frame.ITRF()) # Axes of the Moon in ITRF
```

*Tip: Use tab for auto-completion!*

## Structure

The **Physics** library exhibits the following structure:

```txt
├── Units
│   ├── Length
│   ├── Mass
│   ├── Time
│   ├── Temperature
│   ├── Electric Current
│   ├── Luminous Intensity
│   └── Derived
│       ├── Angle
│       ├── Solid Angle
│       ├── Frequency
│       ├── Force
│       ├── Pressure
│       ├── Area
│       ├── Volume
│       └── Information
├── Time
│   ├── Scale (UTC, TT, TAI, UT1, TCG, TCB, TDB, GMST, GPST, GST, GLST, BDT, QZSST, IRNSST)
│   ├── Instant
│   ├── Duration
│   ├── Interval
│   ├── Date
│   ├── Time
│   └── DateTime
├── Coordinate
│   ├── Transform
│   └── Frame (ECI, ECEF, NED, LVLHGD, LVLHGDGT, ...)
├── Geographic
│   ├── Position
│   ├── Area
│   ├── Volume
│   ├── Coordinate Reference System (CRS)
│   └── Universal Transverse Mercator (UTM)
└── Environment
    ├── Constants
    ├── Object
    │   └── Celestial
    ├── Ephemerides
    │   ├── Analytical
    │   ├── Tabulated
    │   ├── SOFA
    │   └── SPICE (JPL)
    ├── Gravity
    │   ├── Barycentric
    │   ├── Earth Gravitational Model 1996 (EGM96)
    │   └── Earth Gravitational Model 2008 (EGM2008)
    ├── Atmospheric
    │   ├── Exponential
    │   ├── USSA1976
    │   ├── Jacchia Roberts
    │   └── NRLMSISE00
    ├── Magnetic
    │   ├── Dipole
    │   ├── World Magnetic Model 2010 (WMM2010)
    │   ├── World Magnetic Model 2015 (WMM2015)
    │   ├── Enhanced Magnetic Model 2010 (EMM2010)
    │   ├── Enhanced Magnetic Model 2015 (EMM2015)
    │   ├── International Geomagnetic Reference Field 11 (IGRF11)
    │   └── International Geomagnetic Reference Field 12 (IGRF12)
    ├── Radiation
    │   └── Sun Static
    └── Stars
        └── Hipparcos
```

## Documentation

Documentation is available here:

- [C++](https://open-space-collective.github.io/open-space-toolkit-physics)
- [Python](./bindings/python/docs)

## Tutorials

Tutorials are available here:

- [C++](./tutorials/cpp)
- [Python](./tutorials/python)

## Settings

The following environment variables can be set:

| Environment Variable                                                                    | Default Value                                                            |
| --------------------------------------------------------------------------------------- | ------------------------------------------------------------------------ |
| `LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE`                          | `Manual`                                                                 |
| `LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY`              | `./.open-space-toolkit/physics/coordinate/frame/providers/iers`          |
| `LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT` | `60`                                                                     |
| `LIBRARY_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_REMOTE_URL`                    | `ftp://cddis.gsfc.nasa.gov/pub/products/iers/`                           |
| `LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_ENGINE_MODE`                             | `Manual`                                                                 |
| `LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_LOCAL_REPOSITORY`                | `./.open-space-toolkit/physics/environment/ephemerides/spice`            |
| `LIBRARY_PHYSICS_ENVIRONMENT_EPHEMERIDES_SPICE_MANAGER_REMOTE_URL`                      | `https://naif.jpl.nasa.gov/pub/naif/generic_kernels/`                    |
| `LIBRARY_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_ENABLED`                       | `false`                                                                  |
| `LIBRARY_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY`              | `./.open-space-toolkit/physics/environment/gravitational/earth`          |
| `LIBRARY_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_REMOTE_URL`                    | `https://sourceforge.net/projects/geographiclib/files/gravity-distrib/`  |
| `LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_ENABLED`                            | `false`                                                                  |
| `LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY`                   | `./.open-space-toolkit/physics/environment/magnetic/earth`               |
| `LIBRARY_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_REMOTE_URL`                         | `https://sourceforge.net/projects/geographiclib/files/magnetic-distrib/` |

## Setup

### Development Environment

Using [Docker](https://www.docker.com) for development is recommended, to simplify the installation of the necessary build tools and dependencies.
Instructions on how to install Docker are available [here](https://docs.docker.com/install/).

To start the development environment:

```bash
make start-development
```

This will:

1. Build the `openspacecollective/open-space-toolkit-physics-development` Docker image.
2. Create a development environment container with local source files and helper scripts mounted.
3. Start a `bash` shell from the `./build` working directory.

If installing Docker is not an option, you can manually install the development tools (GCC, CMake) and all required dependencies,
by following a procedure similar to the one described in the [Development Dockerfile](./docker/development/Dockerfile).

### Build

From the `./build` directory:

```bash
cmake ..
make
```

*Tip: `helpers/build.sh` simplifies building from within the development environment.*

### Test

To start a container to build and run the tests:

```bash
make test
```

Or to run them manually:

```bash
./bin/open-space-toolkit-physics.test
```

*Tip: `helpers/test.sh` simplifies running tests from within the development environment.*

## Dependencies

| Name          | Version    | License                                                    | Link                                                                                                                                       |
| ------------- | ---------- | ---------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------                       |
| Boost         | 1.69.0     | Boost Software License                                     | [boost.org](https://www.boost.org)                                                                                                         |
| Eigen         | 3.3.7      | MPL2                                                       | [eigen.tuxfamily.org](http://eigen.tuxfamily.org/index.php)                                                                                |
| IAU SOFA      | 2018-01-30 | [SOFA Software License](http://www.iausofa.org/tandc.html) | [www.iausofa.org](http://www.iausofa.org)                                                                                                  |
| SPICE Toolkit | N0066      | [NAIF](https://naif.jpl.nasa.gov/naif/rules.html)          | [naif.jpl.nasa.gov/naif/toolkit.html](https://naif.jpl.nasa.gov/naif/toolkit.html)                                                         |
| GeographicLib | 1.49       | MIT                                                        | [geographiclib.sourceforge.io](https://geographiclib.sourceforge.io)                                                                       |
| Core          | master     | Apache License 2.0                                         | [github.com/open-space-collective/open-space-toolkit-core](https://github.com/open-space-collective/open-space-toolkit-core)               |
| I/O           | master     | Apache License 2.0                                         | [github.com/open-space-collective/open-space-toolkit-io](https://github.com/open-space-collective/open-space-toolkit-io)                   |
| Mathematics   | master     | Apache License 2.0                                         | [github.com/open-space-collective/open-space-toolkit-mathematics](https://github.com/open-space-collective/open-space-toolkit-mathematics) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

Apache License 2.0
