/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>

#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Objects/CelestialBodies/Sun.hpp>

namespace ostk
{
namespace physics
{

Environment::Environment(const Instant& anInstant, const Array<Shared<Object>>& anObjectArray)
    : instant_(anInstant),
      objects_(Array<Shared<const Object>>::Empty())
{
    objects_.reserve(anObjectArray.getSize());

    for (const auto& objectSPtr : anObjectArray)
    {
        objects_.add(Shared<const Object>(objectSPtr->clone()));
    }
}

Environment::Environment(const Environment& anEnvironment)
    : instant_(anEnvironment.instant_),
      objects_(Array<Shared<const Object>>::Empty())
{
    objects_.reserve(anEnvironment.objects_.getSize());

    for (const auto& objectSPtr : anEnvironment.objects_)
    {
        objects_.add(Shared<const Object>(objectSPtr->clone()));
    }
}

Environment& Environment::operator=(const Environment& anEnvironment)
{
    if (this != &anEnvironment)
    {
        instant_ = anEnvironment.instant_;

        objects_.clear();

        objects_.reserve(anEnvironment.objects_.getSize());

        for (const auto& objectSPtr : anEnvironment.objects_)
        {
            objects_.add(Shared<Object>(objectSPtr->clone()));
        }
    }

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Environment& anEnvironment)
{
    ostk::core::utils::Print::Header(anOutputStream, "Environment");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Instant:" << (anEnvironment.isDefined() ? anEnvironment.instant_.toString() : "Undefined");

    ostk::core::utils::Print::Line(anOutputStream) << "Objects:";

    for (const auto& objectSPtr : anEnvironment.objects_)
    {
        ostk::core::utils::Print::Line(anOutputStream) << (*objectSPtr);
    }

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Environment::isDefined() const
{
    return instant_.isDefined();
}

bool Environment::hasObjectWithName(const String& aName) const
{
    if (aName.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Name");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    for (const auto& objectSPtr : objects_)
    {
        if (objectSPtr->accessName() == aName)
        {
            return true;
        }
    }

    return false;
}

bool Environment::intersects(
    const Object::Geometry& aGeometry, const Array<Shared<const Object>>& anObjectToIgnoreArray
) const
{
    if (!aGeometry.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Geometry");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    for (const auto& objectSPtr : objects_)
    {
        if (!anObjectToIgnoreArray.contains(objectSPtr))
        {
            if (objectSPtr->getGeometryIn(aGeometry.accessFrame(), instant_).intersects(aGeometry))
            {
                return true;
            }
        }
    }

    return false;
}

Array<Shared<const Object>> Environment::accessObjects() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    Array<Shared<const Object>> objects = Array<Shared<const Object>>::Empty();

    objects.reserve(objects_.getSize());

    for (const auto& objectSPtr : objects_)
    {
        objects.add(objectSPtr);
    }

    return objects;
}

Shared<const Object> Environment::accessObjectWithName(const String& aName) const
{
    if (aName.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Name");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    for (const auto& objectSPtr : objects_)
    {
        if (objectSPtr->accessName() == aName)
        {
            return objectSPtr;
        }
    }

    throw ostk::core::error::RuntimeError("No object with name [{}].", aName);

    return nullptr;
}

Shared<const Celestial> Environment::accessCelestialObjectWithName(const String& aName) const
{
    if (const auto objectSPtr = this->accessObjectWithName(aName))
    {
        if (const auto celestialObjectSPtr = std::dynamic_pointer_cast<const Celestial>(objectSPtr))
        {
            return celestialObjectSPtr;
        }
    }

    throw ostk::core::error::RuntimeError("No celestial object with name [{}].", aName);

    return nullptr;
}

Instant Environment::getInstant() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    return instant_;
}

Array<String> Environment::getObjectNames() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    Array<String> objectNames = Array<String>::Empty();

    objectNames.reserve(objects_.getSize());

    for (const auto& objectSPtr : objects_)
    {
        objectNames.add(objectSPtr->getName());
    }

    return objectNames;
}

void Environment::setInstant(const Instant& anInstant)
{
    if (!anInstant.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Instant");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    instant_ = anInstant;
}

bool Environment::isPositionInEclipse(const Position& aPosition) const
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;

    using ostk::physics::coord::Frame;
    using ostk::physics::environment::Object;

    if (!aPosition.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    const Instant instant = this->getInstant();

    const Shared<const Frame> gcrfSPtr = Frame::GCRF();

    const Shared<const Object> sunSPtr = this->accessObjectWithName("Sun");

    const Segment sunToObjectSegment_GCRF = {
        Point::Vector(aPosition.inFrame(gcrfSPtr, instant).getCoordinates()),
        Point::Vector(sunSPtr->getPositionIn(gcrfSPtr, instant).getCoordinates()),
    };

    const Object::Geometry sunToObjectGeometry = {sunToObjectSegment_GCRF, gcrfSPtr};

    return this->intersects(sunToObjectGeometry, {sunSPtr});
}

Environment Environment::Undefined()
{
    return {Instant::Undefined(), Array<Shared<Object>>::Empty()};
}

Environment Environment::Default()
{
    using ostk::physics::environment::object::celestial::Earth;
    using ostk::physics::environment::object::celestial::Sun;
    using ostk::physics::environment::object::celestial::Moon;

    const Instant instant = Instant::J2000();

    const Array<Shared<Object>> objects = {
        std::make_shared<Earth>(Earth::Default()),
        std::make_shared<Sun>(Sun::Default()),
        std::make_shared<Moon>(Moon::Default())
    };

    return {instant, objects};
}

}  // namespace physics
}  // namespace ostk
