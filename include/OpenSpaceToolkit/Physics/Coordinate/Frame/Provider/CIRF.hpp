/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF__

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

/// @brief                      Celestial Intermediate Reference Frame (CIRF) provider
///
///                             Bias, precession-nutation
///
/// @ref
/// https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_174.pdf?__blob=publicationFile&v=1

class CIRF : public Provider
{
   public:
    CIRF();

    virtual ~CIRF() override;

    virtual CIRF* clone() const override;

    virtual bool isDefined() const override;

    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
