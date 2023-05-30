/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Velocity__
#define __OpenSpaceToolkit_Physics_Coordinate_Velocity__

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Derived.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{

#define DEFAULT_PRECISION Integer::Undefined()

using ostk::core::types::Shared;
using ostk::core::types::Integer;
using ostk::core::types::String;

using ostk::math::obj::Vector3d;

using ostk::physics::units::Derived;
using ostk::physics::time::Instant;
using ostk::physics::coord::Position;

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

}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
