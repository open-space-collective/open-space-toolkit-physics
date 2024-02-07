/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TEME__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TEME__

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

/// @brief                      True Equator Mean Equinox (TEME) frame provider
///
/// @note                       This frame should only be used with Two-Line Elements (TLE).
///
/// @ref                        https://en.wikipedia.org/wiki/Earth-centered_inertial

class TEME : public Provider
{
   public:
    TEME();

    virtual ~TEME() override;

    virtual TEME* clone() const override;

    virtual bool isDefined() const override;

    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coord
}  // namespace physics
}  // namespace ostk

#endif
