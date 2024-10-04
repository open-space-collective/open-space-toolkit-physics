# Open Space Toolkit ▸ Physics

[![Build and Test](https://github.com/open-space-collective/open-space-toolkit-physics/actions/workflows/build-test.yml/badge.svg?branch=main)](https://github.com/open-space-collective/open-space-toolkit-physics/actions/workflows/build-test.yml)
[![Release](https://github.com/open-space-collective/open-space-toolkit-physics/actions/workflows/release.yml/badge.svg)](https://github.com/open-space-collective/open-space-toolkit-physics/actions/workflows/release.yml)
[![Code Coverage](https://codecov.io/gh/open-space-collective/open-space-toolkit-physics/branch/main/graph/badge.svg)](https://codecov.io/gh/open-space-collective/open-space-toolkit-physics)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/open-space-toolkit-physics)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-physics.svg)](https://badge.fury.io/gh/open-space-collective%2Fopen-space-toolkit-physics)
[![PyPI version](https://badge.fury.io/py/open-space-toolkit-physics.svg)](https://badge.fury.io/py/open-space-toolkit-physics)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Physical units, time, reference frames, environment modeling.

<img src="./docs/assets/gravitational-anomaly.png" height="500px" width="auto">

*Gravitational field anomaly between EGM96 and WGS84 models.*

## Getting Started

Want to get started? This is the simplest and quickest way:

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/open-space-collective/open-space-toolkit/main?urlpath=lab/tree/notebooks)

*Nothing to download or install! This will automatically start a [JupyterLab](https://jupyterlab.readthedocs.io/en/stable/) environment in your browser with Open Space Toolkit libraries and example notebooks ready to use.*

### Alternatives

#### Docker Images

[Docker](https://www.docker.com/) must be installed on your system.

##### iPython

The following command will start an [iPython](https://ipython.org/) shell within a container where the OSTk components are already installed:

```bash
docker run -it openspacecollective/open-space-toolkit-physics-python
```

Once the shell is up and running, playing with it is easy:

```py
from ostk.physics import Environment # Environment modeling class
from ostk.physics.time import Instant # Instant class
from ostk.physics.coordinate import Frame # Reference frame class

environment = Environment.default(set_global=True) # Bootstrap a default environment, and set it as the global environment

moon = environment.access_object_with_name('Moon') # Access Moon

instant = Instant.now()

moon.get_position_in(Frame.ITRF(), instant) # Position of the Moon in ITRF
moon.get_axes_in(Frame.ITRF(), instant) # Axes of the Moon in ITRF
```

By default, OSTk fetches the ephemeris from JPL, Earth Orientation Parameters (EOP) and leap second count from IERS.

As a result, when running OSTk for the first time, it may take a minute to fetch all the necessary data.

*Tip: Use tab for auto-completion!*

##### JupyterLab

The following command will start a [JupyterLab](https://jupyterlab.readthedocs.io/en/stable/) server within a container where the OSTk components are already installed:

```bash
docker run --publish=8888:8888 openspacecollective/open-space-toolkit-physics-jupyter
```

Once the container is running, access [http://localhost:8888/lab](http://localhost:8888/lab) and create a Python 3 Notebook.

## Installation

### C++

The binary packages are hosted using [GitHub Releases](https://github.com/open-space-collective/open-space-toolkit-physics/releases):

- Runtime libraries: `open-space-toolkit-physics-X.Y.Z-1.x86_64-runtime`
- C++ headers: `open-space-toolkit-physics-X.Y.Z-1.x86_64-devel`
- Python bindings: `open-space-toolkit-physics-X.Y.Z-1.x86_64-python`

#### Debian / Ubuntu

After downloading the relevant `.deb` binary packages, install:

```bash
apt install open-space-toolkit-physics-*.deb
```

### Python

Install from [PyPI](https://pypi.org/project/open-space-toolkit-physics/):

```bash
pip install open-space-toolkit-physics
```

## Documentation

Documentation is available [here](https://open-space-collective.github.io/open-space-toolkit-physics/):

<details>
<summary>Structure</summary>
<p>

The library exhibits the following structure:

```txt
├── Unit
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
    ├── Constant
    ├── Object
    │   └── Celestial
    ├── Ephemeris
    │   ├── Analytical
    │   ├── Tabulated
    │   └── SPICE (JPL)
    ├── Gravity
    │   ├── Barycentric
    │   ├── Earth Gravitational Model 1996 (EGM96)
    │   └── Earth Gravitational Model 2008 (EGM2008)
    ├── Atmospheric
    │   ├── Exponential
    │   └── NRLMSISE00
    └── Magnetic
        ├── Dipole
        ├── World Magnetic Model 2010 (WMM2010)
        ├── World Magnetic Model 2015 (WMM2015)
        ├── Enhanced Magnetic Model 2010 (EMM2010)
        ├── Enhanced Magnetic Model 2015 (EMM2015)
        ├── International Geomagnetic Reference Field 11 (IGRF11)
        └── International Geomagnetic Reference Field 12 (IGRF12)
```

</p>
</details>

## Data Management

OSTk Physics uses input data from various sources to determine the state of the space environment at any given time. The following input data is used:

- IERS Reference Frame Data
- CSSI Solar Flux/Space Weather Data
- Gravitational Survey Data
- Magnetic Survey Data
- SPICE Kernels

None of these files are shipped with the source code of this library. OSTk Physics has the capability to fetch the required files at runtime if they are not present or if they are outdated. This is done using file Manager classes (see any file named `Manager.hpp`). Data for any use-case is queried through the Manager class rather than directly, which allows the Manager to handle file loading and fetching.
The managers have two modes, which can be configured via environment variables (explained below).
- `Automatic`: Will load the data from the provided directories, if the data does not exist it will be fetched.
- `Manual`: Will load the data from the provided directories, if the data does not exist it will raise an error.

If you would like to seed the ostk data generation so that you already have an initial copy of all the data files (to avoid a large initial fetch at runtime), then we recommend running the following commands to set up your environment.
```
# Set the environment variable for OSTk Data location
export OSTK_DATA_LOCAL_CACHE=/path/to/preferred/data/storage/dir
export OSTK_PHYSICS_DATA_LOCAL_REPOSITORY=$OSTK_DATA_LOCAL_CACHE/data

# Clone OSTk data repo into that dir
RUN git clone --branch v1 --single-branch --depth=1 https://github.com/open-space-collective/open-space-toolkit-data.git $OSTK_DATA_LOCAL_CACHE && chmod -R g+w $OSTK_DATA_LOCAL_CACHE
```

For users that are installing OSTk into docker images, here is what we recommend you add to your dockerfiles.
```
ARG OSTK_DATA_LOCAL_CACHE="/var/cache/open-space-toolkit-data"
ENV OSTK_DATA_LOCAL_CACHE="${OSTK_DATA_LOCAL_CACHE}"
ENV OSTK_PHYSICS_DATA_LOCAL_REPOSITORY="${OSTK_DATA_LOCAL_CACHE}/data"

RUN git clone --branch v1 --single-branch --depth=1 https://github.com/open-space-collective/open-space-toolkit-data.git ${OSTK_DATA_LOCAL_CACHE} && chmod -R g+w ${OSTK_DATA_LOCAL_CACHE}

# Add the line below if the container's user will not be root
RUN chown -R ${USER_UID}:${USER_GID} ${OSTK_DATA_LOCAL_CACHE}
```
If you have a multi-stage dockerfile, then you can easily just copy the ostk-data repo install from one build stage (in the example below that's `build-env`) to the next, so that you don't have to reinstall it on every build stage.
```
# If you are copying to an image where the user is currently root
COPY --from=build-env ${OSTK_DATA_LOCAL_CACHE} ${OSTK_DATA_LOCAL_CACHE}
# Or if you are copying to an image where the user is not currently root
COPY --from=build-env --chown=${USER_UID}:${USER_GID} ${OSTK_DATA_LOCAL_CACHE} ${OSTK_DATA_LOCAL_CACHE}
```

The following table shows the availabe data source settings with the different environment variables you can set:

| Environment Variable                                                                   | Default Value                                                                                            |
| -------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| `OSTK_PHYSICS_DATA_LOCAL_REPOSITORY`                                                 | `./.open-space-toolkit/physics/data` [Bulk setting. Overridden by specific repository settings below.] |
| `OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_MODE`                           | `Automatic`                                                                                            |
| `OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY`               | `./.open-space-toolkit/physics/data/coordinate/frame/provider/iers`                                    |
| `OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT`  | `60`                                                                                                   |
| `OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_ENGINE_MODE`                               | `Automatic`                                                                                            |
| `OSTK_PHYSICS_ENVIRONMENT_EPHEMERIS_SPICE_MANAGER_LOCAL_REPOSITORY`                  | `./.open-space-toolkit/physics/data/environment/ephemeris/spice`                                       |
| `OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_MODE`                          | `Automatic`                                                                                            |
| `OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY`              | `./.open-space-toolkit/physics/data/environment/gravitational/earth`                                   |
| `OSTK_PHYSICS_ENVIRONMENT_GRAVITATIONAL_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT` | `60`                                                                                                   |
| `OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_MODE`                               | `Automatic`                                                                                            |
| `OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY`                   | `./.open-space-toolkit/physics/data/environment/magnetic/earth`                                        |
| `OSTK_PHYSICS_ENVIRONMENT_MAGNETIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT`      | `60`                                                                                                   |
| `OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE`                            | `Automatic`                                                                                            |
| `OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY`                | `./.open-space-toolkit/physics/data/environment/atmospheric/earth`                                     |
| `OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY_LOCK_TIMEOUT`   | `60`                                                                                                   |
| `OSTK_PHYSICS_DATA_REMOTE_URL`                                                       | `https://github.com/open-space-collective/open-space-toolkit-data/raw/v1/data/`                        |
| `OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY`                                        | `./.open-space-toolkit/physics/data/`                                                                  |
| `OSTK_PHYSICS_DATA_MANIFEST_LOCAL_REPOSITORY_LOCK_TIMEOUT`                           | `60`                                                                                                   |

## Tutorials

Tutorials are available here:

- [C++](./tutorials/cpp)
- [Python](./tutorials/python)

## Setup

### Development Environment

Using [Docker](https://www.docker.com) for development is recommended, to simplify the installation of the necessary build tools and dependencies.
Instructions on how to install Docker are available [here](https://docs.docker.com/install/).

To start the development environment:

```bash
make dev
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

*Tip: The `ostk-build` command simplifies building from within the development environment.*

### Test

To start a container to build and run the tests:

```bash
make test
```

Or to run them manually:

```bash
./bin/open-space-toolkit-physics.test
```

*Tip: The `ostk-test` command simplifies running tests from within the development environment.*

## Dependencies

| Name          | Version        | License                                                 | Link                                                                                                                                    |
| ------------- | -------------- | ------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| Pybind11      | `2.10.1`     | BSD-3-Clause                                            | [github.com/pybind/pybind11](https://github.com/pybind/pybind11)                                                                           |
| {fmt}         | `5.2.0`      | BSD-2-Clause                                            | [github.com/fmtlib/fmt](https://github.com/fmtlib/fmt)                                                                                     |
| ordered-map   | `0.6.0`      | MIT                                                     | [github.com/Tessil/ordered-map](https://github.com/Tessil/ordered-map)                                                                     |
| Eigen         | `3.3.7`      | MPL2                                                    | [eigen.tuxfamily.org](http://eigen.tuxfamily.org/index.php)                                                                                |
| IAU SOFA      | `2018-01-30` | [SOFA Software License](http://www.iausofa.org/tandc.html) | [www.iausofa.org](http://www.iausofa.org)                                                                                                  |
| SPICE Toolkit | `N0067`      | [NAIF](https://naif.jpl.nasa.gov/naif/rules.html)          | [naif.jpl.nasa.gov/naif/toolkit.html](https://naif.jpl.nasa.gov/naif/toolkit.html)                                                         |
| GeographicLib | `1.52`       | MIT                                                     | [geographiclib.sourceforge.io](https://geographiclib.sourceforge.io)                                                                       |
| Core          | `main`       | Apache License 2.0                                      | [github.com/open-space-collective/open-space-toolkit-core](https://github.com/open-space-collective/open-space-toolkit-core)               |
| I/O           | `main`       | Apache License 2.0                                      | [github.com/open-space-collective/open-space-toolkit-io](https://github.com/open-space-collective/open-space-toolkit-io)                   |
| Mathematics   | `main`       | Apache License 2.0                                      | [github.com/open-space-collective/open-space-toolkit-mathematics](https://github.com/open-space-collective/open-space-toolkit-mathematics) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

[![Loft Orbital](https://github.com/open-space-collective/open-space-toolkit/blob/main/assets/thanks/loft_orbital.png)](https://www.loftorbital.com/)

## License

Apache License 2.0
