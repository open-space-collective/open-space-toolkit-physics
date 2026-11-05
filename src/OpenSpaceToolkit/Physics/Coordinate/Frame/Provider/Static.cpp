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
        transform_.accessTranslation(),
        transform_.accessVelocity(),
        transform_.accessOrientation(),
        transform_.accessAngularVelocity(),
        Transform::Type::Passive
    };
}

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
