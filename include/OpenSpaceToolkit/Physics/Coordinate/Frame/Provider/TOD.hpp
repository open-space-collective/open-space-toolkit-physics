/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TOD__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TOD__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IAU/Theory.hpp>
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

namespace iau = ostk::physics::coordinate::frame::provider::iau;

using ostk::physics::time::Instant;
using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Transform;

/// @brief                      True of Date (TOD) frame provider.
///
///                             Form the matrix of precession-nutation for a given date (including frame bias), IAU 2006
///                             precession and IAU 2000A nutation models.
///
/// @ref                        https://en.wikipedia.org/wiki/Earth-centered_inertial
/// @ref                        https://www2.mpia-hd.mpg.de/~mathar/progs/sofa_api/group__SF.html

class TOD : public Provider
{
   public:
    TOD(const Instant& anEpoch, const iau::Theory& aTheory);

    virtual ~TOD() override;

    virtual TOD* clone() const override;

    virtual bool isDefined() const override;

    Instant getEpoch() const;

    iau::Theory getTheory() const;

    virtual Transform getTransformAt(const Instant& anInstant) const override;

   private:
    Instant epoch_;
    iau::Theory theory_;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
