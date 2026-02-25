/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TEME__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TEME__

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

/// @brief True Equator Mean Equinox (TEME) frame provider
///
/// @note This frame should only be used with Two-Line Elements (TLE).
///
/// @ref https://en.wikipedia.org/wiki/Earth-centered_inertial
class TEME : public Provider
{
   public:
    /// @brief Default constructor.
    ///
    /// @code
    ///     TEME provider ;
    /// @endcode
    TEME();

    /// @brief Destructor.
    virtual ~TEME() override;

    /// @brief Clone the TEME provider.
    ///
    /// @code
    ///     TEME* clonePtr = provider.clone() ;
    /// @endcode
    ///
    /// @return A pointer to the cloned TEME provider
    virtual TEME* clone() const override;

    /// @brief Check if the TEME provider is defined.
    ///
    /// @code
    ///     provider.isDefined() ; // True
    /// @endcode
    ///
    /// @return True if the TEME provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from TOD to TEME at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
