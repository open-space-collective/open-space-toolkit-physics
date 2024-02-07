/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>

#include <Global.test.hpp>

using ostk::core::error::RuntimeError;
using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::container::Tuple;
using ostk::core::container::Array;

using ostk::physics::unit::Length;
using ostk::physics::unit::Angle;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::coord::Frame;

using EarthCelestial = ostk::physics::environment::object::celestial::Earth;
using ostk::physics::environment::object::celestial::Sun;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;
using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, Constructor)
{
    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::Exponential));
    }

    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(
            EarthAtmosphericModel::Type::Exponential, EarthAtmosphericModel::InputDataType::Undefined
        ));
    }

    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(EarthAtmosphericModel::Type::NRLMSISE00));
    }

    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(
            EarthAtmosphericModel::Type::NRLMSISE00, EarthAtmosphericModel::InputDataType::CSSISpaceWeatherFile
        ));
    }

    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(
            EarthAtmosphericModel::Type::NRLMSISE00,
            EarthAtmosphericModel::InputDataType::ConstantFluxAndGeoMag,
            150.0,
            150.0,
            3.0
        ));
    }

    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(
            EarthAtmosphericModel::Type::NRLMSISE00,
            EarthAtmosphericModel::InputDataType::ConstantFluxAndGeoMag,
            150.0,
            150.0,
            3.0,
            Frame::ITRF()
        ));
    }

    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(
            EarthAtmosphericModel::Type::NRLMSISE00, EarthAtmosphericModel::InputDataType::ConstantFluxAndGeoMag
        ));
    }

    {
        EXPECT_NO_THROW(EarthAtmosphericModel earthAtmosphericModel(
            EarthAtmosphericModel::Type::NRLMSISE00,
            EarthAtmosphericModel::InputDataType::Undefined  // Using default InputDataType
        ));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, Clone)
{
    {
        const EarthAtmosphericModel earthAtmosphericModel = {EarthAtmosphericModel::Type::Exponential};

        EXPECT_NO_THROW(const EarthAtmosphericModel* earthAtmosphericModelPtr = earthAtmosphericModel.clone();
                        delete earthAtmosphericModelPtr;);
    }

    {
        const EarthAtmosphericModel earthAtmosphericModel = {EarthAtmosphericModel::Type::NRLMSISE00};

        EXPECT_NO_THROW(const EarthAtmosphericModel* earthAtmosphericModelPtr = earthAtmosphericModel.clone();
                        delete earthAtmosphericModelPtr;);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, OperatorEquals)
{
    {
        EarthAtmosphericModel earthAtmosphericModel = {EarthAtmosphericModel::Type::Exponential};
        EarthAtmosphericModel earthAtmosphericModel2 = {EarthAtmosphericModel::Type::Exponential};

        EXPECT_NO_THROW(earthAtmosphericModel2 = earthAtmosphericModel);
    }

    {
        EarthAtmosphericModel earthAtmosphericModel = {EarthAtmosphericModel::Type::NRLMSISE00};
        EarthAtmosphericModel earthAtmosphericModel2 = {EarthAtmosphericModel::Type::NRLMSISE00};

        EXPECT_NO_THROW(earthAtmosphericModel2 = earthAtmosphericModel);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetType)
{
    {
        EXPECT_EQ(
            EarthAtmosphericModel::Type::Exponential,
            EarthAtmosphericModel(EarthAtmosphericModel::Type::Exponential).getType()
        );
    }
    {
        EXPECT_EQ(
            EarthAtmosphericModel::Type::NRLMSISE00,
            EarthAtmosphericModel(EarthAtmosphericModel::Type::NRLMSISE00).getType()
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetInputDataType)
{
    {
        EXPECT_EQ(
            EarthAtmosphericModel::InputDataType::Undefined,
            EarthAtmosphericModel(
                EarthAtmosphericModel::Type::Exponential, EarthAtmosphericModel::InputDataType::Undefined
            )
                .getInputDataType()
        );
    }

    {
        EXPECT_EQ(
            EarthAtmosphericModel::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel(
                EarthAtmosphericModel::Type::NRLMSISE00, EarthAtmosphericModel::InputDataType::CSSISpaceWeatherFile
            )
                .getInputDataType()
        );
    }

    {
        EXPECT_EQ(
            EarthAtmosphericModel::InputDataType::ConstantFluxAndGeoMag,
            EarthAtmosphericModel(
                EarthAtmosphericModel::Type::NRLMSISE00, EarthAtmosphericModel::InputDataType::ConstantFluxAndGeoMag
            )
                .getInputDataType()
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, IsDefined)
{
    {
        EXPECT_FALSE(EarthAtmosphericModel(EarthAtmosphericModel::Type::Undefined).isDefined());

        EXPECT_TRUE(EarthAtmosphericModel(EarthAtmosphericModel::Type::Exponential).isDefined());

        EXPECT_TRUE(EarthAtmosphericModel(EarthAtmosphericModel::Type::NRLMSISE00).isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetDensityAt_Position)
{
    {
        static const Array<Tuple<EarthAtmosphericModel::Type, LLA, Instant, Real, Real>> testCases = {
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0)),
             Instant::J2000(),
             1.77622e-08,
             1e-13},
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(499.0)),
             Instant::J2000(),
             7.08245e-13,
             1e-15},
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0)),
             Instant::J2000(),
             6.85869e-13,
             1e-15},
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(550.0)),
             Instant::J2000(),
             3.18278e-13,
             1e-15},
            {EarthAtmosphericModel::Type::NRLMSISE00,
             LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(500.0)),
             Instant::DateTime(DateTime::Parse("2021-01-01 00:00:00"), Scale::UTC),
             6.7647e-14,
             1e-15}
        };

        for (const auto& testCase : testCases)
        {
            const EarthAtmosphericModel earthAtmosphericModel = {std::get<0>(testCase)};
            const LLA lla = std::get<1>(testCase);

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            const Instant instant = std::get<2>(testCase);
            const Real referenceDensity = std::get<3>(testCase);
            const Real tolerance = std::get<4>(testCase);

            const Real density = earthAtmosphericModel.getDensityAt(position, instant);

            EXPECT_TRUE(density.isNear(referenceDensity, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), (density - referenceDensity)
            );
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetDensityAt_LLA)
{
    {
        // Hand calculated values to validate
        static const Array<Tuple<EarthAtmosphericModel::Type, LLA, Instant, Real, Real>> testCases = {
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0)),
             Instant::J2000(),
             1.77622e-08,
             1e-13},
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(499.0)),
             Instant::J2000(),
             7.08245e-13,
             1e-15},
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0)),
             Instant::J2000(),
             6.85869e-13,
             1e-15},
            {EarthAtmosphericModel::Type::Exponential,
             LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(550.0)),
             Instant::J2000(),
             3.18278e-13,
             1e-15},
            {EarthAtmosphericModel::Type::NRLMSISE00,
             LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(500.0)),
             Instant::DateTime(DateTime::Parse("2021-01-01 00:00:00"), Scale::UTC),
             6.7647e-14,
             1e-15}
        };

        for (const auto& testCase : testCases)
        {
            const EarthAtmosphericModel earthAtmosphericModel = {std::get<0>(testCase)};
            const LLA lla = std::get<1>(testCase);
            const Instant instant = std::get<2>(testCase);
            const Real referenceDensity = std::get<3>(testCase);
            const Real tolerance = std::get<4>(testCase);

            const Real density = earthAtmosphericModel.getDensityAt(lla, instant);

            EXPECT_TRUE(density.isNear(referenceDensity, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), (density - referenceDensity)
            );
        }
    }

    {
        const EarthAtmosphericModel earthAtmosphericModel = {EarthAtmosphericModel::Type::Exponential};

        const LLA lla = LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(1001.0));
        const Instant instant = Instant::J2000();

        const String expectedString =
            "Exponential density model is not valid for altitudes above 1000 km. Altitude = 1001000.0 [m]";

        // Test the throw and the message that is thrown
        EXPECT_THROW(
            {
                try
                {
                    earthAtmosphericModel.getDensityAt(lla, instant);
                }
                catch (const RuntimeError& e)
                {
                    EXPECT_EQ(expectedString, e.getMessage());
                    throw;
                }
            },
            RuntimeError
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetDensityAt_Frames)
{
    {
        static const Array<Tuple<EarthAtmosphericModel::Type, EarthAtmosphericModel::InputDataType, LLA, Instant, Real>>
            testCases = {
                {EarthAtmosphericModel::Type::Exponential,
                 EarthAtmosphericModel::InputDataType::Undefined,
                 LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0)),
                 Instant::J2000(),
                 1e-13},
                {EarthAtmosphericModel::Type::Exponential,
                 EarthAtmosphericModel::InputDataType::Undefined,
                 LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(499.0)),
                 Instant::J2000(),
                 1e-15},
                {EarthAtmosphericModel::Type::Exponential,
                 EarthAtmosphericModel::InputDataType::Undefined,
                 LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(501.0)),
                 Instant::J2000(),
                 1e-15},
                {EarthAtmosphericModel::Type::Exponential,
                 EarthAtmosphericModel::InputDataType::Undefined,
                 LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(550.0)),
                 Instant::J2000(),
                 1e-15},
                {EarthAtmosphericModel::Type::NRLMSISE00,
                 EarthAtmosphericModel::InputDataType::CSSISpaceWeatherFile,
                 LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(500.0)),
                 Instant::DateTime(DateTime::Parse("2021-01-01 00:00:00"), Scale::UTC),
                 3.7e-15}
            };

        for (const auto& testCase : testCases)
        {
            const LLA lla = std::get<2>(testCase);

            const Position positionITRF = {
                lla.toCartesian(
                    EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            const EarthAtmosphericModel earthAtmosphericModelITRF = {
                std::get<0>(testCase), std::get<1>(testCase), 150.0, 150.0, 3.0, Frame::ITRF()
            };
            const EarthAtmosphericModel earthAtmosphericModelTEME = {
                std::get<0>(testCase), std::get<1>(testCase), 150.0, 150.0, 3.0, Frame::TEME()
            };

            const Instant instant = std::get<3>(testCase);
            const Real tolerance = std::get<4>(testCase);

            const Real densityITRF = earthAtmosphericModelITRF.getDensityAt(positionITRF, instant);
            const Real densityTEME = earthAtmosphericModelTEME.getDensityAt(positionITRF, instant);

            EXPECT_TRUE(densityITRF.isNear(densityTEME, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [T]", densityITRF.toString(), densityTEME.toString(), (densityITRF - densityTEME)
            );
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth, GetDensityAt_Solar)
{
    {
        static const Array<Tuple<EarthAtmosphericModel::Type, EarthAtmosphericModel::InputDataType, LLA, Instant, Real>>
            testCases = {
                {EarthAtmosphericModel::Type::NRLMSISE00,
                 EarthAtmosphericModel::InputDataType::CSSISpaceWeatherFile,
                 LLA(Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(350.0)),
                 Instant::DateTime(DateTime::Parse("2021-01-01 00:00:00"), Scale::UTC),
                 1e-15},
                {EarthAtmosphericModel::Type::NRLMSISE00,
                 EarthAtmosphericModel::InputDataType::CSSISpaceWeatherFile,
                 LLA(Angle::Degrees(0.0), Angle::Degrees(0.0), Length::Kilometers(300.0)),
                 Instant::DateTime(DateTime::Parse("2021-01-01 00:00:00"), Scale::UTC),
                 1e-15}
            };

        for (const auto& testCase : testCases)
        {
            const LLA lla = std::get<2>(testCase);

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            const EarthAtmosphericModel earthAtmosphericModelSun = {
                std::get<0>(testCase),
                std::get<1>(testCase),
                Real::Undefined(),
                Real::Undefined(),
                Real::Undefined(),
                Frame::ITRF(),
                EarthGravitationalModel::EGM2008.equatorialRadius_,
                EarthGravitationalModel::EGM2008.flattening_,
                std::make_shared<Sun>(Sun::Default())
            };

            const EarthAtmosphericModel earthAtmosphericModelNoSun = {
                std::get<0>(testCase),
                std::get<1>(testCase),
                Real::Undefined(),
                Real::Undefined(),
                Real::Undefined(),
                Frame::ITRF(),
                EarthGravitationalModel::EGM2008.equatorialRadius_,
                EarthGravitationalModel::EGM2008.flattening_
            };

            const Instant instant = std::get<3>(testCase);
            const Real tolerance = std::get<4>(testCase);

            const Real densitySun = earthAtmosphericModelSun.getDensityAt(position, instant);
            const Real densityNoSun = earthAtmosphericModelNoSun.getDensityAt(position, instant);

            EXPECT_FALSE(densitySun.isNear(densityNoSun, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [T]", densitySun.toString(), densityNoSun.toString(), (densitySun - densityNoSun)
            );
        }
    }
}
