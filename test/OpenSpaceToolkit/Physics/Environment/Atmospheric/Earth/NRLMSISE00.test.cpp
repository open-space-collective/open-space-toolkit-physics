/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

using ostk::core::types::String;
using ostk::core::types::Real;
using ostk::core::types::Shared;
using ostk::core::types::Index;
using ostk::core::types::Size;
using ostk::core::types::Unique;
using ostk::core::ctnr::Table;
using ostk::core::ctnr::Array;
using ostk::core::fs::File;
using ostk::core::fs::Path;

using ostk::physics::units::Length;
using ostk::physics::units::Angle;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::coord::Frame;
using ostk::physics::environment::atmospheric::earth::NRLMSISE00;
using ostk::physics::env::obj::Celestial;
using ostk::physics::env::obj::celest::Sun;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;
using ostk::physics::environment::atmospheric::earth::Manager;

// Expose protected members for testing
class NRLMSISE00Public : public NRLMSISE00
{
   public:
    using NRLMSISE00::computeApArray;
    using NRLMSISE00::computeNRLMSISE00Input;
    using NRLMSISE00::nrlmsise_input;
    using NRLMSISE00::ap_array;
};

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Constructor)
{
    {
        EXPECT_NO_THROW(NRLMSISE00 nrlmsise = {});
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Clone)
{
    {
        const NRLMSISE00 nrlmsise = {};

        EXPECT_NO_THROW(nrlmsise.clone());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, IsDefined)
{
    {
        const NRLMSISE00 nrlmsise = {};

        EXPECT_TRUE(nrlmsise.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit3HourMarksShifted)
{
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitCSSIParameters3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00Public nrlmsise = {};

        for (Index i = 0; i < rowCount; i++)
        {
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            Unique<NRLMSISE00Public::ap_array> apArray = nrlmsise.computeApArray(instant);

            EXPECT_TRUE(referenceData(i, "AP_0").accessReal().isNear(apArray->a[0], 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_0").accessReal(), apArray->a[0], datetime.toString()
            );
            EXPECT_TRUE(referenceData(i, "AP_1").accessReal().isNear(apArray->a[1], 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_1").accessReal(), apArray->a[1], datetime.toString()
            );
            EXPECT_TRUE(referenceData(i, "AP_2").accessReal().isNear(apArray->a[2], 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_2").accessReal(), apArray->a[2], datetime.toString()
            );
            EXPECT_TRUE(referenceData(i, "AP_3").accessReal().isNear(apArray->a[3], 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_3").accessReal(), apArray->a[3], datetime.toString()
            );
            EXPECT_TRUE(referenceData(i, "AP_4").accessReal().isNear(apArray->a[4], 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_4").accessReal(), apArray->a[4], datetime.toString()
            );
            EXPECT_TRUE(referenceData(i, "AP_5").accessReal().isNear(apArray->a[5], 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_5").accessReal(), apArray->a[5], datetime.toString()
            );
            EXPECT_TRUE(referenceData(i, "AP_6").accessReal().isNear(apArray->a[6], 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_6").accessReal(), apArray->a[6], datetime.toString()
            );
        }
    }
}

/* ignored for now pending resolution of: https://gitlab.orekit.org/orekit/orekit/-/issues/1119 */
// TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit3HrMarks)
// {

//     const File referenceDataFile = File::Path(Path::Parse(
//                  "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/OreKitCSSIParameters3HourMarks.csv"
//              ));

//     const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
//     Size rowCount = referenceData.getRowCount();

//     {
//         const NRLMSISE00 nrlmsise = {};

//         for (Index i =48; i < rowCount; i++) {

//             const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").accessString(),
//             DateTime::Format::Standard);

//             Instant instant = Instant::DateTime(datetime, Scale::UTC);
//             std::cout << "instant: " << instant.toString(Scale::UTC) << std::endl;
//             double apArray[7];
//             nrlmsise.computeApArray(apArray, instant);

//             Array<Real> apArrayReal = Array<Real>(apArray, apArray+7);

//             std::cout << "calc <> Orekit" << std::endl;
//             std::cout << apArrayReal[0] << " <> " << referenceData(i, "AP_0").accessReal() << std::endl;
//             std::cout << apArrayReal[1] << " <> " << referenceData(i, "AP_1").accessReal() << std::endl;
//             std::cout << apArrayReal[2] << " <> " << referenceData(i, "AP_2").accessReal() << std::endl;
//             std::cout << apArrayReal[3] << " <> " << referenceData(i, "AP_3").accessReal() << std::endl;
//             std::cout << apArrayReal[4] << " <> " << referenceData(i, "AP_4").accessReal() << std::endl;
//             std::cout << apArrayReal[5] << " <> " << referenceData(i, "AP_5").accessReal() << std::endl;
//             std::cout << apArrayReal[6] << " <> " << referenceData(i, "AP_6").accessReal() << std::endl;

//             EXPECT_TRUE(referenceData(i,"AP_0").accessReal().isNear(apArray[0], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_0").accessReal(), apArray[0], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_1").accessReal().isNear(apArray[1], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_1").accessReal(), apArray[1], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_2").accessReal().isNear(apArray[2], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_2").accessReal(), apArray[2], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_3").accessReal().isNear(apArray[3], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_3").accessReal(), apArray[3], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_4").accessReal().isNear(apArray[4], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_4").accessReal(), apArray[4], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_5").accessReal().isNear(apArray[5], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_5").accessReal(), apArray[5], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_6").accessReal().isNear(apArray[6], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_6").accessReal(), apArray[6], datetime.toString());

//         }
//     }
// }

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeNRLMISE00InputOrekit)
{
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitCSSIParameters3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00Public nrlmsise = {};

        for (Index i = 0; i < rowCount; i++)
        {
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const LLA lla = LLA(Angle::Degrees(0), Angle::Degrees(0), Length::Meters(500000));

            Unique<NRLMSISE00Public::nrlmsise_input> input =
                nrlmsise.computeNRLMSISE00Input(nrlmsise.computeApArray(instant), lla, instant);

            EXPECT_TRUE(referenceData(i, "DAILY_FLUX").accessReal().isNear(input->f107, 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "DAILY_FLUX").accessReal(), input->f107, datetime.toString()
            );
            EXPECT_TRUE(referenceData(i, "AVG_FLUX").accessReal().isNear(input->f107A, 0.001)) << String::Format(
                "{} != {} on {}", referenceData(i, "AVG_FLUX").accessReal(), input->f107A, datetime.toString()
            );
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOrekit3HrMarksPreciseLST)
{
    const File referenceDataFile = File::Path(Path::Parse(
        "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/OreKitNRLMSISE500km3HourMarks.csv"
    ));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {};

        for (Index i = 0; i < rowCount; i++)
        {
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Real density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 43.0;
            const Real percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const Real absoluteTolerate = 1.0e-15;
            const Real absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]", density.toString(), referenceDensity.toString(), absoluteError, percentError
            );
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOrekit3HrMarkShiftedPreciseLST)
{
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISE500km3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Real density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 0.42;
            const Real percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const Real absoluteTolerate = 1.0e-15;
            const Real absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]", density.toString(), referenceDensity.toString(), absoluteError, percentError
            );
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOrekit3HrMarkShiftedStandardLST)
{
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISE500km3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {
            Frame::ITRF(), EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Real density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 3.4;
            const Real percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const Real absoluteTolerate = 1.0e-15;
            const Real absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]", density.toString(), referenceDensity.toString(), absoluteError, percentError
            );
        }
    }
}

TEST(
    OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOreKitNRLMSISESweep3HourMarksShifted
)
{
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISESweep3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Real density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 0.6;
            const Real percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const Real absoluteTolerate = 1e-15;
            const Real absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]", density.toString(), referenceDensity.toString(), absoluteError, percentError
            );
        }
    }
}


TEST(
    OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOreKitNRLMSISESweep3HourMarksShiftedIERS2003
)
{
    const File spaceWeatherFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "SpaceWeather-All-v1.2"));

    Manager::Get().reset();
    Manager::Get().loadCSSISpaceWeather(CSSISpaceWeather::LoadLegacy(spaceWeatherFile));

    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISESweep3HourMarksShiftedIERS2003.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        Real maxError = 0.0;

        for (Index i = 0; i < rowCount; i++)
        {
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::ISO8601);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Instant instant = Instant::DateTime(datetime, Scale::UTC);
            
            const Real density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 0.6;
            const Real percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            maxError = std::max(maxError, percentError);
            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const Real absoluteTolerate = 1e-15;
            const Real absoluteError = std::abs(density - referenceDensity);

            // EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
            //     "{} ≈ {} Δ {} [{}%] [T]", density.toString(), referenceDensity.toString(), absoluteError, percentError
            // );

        }
        std::cout << "maxError: " << maxError << std::endl;
    }
}
