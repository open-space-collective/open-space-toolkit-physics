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

/// @brief Abstract base class for ephemeris providers.
///
/// @ref https://en.wikipedia.org/wiki/Fundamental_ephemeris
class Ephemeris
{
   public:
    /// @brief Default constructor.
    Ephemeris();

    /// @brief Pure virtual destructor.
    virtual ~Ephemeris() = 0;

    /// @brief Clone the ephemeris.
    ///
    /// @return Pointer to cloned ephemeris.
    virtual Ephemeris* clone() const = 0;

    /// @brief Check if the ephemeris is defined.
    ///
    /// @return True if the ephemeris is defined.
    virtual bool isDefined() const = 0;

    /// @brief Access the reference frame of the ephemeris.
    ///
    /// @return Shared pointer to the reference frame.
    virtual Shared<const Frame> accessFrame() const = 0;
};

}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
