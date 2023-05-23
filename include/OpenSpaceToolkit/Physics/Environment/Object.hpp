/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Object__
#define __OpenSpaceToolkit_Physics_Environment_Object__

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Axes.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Velocity.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Geometry.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace env
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Unique;
using ostk::core::types::Shared;
using ostk::core::types::String;

using ostk::physics::time::Instant;
using ostk::physics::coord::Position;
using ostk::physics::coord::Velocity;
using ostk::physics::coord::Axes;
using ostk::physics::coord::Frame;
using ostk::physics::coord::Transform;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Object
{
   public:
    typedef object::Geometry Geometry;

    Object(const String& aName, const Instant& anInstant);

    Object(const String& aName, const Instant& anInstant, const Object::Geometry& aGeometry);

    Object(const Object& anObject);

    virtual ~Object() = 0;

    virtual Object* clone() const = 0;

    Object& operator=(const Object& anObject);

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    virtual bool isDefined() const;

    const String& accessName() const;

    const Instant& accessInstant() const;

    virtual Shared<const Frame> accessFrame() const = 0;

    const Object::Geometry& accessGeometry() const;

    String getName() const;

    Instant getInstant() const;

    Object::Geometry getGeometry() const;

    virtual Position getPositionIn(const Shared<const Frame>& aFrameSPtr) const = 0;

    virtual Velocity getVelocityIn(const Shared<const Frame>& aFrameSPtr) const = 0;

    virtual Transform getTransformTo(const Shared<const Frame>& aFrameSPtr) const = 0;

    virtual Axes getAxesIn(const Shared<const Frame>& aFrameSPtr) const = 0;

    Object::Geometry getGeometryIn(const Shared<const Frame>& aFrameSPtr) const;

    void setInstant(const Instant& anInstant);

   private:
    String name_;
    Instant instant_;

    Object::Geometry geometry_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace env
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
