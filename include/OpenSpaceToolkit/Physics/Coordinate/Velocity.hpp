/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Velocity__
#define __OpenSpaceToolkit_Physics_Coordinate_Velocity__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

#define DEFAULT_PRECISION Integer::Undefined()

using ostk::core::type::Shared;
using ostk::core::type::Integer;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::unit::Derived;
using ostk::physics::time::Instant;
using ostk::physics::coordinate::Position;

class Frame;

/// @brief                      Velocity

class Velocity
{
   public:
    enum class Unit
    {

        Undefined,
        MeterPerSecond

    };

    Velocity(const Vector3d& aCoordinateSet, const Velocity::Unit& aUnit, const Shared<const Frame>& aFrameSPtr);

    bool operator==(const Velocity& aVelocity) const;

    bool operator!=(const Velocity& aVelocity) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Velocity& aVelocity);

    bool isDefined() const;

    const Vector3d& accessCoordinates() const;

    Shared<const Frame> accessFrame() const;

    Vector3d getCoordinates() const;

    Velocity::Unit getUnit() const;

    Velocity inUnit(const Velocity::Unit& aUnit) const;

    Velocity inFrame(const Position& aPosition, const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    String toString(const Integer& aPrecision = DEFAULT_PRECISION) const;

    static Velocity Undefined();

    static Velocity MetersPerSecond(const Vector3d& aCoordinateSet, const Shared<const Frame>& aFrameSPtr);

    static String StringFromUnit(const Velocity::Unit& aUnit);

   private:
    Vector3d coordinates_;
    Velocity::Unit unit_;
    Shared<const Frame> frameSPtr_;  // [TBR] With Transform instead, as Frame is a function of time...

    static Derived::Unit DerivedUnitFromVelocityUnit(const Velocity::Unit& aUnit);
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
