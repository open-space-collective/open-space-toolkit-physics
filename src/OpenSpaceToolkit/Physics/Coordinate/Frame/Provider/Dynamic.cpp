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

bool Dynamic::isDefined() const
{
    return !!generator_;
}

Transform Dynamic::getTransformAt(const Instant& anInstant) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Dynamic provider");
    }

    return generator_(anInstant);
}

Dynamic Dynamic::Undefined()
{
    return {{}};
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
