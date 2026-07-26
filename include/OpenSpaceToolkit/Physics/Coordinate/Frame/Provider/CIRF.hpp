/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_CIRF__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

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

using ostk::core::type::Real;

using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::Instant;

/// @brief Celestial Intermediate Reference Frame (CIRF) provider
///
/// Bias, precession-nutation
///
/// @ref
/// https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_174.pdf?__blob=publicationFile&v=1

class CIRF : public Provider
{
   public:
    /// @brief Default constructor.
    ///
    /// @code
    ///     CIRF provider;
    /// @endcode
    CIRF();

    /// @brief Destructor.
    virtual ~CIRF() override;

    /// @brief Clone the CIRF provider.
    ///
    /// @code
    ///     CIRF* clonePtr = provider.clone();
    /// @endcode
    ///
    /// @return A pointer to the cloned CIRF provider
    virtual CIRF* clone() const override;

    /// @brief Check if the CIRF provider is defined.
    ///
    /// @code
    ///     provider.isDefined(); // True
    /// @endcode
    ///
    /// @return True if the CIRF provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000());
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from GCRF to CIRF at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;

    /// @brief Compute the IAU 2006/2000A CIP X, Y and CIO locator s at a given instant.
    ///
    /// This is the raw model output (before the observed CIP offsets applied by
    /// @ref getTransformAt), evaluated either directly via the SOFA series or by
    /// interpolating a cached grid of the series (see @ref IsXysInterpolationEnabled).
    ///
    /// @param [in] aModifiedJulianDate_TT A Modified Julian Date, in the TT scale
    /// @param [out] x The CIP X coordinate [rad]
    /// @param [out] y The CIP Y coordinate [rad]
    /// @param [out] s The CIO locator s [rad]
    /// @param [in] interpolate If true, interpolate a cached grid of the series; otherwise evaluate it directly
    static void ComputeCIPCoordinates(
        const Real& aModifiedJulianDate_TT, double& x, double& y, double& s, const bool interpolate
    );

    /// @brief Check whether X, Y, s interpolation is enabled.
    ///
    /// Defaults to enabled, unless the environment variable
    /// OSTK_PHYSICS_COORDINATE_FRAME_PROVIDER_CIRF_XYS_INTERPOLATION is set to "Disabled" or "False".
    /// Can be overridden at runtime via @ref SetXysInterpolationEnabled.
    ///
    /// @return True if X, Y, s interpolation is enabled
    static bool IsXysInterpolationEnabled();

    /// @brief Enable or disable X, Y, s interpolation at runtime.
    ///
    /// Overrides the environment-variable default. Primarily intended for testing and benchmarking.
    ///
    /// @param [in] anInterpolationEnabledFlag True to enable interpolation, false to evaluate the series directly
    static void SetXysInterpolationEnabled(const bool anInterpolationEnabledFlag);
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
