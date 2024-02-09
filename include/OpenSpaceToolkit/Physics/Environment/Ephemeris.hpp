/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemeris__
#define __OpenSpaceToolkit_Physics_Environment_Ephemeris__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{

using ostk::core::type::Shared;

using ostk::physics::coordinate::Frame;

/// @brief
///
/// @ref                        https://en.wikipedia.org/wiki/Fundamental_ephemeris

class Ephemeris
{
   public:
    Ephemeris();

    virtual ~Ephemeris() = 0;

    virtual Ephemeris* clone() const = 0;

    virtual bool isDefined() const = 0;

    virtual Shared<const Frame> accessFrame() const = 0;
};

}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
