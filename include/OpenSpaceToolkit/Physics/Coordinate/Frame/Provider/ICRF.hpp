/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_ICRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_ICRF__

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

/// @brief International Celestial Reference Frame (ICRF) provider
///
/// @ref https://en.wikipedia.org/wiki/International_Celestial_Reference_Frame

class ICRF : public Provider
{
   public:
    /// @brief Default constructor.
    ///
    /// @code
    ///     ICRF provider;
    /// @endcode
    ICRF();

    /// @brief Destructor.
    virtual ~ICRF() override;

    /// @brief Clone the ICRF provider.
    ///
    /// @code
    ///     ICRF* clonePtr = provider.clone();
    /// @endcode
    ///
    /// @return A pointer to the cloned ICRF provider
    virtual ICRF* clone() const override;

    /// @brief Check if the ICRF provider is defined.
    ///
    /// @code
    ///     provider.isDefined(); // True
    /// @endcode
    ///
    /// @return True if the ICRF provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000());
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from GCRF to ICRF at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
