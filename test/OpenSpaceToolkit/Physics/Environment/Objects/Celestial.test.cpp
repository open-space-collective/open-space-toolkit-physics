/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Map.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Weak.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/Analytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Mass.hpp>

#include <Global.test.hpp>

using ostk::core::type::Shared;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::Unit;
using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using ostk::physics::unit::Time;
using ostk::physics::unit::Mass;
using ostk::physics::unit::Derived;
using ostk::physics::data::Vector;
using ostk::physics::data::Scalar;
using ostk::physics::time::Instant;
using ostk::physics::coord::Frame;
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::environment::object::Celestial;
using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::ephemeris::Analytical;
using GravitationalModel = ostk::physics::environment::gravitational::Model;
using MagneticModel = ostk::physics::environment::magnetic::Model;
using AtmosphericModel = ostk::physics::environment::atmospheric::Model;
using ostk::physics::environment::gravitational::Spherical;
using ostk::physics::environment::magnetic::Dipole;
using ostk::physics::environment::atmospheric::earth::Exponential;
using EarthCelestial = ostk::physics::environment::object::celestial::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;
using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;

// TEST (OpenSpaceToolkit_Physics_Environment_Object_Celestial, Constructor)
// {

//     using ostk::physics::environment::Object ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial, accessModel)
{
    const String name = "Some Planet";
    const Celestial::Type type = Celestial::Type::Earth;
    const Derived gravitationalParameter = {
        1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
    };
    const Length equatorialRadius = Length::Kilometers(1000.0);
    const Real flattening = 0.0;
    const Real j2 = 0.0;
    const Real j4 = 0.0;

    const EarthGravitationalModel::Parameters gravitationalModelParameters = {
        gravitationalParameter, equatorialRadius, flattening, j2, j4
    };

    const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());
    {
        const Celestial celestial = {
            name, type, gravitationalParameter, equatorialRadius, flattening, j2, j4, nullptr, nullptr, nullptr, nullptr
        };

        EXPECT_ANY_THROW(celestial.accessGravitationalModel());
        EXPECT_ANY_THROW(celestial.accessMagneticModel());
        EXPECT_ANY_THROW(celestial.accessAtmosphericModel());
    }

    {
        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            ephemeris,
            nullptr,
            nullptr,
            nullptr
        };

        EXPECT_EQ(celestial.accessGravitationalModel(), nullptr);
        EXPECT_EQ(celestial.accessMagneticModel(), nullptr);
        EXPECT_EQ(celestial.accessAtmosphericModel(), nullptr);
    }

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel =
            std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Exponential);

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            ephemeris,
            gravitationalModel,
            magneticModel,
            atmosphericModel
        };

        EXPECT_NO_THROW(celestial.accessGravitationalModel());
        EXPECT_NO_THROW(celestial.accessMagneticModel());
        EXPECT_NO_THROW(celestial.accessAtmosphericModel());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial, modelIsDefined)
{
    const String name = "Some Planet";
    const Celestial::Type type = Celestial::Type::Earth;
    const Derived gravitationalParameter = {
        1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
    };
    const Length equatorialRadius = Length::Kilometers(1000.0);
    const Real flattening = 0.0;
    const Real j2 = 0.0;
    const Real j4 = 0.0;

    const EarthGravitationalModel::Parameters gravitationalModelParameters = {
        gravitationalParameter, equatorialRadius, flattening, j2, j4
    };

    const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel =
            std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Exponential);

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            ephemeris,
            nullptr,
            nullptr,
            nullptr
        };

        EXPECT_FALSE(celestial.gravitationalModelIsDefined());
        EXPECT_FALSE(celestial.magneticModelIsDefined());
        EXPECT_FALSE(celestial.atmosphericModelIsDefined());
    }

    {
        const Shared<GravitationalModel> undefinedGravitationalModel =
            std::make_shared<EarthGravitationalModel>(EarthGravitationalModel::Type::Undefined);
        const Shared<MagneticModel> undefinedMagneticModel =
            std::make_shared<EarthMagneticModel>(EarthMagneticModel::Type::Undefined);
        const Shared<AtmosphericModel> undefinedAtmosphericModel =
            std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Undefined);

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            ephemeris,
            undefinedGravitationalModel,
            undefinedMagneticModel,
            undefinedAtmosphericModel
        };

        EXPECT_FALSE(celestial.gravitationalModelIsDefined());
        EXPECT_FALSE(celestial.magneticModelIsDefined());
        EXPECT_FALSE(celestial.atmosphericModelIsDefined());
    }

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel =
            std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Exponential);

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            ephemeris,
            gravitationalModel,
            magneticModel,
            atmosphericModel
        };

        EXPECT_TRUE(celestial.gravitationalModelIsDefined());
        EXPECT_TRUE(celestial.magneticModelIsDefined());
        EXPECT_TRUE(celestial.atmosphericModelIsDefined());
    }

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel =
            std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Exponential);

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            nullptr,
            gravitationalModel,
            magneticModel,
            atmosphericModel
        };

        EXPECT_ANY_THROW(celestial.gravitationalModelIsDefined());
        EXPECT_ANY_THROW(celestial.magneticModelIsDefined());
        EXPECT_ANY_THROW(celestial.atmosphericModelIsDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial, GetGravitationalFieldAt)
{
    {
        const String name = "Some Planet";
        const Celestial::Type type = Celestial::Type::Earth;
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
        };
        const Length equatorialRadius = Length::Kilometers(1000.0);
        const Real flattening = 0.0;
        const Real j2 = 0.0;
        const Real j4 = 0.0;

        const EarthGravitationalModel::Parameters gravitationalModelParameters = {
            gravitationalParameter, equatorialRadius, flattening, j2, j4
        };

        const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Instant instant = Instant::J2000();

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            ephemeris,
            gravitationalModel,
            nullptr,
            nullptr
        };

        {
            const Position position = {{1.0, 0.0, 0.0}, Length::Unit::Meter, celestial.accessFrame()};

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position, instant);

            EXPECT_TRUE(gravitationalFieldValue.isDefined());

            EXPECT_TRUE(gravitationalFieldValue.getValue().isNear(Vector3d {-1.0, 0.0, 0.0}, 1e-20));
            EXPECT_EQ(
                Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)),
                gravitationalFieldValue.getUnit()
            );
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame());
        }

        {
            const Position position = {{0.0, 0.0, 1.0}, Length::Unit::Meter, celestial.accessFrame()};

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position, instant);

            EXPECT_TRUE(gravitationalFieldValue.isDefined());

            EXPECT_TRUE(gravitationalFieldValue.getValue().isNear(Vector3d {0.0, 0.0, -1.0}, 1e-20));
            EXPECT_EQ(
                Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)),
                gravitationalFieldValue.getUnit()
            );
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame());
        }

        {
            const Position position = {{2.0, 0.0, 0.0}, Length::Unit::Meter, celestial.accessFrame()};

            const Vector gravitationalFieldValue = celestial.getGravitationalFieldAt(position, instant);

            EXPECT_TRUE(gravitationalFieldValue.isDefined());

            EXPECT_TRUE(gravitationalFieldValue.getValue().isNear(Vector3d {-0.25, 0.0, 0.0}, 1e-20));
            EXPECT_EQ(
                Unit::Derived(Derived::Unit::Acceleration(Length::Unit::Meter, Time::Unit::Second)),
                gravitationalFieldValue.getUnit()
            );
            EXPECT_EQ(Frame::ITRF(), gravitationalFieldValue.getFrame());
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial, GetMagneticFieldAt)
{
    {
        const String name = "Some Planet";
        const Celestial::Type type = Celestial::Type::Earth;
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
        };
        const Length equatorialRadius = Length::Kilometers(1000.0);
        const Real flattening = 0.0;
        const Real j2 = 0.0;
        const Real j4 = 0.0;
        const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Instant instant = Instant::J2000();

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            ephemeris,
            nullptr,
            magneticModel,
            nullptr
        };

        {
            const Position position = {{1.0, 0.0, 0.0}, Length::Unit::Meter, celestial.accessFrame()};

            const Vector magneticFieldValue = celestial.getMagneticFieldAt(position, instant);

            EXPECT_TRUE(magneticFieldValue.isDefined());

            EXPECT_TRUE(magneticFieldValue.getValue().isNear(Vector3d {0.0, 0.0, -1e-07}, 1e-20));
            EXPECT_EQ(Unit::Derived(Derived::Unit::Tesla()), magneticFieldValue.getUnit());
            EXPECT_EQ(Frame::ITRF(), magneticFieldValue.getFrame());
        }

        {
            const Position position = {{0.0, 0.0, 1.0}, Length::Unit::Meter, celestial.accessFrame()};

            const Vector magneticFieldValue = celestial.getMagneticFieldAt(position, instant);

            EXPECT_TRUE(magneticFieldValue.isDefined());

            EXPECT_TRUE(magneticFieldValue.getValue().isNear(Vector3d {0.0, 0.0, +2e-07}, 1e-20));
            EXPECT_EQ(Unit::Derived(Derived::Unit::Tesla()), magneticFieldValue.getUnit());
            EXPECT_EQ(Frame::ITRF(), magneticFieldValue.getFrame());
        }

        {
            const Position position = {{2.0, 0.0, 0.0}, Length::Unit::Meter, celestial.accessFrame()};

            const Vector magneticFieldValue = celestial.getMagneticFieldAt(position, instant);

            EXPECT_TRUE(magneticFieldValue.isDefined());

            EXPECT_TRUE(magneticFieldValue.getValue().isNear(Vector3d {0.0, 0.0, -1.25e-08}, 1e-20));
            EXPECT_EQ(Unit::Derived(Derived::Unit::Tesla()), magneticFieldValue.getUnit());
            EXPECT_EQ(Frame::ITRF(), magneticFieldValue.getFrame());
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Object_Celestial, GetAtmosphericDensityAt)
{
    {
        const String name = "Some Planet";
        const Celestial::Type type = Celestial::Type::Earth;
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)
        };
        const Real j2 = 0.0;
        const Real j4 = 0.0;
        const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());
        const Shared<AtmosphericModel> atmosphericModel =
            std::make_shared<EarthAtmosphericModel>(EarthAtmosphericModel::Type::Exponential);
        const Instant instant = Instant::J2000();

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            EarthGravitationalModel::EGM2008.equatorialRadius_,
            EarthGravitationalModel::EGM2008.flattening_,
            j2,
            j4,
            ephemeris,
            nullptr,
            nullptr,
            atmosphericModel
        };

        {
            const Position position = {
                LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0))
                    .toCartesian(
                        EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            const Scalar atmosphericDensityValue = celestial.getAtmosphericDensityAt(position, instant);

            EXPECT_TRUE(atmosphericDensityValue.isDefined());

            EXPECT_TRUE(atmosphericDensityValue.getValue().isNear(1.77622e-08, 1e-13));
            EXPECT_EQ(
                Unit::Derived(Derived::Unit::MassDensity(Mass::Unit::Kilogram, Length::Unit::Meter)),
                atmosphericDensityValue.getUnit()
            );
        }

        {
            const Position position = {
                LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(499.0))
                    .toCartesian(
                        EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            const Scalar atmosphericDensityValue = celestial.getAtmosphericDensityAt(position, instant);

            EXPECT_TRUE(atmosphericDensityValue.isDefined());

            EXPECT_TRUE(atmosphericDensityValue.getValue().isNear(7.08245e-13, 1e-15));
            EXPECT_EQ(
                Unit::Derived(Derived::Unit::MassDensity(Mass::Unit::Kilogram, Length::Unit::Meter)),
                atmosphericDensityValue.getUnit()
            );
        }

        {
            const Position position = {
                LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0))
                    .toCartesian(
                        EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            const Scalar atmosphericDensityValue = celestial.getAtmosphericDensityAt(position, instant);

            EXPECT_TRUE(atmosphericDensityValue.isDefined());

            EXPECT_TRUE(atmosphericDensityValue.getValue().isNear(6.85869e-13, 1e-15));
            EXPECT_EQ(
                Unit::Derived(Derived::Unit::MassDensity(Mass::Unit::Kilogram, Length::Unit::Meter)),
                atmosphericDensityValue.getUnit()
            );
        }

        {
            EXPECT_ANY_THROW(celestial.getAtmosphericDensityAt(Position::Undefined(), instant));
        }

        {
            const Position position = {
                LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0))
                    .toCartesian(
                        EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            EXPECT_ANY_THROW(Celestial::Undefined().getAtmosphericDensityAt(position, instant));
        }

        {
            const Position position = {
                LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0))
                    .toCartesian(
                        EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            const Celestial celestialWithoutAtmospheric = {
                name,
                type,
                gravitationalParameter,
                EarthGravitationalModel::EGM2008.equatorialRadius_,
                EarthGravitationalModel::EGM2008.flattening_,
                j2,
                j4,
                ephemeris,
                nullptr,
                nullptr,
                nullptr
            };

            EXPECT_ANY_THROW(celestialWithoutAtmospheric.getAtmosphericDensityAt(position, instant));
        }

        {
            EXPECT_ANY_THROW(celestial.getAtmosphericDensityAt(Position::Undefined(), instant));
        }

        {
            EXPECT_ANY_THROW(Celestial::Undefined().getAtmosphericDensityAt(Position::Undefined(), instant));
        }
    }
}
