/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/Static.hpp>

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

Static::Static(const Transform& aTransform)
    : transform_(aTransform)
{
}

Static::~Static() {}

Static* Static::clone() const
{
    return new Static(*this);
}

Transform Static::getTransformAt(const Instant& anInstant) const
{
    return {
        anInstant,
        transform_.getTranslation(),
        transform_.getVelocity(),
        transform_.getOrientation(),
        transform_.getAngularVelocity(),
        Transform::Type::Passive
    };
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
