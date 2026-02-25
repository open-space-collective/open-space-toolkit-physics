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
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
