/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/NRLMSISE00.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived/Angle.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

#include <Global.test.hpp>

using ostk::core::types::String;
using ostk::core::types::Real;

using ostk::physics::units::Length;
using ostk::physics::units::Angle;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::time::Scale;
using ostk::physics::coord::Position;
using ostk::physics::coord::spherical::LLA;
using ostk::physics::coord::Frame;
using ostk::physics::environment::atmospheric::earth::NRLMSISE00;
using EarthCelestialBody = ostk::physics::env::obj::celest::Earth;
using EarthGravitationalModel = ostk::physics::environment::gravitational::Earth;

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

        EXPECT_NO_THROW(const NRLMSISE00* nrlmsisePtr = nrlmsise.clone(); delete nrlmsisePtr;);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, IsDefined)
{
    using ostk::physics::environment::atmospheric::earth::NRLMSISE00;

    {
        const NRLMSISE00 nrlmsise = {};

        EXPECT_TRUE(nrlmsise.isDefined());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit3HourMarks)
{
    using ostk::core::ctnr::Table;
    using ostk::core::ctnr::Array;

    using ostk::core::fs::File;
    using ostk::core::fs::Path;

    using ostk::core::types::Index;
    using ostk::core::types::Size;
    using ostk::core::types::Integer;

    using ostk::physics::time::Date;
    using ostk::physics::time::Time;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;

    const File referenceDataFile = File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/OreKitCSSIParameters3HourMarks.csv"
             ));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = 10;//referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {};

        for (Index i = 0; i < rowCount; i++) {

            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            Instant instant = Instant::DateTime(datetime, Scale::UTC);
            std::cout << "instant: " << instant.toString(Scale::UTC) << std::endl;
            double apArray[7];
            nrlmsise.computeAPArray(apArray, instant);

            Array<Real> apArrayReal = Array<Real>(apArray, apArray+7);
            // std::cout << "ap array: " << apArrayReal << std::endl;

            std::cout << "reference array" << std::endl;
            std::cout << referenceData(i,"AP_0").accessReal() << " <> " << apArray[0] << std::endl;
            std::cout << referenceData(i,"AP_1").accessReal() << " <> " << apArray[1] << std::endl;
            std::cout << referenceData(i,"AP_2").accessReal() << " <> " << apArray[2] << std::endl;
            std::cout << referenceData(i,"AP_3").accessReal() << " <> " << apArray[3] << std::endl;
            std::cout << referenceData(i,"AP_4").accessReal() << " <> " << apArray[4] << std::endl;
            std::cout << referenceData(i,"AP_5").accessReal() << " <> " << apArray[5] << std::endl;
            std::cout << referenceData(i,"AP_6").accessReal() << " <> " << apArray[6] << std::endl;
            
            EXPECT_TRUE(referenceData(i,"AP_0").accessReal().isNear(apArray[0], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_0").accessReal(), apArray[0], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_1").accessReal().isNear(apArray[1], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_1").accessReal(), apArray[1], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_2").accessReal().isNear(apArray[2], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_2").accessReal(), apArray[2], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_3").accessReal().isNear(apArray[3], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_3").accessReal(), apArray[3], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_4").accessReal().isNear(apArray[4], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_4").accessReal(), apArray[4], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_5").accessReal().isNear(apArray[5], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_5").accessReal(), apArray[5], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_6").accessReal().isNear(apArray[6], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_6").accessReal(), apArray[6], datetime.toString());

        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit3HourMarksShifted)
{
    using ostk::core::ctnr::Table;
    using ostk::core::ctnr::Array;

    using ostk::core::fs::File;
    using ostk::core::fs::Path;

    using ostk::core::types::Index;
    using ostk::core::types::Size;
    using ostk::core::types::Integer;

    using ostk::physics::time::Date;
    using ostk::physics::time::Time;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;

    const File referenceDataFile = File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/OreKitCSSIParameters3HourMarksShifted.csv"
             ));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {};

        for (Index i = 0; i < rowCount; i++) {

            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            Instant instant = Instant::DateTime(datetime, Scale::UTC);

            double apArray[7];
            nrlmsise.computeAPArray(apArray, instant);

            Array<Real> apArrayReal = Array<Real>(apArray, apArray+7);
            
            EXPECT_TRUE(referenceData(i,"AP_0").accessReal().isNear(apArray[0], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_0").accessReal(), apArray[0], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_1").accessReal().isNear(apArray[1], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_1").accessReal(), apArray[1], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_2").accessReal().isNear(apArray[2], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_2").accessReal(), apArray[2], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_3").accessReal().isNear(apArray[3], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_3").accessReal(), apArray[3], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_4").accessReal().isNear(apArray[4], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_4").accessReal(), apArray[4], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_5").accessReal().isNear(apArray[5], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_5").accessReal(), apArray[5], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_6").accessReal().isNear(apArray[6], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_6").accessReal(), apArray[6], datetime.toString());

        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayOrekit)
{
    using ostk::core::ctnr::Table;
    using ostk::core::ctnr::Array;

    using ostk::core::fs::File;
    using ostk::core::fs::Path;

    using ostk::core::types::Index;
    using ostk::core::types::Size;
    using ostk::core::types::Integer;

    using ostk::physics::time::Date;
    using ostk::physics::time::Time;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;

    const File referenceDataFile = File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/OreKitCSSIParameters.csv"
             ));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = 49;//referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {};

        for (Index i = 48; i < rowCount; i++) {

            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);

            Instant instant = Instant::DateTime(datetime, Scale::UTC);
            std::cout << "instant: " << instant.toString(Scale::UTC) << std::endl;
            double apArray[7];
            nrlmsise.computeAPArray(apArray, instant);

            Array<Real> apArrayReal = Array<Real>(apArray, apArray+7);
            // std::cout << "ap array: " << apArrayReal << std::endl;

            // std::cout << "reference array" << std::endl;
            // std::cout << referenceData(i,"AP_0").accessReal() << std::endl;
            // std::cout << referenceData(i,"AP_1").accessReal() << std::endl;
            // std::cout << referenceData(i,"AP_2").accessReal() << std::endl;
            // std::cout << referenceData(i,"AP_3").accessReal() << std::endl;
            // std::cout << referenceData(i,"AP_4").accessReal() << std::endl;
            // std::cout << referenceData(i,"AP_5").accessReal() << std::endl;
            // std::cout << referenceData(i,"AP_6").accessReal() << std::endl;
            
            EXPECT_TRUE(referenceData(i,"AP_0").accessReal().isNear(apArray[0], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_0").accessReal(), apArray[0], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_1").accessReal().isNear(apArray[1], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_1").accessReal(), apArray[1], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_2").accessReal().isNear(apArray[2], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_2").accessReal(), apArray[2], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_3").accessReal().isNear(apArray[3], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_3").accessReal(), apArray[3], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_4").accessReal().isNear(apArray[4], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_4").accessReal(), apArray[4], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_5").accessReal().isNear(apArray[5], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_5").accessReal(), apArray[5], datetime.toString());
            EXPECT_TRUE(referenceData(i,"AP_6").accessReal().isNear(apArray[6], 0.001)) << String::Format(
            "{} != {} on {}", referenceData(i,"AP_6").accessReal(), apArray[6], datetime.toString());

        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, ComputeAPArrayCCMC)
{
    using ostk::core::ctnr::Table;
    using ostk::core::ctnr::Array;

    using ostk::core::fs::File;
    using ostk::core::fs::Path;

    using ostk::core::types::Index;
    using ostk::core::types::Size;
    using ostk::core::types::Integer;

    using ostk::physics::time::Date;
    using ostk::physics::time::Time;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;

    const File referenceDataFile = File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CCMCGoddardTest.csv"
             ));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = 3;//referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {};

        for (Index i = 0; i < rowCount; i++) {

            const Integer year = referenceData(i, "Year").accessInteger();
            const Integer month = referenceData(i, "Mon").accessInteger();
            const Integer day = referenceData(i, "Day").accessInteger();
            const Real hour = referenceData(i, "hour").accessReal();

            Instant instant = Instant::DateTime(DateTime(Date(year, month, day), Time(hour.floor(), 0, 0)), Scale::UTC);
            std::cout << "instant: " << instant.toString(Scale::UTC) << std::endl;
            double apArray[7];
            nrlmsise.computeAPArray(apArray, instant);

            Array<Real> apArrayReal = Array<Real>(apArray, apArray+7);
            std::cout << "ap array: " << apArrayReal << std::endl;

            std::cout << "reference array" << std::endl;
            std::cout << referenceData(i,"apdaily").accessReal() << std::endl;
            std::cout << referenceData(i,"ap0-3").accessReal() << std::endl;
            std::cout << referenceData(i,"ap3-6").accessReal() << std::endl;
            std::cout << referenceData(i,"ap6-9").accessReal() << std::endl;
            std::cout << referenceData(i,"ap9-12").accessReal() << std::endl;
            std::cout << referenceData(i,"ap12-33").accessReal() << std::endl;
            std::cout << referenceData(i,"ap33-59").accessReal() << std::endl;
            // CCMC reference rounds to nearest 0.1
            // EXPECT_TRUE(referenceData(i,"apdaily").accessReal().isNear(apArray[0], 0.1));
            // EXPECT_TRUE(referenceData(i,"ap0-3").accessReal().isNear(apArray[1], 0.1));
            // EXPECT_TRUE(referenceData(i,"ap3-6").accessReal().isNear(apArray[2], 0.1));
            // EXPECT_TRUE(referenceData(i,"ap6-9").accessReal().isNear(apArray[3], 0.1));
            // EXPECT_TRUE(referenceData(i,"ap9-12").accessReal().isNear(apArray[4], 0.1));
            // EXPECT_TRUE(referenceData(i,"ap12-33").accessReal().isNear(apArray[5], 0.1));
            // EXPECT_TRUE(referenceData(i,"ap33-59").accessReal().isNear(apArray[6], 0.1));

        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_NRLMSISE00, GetDensityAt)
{
    using ostk::core::ctnr::Table;
    using ostk::core::fs::File;
    using ostk::core::fs::Path;

    using ostk::core::types::Index;
    using ostk::core::types::Size;

    const File referenceDataFile = File::Path(Path::Parse(
                 "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/OreKitNRLMSISE500km.csv"
             ));

    const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);
    Size rowCount = referenceData.getRowCount();

    {
        const NRLMSISE00 nrlmsise = {};

        for (Index i = 0; i < rowCount; i++) {

            const Real latitude = referenceData(i, "LAT").accessReal();
            const Real longitude = referenceData(i, "LON").accessReal();
            const Real altitude = referenceData(i, "ALT").accessReal();
            const Real referenceDensity = referenceData(i, "DENSITY").accessReal();
            const DateTime datetime = DateTime::Parse(referenceData(i, "DATE").accessString(), DateTime::Format::Standard);


            const LLA lla = LLA(Angle::Degrees(latitude), Angle::Degrees(longitude), Length::Meters(altitude));

            const Position position = {
                lla.toCartesian(
                    EarthGravitationalModel::EGM2008.equatorialRadius_, EarthGravitationalModel::EGM2008.flattening_
                ),
                Position::Unit::Meter,
                Frame::ITRF()};

            const Real density = nrlmsise.getDensityAt(position, Instant::DateTime(datetime, Scale::UTC));

            const Real tolerance = 1e-15;

            EXPECT_TRUE(density.isNear(referenceDensity, tolerance)) << String::Format(
                "{} ≈ {} Δ {} [T]", density.toString(), referenceDensity.toString(), (density - referenceDensity)
            );
        }
    }
}
