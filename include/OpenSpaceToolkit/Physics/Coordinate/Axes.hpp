/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Axes__
#define __OpenSpaceToolkit_Physics_Coordinate_Axes__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{

using ostk::core::type::Shared;

using ostk::mathematics::object::Vector3d;

using ostk::physics::time::Instant;

class Frame;

/// @brief                      Axes

class Axes
{
   public:
    Axes(const Vector3d& aXAxis, const Vector3d& aYAxis, const Vector3d& aZAxis, const Shared<const Frame>& aFrameSPtr);

    bool operator==(const Axes& anAxes) const;

    bool operator!=(const Axes& anAxes) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Axes& anAxes);

    bool isDefined() const;

    const Vector3d& x() const;

    const Vector3d& y() const;

    const Vector3d& z() const;

    Shared<const Frame> getFrame() const;

    Axes inFrame(const Shared<const Frame>& aFrameSPtr, const Instant& anInstant) const;

    static Axes Undefined();

   private:
    Vector3d x_;
    Vector3d y_;
    Vector3d z_;

    Shared<const Frame> frameSPtr_;
};

}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
