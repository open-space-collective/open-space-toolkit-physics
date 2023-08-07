/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Data/ManagerBase.hpp>

#include <Global.test.hpp>

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;
using ostk::physics::time::DateTime;

using ostk::physics::data::ManagerBase;

class ManagerBaseTest : ManagerBase
{
   public:
    using ManagerBase::getLastUpdateTimestampFor;
};

TEST(OpenSpaceToolkit_Physics_Data_ManagerBase, getLastUpdateTimestampFor)
{
    ManagerBaseTest manager = ManagerBaseTest();
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
