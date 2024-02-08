/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_GCRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_GCRF__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Transform.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace coordinate
{
namespace frame
{
namespace provider
{

using ostk::physics::time::Instant;
using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Transform;

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
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
