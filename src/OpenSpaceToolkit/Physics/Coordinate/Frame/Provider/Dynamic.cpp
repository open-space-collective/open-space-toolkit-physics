/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Dynamic.hpp>

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

Dynamic::Dynamic(const Dynamic::Generator& aGenerator)
    : generator_(aGenerator)
{
}

Dynamic::~Dynamic() {}

Dynamic* Dynamic::clone() const
{
    return new Dynamic(*this);
}

Transform Dynamic::getTransformAt(const Instant& anInstant) const
{
    return generator_(anInstant);
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
