/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Ephemerides/Analytical.hpp>

namespace ostk
{
namespace physics
{
namespace env
{
namespace ephem
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

}  // namespace ephem
}  // namespace env
}  // namespace physics
}  // namespace ostk
