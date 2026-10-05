/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/IO/URL.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::container::Tuple;
using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::io::URL;

using ostk::mathematics::object::Vector2d;

using ostk::physics::coordinate::frame::provider::iers::BulletinA;
using ostk::physics::coordinate::frame::provider::iers::Finals2000A;
using ostk::physics::coordinate::frame::provider::iers::Manager;
using ostk::physics::time::DateTime;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

class OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        manager_.setLocalRepository(localRepositoryDirectory);

        this->bulletinA_ = BulletinA::Load(bulletinAFile_);
        this->finals2000A_ = Finals2000A::Load(finals2000AFile_);

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

        manager_.setLocalRepository(localRepositoryDirectory);
        manager_.setMode(Manager::Mode::Automatic);
        manager_.reset();
    }

    const File bulletinAFile_ =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/bulletin-A/ser7.dat")
        );

    const File finals2000AFile_ = File::Path(
        Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/finals2000A.data")
    );

    BulletinA bulletinA_ = BulletinA::Undefined();
    Finals2000A finals2000A_ = Finals2000A::Undefined();

    Manager& manager_ = Manager::Get();

    const Directory localRepositoryDirectory =
        Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/"));

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";
    const char* modeVarName_ = "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_IERS_MANAGER_MODE";

    char* localRepositoryPath;
    char* fullDataPath_;
    char* modeValue_;
};

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetLocalRepository)
{
    {
        EXPECT_EQ("IERS", manager_.getLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetBulletinADirectory)
{
    {
        EXPECT_EQ("bulletin-A", manager_.getBulletinADirectory().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetFinals2000ADirectory)
{
    {
        EXPECT_EQ("finals-2000A", manager_.getFinals2000ADirectory().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetBulletinA_Automatic)
{
    manager_.setMode(Manager::Mode::Automatic);
    manager_.loadBulletinA(bulletinA_);

    EXPECT_NO_THROW(manager_.getBulletinA());
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetBulletinA_Manual)
{
    {
        manager_.reset();
        manager_.setMode(Manager::Mode::Manual);
        Directory newDirectory = Directory::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/bulletin-A/Temp")
        );
        manager_.setLocalRepository(newDirectory);

        EXPECT_THROW(manager_.getBulletinA(), ostk::core::error::RuntimeError);

        manager_.setMode(Manager::Mode::Automatic);
        manager_.setLocalRepository(localRepositoryDirectory);
        newDirectory.remove();
    }

    {
        manager_.reset();
        manager_.setMode(Manager::Mode::Manual);

        EXPECT_NO_THROW(manager_.getBulletinA());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetBulletinAFetch)
{
    // This test is not deterministic, as it depends on the remote server
    {
        manager_.reset();
        Directory directory = Directory::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/bulletin-A/New")
        );
        manager_.setLocalRepository(directory);

        File bulletinAFile = File::Undefined();
        EXPECT_NO_THROW(bulletinAFile = manager_.fetchLatestBulletinA());

        BulletinA bulletinA = BulletinA::Load(bulletinAFile);

        bulletinAFile.remove();

        EXPECT_NO_THROW(manager_.getBulletinA());

        manager_.setLocalRepository(localRepositoryDirectory);
        directory.remove();
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetFinals2000A_Automatic)
{
    manager_.setMode(Manager::Mode::Automatic);
    manager_.loadFinals2000A(finals2000A_);

    EXPECT_NO_THROW(manager_.getFinals2000A());
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetFinals2000AFetch)
{
    // This test is not deterministic, as it depends on the remote server
    {
        manager_.reset();
        Directory directory = Directory::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/New")
        );
        manager_.setLocalRepository(directory);

        EXPECT_NO_THROW(manager_.getFinals2000A());

        manager_.loadFinals2000A(finals2000A_);
        manager_.setLocalRepository(localRepositoryDirectory);
        directory.remove();
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetFinals2000A_Manual)
{
    // Test case with missing data
    {
        manager_.reset();
        manager_.setMode(Manager::Mode::Manual);
        Directory newDirectory = Directory::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/Temp")
        );
        manager_.setLocalRepository(newDirectory);

        EXPECT_THROW(manager_.getFinals2000A(), ostk::core::error::RuntimeError);

        manager_.setMode(Manager::Mode::Automatic);
        manager_.setLocalRepository(localRepositoryDirectory);
        newDirectory.remove();
    }

    {
        manager_.reset();
        manager_.setMode(Manager::Mode::Manual);

        EXPECT_NO_THROW(manager_.getFinals2000A());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetPolarMotionAt_Past)
{
    {
        const Array<Tuple<File, Real>> referenceScenarios = {
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager/"
                                    "GetPolarMotionAt/Pole Wander 1.csv")),
             1e-8},
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager/"
                                    "GetPolarMotionAt/Pole Wander 2.csv")),
             1e-8},
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager/"
                                    "GetPolarMotionAt/Pole Wander 3.csv")),
             1e-8}
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario);
            const Real tolerance = std::get<1>(referenceScenario);

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Test

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI);

                const Vector2d referencePolarMotion_rad = {referenceRow[1].accessReal(), referenceRow[2].accessReal()};

                const Vector2d polarMotion_rad = manager_.getPolarMotionAt(instant) * (Real::Pi() / 180.0 / 3600.0);

                EXPECT_TRUE(polarMotion_rad.isNear(referencePolarMotion_rad, tolerance)) << String::Format(
                    "{} - {} ~ {}",
                    instant.toString(Scale::TAI),
                    referencePolarMotion_rad.toString(),
                    polarMotion_rad.toString()
                );
            }
        }
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetPolarMotionAt_Future)
{
    Directory directory = Directory::Path(
        Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/Temp")
    );
    manager_.setLocalRepository(directory);
    const File latestFinals2000A = manager_.fetchLatestFinals2000A();
    const Finals2000A finals2000A = Finals2000A::Load(latestFinals2000A);
    manager_.loadFinals2000A(finals2000A);

    {
        const Instant instant = Instant::Now() + Duration::Weeks(12.0);

        manager_.getPolarMotionAt(instant);
    }

    {
        const Instant instant = Instant::Now() + Duration::Weeks(55.0);

        EXPECT_THROW(manager_.getPolarMotionAt(instant), ostk::core::error::RuntimeError);
    }

    directory.remove();
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetUt1MinusUtcAt)
{
    using ostk::core::container::Array;
    using ostk::core::container::Table;
    using ostk::core::container::Tuple;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Scale;

    {
        const Array<Tuple<File, Real>> referenceScenarios = {
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager/"
                                    "GetUt1MinusUtcAt/DUT1 1.csv")),
             1e-4},
            {File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager/"
                                    "GetUt1MinusUtcAt/DUT1 2.csv")),
             1e-4},
            // {
            // File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager/GetUt1MinusUtcAt/DUT1
            // 3.csv")), 1e-4 } // At 2017-01-01 00:00:37 TAI (00:00:00 UTC, right after the leap second), STK still
            // returns the value before the leap second (-0.4087 s), while IERS tabulates +0.5913 s for that date. See
            // GetUt1MinusUtcAt_LeapSecond for the leap second crossing.
        };

        for (const auto& referenceScenario : referenceScenarios)
        {
            // Reference data setup

            const File referenceDataFile = std::get<0>(referenceScenario);
            const Real tolerance = std::get<1>(referenceScenario);

            const Table referenceData = Table::Load(referenceDataFile, Table::Format::CSV, true);

            // Test

            for (const auto& referenceRow : referenceData)
            {
                const Instant instant = Instant::DateTime(DateTime::Parse(referenceRow[0].accessString()), Scale::TAI);

                const Real referenceDUT1 = {referenceRow[3].accessReal()};

                const Real dUT1 = manager_.getUt1MinusUtcAt(instant);

                EXPECT_NEAR(referenceDUT1, dUT1, tolerance)
                    << String::Format("{} - {} ~ {}", instant.toString(Scale::TAI), referenceDUT1, dUT1);
            }
        }
    }

    {
        const Instant instant = Instant::DateTime(DateTime(2018, 10, 10, 0, 0, 0), Scale::UTC);

        EXPECT_NO_THROW(manager_.getUt1MinusUtcAt(instant));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetUt1MinusUtcAt_LeapSecond)
{
    using ostk::core::container::Array;
    using ostk::core::container::Tuple;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::physics::time::DateTime;
    using ostk::physics::time::Instant;
    using ostk::physics::time::Scale;

    // UT1 - UTC jumps by +1 s at the leap second ending 2016-12-31, while UT1 - TAI is continuous.
    // Finals 2000A: UT1 - UTC = -0.4077601 s on 2016-12-31 and +0.5912821 s on 2017-01-01,
    // i.e. UT1 - TAI = -36.4077601 s and -36.4087179 s.
    // The Bulletin A loaded by the fixture (June 2018) does not cover these dates: Finals 2000A is used.

    const Array<Tuple<String, Real>> referenceValues = {
        {"2016-12-31 00:00:00", -0.4077601},
        {"2016-12-31 12:00:00", -0.4082390},
        {"2016-12-31 23:59:59", -0.4087179},
        {"2017-01-01 00:00:00", +0.5912821},
        {"2017-01-01 12:00:00", +0.5907287},
    };

    for (const auto& referenceValue : referenceValues)
    {
        const Instant instant = Instant::DateTime(DateTime::Parse(std::get<0>(referenceValue)), Scale::UTC);
        const Real referenceUt1MinusUtc = std::get<1>(referenceValue);

        EXPECT_NEAR(referenceUt1MinusUtc, manager_.getUt1MinusUtcAt(instant), 1e-7) << std::get<0>(referenceValue);
        EXPECT_NEAR(referenceUt1MinusUtc, finals2000A_.getUt1MinusUtcAt(instant), 1e-7) << std::get<0>(referenceValue);
        EXPECT_NEAR(referenceUt1MinusUtc, finals2000A_.getDataAt(instant).ut1MinusUtc_A, 1e-7)
            << std::get<0>(referenceValue);
    }

    {
        // Bulletin B values: UT1 - UTC = -0.4077600 s on 2016-12-31 and +0.5912975 s on 2017-01-01

        const Instant instant = Instant::DateTime(DateTime::Parse("2016-12-31 12:00:00"), Scale::UTC);

        EXPECT_NEAR(-0.40823125, finals2000A_.getDataAt(instant).ut1MinusUtc_B, 1e-7);
    }

    {
        // UT1 - UTC applies to the UTC representation of the instant, including during the leap second itself
        // (2016-12-31 23:59:60 UTC, from 2017-01-01 00:00:36 TAI): UT1 - TAI must stay continuous across it

        const Array<String> dateTimeStrings_TAI = {
            "2017-01-01 00:00:35",
            "2017-01-01 00:00:36",
            "2017-01-01 00:00:36.5",
            "2017-01-01 00:00:37",
        };

        for (const auto& dateTimeString_TAI : dateTimeStrings_TAI)
        {
            const Instant instant = Instant::DateTime(DateTime::Parse(dateTimeString_TAI), Scale::TAI);

            const Real ut1MinusTai =
                (instant.getModifiedJulianDate(Scale::UTC) - instant.getModifiedJulianDate(Scale::TAI)) * 86400.0 +
                manager_.getUt1MinusUtcAt(instant);

            EXPECT_NEAR(-36.4087179, ut1MinusTai, 1e-5) << dateTimeString_TAI;
        }
    }
}

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetLodAt)
// {

//     using ostk::physics::coordinate::frame::provider::iers::Manager ;

//     {

//         FAIL() ;

//     }

// }

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, SetMode)
{
    {
        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());

        manager_.setMode(Manager::Mode::Manual);

        EXPECT_EQ(Manager::Mode::Manual, manager_.getMode());

        manager_.setMode(Manager::Mode::Automatic);

        EXPECT_EQ(Manager::Mode::Automatic, manager_.getMode());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, SetLocalRepository)
{
    {
        EXPECT_EQ("IERS", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/coordinate/frame/provider/iers"))
        );

        EXPECT_EQ("iers", manager_.getLocalRepository().getName());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, LoadBulletinA)
{
    {
        manager_.reset();

        EXPECT_NO_THROW(manager_.loadBulletinA(bulletinA_));
        EXPECT_ANY_THROW(manager_.loadBulletinA(BulletinA::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, LoadFinals2000A)
{
    {
        const File file = File::Path(Path::Parse(
            "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/finals2000A.data"
        ));

        const Finals2000A finals2000a = Finals2000A::Load(file);

        manager_.reset();
        manager_.loadFinals2000A(finals2000a);

        EXPECT_NO_THROW(manager_.loadFinals2000A(finals2000a));
        EXPECT_ANY_THROW(manager_.loadFinals2000A(Finals2000A::Undefined()));
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, FetchLatestBulletinA)
{
    {
        manager_.reset();

        Directory directory = Directory::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/bulletin-A/New")
        );
        manager_.setLocalRepository(directory);
        const File latestBulletinA = manager_.fetchLatestBulletinA();

        EXPECT_EQ("ser7.dat", latestBulletinA.getName());
        EXPECT_EQ("bulletin-A", latestBulletinA.getParentDirectory().getName());
        EXPECT_EQ(
            manager_.getLocalRepository().getPath().getNormalizedPath(),
            latestBulletinA.getParentDirectory().getParentDirectory().getPath().getNormalizedPath()
        );
        directory.remove();
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, FetchLatestFinals2000A)
{
    {
        manager_.reset();
        Directory directory = Directory::Path(
            Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/finals-2000A/New")
        );
        manager_.setLocalRepository(directory);

        const File latestFinals2000A = manager_.fetchLatestFinals2000A();

        EXPECT_EQ("finals2000A.data", latestFinals2000A.getName());
        EXPECT_EQ("finals-2000A", latestFinals2000A.getParentDirectory().getName());
        EXPECT_EQ(
            manager_.getLocalRepository().getPath().getNormalizedPath(),
            latestFinals2000A.getParentDirectory().getParentDirectory().getPath().getNormalizedPath()
        );
        manager_.setLocalRepository(localRepositoryDirectory);
        directory.remove();
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, Reset)
{
    {
        manager_.loadBulletinA(bulletinA_);

        EXPECT_TRUE(manager_.getBulletinA().isDefined());
        EXPECT_TRUE(manager_.getFinals2000A().isDefined());

        EXPECT_NO_THROW(manager_.reset());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, ClearLocalRepository)
{
    {
        Directory directory =
            Directory::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Manager/Temp"
            ));
        manager_.setLocalRepository(directory);
        manager_.clearLocalRepository();

        EXPECT_TRUE(manager_.getBulletinADirectory().isEmpty());
        EXPECT_TRUE(manager_.getFinals2000ADirectory().isEmpty());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, Get)
{
    {
        EXPECT_NO_THROW(Manager::Get());
    }
}
