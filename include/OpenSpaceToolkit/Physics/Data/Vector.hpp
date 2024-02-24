/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Vector__
#define __OpenSpaceToolkit_Physics_Data_Vector__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

namespace ostk
{
namespace physics
{
namespace data
{

using ostk::core::type::Shared;
using ostk::core::type::Integer;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::Unit;
using ostk::physics::time::Instant;
using ostk::physics::coordinate::Frame;

/// @brief                      Vector quantity

class Vector
{
   public:
    Vector(const Vector3d& aValue, const Unit& aUnit, const Shared<const Frame>& aFrameSPtr);

    bool operator==(const Vector& aVector) const;

    bool operator!=(const Vector& aVector) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Vector& aVector);

    bool isDefined() const;

    Vector3d getValue() const;

    Unit getUnit() const;

    Shared<const Frame> getFrame() const;

    Vector inUnit(const Unit& aUnit) const;

    Vector inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    String toString(const Integer& aPrecision = 6) const;

    static Vector Undefined();

   private:
    Vector3d value_;
    Unit unit_;
    Shared<const Frame> frameSPtr_;
};

}  // namespace data
}  // namespace physics
}  // namespace ostk

#endif
