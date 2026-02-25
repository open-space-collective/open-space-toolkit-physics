/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_Static__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_Static__

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

/// @brief Static provider

class Static : public Provider
{
   public:
    /// @brief Constructor.
    ///
    /// @code
    ///     Static provider(transform) ;
    /// @endcode
    ///
    /// @param [in] aTransform A static transform
    Static(const Transform& aTransform);

    /// @brief Destructor.
    virtual ~Static() override;

    /// @brief Clone the Static provider.
    ///
    /// @code
    ///     Static* clonePtr = provider.clone() ;
    /// @endcode
    ///
    /// @return A pointer to the cloned Static provider
    virtual Static* clone() const override;

    /// @brief Check if the Static provider is defined.
    ///
    /// @code
    ///     provider.isDefined() ; // True
    /// @endcode
    ///
    /// @return True if the Static provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant (ignored for static transforms)
    /// @return The static transform
    virtual Transform getTransformAt(const Instant& anInstant) const override;

   private:
    Transform transform_;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
