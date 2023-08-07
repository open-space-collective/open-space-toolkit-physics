/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/Manager.hpp>

#include <Global.test.hpp>

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;

using ostk::physics::data::Manager;


TEST(OpenSpaceToolkit_Physics_Data_Manager, getLastUpdateTimestampFor)
{
    Manager& manager = Manager::Get();
    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2023-08-04T12:02:17.028701"), Scale::UTC),
            manager.getLastUpdateTimestampFor("bulletin-A")
        );
    }

    {
        EXPECT_EQ(
            Instant::DateTime(DateTime::Parse("2023-08-03T00:03:15.288325"), Scale::UTC),
            manager.getLastUpdateTimestampFor("finals-2000A")
        );
    }
}

TEST(OpenSpaceToolkit_Physics_Data_Manager, getRemoteUrl)
{
    Manager& manager = Manager::Get();
    {
        EXPECT_EQ(
            "https://github.com/open-space-collective/open-space-toolkit-data/raw/main/data/",
            manager.getRemoteUrl().toString()
        );
    }
}
