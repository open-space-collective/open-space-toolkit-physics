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

using ostk::core::filesystem::Path;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Directory;
using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::container::Tuple;
using ostk::core::container::Array;
using ostk::core::container::Table;

using ostk::io::URL;

using ostk::mathematics::object::Vector2d;

using ostk::physics::time::Duration;
using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;
using ostk::physics::coord::frame::provider::iers::BulletinA;
using ostk::physics::coord::frame::provider::iers::Manager;
using ostk::physics::coord::frame::provider::iers::Finals2000A;

class OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager : public ::testing::Test
{
   protected:
    void SetUp() override
    {
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
    }

    const File bulletinAFile_ =
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/BulletinA/ser7.dat")
        );

    const File finals2000AFile_ = File::Path(
        Path::Parse("/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A/finals2000A.data")
    );

    BulletinA bulletinA_ = BulletinA::Undefined();
    Finals2000A finals2000A_ = Finals2000A::Undefined();

    Manager& manager_ = Manager::Get();

    const char* localRepositoryVarName_ = "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_LOCAL_REPOSITORY";
    const char* fullDataVarName_ = "OSTK_PHYSICS_DATA_LOCAL_REPOSITORY";
    const char* modeVarName_ = "OSTK_PHYSICS_COORDINATE_FRAME_PROVIDERS_IERS_MANAGER_MODE";

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
        EXPECT_EQ("iers", manager_.getLocalRepository().getName());
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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetBulletinA)
{
    {
        manager_.loadBulletinA(bulletinA_);

        EXPECT_NO_THROW(manager_.getBulletinA());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetBulletinAFetch)
{
    // This test is not deterministic, as it depends on the remote server
    {
        manager_.reset();
        manager_.clearLocalRepository();

        File bulletinAFile = File::Undefined();
        EXPECT_NO_THROW(bulletinAFile = manager_.fetchLatestBulletinA());

        BulletinA bulletinA = BulletinA::Load(bulletinAFile);

        bulletinAFile.remove();

        EXPECT_NO_THROW(manager_.getBulletinA());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetFinals2000A)
{
    {
        const File file = File::Path(Path::Parse(
            "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A/finals2000A.data"
        ));

        const Finals2000A finals2000a = Finals2000A::Load(file);

        manager_.loadFinals2000A(finals2000a);

        EXPECT_NO_THROW(manager_.getFinals2000A());
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetFinals2000AFetch)
{
    // This test is not deterministic, as it depends on the remote server
    {
        manager_.reset();
        manager_.clearLocalRepository();

        EXPECT_NO_THROW(manager_.getFinals2000A());

        manager_.loadFinals2000A(finals2000A_);
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
    {
        const Instant instant = Instant::Now() + Duration::Weeks(12.0);

        manager_.getPolarMotionAt(instant);
    }

    {
        const Instant instant = Instant::Now() + Duration::Weeks(53.0);

        EXPECT_THROW(manager_.getPolarMotionAt(instant), ostk::core::error::RuntimeError);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetUt1MinusUtcAt)
{
    using ostk::core::type::Real;
    using ostk::core::type::String;
    using ostk::core::container::Tuple;
    using ostk::core::container::Array;
    using ostk::core::container::Table;

    using ostk::physics::time::Scale;
    using ostk::physics::time::Instant;
    using ostk::physics::time::DateTime;

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
            // 3.csv")), 1e-4 } // [TBI] Discrepancy with STK at leap second crossing
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

// TEST (OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, GetLodAt)
// {

//     using ostk::physics::coord::frame::provider::iers::Manager ;

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
        EXPECT_EQ("iers", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(Directory::Path(Path::Parse("/tmp")));

        EXPECT_EQ("tmp", manager_.getLocalRepository().getName());

        manager_.setLocalRepository(
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/coordinate/frame/providers/iers"))
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
            "/app/test/OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Finals2000A/finals2000A.data"
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
        manager_.clearLocalRepository();

        const File latestBulletinA = manager_.fetchLatestBulletinA();

        EXPECT_EQ("ser7.dat", latestBulletinA.getName());
        EXPECT_EQ("bulletin-A", latestBulletinA.getParentDirectory().getName());
        EXPECT_EQ(
            manager_.getLocalRepository().getPath().getNormalizedPath(),
            latestBulletinA.getParentDirectory().getParentDirectory().getPath().getNormalizedPath()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, FetchLatestFinals2000A)
{
    {
        manager_.reset();
        manager_.clearLocalRepository();

        const File latestFinals2000A = manager_.fetchLatestFinals2000A();

        EXPECT_EQ("finals2000A.data", latestFinals2000A.getName());
        EXPECT_EQ("finals-2000A", latestFinals2000A.getParentDirectory().getName());
        EXPECT_EQ(
            manager_.getLocalRepository().getPath().getNormalizedPath(),
            latestFinals2000A.getParentDirectory().getParentDirectory().getPath().getNormalizedPath()
        );
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, Reset)
{
    {
        manager_.loadBulletinA(bulletinA_);

        EXPECT_TRUE(manager_.getBulletinA().isDefined());

        manager_.reset();

        manager_.setMode(Manager::Mode::Manual);

        EXPECT_ANY_THROW(manager_.getBulletinA().isDefined());

        manager_.setMode(Manager::Mode::Automatic);
    }
}

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, ClearLocalRepository)
{
    {
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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, DefaultMode)
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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, DefaultLocalRepository)
{
    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        EXPECT_EQ(
            Manager::DefaultLocalRepository(),
            Directory::Path(Path::Parse("./.open-space-toolkit/physics/data/coordinate/frame/providers/iers"))
        );
    }

    {
        unsetenv(localRepositoryVarName_);
        unsetenv(fullDataVarName_);

        setenv(fullDataVarName_, "/tmp", true);

        EXPECT_EQ(
            Manager::DefaultLocalRepository(), Directory::Path(Path::Parse("/tmp/coordinate/frame/providers/iers"))
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

TEST_F(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Manager, DefaultLocalRepositoryLockTimeout)
{
    {
        EXPECT_EQ(Duration::Seconds(60.0), Manager::DefaultLocalRepositoryLockTimeout());
    }
}
