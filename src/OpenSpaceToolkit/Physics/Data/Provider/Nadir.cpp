/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Data/Provider/Nadir.hpp>

namespace ostk
{
namespace physics
{
namespace data
{
namespace provider
{

Direction Nadir(const Position& aPosition, const Celestial& aCelestialObject, const Environment& anEnvironment)
{
    using ostk::physics::coordinate::spherical::LLA;

    const LLA lla = LLA::Cartesian(
        aPosition.inFrame(aCelestialObject.accessFrame(), anEnvironment.getInstant()).getCoordinates(),
        aCelestialObject.getEquatorialRadius(),
        aCelestialObject.getFlattening()
    );

    const Shared<const Frame> nedFrameSPtr = aCelestialObject.getFrameAt(lla, Celestial::FrameType::NED);

    const Vector3d z_NED_FIXED =
        nedFrameSPtr->getAxesIn(aCelestialObject.accessFrame(), anEnvironment.getInstant()).z();

    return {z_NED_FIXED, aCelestialObject.accessFrame()};
}

}  // namespace provider
}  // namespace data
}  // namespace physics
}  // namespace ostk
