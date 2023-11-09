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
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
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
using ostk::core::types::Integer;
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
using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;
using ostk::physics::environment::atmospheric::earth::Manager;

// Expose protected members for testing
class NRLMSISE00Public : public NRLMSISE00
{
   public:
    NRLMSISE00Public(
        const NRLMSISE00::InputDataType& anInputDataType =
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
        const Real& aF107ConstantValue = Real::Undefined(),
        const Real& aF107AConstantValue = Real::Undefined(),
        const Real& aKpConstantValue = Real::Undefined(),
        const Shared<const Frame>& anEarthFrameSPtr = Frame::ITRF(),
        const Length& anEarthRadius = EarthGravitationalModel::WGS84.equatorialRadius_,
        const Real& anEarthFlattening = EarthGravitationalModel::WGS84.flattening_,
        const Shared<Celestial>& aSunCelestialSPtr = nullptr
    )
        : NRLMSISE00(
              anInputDataType,
              aF107ConstantValue,
              aF107AConstantValue,
              aKpConstantValue,
              anEarthFrameSPtr,
              anEarthRadius,
              anEarthFlattening,
              aSunCelestialSPtr
          )
    {
    }

    using NRLMSISE00::convertKpToAp;
    using NRLMSISE00::computeApArray;
    using NRLMSISE00::computeNRLMSISE00Input;
    using NRLMSISE00::nrlmsise_input;
    using NRLMSISE00::ap_array;
    using NRLMSISE00::GetDensityAt;
};

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Constructor)
{
    {
        EXPECT_NO_THROW(NRLMSISE00 nrlmsise = {});
    }

    {
        EXPECT_NO_THROW(NRLMSISE00 nrlmsise = {NRLMSISE00::InputDataType::CSSISpaceWeatherFile});
    }

    {
        EXPECT_NO_THROW(NRLMSISE00 nrlmsise = {NRLMSISE00::InputDataType::ConstantFluxAndGeoMag});
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

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Getters)
{
    {
        NRLMSISE00::InputDataType inputDataSourceType = NRLMSISE00::InputDataType::ConstantFluxAndGeoMag;
        Real f107ConstantValue = 200.0;
        Real f107AConstantValue = 205.0;
        Real kpConstantValue = 3.0;

        NRLMSISE00 nrlmsise = {inputDataSourceType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        EXPECT_EQ(inputDataSourceType, nrlmsise.getInputDataType());
        EXPECT_EQ(f107ConstantValue, nrlmsise.getF107ConstantValue());
        EXPECT_EQ(f107AConstantValue, nrlmsise.getF107AConstantValue());
        EXPECT_EQ(kpConstantValue, nrlmsise.getKpConstantValue());
    }

    {
        NRLMSISE00::InputDataType inputDataSourceType = NRLMSISE00::InputDataType::CSSISpaceWeatherFile;
        Real f107ConstantValue = 200.0;
        Real f107AConstantValue = 205.0;
        Real kpConstantValue = 3.0;

        NRLMSISE00 nrlmsise = {inputDataSourceType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        EXPECT_EQ(inputDataSourceType, nrlmsise.getInputDataType());
        EXPECT_EQ(f107ConstantValue, nrlmsise.getF107ConstantValue());
        EXPECT_EQ(f107AConstantValue, nrlmsise.getF107AConstantValue());
        EXPECT_EQ(kpConstantValue, nrlmsise.getKpConstantValue());
    }

    {
        NRLMSISE00::InputDataType inputDataSourceType = NRLMSISE00::InputDataType::CSSISpaceWeatherFile;

        NRLMSISE00 nrlmsise = {inputDataSourceType};

        EXPECT_EQ(inputDataSourceType, nrlmsise.getInputDataType());
        EXPECT_EQ(EarthAtmosphericModel::defaultF107ConstantValue, nrlmsise.getF107ConstantValue());
        EXPECT_EQ(
            EarthAtmosphericModel::defaultF107AConstantValue, nrlmsise.getF107AConstantValue()
        );  // TBI: Make these static default var
        EXPECT_EQ(EarthAtmosphericModel::defaultKpConstantValue, nrlmsise.getKpConstantValue());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ConvertKpToAp)
{
    {
        EXPECT_EQ(NRLMSISE00Public::convertKpToAp(-1.6), 1.0);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayConstantFluxAndGeoMag)
{
    /*
     * This test is to confirm that we compute fixed values for AP solar index values when using constant flux input
     * data source type.
     */

    {
        NRLMSISE00Public::InputDataType inputDataSourceType =
            NRLMSISE00Public::InputDataType::ConstantFluxAndGeoMag;
        Real f107ConstantValue = 200.0;
        Real f107AConstantValue = 205.0;
        Real kpConstantValue = -1.6;

        NRLMSISE00Public nrlmsise = {inputDataSourceType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        Array<Instant> instants = {
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2020, 1, 2, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2024, 1, 2, 0, 0, 0), Scale::UTC),
        };

        for (const auto& instant : instants)
        {
            Unique<NRLMSISE00Public::ap_array> apArray = nrlmsise.computeApArray(instant);

            for (Index i = 0; i < 7; i++)
            {
                EXPECT_EQ(apArray->a[i], 1.0);
            }
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit3HourMarksShifted)
{
    /*
     * This test is to confirm that we compute the same AP solar index values as Orekit when not at 3hour marks.
     */
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
    /*
     * This test is to confirm that we compute the same Flux values as Orekit when not at 3hour marks.
     */
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
    /*
     * This test uses a precise local solar time just like Orekit. It doesn't match well for the following reasons:
     * 1. There are know difference in how Orekit computes AP values at exact 3 hour marks
     * 2. The orekit data was generated using their default UT1 time scale, rather than UTC
     */
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
    /*
     * This test uses a precise local solar time just like Orekit. It also avoids 3hour marks to show that we match
     * quite well in this case. It matches very well because we're at 500km altitude and all of the differences are in
     * the noise at 1e-15 Some known differences:
     * 1. The orekit data was generated using their default UT1 time scale, rather than UTC
     * 2. There may be some differences due to the difference in the IERS convention used in frame transformations. They
     * use IERS 2010, we use IERS 2003.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISE500km3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            Real::Undefined(),
            Real::Undefined(),
            Real::Undefined(),
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

            const Real absoluteTolerate = 1.0e-15;
            const Real absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate)
                << String::Format("{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), absoluteError);
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOrekit3HrMarkShiftedStandardLST)
{
    /*
     * This test uses a rough local solar time calculation, which is reccomended by the NRLMSISE docs. This shows the
     * effect vs. Orekit of using a rough LST calculation. This test is also at 500km altitude, but there is error
     * >1e-15 The known differences:
     * 1. Using a rough LST calculation.
     * 2. The orekit data was generated using their default UT1 time scale, rather than UTC
     * 3. There may be some differences due to the difference in the IERS convention used in frame transformations. They
     * use IERS 2010, we use IERS 2003.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISE500km3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            Real::Undefined(),
            Real::Undefined(),
            Real::Undefined(),
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_
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
            const Real percentTolerance = 3.62;
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
    /*
     * This test uses a precise LST calculation, but sweeps various lat/lon/alt/time values to get a better sense of the
     * error over the full range. All error is in the noise at 1e-15 The known differences:
     * 1. The orekit data was generated using their default UT1 time scale, rather than UTC
     * 2. There may be some differences due to the difference in the IERS convention used in frame transformations. They
     * use IERS 2010, we use IERS 2003.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISESweep3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            Real::Undefined(),
            Real::Undefined(),
            Real::Undefined(),
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

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const Real absoluteTolerate = 1e-15;
            const Real absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate)
                << String::Format("{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), absoluteError);
        }
    }
}

TEST(
    OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00,
    GetDensityAtOreKitNRLMSISESweep3HourMarksShiftedIERS2003
)
{
    /*
     * This test uses a precise LST calculation, sweeps various lat/lon/alt/time values, uses the IERS2003 convention in
     * Orekit AND uses the legacy space weather input file in OSTk. The known differences:
     * 1. The orekit data was generated using their default UT1 time scale, rather than UTC
     */
    const File spaceWeatherFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "SpaceWeather-All-v1.2.txt"));

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
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            Real::Undefined(),
            Real::Undefined(),
            Real::Undefined(),
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
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::ISO8601);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Real density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 0.0131;
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

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtNRLMSISEWithOrekitInputs)
{
    /*
     * This test checks the density generated by OSTk when using the actual inputs that Orekit generates for itself. It
     * was exported using some shenanigans in orekit_tooling. See `GenerateNRLMSISEDensityTestDataWithInputs`
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISEInputsAndDensity.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        for (Index i = 0; i < rowCount; i++)
        {
            const Integer doy = referenceData(i, "DOY").accessInteger();
            const Real sec = referenceData(i, "SEC").accessReal();
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real lst = referenceData(i, "LST").accessReal();
            const Real avgFlux = referenceData(i, "AVG_FLUX").accessReal();
            const Real dailyFlux = referenceData(i, "DAILY_FLUX").accessReal();
            const Real ap1 = referenceData(i, "AP1").accessReal();
            const Real ap2 = referenceData(i, "AP2").accessReal();
            const Real ap3 = referenceData(i, "AP3").accessReal();
            const Real ap4 = referenceData(i, "AP4").accessReal();
            const Real ap5 = referenceData(i, "AP5").accessReal();
            const Real ap6 = referenceData(i, "AP6").accessReal();
            const Real ap7 = referenceData(i, "AP7").accessReal();
            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();

            NRLMSISE00Public::ap_array apArray;
            apArray.a[0] = ap1;
            apArray.a[1] = ap2;
            apArray.a[2] = ap3;
            apArray.a[3] = ap4;
            apArray.a[4] = ap5;
            apArray.a[5] = ap6;
            apArray.a[6] = ap7;

            NRLMSISE00Public::nrlmsise_input input = {
                2022, doy, sec, altitude, latitude, longitude, lst, avgFlux, dailyFlux, ap1, &apArray
            };

            const Real density = NRLMSISE00Public::GetDensityAt(input);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 0.0131;
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

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, OrekitGenerateNRLMSISEInputs)
{
    /*
     * This test checks the input set generated by OSTk vs. Orekit. It was exported using some shenanigans in
     * orekit_tooling. See `GenerateNRLMSISEDensityTestDataWithInputs`
     *
     * The default UT1 was used in Orekit, rather than UTC, so the `sec` and `lst` values are known not to match.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISEInputsAndDensity.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());
        const NRLMSISE00Public nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            Real::Undefined(),
            Real::Undefined(),
            Real::Undefined(),
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const Integer doy = referenceData(i, "DOY").accessInteger();
            const Real sec = referenceData(i, "SEC").accessReal();
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real lst = referenceData(i, "LST").accessReal();
            const Real avgFlux = referenceData(i, "AVG_FLUX").accessReal();
            const Real dailyFlux = referenceData(i, "DAILY_FLUX").accessReal();
            const Real ap1 = referenceData(i, "AP1").accessReal();
            const Real ap2 = referenceData(i, "AP2").accessReal();
            const Real ap3 = referenceData(i, "AP3").accessReal();
            const Real ap4 = referenceData(i, "AP4").accessReal();
            const Real ap5 = referenceData(i, "AP5").accessReal();
            const Real ap6 = referenceData(i, "AP6").accessReal();
            const Real ap7 = referenceData(i, "AP7").accessReal();
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::ISO8601);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Kilometers(altitude));
            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Unique<NRLMSISE00Public::ap_array> apValues = nrlmsise.computeApArray(instant);
            const Unique<NRLMSISE00Public::nrlmsise_input> input =
                nrlmsise.computeNRLMSISE00Input(apValues, lla, instant);

            const Real secTolerance = 0.02;  // does not match well
            const Real altTolerance = 1e-15;
            const Real lstTolerance = 4e-5;  // does not match well

            const Real secError = std::abs(sec - input->sec);
            const Real altError = std::abs(altitude - input->alt);
            const Real lstError = std::abs(lst - input->lst);

            EXPECT_EQ(doy, input->doy);
            EXPECT_TRUE(secError < secTolerance) << String::Format("{} ≈ {} Δ {} [T]", sec, input->sec, secError);
            EXPECT_TRUE(altError < altTolerance)
                << String::Format("{} ≈ {} Δ {} [T]", altitude, input->alt, altTolerance);
            EXPECT_EQ(latitude, input->g_lat);
            EXPECT_EQ(longitude, input->g_long);
            EXPECT_TRUE(lstError < lstTolerance) << String::Format("{} ≈ {} Δ {} [T]", lst, input->lst, lstError);
            EXPECT_EQ(avgFlux, input->f107A);
            EXPECT_EQ(dailyFlux, input->f107);
            EXPECT_EQ(ap1, input->ap_a->a[0]);
            EXPECT_EQ(ap2, input->ap_a->a[1]);
            EXPECT_EQ(ap3, input->ap_a->a[2]);
            EXPECT_EQ(ap4, input->ap_a->a[3]);
            EXPECT_EQ(ap5, input->ap_a->a[4]);
            EXPECT_EQ(ap6, input->ap_a->a[5]);
            EXPECT_EQ(ap7, input->ap_a->a[6]);
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, OrekitGenerateNRLMSISEInputsUTC)
{
    /*
     * This test checks the input set generated by OSTk vs. Orekit. It was exported using some shenanigans in
     * orekit_tooling. See `GenerateNRLMSISEDensityTestDataWithInputsUTC`
     *
     * This test shows that differences in `sec` and `lst` values comes from the UT1/UTC difference. So unlike the
     * previous test, those inputs match here.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISEInputsAndDensityUTC.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());
        const NRLMSISE00Public nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            Real::Undefined(),
            Real::Undefined(),
            Real::Undefined(),
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const Integer doy = referenceData(i, "DOY").accessInteger();
            const Real sec = referenceData(i, "SEC").accessReal();
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real lst = referenceData(i, "LST").accessReal();
            const Real avgFlux = referenceData(i, "AVG_FLUX").accessReal();
            const Real dailyFlux = referenceData(i, "DAILY_FLUX").accessReal();
            const Real ap1 = referenceData(i, "AP1").accessReal();
            const Real ap2 = referenceData(i, "AP2").accessReal();
            const Real ap3 = referenceData(i, "AP3").accessReal();
            const Real ap4 = referenceData(i, "AP4").accessReal();
            const Real ap5 = referenceData(i, "AP5").accessReal();
            const Real ap6 = referenceData(i, "AP6").accessReal();
            const Real ap7 = referenceData(i, "AP7").accessReal();
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::ISO8601);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Kilometers(altitude));
            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Unique<NRLMSISE00Public::ap_array> apValues = nrlmsise.computeApArray(instant);
            const Unique<NRLMSISE00Public::nrlmsise_input> input =
                nrlmsise.computeNRLMSISE00Input(apValues, lla, instant);

            const Real secTolerance = 1e-15;  // matches much better when accounting for UT1/UTC difference!
            const Real altTolerance = 1e-15;
            const Real lstTolerance = 1.3e-8;  // matches much better when accounting for UT1/UTC difference!

            const Real secError = std::abs(sec - input->sec);
            const Real altError = std::abs(altitude - input->alt);
            const Real lstError = std::abs(lst - input->lst);

            EXPECT_EQ(doy, input->doy);
            EXPECT_TRUE(secError < secTolerance) << String::Format("{} ≈ {} Δ {} [T]", sec, input->sec, secError);
            EXPECT_TRUE(altError < altTolerance)
                << String::Format("{} ≈ {} Δ {} [T]", altitude, input->alt, altTolerance);
            EXPECT_EQ(latitude, input->g_lat);
            EXPECT_EQ(longitude, input->g_long);
            EXPECT_TRUE(lstError < lstTolerance) << String::Format("{} ≈ {} Δ {} [T]", lst, input->lst, lstError);
            EXPECT_EQ(avgFlux, input->f107A);
            EXPECT_EQ(dailyFlux, input->f107);
            EXPECT_EQ(ap1, input->ap_a->a[0]);
            EXPECT_EQ(ap2, input->ap_a->a[1]);
            EXPECT_EQ(ap3, input->ap_a->a[2]);
            EXPECT_EQ(ap4, input->ap_a->a[3]);
            EXPECT_EQ(ap5, input->ap_a->a[4]);
            EXPECT_EQ(ap6, input->ap_a->a[5]);
            EXPECT_EQ(ap7, input->ap_a->a[6]);
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, OrekitGenerateNRLMSISEDensityUTC)
{
    /*
     * This test compares the computed density when we theoretically have identical inputs as Orekit. It uses the same
     * comparison file as the previous test, which shows that the inputs are nearly identical.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISEInputsAndDensityUTC.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());
        const NRLMSISE00Public nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            Real::Undefined(),
            Real::Undefined(),
            Real::Undefined(),
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const DateTime datetime =
                DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::ISO8601);
            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();

            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Kilometers(altitude));
            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Real density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const Real percentTolerance = 0.014;
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
    OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00,
    GetDensityConstantFluxAndGeoMagInputDataType
)
{
    /*
     * This test verifies that for a given position the density is the same for all instants for ConstantFluxAndGeoMag
     * Inpout Data Source Type.
     */
    {
        NRLMSISE00::InputDataType inputDataSourceType = NRLMSISE00::InputDataType::ConstantFluxAndGeoMag;
        Real f107ConstantValue = 200.0;
        Real f107AConstantValue = 205.0;
        Real kpConstantValue = -1.6;

        NRLMSISE00 nrlmsise = {inputDataSourceType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        Array<Instant> instants = {
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2020, 1, 2, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2024, 1, 2, 0, 0, 0), Scale::UTC),
        };

        LLA lla = {Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0)};

        for (const auto& instant : instants)
        {
            Real density = nrlmsise.getDensityAt(lla, instant);
            EXPECT_TRUE(1.16099e-08 - density <= 1e-12);  // Always the same value
        }
    }
}
