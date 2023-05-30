/// Apache License 2.0

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/GCRF.hpp>

namespace ostk
{
namespace physics
{
namespace coord
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
}  // namespace coord
}  // namespace physics
}  // namespace ostk
