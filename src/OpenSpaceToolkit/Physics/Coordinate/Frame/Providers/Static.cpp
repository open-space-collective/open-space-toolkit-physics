/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Providers/Static.hpp>

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

Static::Static(const Transform& aTransform)
    : transform_(aTransform)
{
}

Static::~Static() {}

Static* Static::clone() const
{
    return new Static(*this);
}

bool Static::isDefined() const
{
    return transform_.isDefined();
}

Transform Static::getTransformAt(const Instant& anInstant) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Static provider");
    }

    return {
        anInstant,
        transform_.accessTranslation(),
        transform_.accessVelocity(),
        transform_.accessOrientation(),
        transform_.accessAngularVelocity(),
        Transform::Type::Passive
    };
}

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk
