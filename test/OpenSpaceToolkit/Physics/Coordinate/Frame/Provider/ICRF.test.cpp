/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/ICRF.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <Global.test.hpp>

using ostk::physics::coordinate::frame::provider::ICRF;
using ostk::physics::time::Instant;

TEST(OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_ICRF, GetTransformAt)
{
    EXPECT_THROW(ICRF().getTransformAt(Instant::J2000()), ostk::core::error::runtime::ToBeImplemented);
}
