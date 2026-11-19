/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>

#include <Global.test.hpp>

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Axes;
using ostk::physics::coordinate::Frame;

TEST(OpenSpaceToolkit_Physics_Coordinate_Axes, Constructor)
{
    {
        EXPECT_NO_THROW(Axes(Vector3d::X(), Vector3d::Y(), Vector3d::Z(), Frame::GCRF()));
    }

    {
        EXPECT_THROW(Axes(Vector3d::X(), Vector3d::Y(), Vector3d::Z(), nullptr), ostk::core::error::runtime::Undefined);
    }
}
