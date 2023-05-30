/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemerides_Analytical__
#define __OpenSpaceToolkit_Physics_Environment_Ephemerides_Analytical__

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace env
{
namespace ephem
{

using ostk::core::types::Shared;

using ostk::physics::time::Instant;
using ostk::physics::coord::Frame;
using ostk::physics::env::Ephemeris;

class Analytical : public Ephemeris
{
   public:
    Analytical(const Shared<const Frame>& aFrameSPtr);

    virtual ~Analytical() override;

    virtual Analytical* clone() const override;

    virtual bool isDefined() const override;

    virtual Shared<const Frame> accessFrame() const override;

   private:
    Shared<const Frame> frameSPtr_;
};

}  // namespace ephem
}  // namespace env
}  // namespace physics
}  // namespace ostk

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
