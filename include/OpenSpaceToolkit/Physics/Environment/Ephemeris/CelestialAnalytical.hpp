/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Ephemeris_CelestialAnalytical__
#define __OpenSpaceToolkit_Physics_Environment_Ephemeris_CelestialAnalytical__

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Ephemeris.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>
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

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::environment::Ephemeris;
using ostk::physics::environment::object::Celestial;
using ostk::physics::time::Instant;

/// @brief Low-precision analytical celestial ephemeris.
///
/// Positions are computed from the analytical series of Montenbruck & Gill,
/// approximating the body position with respect to the mean equator and equinox of J2000,
/// which is treated as GCRF (the frame bias of ~23 mas is far below the accuracy of the series).
///
/// Only the Sun and the Moon are currently supported.
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
class CelestialAnalytical : public Ephemeris
{
   public:
    /// @brief Constructor
    ///
    /// Only Celestial::Type::Sun and Celestial::Type::Moon are currently supported.
    ///
    /// @code
    ///     CelestialAnalytical sunEphemeris = CelestialAnalytical(Celestial::Type::Sun);
    /// @endcode
    ///
    /// @param [in] aType A celestial body type
    CelestialAnalytical(const Celestial::Type& aType);

    /// @brief Destructor
    virtual ~CelestialAnalytical() override;

    /// @brief Clone
    ///
    /// @return Pointer to CelestialAnalytical
    virtual CelestialAnalytical* clone() const override;

    /// @brief Returns true if CelestialAnalytical is defined
    ///
    /// @return True if CelestialAnalytical is defined
    virtual bool isDefined() const override;

    /// @brief Access frame of the celestial body
    ///
    /// The frame is centered on the celestial body,
    /// with an identity orientation with respect to GCRF.
    ///
    /// @code
    ///     CelestialAnalytical sunEphemeris = CelestialAnalytical(Celestial::Type::Sun);
    ///     Shared<const Frame> frame = sunEphemeris.accessFrame();
    /// @endcode
    ///
    /// @return Shared pointer to frame
    virtual Shared<const Frame> accessFrame() const override;

    /// @brief Get celestial body type
    ///
    /// @return Celestial body type
    Celestial::Type getType() const;

   private:
    Celestial::Type type_;

    /// @brief Return the frame name for a celestial body type (e.g. "Sun").
    static String StringFromType(const Celestial::Type& aType);

    /// @brief Compute the body position [m], with respect to the mean equator and equinox of J2000 (treated as GCRF).
    static Vector3d ComputePosition(const Celestial::Type& aType, const Instant& anInstant);

    /// @brief Compute the Sun position [m], with respect to the mean equator and equinox of J2000 (treated as GCRF).
    static Vector3d ComputeSunPosition(const Instant& anInstant);

    /// @brief Compute the Moon position [m], with respect to the mean equator and equinox of J2000 (treated as GCRF).
    static Vector3d ComputeMoonPosition(const Instant& anInstant);

    /// @brief Rotate a vector from the J2000 ecliptic plane to the mean equator and equinox of J2000.
    static Vector3d EquatorialFromEcliptic(const Vector3d& anEclipticVector);

    /// @brief Julian centuries (TT) since J2000, i.e. (MJD_TT - 51544.5) / 36525.
    static double JulianCenturiesSinceJ2000(const Instant& anInstant);

    /// @brief Return the fractional part of a value.
    static double FractionalPart(const double aValue);
};

}  // namespace ephemeris
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
