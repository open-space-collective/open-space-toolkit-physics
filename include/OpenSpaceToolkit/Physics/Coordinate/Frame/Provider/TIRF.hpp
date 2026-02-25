/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TIRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TIRF__

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

/// @brief Terrestrial Intermediate Reference Frame (TIRF) provider
///
/// Earth rotation angle
///
/// @ref
/// https://www.iers.org/SharedDocs/Publikationen/EN/IERS/Publications/tn/TechnNote36/tn36_174.pdf?__blob=publicationFile&v=1
class TIRF : public Provider
{
   public:
    /// @brief Default constructor.
    ///
    /// @code
    ///     TIRF provider;
    /// @endcode
    TIRF();

    /// @brief Destructor.
    virtual ~TIRF() override;

    /// @brief Clone the TIRF provider.
    ///
    /// @code
    ///     TIRF* clonePtr = provider.clone();
    /// @endcode
    ///
    /// @return A pointer to the cloned TIRF provider
    virtual TIRF* clone() const override;

    /// @brief Check if the TIRF provider is defined.
    ///
    /// @code
    ///     provider.isDefined(); // True
    /// @endcode
    ///
    /// @return True if the TIRF provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000());
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from CIRF to TIRF at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
