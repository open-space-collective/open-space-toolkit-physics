/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical__
#define __OpenSpaceToolkit_Physics_Environment_Ephemeris_SunMoonAnalytical__

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

/// @brief Low-precision analytical Sun/Moon ephemeris.
///
/// Positions are computed from the analytical series of Montenbruck & Gill,
/// approximating the body position with respect to the mean equator and equinox of J2000,
/// which is treated as GCRF (the frame bias of ~23 mas is far below the accuracy of the series).
///
/// Accuracy with respect to high-precision (JPL DE) ephemerides, measured over 2020-2026:
/// - Sun: < 0.1 deg in direction, < 0.01% in distance
/// - Moon: < 0.1 deg in direction, < 0.15% in distance
/// The dominant Sun error is a slow drift (~11.6 arcsec/year) due to the neglected motion of the Earth's perihelion.
///
/// This is orders of magnitude faster than a SPICE-based ephemeris,
/// and well-suited for applications such as third-body point-mass gravity
/// where only an approximate body position is needed.
///
/// @ref O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2.
class SunMoonAnalytical : public Ephemeris
{
   public:
    /// @brief Celestial body
    enum class Body
    {

        Sun,
        Moon

    };

    /// @brief Constructor
    ///
    /// @code
    ///     SunMoonAnalytical sunEphemeris = SunMoonAnalytical(SunMoonAnalytical::Body::Sun);
    /// @endcode
    ///
    /// @param [in] aBody A celestial body
    SunMoonAnalytical(const SunMoonAnalytical::Body& aBody);

    /// @brief Destructor
    virtual ~SunMoonAnalytical() override;

    /// @brief Clone
    ///
    /// @return Pointer to SunMoonAnalytical
    virtual SunMoonAnalytical* clone() const override;

    /// @brief Returns true if SunMoonAnalytical is defined
    ///
    /// @return True if SunMoonAnalytical is defined
    virtual bool isDefined() const override;

    /// @brief Access frame of the celestial body
    ///
    /// The frame is centered on the celestial body,
    /// with an identity orientation with respect to GCRF.
    ///
    /// @code
    ///     SunMoonAnalytical sunEphemeris = SunMoonAnalytical(SunMoonAnalytical::Body::Sun);
    ///     Shared<const Frame> frame = sunEphemeris.accessFrame();
    /// @endcode
    ///
    /// @return Shared pointer to frame
    virtual Shared<const Frame> accessFrame() const override;

    /// @brief Get celestial body
    ///
    /// @return Celestial body
    SunMoonAnalytical::Body getBody() const;

    /// @brief Convert celestial body to string
    ///
    /// @code
    ///     String str = SunMoonAnalytical::StringFromBody(SunMoonAnalytical::Body::Sun); // "Sun"
    /// @endcode
    ///
    /// @param [in] aBody A celestial body
    /// @return String representation of celestial body
    static String StringFromBody(const SunMoonAnalytical::Body& aBody);

   private:
    SunMoonAnalytical::Body body_;
};

}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
