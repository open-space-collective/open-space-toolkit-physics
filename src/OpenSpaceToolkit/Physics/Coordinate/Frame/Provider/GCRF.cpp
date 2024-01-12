/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/GCRF.hpp>

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

GCRF::GCRF() {}

GCRF::~GCRF() {}

GCRF* GCRF::clone() const
{
    return new GCRF(*this);
}

bool GCRF::isDefined() const
{
    return true;
}

Transform GCRF::getTransformAt(const Instant& anInstant) const
{
    return Transform::Identity(anInstant);
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
