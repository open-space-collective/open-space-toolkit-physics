/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <Global.test.hpp>

namespace iau = ostk::physics::coord::frame::providers::iau;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IAU_Theory, StringFromTheory)
{
    {
        EXPECT_EQ("IAU 2000A", iau::StringFromTheory(iau::Theory::IAU_2000A));
        EXPECT_EQ("IAU 2000B", iau::StringFromTheory(iau::Theory::IAU_2000B));
        EXPECT_EQ("IAU 2006", iau::StringFromTheory(iau::Theory::IAU_2006));
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_IAU_Theory, TheoryFromString)
{
    {
        EXPECT_EQ(iau::Theory::IAU_2000A, iau::TheoryFromString("IAU 2000A"));
        EXPECT_EQ(iau::Theory::IAU_2000B, iau::TheoryFromString("IAU 2000B"));
        EXPECT_EQ(iau::Theory::IAU_2006, iau::TheoryFromString("IAU 2006"));
    }
}
