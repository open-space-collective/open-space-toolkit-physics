/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object__
#define __OpenSpaceToolkit_Physics_Environment_Object__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Geometry.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{

using ostk::core::type::Shared;
using ostk::core::type::String;
using ostk::core::type::Unique;

using ostk::physics::coordinate::Axes;
using ostk::physics::coordinate::Frame;
using ostk::physics::coordinate::Position;
using ostk::physics::coordinate::Transform;
using ostk::physics::coordinate::Velocity;
using ostk::physics::time::Instant;

class Object
{
   public:
    typedef object::Geometry Geometry;

    Object(const String& aName);

    Object(const String& aName, const Object::Geometry& aGeometry);

    Object(const Object& anObject);

    virtual ~Object() = 0;

    virtual Object* clone() const = 0;

    Object& operator=(const Object& anObject);

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    virtual bool isDefined() const;

    const String& accessName() const;

    virtual Shared<const Frame> accessFrame() const = 0;

    const Object::Geometry& accessGeometry() const;

    String getName() const;

    Object::Geometry getGeometry() const;

    virtual Position getPositionIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const = 0;

    virtual Velocity getVelocityIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const = 0;

    virtual Transform getTransformTo(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const = 0;

    virtual Axes getAxesIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const = 0;

    Object::Geometry getGeometryIn(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

   private:
    String name_;

    Object::Geometry geometry_;
};

}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
