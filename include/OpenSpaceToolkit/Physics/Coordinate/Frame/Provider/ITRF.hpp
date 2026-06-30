/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_ITRF__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_ITRF__

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

/// @brief International Terrestrial Reference System (ITRF) provider
///
/// @ref https://en.wikipedia.org/wiki/International_Terrestrial_Reference_System

class ITRF : public Provider
{
   public:
    /// @brief Default constructor.
    ///
    /// @code
    ///     ITRF provider;
    /// @endcode
    ITRF();

    /// @brief Destructor.
    virtual ~ITRF() override;

    /// @brief Clone the ITRF provider.
    ///
    /// @code
    ///     ITRF* clonePtr = provider.clone();
    /// @endcode
    ///
    /// @return A pointer to the cloned ITRF provider
    virtual ITRF* clone() const override;

    /// @brief Check if the ITRF provider is defined.
    ///
    /// @code
    ///     provider.isDefined(); // True
    /// @endcode
    ///
    /// @return True if the ITRF provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000());
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from TIRF to ITRF at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
