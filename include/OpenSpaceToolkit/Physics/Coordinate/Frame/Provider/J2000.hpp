/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_J2000__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_J2000__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider.hpp>
#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IAU/Theory.hpp>
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

/// @brief J2000 frame provider.
/// @details Defined with the Earth's Mean Equator and Mean Equinox (MEME) at 12:00 Terrestrial Time
/// on 1 January 2000. Also known as EME2000.
///
/// @ref https://en.wikipedia.org/wiki/Earth-centered_inertial

class J2000 : public Provider
{
   public:
    /// @brief Constructor.
    ///
    /// @code
    ///     J2000 provider = J2000(theory);
    /// @endcode
    ///
    /// @param [in] aTheory An IAU theory
    J2000(const iau::Theory& aTheory);

    /// @brief Destructor.
    virtual ~J2000() override;

    /// @brief Clone the J2000 provider.
    ///
    /// @code
    ///     J2000* clone = j2000.clone();
    /// @endcode
    ///
    /// @return A pointer to the cloned J2000 provider
    virtual J2000* clone() const override;

    /// @brief Check if the J2000 provider is defined.
    ///
    /// @code
    ///     bool isDefined = provider.isDefined();
    /// @endcode
    ///
    /// @return True if the J2000 provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the IAU theory.
    ///
    /// @code
    ///     iau::Theory theory = provider.getTheory();
    /// @endcode
    ///
    /// @return The IAU theory
    iau::Theory getTheory() const;

    /// @brief Get the J2000 epoch.
    ///
    /// @code
    ///     Instant epoch = provider.getEpoch();
    /// @endcode
    ///
    /// @return The J2000 epoch instant
    Instant getEpoch() const;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(instant);
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from GCRF to J2000 at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;

   private:
    iau::Theory theory_;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
