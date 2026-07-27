/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_MoonAnalytical__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_MoonAnalytical__

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

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

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::Instant;

/// @brief Low-precision analytical Moon frame provider.
///
/// Provides the transform from GCRF to a frame centered on the Moon, with an identity orientation
/// with respect to GCRF. The Moon position is computed from the analytical series of Montenbruck & Gill,
/// approximating the position with respect to the mean equator and equinox of J2000, which is treated as
/// GCRF (the frame bias of ~23 mas is far below the accuracy of the series).
///
/// Accuracy with respect to high-precision (JPL DE) ephemerides, measured over 2020-2026:
/// < 0.1 deg in direction, < 0.15% in distance.
///
/// This is orders of magnitude faster than a SPICE-based ephemeris,
/// and well-suited for applications such as third-body point-mass gravity
/// where only an approximate body position is needed.
///
/// @ref O. Montenbruck, E. Gill, "Satellite Orbits: Models, Methods and Applications", Section 3.3.2.
class MoonAnalytical : public Provider
{
   public:
    /// @brief Constructor
    MoonAnalytical();

    /// @brief Destructor
    virtual ~MoonAnalytical() override;

    /// @brief Clone
    ///
    /// @return Pointer to MoonAnalytical
    virtual MoonAnalytical* clone() const override;

    /// @brief Returns true if MoonAnalytical is defined
    ///
    /// @return True if MoonAnalytical is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @param [in] anInstant An instant
    /// @return The transform at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;

   private:
    /// @brief Compute the Moon position [m], with respect to the mean equator and equinox of J2000 (treated as
    /// GCRF).
    static Vector3d ComputePosition(const Instant& anInstant);

    /// @brief Rotate a vector from the J2000 ecliptic plane to the mean equator and equinox of J2000.
    static Vector3d EquatorialFromEcliptic(const Vector3d& anEclipticVector);

    /// @brief Julian centuries (TT) since J2000, i.e. (MJD_TT - 51544.5) / 36525.
    static double JulianCenturiesSinceJ2000(const Instant& anInstant);

    /// @brief Return the fractional part of a value.
    static double FractionalPart(const double aValue);
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
