/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Weak.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Exponential.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/Analytical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Gravitational/Spherical.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Magnetic/Dipole.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>
#include <OpenSpaceToolkit/Physics/Units/Mass.hpp>

#include <Global.test.hpp>

using ostk::core::types::Shared;
using ostk::core::types::Real;
using ostk::core::types::String;

using ostk::math::obj::Vector3d;

using ostk::physics::Unit;
using ostk::physics::units::Angle;
using ostk::physics::units::Length;
using ostk::physics::units::Time;
using ostk::physics::units::Mass;
using ostk::physics::units::Derived;
using ostk::physics::data::Vector;
using ostk::physics::data::Scalar;
using ostk::physics::time::Instant;
using ostk::physics::coord::Frame;
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::env::obj::Celestial;
using ostk::physics::env::Ephemeris;
using ostk::physics::env::ephem::Analytical;
using GravitationalModel = ostk::physics::environment::gravitational::Model;
using MagneticModel = ostk::physics::environment::magnetic::Model;
using AtmosphericModel = ostk::physics::environment::atmospheric::Model;
using ostk::physics::environment::gravitational::Spherical;
using ostk::physics::environment::magnetic::Dipole;
using ostk::physics::environment::atmospheric::earth::Exponential;
using EarthCelestialBody = ostk::physics::env::obj::celest::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using EarthMagneticModel = ostk::physics::environment::magnetic::Earth;
using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;

// TEST (OpenSpaceToolkit_Physics_Environment_Objects_Celestial, Constructor)
// {

//     using ostk::physics::env::Object ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Physics_Environment_Objects_Celestial, accessModel)
{
    const String name = "Some Planet";
    const Celestial::Type type = Celestial::Type::Earth;
    const Derived gravitationalParameter = {
        1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)};
    const Length equatorialRadius = Length::Kilometers(1000.0);
    const Real flattening = 0.0;
    const Real j2 = 0.0;
    const Real j4 = 0.0;

    const EarthGravitationalModel::Parameters gravitationalModelParameters = {
        gravitationalParameter, equatorialRadius, flattening, j2, j4};

    const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());
    {
        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            equatorialRadius,
            flattening,
            j2,
            j4,
            nullptr,
            nullptr,
            nullptr,
            nullptr};

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
            nullptr};

        EXPECT_EQ(celestial.accessGravitationalModel(), nullptr);
        EXPECT_EQ(celestial.accessMagneticModel(), nullptr);
        EXPECT_EQ(celestial.accessAtmosphericModel(), nullptr);
    }

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel = std::make_shared<Exponential>();

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
            atmosphericModel};

        EXPECT_NO_THROW(celestial.accessGravitationalModel());
        EXPECT_NO_THROW(celestial.accessMagneticModel());
        EXPECT_NO_THROW(celestial.accessAtmosphericModel());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_Celestial, modelIsDefined)
{
    const String name = "Some Planet";
    const Celestial::Type type = Celestial::Type::Earth;
    const Derived gravitationalParameter = {
        1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)};
    const Length equatorialRadius = Length::Kilometers(1000.0);
    const Real flattening = 0.0;
    const Real j2 = 0.0;
    const Real j4 = 0.0;

    const EarthGravitationalModel::Parameters gravitationalModelParameters = {
        gravitationalParameter, equatorialRadius, flattening, j2, j4};

    const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel = std::make_shared<Exponential>();

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
            nullptr};

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
            undefinedAtmosphericModel};

        EXPECT_FALSE(celestial.gravitationalModelIsDefined());
        EXPECT_FALSE(celestial.magneticModelIsDefined());
        EXPECT_FALSE(celestial.atmosphericModelIsDefined());
    }

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel = std::make_shared<Exponential>();

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
            atmosphericModel};

        EXPECT_TRUE(celestial.gravitationalModelIsDefined());
        EXPECT_TRUE(celestial.magneticModelIsDefined());
        EXPECT_TRUE(celestial.atmosphericModelIsDefined());
    }

    {
        const Shared<GravitationalModel> gravitationalModel = std::make_shared<Spherical>(gravitationalModelParameters);
        const Shared<MagneticModel> magneticModel = std::make_shared<Dipole>(Vector3d {0.0, 0.0, 1.0});
        const Shared<AtmosphericModel> atmosphericModel = std::make_shared<Exponential>();

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
            atmosphericModel};

        EXPECT_ANY_THROW(celestial.gravitationalModelIsDefined());
        EXPECT_ANY_THROW(celestial.magneticModelIsDefined());
        EXPECT_ANY_THROW(celestial.atmosphericModelIsDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Objects_Celestial, GetGravitationalFieldAt)
{
    {
        const String name = "Some Planet";
        const Celestial::Type type = Celestial::Type::Earth;
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)};
        const Length equatorialRadius = Length::Kilometers(1000.0);
        const Real flattening = 0.0;
        const Real j2 = 0.0;
        const Real j4 = 0.0;

        const EarthGravitationalModel::Parameters gravitationalModelParameters = {
            gravitationalParameter, equatorialRadius, flattening, j2, j4};

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
            nullptr};

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

TEST(OpenSpaceToolkit_Physics_Environment_Objects_Celestial, GetMagneticFieldAt)
{
    {
        const String name = "Some Planet";
        const Celestial::Type type = Celestial::Type::Earth;
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)};
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
            nullptr};

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

TEST(OpenSpaceToolkit_Physics_Environment_Objects_Celestial, GetAtmosphericDensityAt)
{
    {
        const String name = "Some Planet";
        const Celestial::Type type = Celestial::Type::Earth;
        const Derived gravitationalParameter = {
            1.0, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second)};
        const Real j2 = 0.0;
        const Real j4 = 0.0;
        const Shared<Ephemeris> ephemeris = std::make_shared<Analytical>(Frame::ITRF());
        const Shared<AtmosphericModel> atmosphericModel = std::make_shared<Exponential>();
        const Instant instant = Instant::J2000();

        const Celestial celestial = {
            name,
            type,
            gravitationalParameter,
            EarthGravitationalModel::EGM2008Parameters.equatorialRadius_,
            EarthGravitationalModel::EGM2008Parameters.flattening_,
            j2,
            j4,
            ephemeris,
            nullptr,
            nullptr,
            atmosphericModel};

        {
            const Position position = {
                LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0))
                    .toCartesian(
                        EarthGravitationalModel::EGM2008Parameters.equatorialRadius_,
                        EarthGravitationalModel::EGM2008Parameters.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()};

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
                        EarthGravitationalModel::EGM2008Parameters.equatorialRadius_,
                        EarthGravitationalModel::EGM2008Parameters.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()};

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
                        EarthGravitationalModel::EGM2008Parameters.equatorialRadius_,
                        EarthGravitationalModel::EGM2008Parameters.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()};

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
                        EarthGravitationalModel::EGM2008Parameters.equatorialRadius_,
                        EarthGravitationalModel::EGM2008Parameters.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()};

            EXPECT_ANY_THROW(Celestial::Undefined().getAtmosphericDensityAt(position, instant));
        }

        {
            const Position position = {
                LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0))
                    .toCartesian(
                        EarthGravitationalModel::EGM2008Parameters.equatorialRadius_,
                        EarthGravitationalModel::EGM2008Parameters.flattening_
                    ),
                Position::Unit::Meter,
                Frame::ITRF()};

            const Celestial celestialWithoutAtmospheric = {
                name,
                type,
                gravitationalParameter,
                EarthGravitationalModel::EGM2008Parameters.equatorialRadius_,
                EarthGravitationalModel::EGM2008Parameters.flattening_,
                j2,
                j4,
                ephemeris,
                nullptr,
                nullptr,
                nullptr};

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
