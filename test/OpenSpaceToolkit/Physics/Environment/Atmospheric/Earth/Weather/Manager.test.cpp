/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/Manager.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetMode)
{
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const Manager& manager = Manager::Get();

        EXPECT_EQ(Manager::Mode::Automatic, manager.getMode());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetLocalRepository)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::Directory;

    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const Manager& manager = Manager::Get();

        EXPECT_EQ("weather", manager.getLocalRepository().getName());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetRemoteUrl)
{
    using ostk::io::URL;

    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const Manager& manager = Manager::Get();
        EXPECT_EQ(URL::Parse("https://celestrak.org/SpaceData/"), manager.getRemoteUrl());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetCSSISpaceWeatherArray)
{
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const Manager& manager = Manager::Get();

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherArray());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetCSSISpaceWeatherAt)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::environment::atmospheric::earth::weather::CSSISpaceWeather;
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather/SW-Last5Years.test.csv")
        );

        const CSSISpaceWeather spaceWeather = CSSISpaceWeather::Load(file);

        Manager& manager = Manager::Get();

        manager.loadCSSISpaceWeather(spaceWeather);

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.getObservationInterval().accessStart()));
        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.getObservationInterval().accessEnd()));

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.getDailyPredictionInterval().accessStart()));
        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.getDailyPredictionInterval().accessEnd()));

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.getMonthlyPredictionInterval().accessStart()));
        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.getMonthlyPredictionInterval().accessEnd()));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, getKp3HourSolarIndicesAt)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Tuple;
    using ostk::core::ctnr::Array;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const Array<Tuple<String, Array<Integer>>> referenceScenarios = {
          {"2018-01-02 12:34:56", {0,7,10,7,3,10,3,0}},
          {"2023-06-18 12:34:56", {27,20,13,20,17,17,27,20}},
          {"2023-08-02 12:34:56", {13,13,13,13,13,13,13,13}},
          {"2023-08-03 12:34:56", {13,13,13,13,13,13,13,13}},  
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Manager& manager = Manager::Get();

            // Reference data setup

            const Instant referenceInstant = Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Array<Integer> referenceIndices = std::get<1>(referenceScenario);
            
            // Test
            EXPECT_EQ(referenceIndices, manager.getKp3HourSolarIndicesAt(referenceInstant));
        }
    }
}
/*
TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetPolarMotionAt_Future)
{
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Tuple;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::math::obj::Vector2d;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::time::Duration;
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const Manager& manager = Manager::Get();

        const Instant instant = Instant::Now() + Duration::Weeks(12.0);

        manager.getPolarMotionAt(instant);
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetUt1MinusUtcAt)
{
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Tuple;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Table;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const Array<Tuple<File, Real>> referenceScenarios = {
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/"
                                    "GetUt1MinusUtcAt/DUT1 1.csv")),
             1e-4},
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/"
                                    "GetUt1MinusUtcAt/DUT1 2.csv")),
             1e-4},
            // {
            // File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/IERS/Manager/GetUt1MinusUtcAt/DUT1
            // 3.csv")), 1e-4 } // [TBI] Discrepancy with STK at leap second crossing
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Manager& manager = Manager::Get();

            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario);
            const Real tolerance = std::get<1>(referenceScenario);

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Test

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI);

                const Real referenceDUT1 = {referenceRow[3].accessReal()};

                const Real dUT1 = manager.getUt1MinusUtcAt(instant);

                EXPECT_NEAR(referenceDUT1, dUT1, tolerance)
                    << String::Format("{} - {} ~ {}", instant.toString(Scale::TAI), referenceDUT1, dUT1);
            }
        }
    }

    {
        const Manager& manager = Manager::Get();

        const Instant instant = Instant::DateTime(DateTime(2018, 10, 10, 0, 0, 0), Scale::UTC);

        EXPECT_NO_THROW(manager.getUt1MinusUtcAt(instant));
    }
}
*/
TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, SetMode)
{
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        Manager& manager = Manager::Get();

        EXPECT_EQ(Manager::Mode::Automatic, manager.getMode());

        manager.setMode(Manager::Mode::Manual);

        EXPECT_EQ(Manager::Mode::Manual, manager.getMode());

        manager.setMode(Manager::Mode::Automatic);

        EXPECT_EQ(Manager::Mode::Automatic, manager.getMode());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, SetLocalRepository)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::Directory;

    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        Manager& manager = Manager::Get();

        EXPECT_EQ("weather", manager.getLocalRepository().getName());

        manager.setLocalRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager.getLocalRepository().getName());

        manager.setLocalRepository(
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/environment/atmospheric/earth/weather"))
        );

        EXPECT_EQ("weather", manager.getLocalRepository().getName());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, SetRemoteUrl)
{
    using ostk::io::URL;

    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        Manager& manager = Manager::Get();

        EXPECT_EQ(URL::Parse("https://celestrak.org/SpaceData/"), manager.getRemoteUrl());

        manager.setRemoteUrl(URL::Parse("http://example.com"));

        EXPECT_EQ(URL::Parse("http://example.com"), manager.getRemoteUrl());

        manager.setRemoteUrl(URL::Parse("https://celestrak.org/SpaceData/"));

        EXPECT_EQ(URL::Parse("https://celestrak.org/SpaceData/"), manager.getRemoteUrl());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, LoadCSSISpaceWeather)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    using ostk::physics::environment::atmospheric::earth::weather::CSSISpaceWeather;
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        const File file = File::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather/SW-Last5Years.test.csv")
        );

        const CSSISpaceWeather spaceWeather = CSSISpaceWeather::Load(file);

        Manager& manager = Manager::Get();

        manager.reset();
        manager.loadCSSISpaceWeather(spaceWeather);

        EXPECT_ANY_THROW(manager.loadCSSISpaceWeather(spaceWeather));
        EXPECT_ANY_THROW(manager.loadCSSISpaceWeather(CSSISpaceWeather::Undefined()));
    }
}


TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, FetchLatestCSSISpaceWeather)
{
    using ostk::core::fs::File;

    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        Manager& manager = Manager::Get();

        manager.reset();
        manager.clearLocalRepository();

        const File latestCSSISpaceWeather = manager.fetchLatestCSSISpaceWeather();

        EXPECT_EQ("SW-Last5Years.csv", latestCSSISpaceWeather.getName());
        EXPECT_EQ("weather", latestCSSISpaceWeather.getParentDirectory().getParentDirectory().getParentDirectory().getName());
        EXPECT_EQ("CSSISpaceWeather", latestCSSISpaceWeather.getParentDirectory().getParentDirectory().getName());
        EXPECT_EQ("2023-06-20", latestCSSISpaceWeather.getParentDirectory().getName());
        EXPECT_EQ(
            manager.getLocalRepository().getPath().getNormalizedPath(),
            latestCSSISpaceWeather.getParentDirectory().getParentDirectory().getParentDirectory().getPath().getNormalizedPath()
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, Reset)
{
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        Manager& manager = Manager::Get();

        manager.reset();

        EXPECT_TRUE(manager.getCSSISpaceWeatherArray().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, ClearLocalRepository)
{
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        Manager& manager = Manager::Get();

        manager.clearLocalRepository();

        EXPECT_TRUE(manager.getCSSISpaceWeatherDirectory().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, Get)
{
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        EXPECT_NO_THROW(Manager::Get());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultMode)
{
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        EXPECT_EQ(Manager::Mode::Automatic, Manager::DefaultMode());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultLocalRepository)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::Directory;

    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        EXPECT_EQ("weather", Manager::DefaultLocalRepository().getName());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultLocalRepositoryLockTimeout)
{
    using ostk::physics::time::Duration;
    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        EXPECT_EQ(Duration::Seconds(60.0), Manager::DefaultLocalRepositoryLockTimeout());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultRemoteUrl)
{
    using ostk::io::URL;

    using ostk::physics::environment::atmospheric::earth::weather::Manager;

    {
        EXPECT_EQ(URL::Parse("https://celestrak.org/SpaceData/"), Manager::DefaultRemoteUrl());
    }
}

