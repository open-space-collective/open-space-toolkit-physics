/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Position__
#define __OpenSpaceToolkit_Physics_Coordinate_Position__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Spherical/LLA.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Units/Length.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{

#define DEFAULT_PRECISION Integer::Undefined()

using ostk::core::type::Shared;
using ostk::core::type::Integer;
using ostk::core::type::String;

using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::object::Vector3d;

using ostk::physics::units::Length;
using ostk::physics::time::Instant;

class Frame;

/// @brief                      Position

class Position
{
   public:
    typedef Length::Unit Unit;

    Position(
        const Vector3d& aCoordinateSet,  // [TBI] Replace w/ Point
        const Position::Unit& aUnit,
        const Shared<const Frame>& aFrameSPtr
    );

    Position(const Position& aPosition);

    Position& operator=(const Position& aPosition);

    bool operator==(const Position& aPosition) const;

    bool operator!=(const Position& aPosition) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Position& aPosition);

    bool isDefined() const;

    bool isNear(const Position& aPosition, const Length& aTolerance) const;

    const Vector3d& accessCoordinates() const;

    Shared<const Frame> accessFrame() const;

    Vector3d getCoordinates() const;

    Position::Unit getUnit() const;

    Position inUnit(const Position::Unit& aUnit) const;

    Position inMeters() const;

    Position inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    String toString(const Integer& aPrecision = DEFAULT_PRECISION) const;

    static Position Undefined();

    static Position Meters(const Vector3d& aCoordinateSet, const Shared<const Frame>& aFrameSPtr);

   private:
    Vector3d coordinates_;
    Position::Unit unit_;
    Shared<const Frame> frameSPtr_;  // [TBR] With Transform instead, as Frame is a function of time...
};

}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
