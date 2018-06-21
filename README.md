Library :: Physics
==================

Physical units, time, reference frames, environment modeling.

[![Build Status](https://travis-ci.com/open-space-collective/library-physics.svg?branch=master)](https://travis-ci.com/open-space-collective/library-physics)
[![Code Coverage](https://codecov.io/gh/open-space-collective/library-physics/branch/master/graph/badge.svg)](https://codecov.io/gh/open-space-collective/library-physics)
[![Documentation](https://readthedocs.org/projects/docs/badge/?version=latest)](https://open-space-collective.github.io/library-physics)

## Warning

Library **name** and **license** are yet to be defined.

Please check the following projects:

- [Naming Project](https://github.com/orgs/open-space-collective/projects/1)
- [Licensing Project](https://github.com/orgs/open-space-collective/projects/2)

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
    │   └── Celestial Body
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

The documentation can be found [here](https://open-space-collective.github.io/library-physics).

## Setup

### Development

Using [Docker](https://www.docker.com) is recommended, as the development tools and dependencies setup is described in the provided [Dockerfile](./tools/development/docker/Dockerfile).

Instructions to install Docker can be found [here](https://docs.docker.com/install/).

Start the development environment:

```bash
./tools/development/start.sh
```

This will also build the `openspacecollective/library-physics:latest` Docker image, if not present already.

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

| Name        | Version | License                | Link                                                                                                                 |
|-------------|---------|------------------------|----------------------------------------------------------------------------------------------------------------------|
| Boost       | 1.67.0  | Boost Software License | [boost.org](https://www.boost.org)                                                                                   |
| Eigen       | 3.3.4   | MPL2                   | [eigen.tuxfamily.org](http://eigen.tuxfamily.org/index.php)                                                          |
| Core        | master  | TBD                    | [github.com/open-space-collective/library-core](https://github.com/open-space-collective/library-core)               |
| Mathematics | master  | TBD                    | [github.com/open-space-collective/library-mathematics](https://github.com/open-space-collective/library-mathematics) |

## Contribution

Contributions are more than welcome!

Please read our [contributing guide](CONTRIBUTING.md) to learn about our development process, how to propose fixes and improvements, and how to build and test the code.

## Special Thanks

*To be completed...*

## License

*To be defined...*