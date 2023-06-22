/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>
#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/CSSISpaceWeather.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::ctnr::Tuple;
using ostk::core::ctnr::Array;
using ostk::core::fs::Path;
using ostk::core::fs::File;
using ostk::core::fs::Directory;

using ostk::io::URL;

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::Duration;
using ostk::physics::time::DateTime;
using ostk::physics::environment::atmospheric::earth::weather::Manager;
using ostk::physics::environment::atmospheric::earth::weather::CSSISpaceWeather;

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetMode)
{
    {
        const Manager& manager = Manager::Get();

        EXPECT_EQ(Manager::Mode::Automatic, manager.getMode());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetLocalRepository)
{
    {
        const Manager& manager = Manager::Get();

        EXPECT_EQ("weather", manager.getLocalRepository().getName());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetRemoteUrl)
{
    {
        const Manager& manager = Manager::Get();
        EXPECT_EQ(URL::Parse("https://celestrak.org/SpaceData/"), manager.getRemoteUrl());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetCSSISpaceWeatherArray)
{
    {
        const Manager& manager = Manager::Get();

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherArray());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetCSSISpaceWeatherAt)
{
    {
        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/"
                                   "CSSISpaceWeather/SW-Last5Years.test.csv"));

        const CSSISpaceWeather spaceWeather = CSSISpaceWeather::Load(file);

        Manager& manager = Manager::Get();

        manager.loadCSSISpaceWeather(spaceWeather);

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.accessObservationInterval().accessStart()));
        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.accessObservationInterval().accessEnd()));

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.accessDailyPredictionInterval().accessStart()));
        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.accessDailyPredictionInterval().accessEnd()));

        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.accessMonthlyPredictionInterval().accessStart()));
        EXPECT_NO_THROW(manager.getCSSISpaceWeatherAt(spaceWeather.accessMonthlyPredictionInterval().accessEnd()));
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetKp3HourSolarIndicesAt)
{
    {
        const Array<Tuple<String, Array<Integer>>> referenceScenarios = {
            //{"2018-01-02 12:34:56", {17, 7, 3, 7, 17, 10, 20, 10}},
            //{"2023-06-18 12:34:56", {27, 20, 13, 20, 17, 17, 27, 20}},
            //{"2023-08-02 12:34:56", {13, 13, 13, 13, 13, 13, 13, 13}},
            {"2023-08-03 12:34:56", {13, 13, 13, 13, 13, 13, 13, 13}},
        };

        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/"
                                   "CSSISpaceWeather/SW-Last5Years.test.csv"));

        const CSSISpaceWeather spaceWeather = CSSISpaceWeather::Load(file);

        Manager& manager = Manager::Get();
        manager.reset();
        manager.loadCSSISpaceWeather(spaceWeather);

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Array<Integer> referenceIndices = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceIndices, manager.getKp3HourSolarIndicesAt(referenceInstant));
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetAp3HourSolarIndicesAt)
{
    {
        const Array<Tuple<String, Array<Integer>>> referenceScenarios = {
            {"2018-01-02 12:34:56", {6, 3, 2, 3, 6, 4, 7, 4, 4}},
            {"2023-06-18 12:34:56", {12, 7, 5, 7, 6, 6, 12, 7, 8}},
            {"2023-08-02 12:34:56", {5, 5, 5, 5, 5, 5, 5, 5, 5}},
            {"2023-08-03 12:34:56", {5, 5, 5, 5, 5, 5, 5, 5, 5}},
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Manager& manager = Manager::Get();

            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Array<Integer> referenceIndices = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceIndices, manager.getAp3HourSolarIndicesAt(referenceInstant));
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetF107SolarFluxAt)
{
    {
        const Array<Tuple<String, Real>> referenceScenarios = {
            {"2018-01-02 12:34:56", 69.5},  // observation
            {"2023-06-18 12:34:56", 164.1},
            {"2023-08-02 12:34:56", 165.0},  // daily prediction
            {"2023-08-03 12:34:56", 165.1},
            {"2023-10-01 12:34:56", 154.0},  // monthly prediction
            {"2028-09-01 12:34:56", 82.7},
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Manager& manager = Manager::Get();

            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Real referenceValue = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceValue, manager.getF107SolarFluxAt(referenceInstant));
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, GetF107SolarFlux81DayAvgAt)
{
    {
        const Array<Tuple<String, Real>> referenceScenarios = {
            {"2018-01-02 12:34:56", 71.5},  // observation
            {"2023-06-18 12:34:56", 160.4},
            {"2023-08-02 12:34:56", 157.5},  // daily prediction
            {"2023-08-03 12:34:56", 157.4},
            {"2023-10-01 12:34:56", 153.9},  // monthly prediction
            {"2028-09-01 12:34:56", 83.2},
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            const Manager& manager = Manager::Get();

            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Real referenceValue = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceValue, manager.getF107SolarFlux81DayAvgAt(referenceInstant));
        }
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, SetMode)
{
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
    {
        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Weather/"
                                   "CSSISpaceWeather/SW-Last5Years.test.csv"));

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
    {
        Manager& manager = Manager::Get();

        manager.reset();
        manager.clearLocalRepository();

        const File latestCSSISpaceWeather = manager.fetchLatestCSSISpaceWeather();

        EXPECT_EQ("SW-Last5Years.csv", latestCSSISpaceWeather.getName());
        EXPECT_EQ(
            "weather", latestCSSISpaceWeather.getParentDirectory().getParentDirectory().getParentDirectory().getName()
        );
        EXPECT_EQ("CSSISpaceWeather", latestCSSISpaceWeather.getParentDirectory().getParentDirectory().getName());
        EXPECT_EQ(
            manager.getLocalRepository().getPath().getNormalizedPath(),
            latestCSSISpaceWeather.getParentDirectory()
                .getParentDirectory()
                .getParentDirectory()
                .getPath()
                .getNormalizedPath()
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, Reset)
{
    {
        Manager& manager = Manager::Get();

        manager.reset();

        EXPECT_TRUE(manager.getCSSISpaceWeatherArray().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, ClearLocalRepository)
{
    {
        Manager& manager = Manager::Get();

        manager.clearLocalRepository();

        EXPECT_TRUE(manager.getCSSISpaceWeatherDirectory().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, Manager::DefaultMode());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultLocalRepository)
{
    {
        EXPECT_EQ("weather", Manager::DefaultLocalRepository().getName());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultLocalRepositoryLockTimeout)
{
    {
        EXPECT_EQ(Duration::Seconds(60.0), Manager::DefaultLocalRepositoryLockTimeout());
    }
}

TEST(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Weather_Manager, DefaultRemoteUrl)
{
    {
        EXPECT_EQ(URL::Parse("https://celestrak.org/SpaceData/"), Manager::DefaultRemoteUrl());
    }
}
