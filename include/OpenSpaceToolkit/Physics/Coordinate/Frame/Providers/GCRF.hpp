/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_GCRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Providers_GCRF__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{

using ostk::physics::time::Instant;
using ostk::physics::coord::frame::Provider;
using ostk::physics::coord::Transform;

/// @brief                      Geocentric Celestial Reference Frame (GCRF) provider
///
/// @ref                        https://en.wikipedia.org/wiki/Earth-centered_inertial

class GCRF : public Provider
{
   public:
    GCRF();

    virtual ~GCRF() override;

    virtual GCRF* clone() const override;

    virtual bool isDefined() const override;

    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
