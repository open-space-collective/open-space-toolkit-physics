/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/ICRF.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{

ICRF::ICRF() {}

ICRF::~ICRF() {}

ICRF* ICRF::clone() const
{
    return new ICRF(*this);
}

bool ICRF::isDefined() const
{
    return true;
}

Transform ICRF::getTransformAt(const Instant& anInstant) const
{
    (void)anInstant;

    // return Transform(anInstant, Vector3d::Zero(), Vector3d::Zero()) ; // THIS IS WRONG
    return Transform::Undefined();
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
