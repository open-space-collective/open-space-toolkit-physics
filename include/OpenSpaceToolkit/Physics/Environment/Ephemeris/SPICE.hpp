/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE__
#define __OpenSpaceToolkit_Physics_Environment_Ephemeris_SPICE__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace ephemeris
{

using ostk::core::type::Shared;
using ostk::core::type::String;

using ostk::physics::coordinate::Frame;
using ostk::physics::environment::Ephemeris;
using ostk::physics::time::Instant;

/// @brief                      SPICE Toolkit ephemeris
///
/// @ref                        https://en.wikipedia.org/wiki/Jet_Propulsion_Laboratory_Development_Ephemeris

class SPICE : public Ephemeris
{
   public:
    /// @brief              SPICE object

    enum class Object
    {

        Undefined,
        Sun,
        Mercury,
        Venus,
        Earth,
        Moon,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune

    };

    /// @brief              Constructor
    ///
    /// @param              [in] anObject A SPICE object

    SPICE(const SPICE::Object& anObject);

    /// @brief              Destructor

    virtual ~SPICE() override;

    /// @brief              Clone
    ///
    /// @return             Pointer to SPICE

    virtual SPICE* clone() const override;

    /// @brief              Returns true if SPICE is defined
    ///
    /// @return             True if SPICE is defined

    virtual bool isDefined() const override;

    /// @brief              Access frame of SPICE object
    ///
    /// @return             Shared pointer to frame

    virtual Shared<const Frame> accessFrame() const override;

    /// @brief              Convert SPICE object to string
    ///
    /// @param              [in] anObject A SPICE object
    /// @return             String representation of SPICE object

    static String StringFromObject(const SPICE::Object& anObject);

   private:
    SPICE::Object object_;
};

}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
