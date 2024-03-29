/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemeris/Analytical.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{

Analytical::Analytical(const Shared<const Frame>& aFrameSPtr)
    : frameSPtr_(aFrameSPtr)
{
}

Analytical::~Analytical() {}

Analytical* Analytical::clone() const
{
    return new Analytical(*this);
}

bool Analytical::isDefined() const
{
    return (frameSPtr_ != nullptr) && frameSPtr_->isDefined();
}

Shared<const Frame> Analytical::accessFrame() const
{
    return frameSPtr_;
}

}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk
