/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Tuple;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::io::URL;

using ostk::physics::environment::atmospheric::earth::CSSISpaceWeather;
using ostk::physics::environment::atmospheric::earth::Manager;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

class OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        // Default all tests to use local testing file to avoid accidental remote requests
        spaceWeather_ = CSSISpaceWeather::Load(spaceWeatherFile_);
        manager_.loadCSSISpaceWeather(spaceWeather_);

        // cache current directory environment variables
        localRepositoryPath = std::getenv(localRepositoryVarName_);
        fullDataPath_ = std::getenv(fullDataVarName_);
        modeValue_ = std::getenv(modeVarName_);
    }

    virtual void TearDown()
    {
        // reset cached environment variables
        if (fullDataPath_)
        {
            setenv(fullDataVarName_, fullDataPath_, true);
        }
        else
        {
            unsetenv(fullDataVarName_);
        }

        if (localRepositoryPath)
        {
            setenv(localRepositoryVarName_, localRepositoryPath, true);
        }
        else
        {
            unsetenv(localRepositoryVarName_);
        }

        if (modeValue_)
        {
            setenv(modeVarName_, modeValue_, true);
        }
        else
        {
            unsetenv(modeVarName_);
        }

        // reset repository so other test suites do not use the test data
        manager_.reset();
    }

    const File spaceWeatherFile_ = File::Path(Path::Parse(
        "/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/CSSISpaceWeather/SW-Last5Years.test.csv"
    ));

    CSSISpaceWeather spaceWeather_ = CSSISpaceWeather::Undefined();

    Manager& manager_ = Manager::Get();

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";
    const char* modeVarName_ = "OSTK_PHYSICS_ENVIRONMENT_ATMOSPHERIC_EARTH_MANAGER_MODE";

    char* localRepositoryPath;
    char* fullDataPath_;
    char* modeValue_;
};

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetLocalRepository)
{
    {
        EXPECT_EQ("earth", manager_.getLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetCSSISpaceWeatherAt)
{
    {
        manager_.setMode(Manager::Mode::Manual);

        EXPECT_THROW(manager_.getCSSISpaceWeatherAt(Instant::Undefined()), ostk::core::error::runtime::Undefined);

        EXPECT_THROW(
            manager_.getCSSISpaceWeatherAt(Instant::DateTime(DateTime::Parse("2010-01-01 00:00:00"), Scale::UTC)),
            ostk::core::error::RuntimeError
        );

        EXPECT_NO_THROW(manager_.getCSSISpaceWeatherAt(spaceWeather_.accessObservationInterval().accessStart()));
        EXPECT_NO_THROW(manager_.getCSSISpaceWeatherAt(spaceWeather_.accessObservationInterval().accessEnd()));

        EXPECT_NO_THROW(manager_.getCSSISpaceWeatherAt(spaceWeather_.accessDailyPredictionInterval().accessStart()));
        EXPECT_NO_THROW(manager_.getCSSISpaceWeatherAt(spaceWeather_.accessDailyPredictionInterval().accessEnd()));

        EXPECT_NO_THROW(manager_.getCSSISpaceWeatherAt(spaceWeather_.accessMonthlyPredictionInterval().accessStart()));
        EXPECT_NO_THROW(manager_.getCSSISpaceWeatherAt(spaceWeather_.accessMonthlyPredictionInterval().accessEnd()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetKp3HourSolarIndicesAt)
{
    {
        const Array<Tuple<String, Array<Integer>>> referenceScenarios = {
            {"2018-01-02 12:34:56", {17, 7, 3, 7, 17, 10, 20, 10}},
            {"2023-06-18 12:34:56", {27, 20, 13, 20, 17, 17, 27, 20}},
            {"2023-08-02 12:34:56", {13, 13, 13, 13, 13, 13, 13, 13}},
            {"2023-08-03 12:34:56", {13, 13, 13, 13, 13, 13, 13, 13}},
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Array<Integer> referenceIndices = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceIndices, manager_.getKp3HourSolarIndicesAt(referenceInstant));
        }

        manager_.setMode(Manager::Mode::Manual);
        EXPECT_THROW(manager_.getKp3HourSolarIndicesAt(Instant::Undefined()), ostk::core::error::runtime::Undefined);
        EXPECT_THROW(
            manager_.getKp3HourSolarIndicesAt(Instant::DateTime(DateTime::Parse("2010-01-01 00:00:00"), Scale::UTC)),
            ostk::core::error::RuntimeError
        );

        manager_.setMode(Manager::Mode::Automatic);
    }

    {
        // Test data extrapolation

        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/"
                                   "CSSISpaceWeather/SW-Last5Years_missing_data.test.csv"));

        const CSSISpaceWeather spaceWeatherMissingData = CSSISpaceWeather::Load(file);

        manager_.reset();
        manager_.loadCSSISpaceWeather(spaceWeatherMissingData);

        // Reference data setup

        const Instant referenceInstant = Instant::DateTime(DateTime::Parse("2023-06-20 12:34:56"), Scale::UTC);
        const Array<Integer> referenceIndices {23, 17, 17, 13, 20, 27, 30, 30};

        // Test
        EXPECT_EQ(referenceIndices, manager_.getKp3HourSolarIndicesAt(referenceInstant));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetAp3HourSolarIndicesAt)
{
    {
        const Array<Tuple<String, Array<Integer>>> referenceScenarios = {
            {"2018-01-02 12:34:56", {6, 3, 2, 3, 6, 4, 7, 4}},
            {"2023-06-18 12:34:56", {12, 7, 5, 7, 6, 6, 12, 7}},
            {"2023-08-02 12:34:56", {5, 5, 5, 5, 5, 5, 5, 5}},
            {"2023-08-03 12:34:56", {5, 5, 5, 5, 5, 5, 5, 5}},
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Array<Integer> referenceIndices = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceIndices, manager_.getAp3HourSolarIndicesAt(referenceInstant));
        }

        manager_.setMode(Manager::Mode::Manual);
        EXPECT_THROW(manager_.getAp3HourSolarIndicesAt(Instant::Undefined()), ostk::core::error::runtime::Undefined);
        EXPECT_THROW(
            manager_.getAp3HourSolarIndicesAt(Instant::DateTime(DateTime::Parse("2010-01-01 00:00:00"), Scale::UTC)),
            ostk::core::error::RuntimeError
        );

        manager_.setMode(Manager::Mode::Automatic);
    }

    {
        // Test data extrapolation

        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/"
                                   "CSSISpaceWeather/SW-Last5Years_missing_data.test.csv"));

        const CSSISpaceWeather spaceWeatherMissingData = CSSISpaceWeather::Load(file);

        manager_.reset();
        manager_.loadCSSISpaceWeather(spaceWeatherMissingData);

        // Reference data setup

        const Instant referenceInstant = Instant::DateTime(DateTime::Parse("2023-06-21 12:34:56"), Scale::UTC);
        const Array<Integer> referenceIndices {12, 7, 4, 6, 7, 9, 4, 27};

        // Test
        EXPECT_EQ(referenceIndices, manager_.getAp3HourSolarIndicesAt(referenceInstant));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetApDailySolarIndexAt)
{
    {
        const Array<Tuple<String, Integer>> referenceScenarios = {
            {"2018-01-02 12:34:56", 4},
            {"2023-06-18 12:34:56", 8},
            {"2023-08-02 12:34:56", 5},
            {"2023-08-03 12:34:56", 5},
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Integer referenceIndex = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceIndex, manager_.getApDailyIndexAt(referenceInstant));
        }

        manager_.setMode(Manager::Mode::Manual);
        EXPECT_THROW(manager_.getApDailyIndexAt(Instant::Undefined()), ostk::core::error::runtime::Undefined);
        EXPECT_THROW(
            manager_.getApDailyIndexAt(Instant::DateTime(DateTime::Parse("2010-01-01 00:00:00"), Scale::UTC)),
            ostk::core::error::RuntimeError
        );

        manager_.setMode(Manager::Mode::Automatic);
    }

    {
        // Test data extrapolation

        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/"
                                   "CSSISpaceWeather/SW-Last5Years_missing_data.test.csv"));

        const CSSISpaceWeather spaceWeatherMissingData = CSSISpaceWeather::Load(file);

        manager_.reset();
        manager_.loadCSSISpaceWeather(spaceWeatherMissingData);

        // Reference data setup

        const Instant referenceInstant = Instant::DateTime(DateTime::Parse("2023-06-21 12:34:56"), Scale::UTC);
        const Integer referenceIndex = 9;

        // Test
        EXPECT_EQ(referenceIndex, manager_.getApDailyIndexAt(referenceInstant));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetF107SolarFluxAt)
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
            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Real referenceValue = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceValue, manager_.getF107SolarFluxAt(referenceInstant));
        }

        manager_.setMode(Manager::Mode::Manual);
        EXPECT_THROW(manager_.getF107SolarFluxAt(Instant::Undefined()), ostk::core::error::runtime::Undefined);
        EXPECT_THROW(
            manager_.getF107SolarFluxAt(Instant::DateTime(DateTime::Parse("2010-01-01 00:00:00"), Scale::UTC)),
            ostk::core::error::RuntimeError
        );

        manager_.setMode(Manager::Mode::Automatic);
    }

    {
        // Test data extrapolation

        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/"
                                   "CSSISpaceWeather/SW-Last5Years_missing_data.test.csv"));

        const CSSISpaceWeather spaceWeatherMissingData = CSSISpaceWeather::Load(file);

        manager_.reset();
        manager_.loadCSSISpaceWeather(spaceWeatherMissingData);

        // Reference data setup

        const Instant referenceInstant = Instant::DateTime(DateTime::Parse("2018-01-03 12:34:56"), Scale::UTC);
        const Real referenceValue = 69.1;

        // Test
        EXPECT_EQ(referenceValue, manager_.getF107SolarFluxAt(referenceInstant));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, GetF107SolarFlux81DayAvgAt)
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
            // Reference data setup

            const Instant referenceInstant =
                Instant::DateTime(DateTime::Parse(std::get<0>(referenceScenario)), Scale::UTC);
            const Real referenceValue = std::get<1>(referenceScenario);

            // Test
            EXPECT_EQ(referenceValue, manager_.getF107SolarFlux81DayAvgAt(referenceInstant));
        }

        manager_.setMode(Manager::Mode::Manual);
        EXPECT_THROW(manager_.getF107SolarFlux81DayAvgAt(Instant::Undefined()), ostk::core::error::runtime::Undefined);
        EXPECT_THROW(
            manager_.getF107SolarFlux81DayAvgAt(Instant::DateTime(DateTime::Parse("2010-01-01 00:00:00"), Scale::UTC)),
            ostk::core::error::RuntimeError
        );

        manager_.setMode(Manager::Mode::Automatic);
    }

    {
        // Test data extrapolation

        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/"
                                   "CSSISpaceWeather/SW-Last5Years_missing_data.test.csv"));

        const CSSISpaceWeather spaceWeatherMissingData = CSSISpaceWeather::Load(file);

        manager_.reset();
        manager_.loadCSSISpaceWeather(spaceWeatherMissingData);

        // Reference data setup

        const Instant referenceInstant = Instant::DateTime(DateTime::Parse("2018-01-03 12:34:56"), Scale::UTC);
        const Real referenceValue = 71.5;

        // Test
        EXPECT_EQ(referenceValue, manager_.getF107SolarFlux81DayAvgAt(referenceInstant));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, SetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());

        manager_.setMode(Manager::Mode::Manual);

        EXPECT_EQ(Manager::Mode::Manual, manager_.getMode());

        manager_.setMode(Manager::Mode::Automatic);

        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, SetLocalRepository)
{
    {
        EXPECT_EQ("earth", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/environment/atmospheric/earth"))
        );

        EXPECT_EQ("earth", manager_.getLocalRepository().getName());

        EXPECT_THROW(manager_.setLocalRepository(Directory::Undefined()), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, LoadCSSISpaceWeather)
{
    {
        const File file =
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Environment/Atmospheric/Earth/"
                                   "CSSISpaceWeather/SW-Last5Years.test.csv"));

        const CSSISpaceWeather spaceWeather = CSSISpaceWeather::Load(file);

        EXPECT_ANY_THROW(manager_.loadCSSISpaceWeather(spaceWeather));
        EXPECT_ANY_THROW(manager_.loadCSSISpaceWeather(CSSISpaceWeather::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, FetchLatestCSSISpaceWeather)
{
    {
        manager_.clearLocalRepository();

        const File latestCSSISpaceWeather = manager_.fetchLatestCSSISpaceWeather();

        EXPECT_EQ("SW-Last5Years.csv", latestCSSISpaceWeather.getName());
        EXPECT_EQ("earth", latestCSSISpaceWeather.getParentDirectory().getParentDirectory().getName());
        EXPECT_EQ("CSSISpaceWeather", latestCSSISpaceWeather.getParentDirectory().getName());
        EXPECT_EQ(
            manager_.getLocalRepository().getPath().getNormalizedPath(),
            latestCSSISpaceWeather.getParentDirectory().getParentDirectory().getPath().getNormalizedPath()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, Reset)
{
    {
        manager_.reset();

        EXPECT_FALSE(manager_.getLoadedCSSISpaceWeather().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, ClearLocalRepository)
{
    {
        manager_.clearLocalRepository();

        EXPECT_TRUE(manager_.getCSSISpaceWeatherDirectory().isEmpty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, DefaultMode)
{
    {
        unsetenv(modeVarName_);
        EXPECT_EQ(Manager::Mode::Automatic, Manager::DefaultMode());
    }
    {
        setenv(modeVarName_, "SuperUltraAutomatic", true);
        EXPECT_THROW(Manager::DefaultMode(), ostk::core::error::runtime::Wrong);
    }
    {
        setenv(modeVarName_, "Automatic", true);
        EXPECT_EQ(Manager::Mode::Automatic, Manager::DefaultMode());
    }
    {
        setenv(modeVarName_, "Manual", true);
        EXPECT_EQ(Manager::Mode::Manual, Manager::DefaultMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, DefaultLocalRepository)
{
    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        EXPECT_EQ(
            Manager::DefaultLocalRepository(),
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/environment/atmospheric/earth"))
        );
    }

    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        setenv(fullDataVarName_, "/tmp", true);

        EXPECT_EQ(
            Manager::DefaultLocalRepository(), Directory::Path(Path::Parse("/tmp/environment/atmospheric/earth"))
        );
    }

    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        setenv(fullDataVarName_, "/tmp", true);
        setenv(localRepositoryVarName_, "/local_override", true);

        EXPECT_EQ(Manager::DefaultLocalRepository(), Directory::Path(Path::Parse("/local_override")));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Environment_Atmospheric_Earth_Manager, DefaultLocalRepositoryLockTimeout)
{
    {
        EXPECT_EQ(Duration::Seconds(60.0), Manager::DefaultLocalRepositoryLockTimeout());
    }
}
