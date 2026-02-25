/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_GCRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_GCRF__

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

/// @brief Geocentric Celestial Reference Frame (GCRF) provider
///
/// @ref https://en.wikipedia.org/wiki/Earth-centered_inertial

class GCRF : public Provider
{
   public:
    /// @brief Default constructor.
    ///
    /// @code
    ///     GCRF provider ;
    /// @endcode
    GCRF();

    /// @brief Destructor.
    virtual ~GCRF() override;

    /// @brief Clone the GCRF provider.
    ///
    /// @code
    ///     GCRF* clonePtr = provider.clone() ;
    /// @endcode
    ///
    /// @return A pointer to the cloned GCRF provider
    virtual GCRF* clone() const override;

    /// @brief Check if the GCRF provider is defined.
    ///
    /// @code
    ///     provider.isDefined() ; // True
    /// @endcode
    ///
    /// @return True if the GCRF provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The identity transform (GCRF is the root frame)
    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
