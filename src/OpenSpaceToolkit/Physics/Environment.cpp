/// Apache License 2.0

#include <mutex>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>

#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Earth.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Moon.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial/Sun.hpp>

namespace ostk
{
namespace physics
{

static std::shared_mutex mutex;
Shared<Environment> instance = nullptr;

Environment::Environment(
    const Instant& anInstant, const Array<Shared<const Object>>& anObjectArray, const bool& setGlobalInstance
)
    : instant_(anInstant),
      objects_(Array<Shared<const Object>>::Empty()),
      centralCelestialObject_(nullptr)
{
    objects_.reserve(anObjectArray.getSize());

    for (const auto& objectSPtr : anObjectArray)
    {
        objects_.add(Shared<const Object>(objectSPtr->clone()));
    }

    if (setGlobalInstance)
    {
        Environment::SetGlobalInstance(std::make_shared<Environment>(*this));
    }
}

Environment::Environment(
    const Shared<const Object>& aCentralCelestialObject,
    const Array<Shared<const Object>>& anObjectArray,
    const Instant& anInstant,
    const bool& setGlobalInstance
)
    : instant_(anInstant),
      objects_(Array<Shared<const Object>>::Empty()),
      centralCelestialObject_(nullptr)
{
    objects_.reserve(anObjectArray.getSize() + 1);

    const Shared<const Object> centralCelestialObject = Shared<const Object>(aCentralCelestialObject->clone());
    centralCelestialObject_ = centralCelestialObject;

    objects_.add(centralCelestialObject);
    for (const auto& objectSPtr : anObjectArray)
    {
        objects_.add(Shared<const Object>(objectSPtr->clone()));
    }

    if (setGlobalInstance)
    {
        Environment::SetGlobalInstance(std::make_shared<Environment>(*this));
    }
}

Environment::Environment(const Environment& anEnvironment)
    : instant_(anEnvironment.instant_),
      objects_(Array<Shared<const Object>>::Empty()),
      centralCelestialObject_(nullptr)
{
    objects_.reserve(anEnvironment.objects_.getSize());

    for (const auto& objectSPtr : anEnvironment.objects_)
    {
        objects_.add(Shared<const Object>(objectSPtr->clone()));
    }

    centralCelestialObject_ =
        anEnvironment.hasCentralCelestialObject() ? anEnvironment.centralCelestialObject_ : nullptr;
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
            objects_.add(Shared<const Object>(objectSPtr->clone()));
        }

        centralCelestialObject_ =
            anEnvironment.hasCentralCelestialObject() ? anEnvironment.centralCelestialObject_ : nullptr;
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

    if (anEnvironment.hasCentralCelestialObject())
    {
        ostk::core::utils::Print::Line(anOutputStream) << "Central celestial object:";

        ostk::core::utils::Print::Line(anOutputStream) << (*anEnvironment.centralCelestialObject_);
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

bool Environment::hasCentralCelestialObject() const
{
    return centralCelestialObject_ != nullptr;
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

Shared<const Celestial> Environment::accessCentralCelestialObject() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    if (centralCelestialObject_ == nullptr)
    {
        throw ostk::core::error::RuntimeError("No central celestial object.");
    }

    return std::static_pointer_cast<const Celestial>(centralCelestialObject_);
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

    using ostk::physics::coordinate::Frame;
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
    return {Instant::Undefined(), Array<Shared<const Object>>::Empty()};
}

Environment Environment::Default(const bool& setGlobalInstance)
{
    using ostk::physics::environment::object::celestial::Earth;
    using ostk::physics::environment::object::celestial::Moon;
    using ostk::physics::environment::object::celestial::Sun;

    const Shared<const Object> earth = std::make_shared<Earth>(Earth::Default());
    const Shared<const Object> sun = std::make_shared<Sun>(Sun::Default());
    const Shared<const Object> moon = std::make_shared<Moon>(Moon::Default());

    const Array<Shared<const Object>> objects = {
        sun,
        moon,
    };

    const Environment environment = {earth, objects};

    if (setGlobalInstance)
    {
        Environment::SetGlobalInstance(std::make_shared<Environment>(environment));
    }

    return environment;
}

void Environment::ResetGlobalInstance()
{
    std::unique_lock<std::shared_mutex> lock(mutex);
    instance = nullptr;
}

Shared<Environment> Environment::AccessGlobalInstance()
{
    std::shared_lock<std::shared_mutex> lock(mutex);

    if (instance == nullptr)
    {
        throw ostk::core::error::RuntimeError("Environment instance is not set.");
    }

    return instance;
}

void Environment::SetGlobalInstance(const Shared<Environment>& anInstance)
{
    std::unique_lock<std::shared_mutex> lock(mutex);
    instance = anInstance;
}

}  // namespace physics
}  // namespace ostk
