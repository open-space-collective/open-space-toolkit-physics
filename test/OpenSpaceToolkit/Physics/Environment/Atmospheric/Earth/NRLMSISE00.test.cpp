/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/SPICE.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Length.hpp>
#include <OpenSpaceToolkit/Physics/Utility/String.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Index;
using ostk::core::type::Shared;
using ostk::core::type::Size;
using ostk::core::type::String;
using ostk::core::type::Unique;

using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::spherical::LLA;
using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;
using ostk::physics::environment::atmospheric::earth::NRLMSISE00;
using ostk::physics::environment::object::Celestial;
using ostk::physics::environment::object::celestial::Sun;
using ostk::physics::time::DateTime;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;
using ostk::physics::unit::Angle;
using ostk::physics::unit::Length;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

using EarthAtmosphericModel = ostk::physics::environment::atmospheric::Earth;
using ostk::physics::environment::atmospheric::earth::Manager;
using ostk::physics::utility::DoubleToString;

// Expose protected members for testing
class NRLMSISE00Public : public NRLMSISE00
{
   public:
    NRLMSISE00Public(
        const NRLMSISE00::InputDataType& anInputDataType = NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
        double aF107ConstantValue = EarthAtmosphericModel::defaultF107ConstantValue,
        double aF107AConstantValue = EarthAtmosphericModel::defaultF107AConstantValue,
        double aKpConstantValue = EarthAtmosphericModel::defaultKpConstantValue,
        const Shared<const Frame>& anEarthFrameSPtr = Frame::ITRF(),
        const Length& anEarthRadius = EarthGravitationalModel::WGS84.equatorialRadius_,
        double anEarthFlattening = EarthGravitationalModel::WGS84.flattening_,
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

    using NRLMSISE00::ap_array;
    using NRLMSISE00::computeApArray;
    using NRLMSISE00::computeNRLMSISE00Input;
    using NRLMSISE00::convertKpToAp;
    using NRLMSISE00::GetDensityAt;
    using NRLMSISE00::nrlmsise_input;
};

class OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00 : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/SW-Last5Years.csv")
        );
        const CSSISpaceWeather spaceWeather = CSSISpaceWeather::Load(file);

        manager_.loadCSSISpaceWeather(spaceWeather);
    }

    Manager& manager_ = Manager::Get();
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Constructor)
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

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Clone)
{
    {
        const NRLMSISE00 nrlmsise = {};

        EXPECT_NO_THROW(nrlmsise.clone());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, Getters)
{
    {
        const NRLMSISE00::InputDataType inputDataType = NRLMSISE00::InputDataType::ConstantFluxAndGeoMag;
        const double f107ConstantValue = 200.0;
        const double f107AConstantValue = 205.0;
        const double kpConstantValue = 3.0;

        const NRLMSISE00 nrlmsise = {inputDataType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        EXPECT_EQ(inputDataType, nrlmsise.getInputDataType());
        EXPECT_EQ(f107ConstantValue, nrlmsise.getF107ConstantValue());
        EXPECT_EQ(f107AConstantValue, nrlmsise.getF107AConstantValue());
        EXPECT_EQ(kpConstantValue, nrlmsise.getKpConstantValue());
    }

    {
        const NRLMSISE00::InputDataType inputDataType = NRLMSISE00::InputDataType::CSSISpaceWeatherFile;
        const double f107ConstantValue = 200.0;
        const double f107AConstantValue = 205.0;
        const double kpConstantValue = 3.0;

        const NRLMSISE00 nrlmsise = {inputDataType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        EXPECT_EQ(inputDataType, nrlmsise.getInputDataType());
        EXPECT_EQ(f107ConstantValue, nrlmsise.getF107ConstantValue());
        EXPECT_EQ(f107AConstantValue, nrlmsise.getF107AConstantValue());
        EXPECT_EQ(kpConstantValue, nrlmsise.getKpConstantValue());
    }

    {
        const NRLMSISE00::InputDataType inputDataType = NRLMSISE00::InputDataType::CSSISpaceWeatherFile;

        const NRLMSISE00 nrlmsise = {inputDataType};

        EXPECT_EQ(inputDataType, nrlmsise.getInputDataType());
        EXPECT_EQ(EarthAtmosphericModel::defaultF107ConstantValue, nrlmsise.getF107ConstantValue());
        EXPECT_EQ(
            EarthAtmosphericModel::defaultF107AConstantValue, nrlmsise.getF107AConstantValue()
        );  // TBI: Make these static default var
        EXPECT_EQ(EarthAtmosphericModel::defaultKpConstantValue, nrlmsise.getKpConstantValue());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ConvertKpToAp)
{
    {
        EXPECT_EQ(NRLMSISE00Public::convertKpToAp(-1.6), 1.0);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayConstantFluxAndGeoMag)
{
    /*
     * This test is to confirm that we compute fixed values for AP solar index values when using constant flux input
     * data source type.
     */

    {
        const NRLMSISE00Public::InputDataType inputDataType = NRLMSISE00Public::InputDataType::ConstantFluxAndGeoMag;
        const double f107ConstantValue = 200.0;
        const double f107AConstantValue = 205.0;
        const double kpConstantValue = -1.6;

        const NRLMSISE00Public nrlmsise = {inputDataType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        const Array<Instant> instants = {
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

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit3HourMarksShifted)
{
    /*
     * This test is to confirm that we compute the same AP solar index values as Orekit when not at 3hour marks.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitCSSIParameters3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    const Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00Public nrlmsise = {};

        for (Index i = 0; i < rowCount; i++)
        {
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::Standard);

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            Unique<NRLMSISE00Public::ap_array> apArray = nrlmsise.computeApArray(instant);

            EXPECT_NEAR(referenceData(i, "AP_0").getReal(), apArray->a[0], 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_0").getReal(), apArray->a[0], datetime.toString()
            );
            EXPECT_NEAR(referenceData(i, "AP_1").getReal(), apArray->a[1], 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_1").getReal(), apArray->a[1], datetime.toString()
            );
            EXPECT_NEAR(referenceData(i, "AP_2").getReal(), apArray->a[2], 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_2").getReal(), apArray->a[2], datetime.toString()
            );
            EXPECT_NEAR(referenceData(i, "AP_3").getReal(), apArray->a[3], 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_3").getReal(), apArray->a[3], datetime.toString()
            );
            EXPECT_NEAR(referenceData(i, "AP_4").getReal(), apArray->a[4], 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_4").getReal(), apArray->a[4], datetime.toString()
            );
            EXPECT_NEAR(referenceData(i, "AP_5").getReal(), apArray->a[5], 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_5").getReal(), apArray->a[5], datetime.toString()
            );
            EXPECT_NEAR(referenceData(i, "AP_6").getReal(), apArray->a[6], 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AP_6").getReal(), apArray->a[6], datetime.toString()
            );
        }
    }
}

/* ignored for now pending resolution of: https://gitlab.orekit.org/orekit/orekit/-/issues/1119 */
// TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit3HrMarks)
// {

//     const File referenceDataFile = File::Path(Path::Parse(
//                  "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/OreKitCSSIParameters3HourMarks.csv"
//              ));

//     const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
//     const Size rowCount = referenceData.getRowCount();

//     {
//         const NRLMSISE00 nrlmsise = {};

//         for (Index i =48; i < rowCount; i++) {

//             const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(),
//             DateTime::Format::Standard);

//             Instant instant = Instant::DateTime(datetime, Scale::UTC);
//             std::cout << "instant: " << instant.toString(Scale::UTC) << std::endl;
//             double apArray[7];
//             nrlmsise.computeApArray(apArray, instant);

//             Array<double> apArrayReal = Array<double>(apArray, apArray+7);

//             std::cout << "calc <> Orekit" << std::endl;
//             std::cout << apArrayReal[0] << " <> " << referenceData(i, "AP_0").getReal() << std::endl;
//             std::cout << apArrayReal[1] << " <> " << referenceData(i, "AP_1").getReal() << std::endl;
//             std::cout << apArrayReal[2] << " <> " << referenceData(i, "AP_2").getReal() << std::endl;
//             std::cout << apArrayReal[3] << " <> " << referenceData(i, "AP_3").getReal() << std::endl;
//             std::cout << apArrayReal[4] << " <> " << referenceData(i, "AP_4").getReal() << std::endl;
//             std::cout << apArrayReal[5] << " <> " << referenceData(i, "AP_5").getReal() << std::endl;
//             std::cout << apArrayReal[6] << " <> " << referenceData(i, "AP_6").getReal() << std::endl;

//             EXPECT_TRUE(referenceData(i,"AP_0").getReal().isNear(apArray[0], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_0").getReal(), apArray[0], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_1").getReal().isNear(apArray[1], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_1").getReal(), apArray[1], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_2").getReal().isNear(apArray[2], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_2").getReal(), apArray[2], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_3").getReal().isNear(apArray[3], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_3").getReal(), apArray[3], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_4").getReal().isNear(apArray[4], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_4").getReal(), apArray[4], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_5").getReal().isNear(apArray[5], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_5").getReal(), apArray[5], datetime.toString());
//             EXPECT_TRUE(referenceData(i,"AP_6").getReal().isNear(apArray[6], 0.001)) << String::Format(
//             "{} != {} on {}", referenceData(i,"AP_6").getReal(), apArray[6], datetime.toString());

//         }
//     }
// }

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeNRLMISE00InputOrekit)
{
    /*
     * This test is to confirm that we compute the same Flux values as Orekit when not at 3hour marks.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitCSSIParameters3HourMarksShifted.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    const Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00Public nrlmsise = {};

        for (Index i = 0; i < rowCount; i++)
        {
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::Standard);

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const LLA lla = LLA(Angle::Degrees(0), Angle::Degrees(0), Length::Meters(500000));

            Unique<NRLMSISE00Public::nrlmsise_input> input =
                nrlmsise.computeNRLMSISE00Input(nrlmsise.computeApArray(instant), lla, instant);

            EXPECT_NEAR(referenceData(i, "DAILY_FLUX").getReal(), input->f107, 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "DAILY_FLUX").getReal(), input->f107, datetime.toString()
            );
            EXPECT_NEAR(referenceData(i, "AVG_FLUX").getReal(), input->f107A, 0.001) << String::Format(
                "{} != {} on {}", referenceData(i, "AVG_FLUX").getReal(), input->f107A, datetime.toString()
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOrekit3HrMarksPreciseLST)
{
    /*
     * This test uses a precise local solar time just like Orekit. It doesn't match well for the following reasons:
     * 1. There are know difference in how Orekit computes AP values at exact 3 hour marks
     * 2. The orekit data was generated using their default UT1 time scale, rather than UTC
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISE500km3HourMarks.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    const Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {};

        for (Index i = 0; i < rowCount; i++)
        {
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double referenceDensity = referenceData(i, "DENSITY").getReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const double density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const double percentTolerance = 43.0;
            const double percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const double absoluteTolerate = 1.0e-15;
            const double absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]",
                DoubleToString(density),
                DoubleToString(referenceDensity),
                absoluteError,
                percentError
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOrekit3HrMarkShiftedPreciseLST)
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
    const Size rowCount = referenceData.getRowCount();

    {
        const Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel::defaultF107ConstantValue,
            EarthAtmosphericModel::defaultF107AConstantValue,
            EarthAtmosphericModel::defaultKpConstantValue,
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double referenceDensity = referenceData(i, "DENSITY").getReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const double density = nrlmsise.getDensityAt(lla, instant);

            const double absoluteTolerate = 1.0e-15;
            const double absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate) << String::Format(
                "{} ≈ {} Δ {} [T]", DoubleToString(density), DoubleToString(referenceDensity), absoluteError
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtOrekit3HrMarkShiftedStandardLST)
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
    const Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel::defaultF107ConstantValue,
            EarthAtmosphericModel::defaultF107AConstantValue,
            EarthAtmosphericModel::defaultKpConstantValue,
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double referenceDensity = referenceData(i, "DENSITY").getReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const double density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const double percentTolerance = 3.62;
            const double percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const double absoluteTolerate = 1.0e-15;
            const double absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]",
                DoubleToString(density),
                DoubleToString(referenceDensity),
                absoluteError,
                percentError
            );
        }
    }
}

TEST_F(
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
    const Size rowCount = referenceData.getRowCount();

    {
        const Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel::defaultF107ConstantValue,
            EarthAtmosphericModel::defaultF107AConstantValue,
            EarthAtmosphericModel::defaultKpConstantValue,
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double referenceDensity = referenceData(i, "DENSITY").getReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::Standard);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::WGS84.equatorialRadius_, EarthGravitationalModel::WGS84.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()
            };

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const double density = nrlmsise.getDensityAt(lla, instant);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const double absoluteTolerate = 1e-15;
            const double absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate) << String::Format(
                "{} ≈ {} Δ {} [T]", DoubleToString(density), DoubleToString(referenceDensity), absoluteError
            );
        }
    }
}

TEST_F(
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
    const Size rowCount = referenceData.getRowCount();

    {
        const Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());

        const NRLMSISE00 nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel::defaultF107ConstantValue,
            EarthAtmosphericModel::defaultF107AConstantValue,
            EarthAtmosphericModel::defaultKpConstantValue,
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double referenceDensity = referenceData(i, "DENSITY").getReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::ISO8601);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const double density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const double percentTolerance = 0.0131;
            const double percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const double absoluteTolerate = 1e-15;
            const double absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]",
                DoubleToString(density),
                DoubleToString(referenceDensity),
                absoluteError,
                percentError
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAtNRLMSISEWithOrekitInputs)
{
    /*
     * This test checks the density generated by OSTk when using the actual inputs that Orekit generates for itself. It
     * was exported using some shenanigans in orekit_tooling. See `GenerateNRLMSISEDensityTestDataWithInputs`
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISEInputsAndDensity.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    const Size rowCount = referenceData.getRowCount();

    {
        for (Index i = 0; i < rowCount; i++)
        {
            const int doy = referenceData(i, "DOY").getInteger();
            const double sec = referenceData(i, "SEC").getReal();
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double lst = referenceData(i, "LST").getReal();
            const double avgFlux = referenceData(i, "AVG_FLUX").getReal();
            const double dailyFlux = referenceData(i, "DAILY_FLUX").getReal();
            const double ap1 = referenceData(i, "AP1").getReal();
            const double ap2 = referenceData(i, "AP2").getReal();
            const double ap3 = referenceData(i, "AP3").getReal();
            const double ap4 = referenceData(i, "AP4").getReal();
            const double ap5 = referenceData(i, "AP5").getReal();
            const double ap6 = referenceData(i, "AP6").getReal();
            const double ap7 = referenceData(i, "AP7").getReal();
            const double referenceDensity = referenceData(i, "DENSITY").getReal();

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

            const double density = NRLMSISE00Public::GetDensityAt(input);

            // Check percent tolerance here for low altitudes
            const double percentTolerance = 0.0131;
            const double percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const double absoluteTolerate = 1e-15;
            const double absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]",
                DoubleToString(density),
                DoubleToString(referenceDensity),
                absoluteError,
                percentError
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, OrekitGenerateNRLMSISEInputs)
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
    const Size rowCount = referenceData.getRowCount();

    {
        const Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());
        const NRLMSISE00Public nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel::defaultF107ConstantValue,
            EarthAtmosphericModel::defaultF107AConstantValue,
            EarthAtmosphericModel::defaultKpConstantValue,
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const int doy = referenceData(i, "DOY").getInteger();
            const double sec = referenceData(i, "SEC").getReal();
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double lst = referenceData(i, "LST").getReal();
            const double avgFlux = referenceData(i, "AVG_FLUX").getReal();
            const double dailyFlux = referenceData(i, "DAILY_FLUX").getReal();
            const double ap1 = referenceData(i, "AP1").getReal();
            const double ap2 = referenceData(i, "AP2").getReal();
            const double ap3 = referenceData(i, "AP3").getReal();
            const double ap4 = referenceData(i, "AP4").getReal();
            const double ap5 = referenceData(i, "AP5").getReal();
            const double ap6 = referenceData(i, "AP6").getReal();
            const double ap7 = referenceData(i, "AP7").getReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::ISO8601);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Kilometers(altitude));
            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Unique<NRLMSISE00Public::ap_array> apValues = nrlmsise.computeApArray(instant);
            const Unique<NRLMSISE00Public::nrlmsise_input> input =
                nrlmsise.computeNRLMSISE00Input(apValues, lla, instant);

            const double secTolerance = 0.02;  // does not match well
            const double altTolerance = 1e-15;
            const double lstTolerance = 4e-5;  // does not match well

            const double secError = std::abs(sec - input->sec);
            const double altError = std::abs(altitude - input->alt);
            const double lstError = std::abs(lst - input->lst);

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

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, OrekitGenerateNRLMSISEInputsUTC)
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
    const Size rowCount = referenceData.getRowCount();

    {
        const Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());
        const NRLMSISE00Public nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel::defaultF107ConstantValue,
            EarthAtmosphericModel::defaultF107AConstantValue,
            EarthAtmosphericModel::defaultKpConstantValue,
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const int doy = referenceData(i, "DOY").getInteger();
            const double sec = referenceData(i, "SEC").getReal();
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();
            const double lst = referenceData(i, "LST").getReal();
            const double avgFlux = referenceData(i, "AVG_FLUX").getReal();
            const double dailyFlux = referenceData(i, "DAILY_FLUX").getReal();
            const double ap1 = referenceData(i, "AP1").getReal();
            const double ap2 = referenceData(i, "AP2").getReal();
            const double ap3 = referenceData(i, "AP3").getReal();
            const double ap4 = referenceData(i, "AP4").getReal();
            const double ap5 = referenceData(i, "AP5").getReal();
            const double ap6 = referenceData(i, "AP6").getReal();
            const double ap7 = referenceData(i, "AP7").getReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::ISO8601);

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Kilometers(altitude));
            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const Unique<NRLMSISE00Public::ap_array> apValues = nrlmsise.computeApArray(instant);
            const Unique<NRLMSISE00Public::nrlmsise_input> input =
                nrlmsise.computeNRLMSISE00Input(apValues, lla, instant);

            const double secTolerance = 1e-15;  // matches much better when accounting for UT1/UTC difference!
            const double altTolerance = 1e-15;
            const double lstTolerance = 1.3e-8;  // matches much better when accounting for UT1/UTC difference!

            const double secError = std::abs(sec - input->sec);
            const double altError = std::abs(altitude - input->alt);
            const double lstError = std::abs(lst - input->lst);

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

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, OrekitGenerateNRLMSISEDensityUTC)
{
    /*
     * This test compares the computed density when we theoretically have identical inputs as Orekit. It uses the same
     * comparison file as the previous test, which shows that the inputs are nearly identical.
     */
    const File referenceDataFile =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00/"
                               "OreKitNRLMSISEInputsAndDensityUTC.csv"));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    const Size rowCount = referenceData.getRowCount();

    {
        const Shared<Celestial> sun = std::make_shared<Celestial>(Sun::Default());
        const NRLMSISE00Public nrlmsise = {
            NRLMSISE00::InputDataType::CSSISpaceWeatherFile,
            EarthAtmosphericModel::defaultF107ConstantValue,
            EarthAtmosphericModel::defaultF107AConstantValue,
            EarthAtmosphericModel::defaultKpConstantValue,
            Frame::ITRF(),
            EarthGravitationalModel::WGS84.equatorialRadius_,
            EarthGravitationalModel::WGS84.flattening_,
            sun
        };

        for (Index i = 0; i < rowCount; i++)
        {
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").getString(), DateTime::Format::ISO8601);
            const double latitude = referenceData(i, "LAT").getReal();
            const double longitude = referenceData(i, "LON").getReal();
            const double altitude = referenceData(i, "ALT").getReal();

            const double referenceDensity = referenceData(i, "DENSITY").getReal();

            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Kilometers(altitude));
            const Instant instant = Instant::DateTime(datetime, Scale::UTC);

            const double density = nrlmsise.getDensityAt(lla, instant);

            // Check percent tolerance here for low altitudes
            const double percentTolerance = 0.014;
            const double percentError = 100.0 * (std::abs(density - referenceDensity) / referenceDensity);

            // But still allow a pass if the absolute error is small (because we're close to machine precision)
            const double absoluteTolerate = 1e-15;
            const double absoluteError = std::abs(density - referenceDensity);

            EXPECT_TRUE(absoluteError < absoluteTolerate || percentError < percentTolerance) << String::Format(
                "{} ≈ {} Δ {} [{}%] [T]",
                DoubleToString(density),
                DoubleToString(referenceDensity),
                absoluteError,
                percentError
            );
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityConstantFluxAndGeoMagInputDataType)
{
    /*
     * This test verifies that for a given position the density is the same for all instants for ConstantFluxAndGeoMag
     * Inpout Data Source Type.
     */
    {
        const NRLMSISE00::InputDataType inputDataType = NRLMSISE00::InputDataType::ConstantFluxAndGeoMag;
        const double f107ConstantValue = 200.0;
        const double f107AConstantValue = 205.0;
        const double kpConstantValue = -1.6;

        const NRLMSISE00 nrlmsise = {inputDataType, f107ConstantValue, f107AConstantValue, kpConstantValue};

        const Array<Instant> instants = {
            Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2020, 1, 2, 0, 0, 0), Scale::UTC),
            Instant::DateTime(DateTime(2024, 1, 2, 0, 0, 0), Scale::UTC),
        };

        const LLA lla = {Angle::Degrees(35.076832), Angle::Degrees(-92.546296), Length::Kilometers(123.0)};

        for (const auto& instant : instants)
        {
            const double density = nrlmsise.getDensityAt(lla, instant);
            EXPECT_TRUE(1.16099e-08 - density <= 1e-12);  // Always the same value
        }
    }
}
