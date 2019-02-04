Library ▸ Physics
=================

Physical units, time, reference frames, environment modeling.

[![Build Status](https://travis-ci.com/open-space-collective/library-physics.svg?branch=master)](https://travis-ci.com/open-space-collective/library-physics)
[![Code Coverage](https://codecov.io/gh/open-space-collective/library-physics/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/library-physics)
[![Documentation](https://img.shields.io/readthedocs/pip/stable.svg)](https://open-space-collective.github.io/library-physics)
[![GitHub version](https://badge.fury.io/gh/open-space-collective%2Flibrary-physics.svg)](https://badge.fury.io/gh/open-space-collective%2Flibrary-physics)
[![PyPI version](https://badge.fury.io/py/LibraryPhysicsPy.svg)](https://badge.fury.io/py/LibraryPhysicsPy)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Warning

Library **name** is yet to be defined.

Please check the following projects:

- [Naming Project](https://github.com/orgs/open-space-collective/projects/1)

*⚠ This library is still under heavy development. Do not use!*

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

The documentation can be found here:

- [C++](https://open-space-collective.github.io/library-physics)
- [Python](./bindings/python/docs)

## Tutorials

Various tutorials are available here:

- [C++](./tutorials/cpp)
- [Python](./tutorials/python)

## Setup

### Development

Using [Docker](https://www.docker.com) is recommended, as the development tools and dependencies setup is described in the provided [Dockerfile](./tools/development/docker/Dockerfile).

Instructions to install Docker can be found [here](https://docs.docker.com/install/).

Start the development environment:

```bash
./tools/development/start.sh
```

This will also build the `openspacecollective/library-physics:latest` Docker image, if not already.

If installing Docker is not an option, please manually install the development tools (GCC, CMake) and the dependencies.
The procedure should be similar to the one described in the [Dockerfile](./tools/development/docker/Dockerfile).

### Build

From the development environment:

```bash
./build.sh
```

Manually:

```bash
mkdir -p build
cd build
cmake ..
make
```

### Test

From the development environment:

```bash
./test.sh
```

Manually:

```bash
./bin/library-physics.test
```

## Dependencies

The **Physics** library internally uses the following dependencies:

| Name          | Version    | License                                                    | Link                                                                                                                 |
|---------------|------------|------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------|
| Boost         | 1.67.0     | Boost Software License                                     | [boost.org](https://www.boost.org)                                                                                   |
| Eigen         | 3.3.4      | MPL2                                                       | [eigen.tuxfamily.org](http://eigen.tuxfamily.org/index.php)                                                          |
| IAU SOFA      | 2018-01-30 | [SOFA Software License](http://www.iausofa.org/tandc.html) | [www.iausofa.org](http://www.iausofa.org)                                                                            |
| SPICE Toolkit | N0066      | [NAIF](https://naif.jpl.nasa.gov/naif/rules.html)          | [naif.jpl.nasa.gov/naif/toolkit.html](https://naif.jpl.nasa.gov/naif/toolkit.html)                                   |
| GeographicLib | 1.49       | MIT                                                        | [geographiclib.sourceforge.io](https://geographiclib.sourceforge.io)                                                 |
| Core          | master     | Apache License 2.0                                         | [github.com/open-space-collective/library-core](https://github.com/open-space-collective/library-core)               |
| I/O           | master     | Apache License 2.0                                         | [github.com/open-space-collective/library-io](https://github.com/open-space-collective/library-io)                   |
| Mathematics   | master     | Apache License 2.0                                         | [github.com/open-space-collective/library-mathematics](https://github.com/open-space-collective/library-mathematics) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

Apache License 2.0