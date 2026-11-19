/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Dynamic.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <Global.test.hpp>

using ostk::physics::coordinate::frame::provider::Dynamic;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::Instant;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_Dynamic, Constructor)
{
    {
        EXPECT_NO_THROW(Dynamic(
            [](const Instant& anInstant)
            {
                return Transform::Identity(anInstant);
            }
        ));
    }

    {
        EXPECT_THROW(Dynamic(Dynamic::Generator()), ostk::core::error::runtime::Undefined);
    }
}

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_Dynamic, GetTransformAt)
{
    const Dynamic dynamic = {[](const Instant& anInstant)
                             {
                                 return Transform::Identity(anInstant);
                             }};

    EXPECT_EQ(Instant::J2000(), dynamic.getTransformAt(Instant::J2000()).getInstant());
}
