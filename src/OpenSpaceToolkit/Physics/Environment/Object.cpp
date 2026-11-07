/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{

Object::Object(const String& aName)
    : name_(aName),
      geometry_(std::nullopt)
{
}

Object::Object(const String& aName, const Object::Geometry& aGeometry)
    : name_(aName),
      geometry_(aGeometry)
{
}

Object::Object(const Object& anObject)
    : name_(anObject.name_),
      geometry_(anObject.geometry_)
{
}

Object::~Object() {}

Object& Object::operator=(const Object& anObject)
{
    if (this != &anObject)
    {
        name_ = anObject.name_;
        geometry_ = anObject.geometry_;
    }

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject)
{
    ostk::core::utils::Print::Header(anOutputStream, "Object");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Name:" << (!anObject.name_.isEmpty() ? anObject.name_ : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

const String& Object::getName() const
{
    return name_;
}

const std::optional<Object::Geometry>& Object::getGeometry() const
{
    return geometry_;
}

std::optional<Object::Geometry> Object::getGeometryIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant)
    const
{
    if (!geometry_.has_value())
    {
        return std::nullopt;
    }

    return geometry_->in(aFrameSPtr, anInstant);
}

}  // namespace environment
}  // namespace physics
}  // namespace ostk
