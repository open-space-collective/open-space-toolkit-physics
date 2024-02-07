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
      geometry_(Geometry::Undefined())
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

bool Object::isDefined() const
{
    return !name_.isEmpty();
}

const String& Object::accessName() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    return name_;
}

const Object::Geometry& Object::accessGeometry() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    return geometry_;
}

String Object::getName() const
{
    return this->accessName();
}

Object::Geometry Object::getGeometry() const
{
    return this->accessGeometry();
}

Object::Geometry Object::getGeometryIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const
{
    return this->accessGeometry().in(aFrameSPtr, anInstant);
}

}  // namespace environment
}  // namespace physics
}  // namespace ostk
