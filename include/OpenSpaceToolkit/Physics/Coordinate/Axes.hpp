/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Axes__
#define __OpenSpaceToolkit_Physics_Coordinate_Axes__

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{

using ostk::core::types::Shared;

using ostk::math::obj::Vector3d;

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

}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
