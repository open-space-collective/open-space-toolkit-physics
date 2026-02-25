/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TOD__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_TOD__

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

namespace iau = ostk::physics::coordinate::frame::provider::iau;

using ostk::physics::coordinate::frame::Provider;
using ostk::physics::coordinate::Transform;
using ostk::physics::time::Instant;

/// @brief True of Date (TOD) frame provider.
///
/// Form the matrix of precession-nutation for a given date (including frame bias), IAU 2006
/// precession and IAU 2000A nutation models.
///
/// @ref https://en.wikipedia.org/wiki/Earth-centered_inertial
/// @ref https://www2.mpia-hd.mpg.de/~mathar/progs/sofa_api/group__SF.html
class TOD : public Provider
{
   public:
    /// @brief Constructor.
    ///
    /// @code
    ///     TOD provider(Instant::J2000(), iau::Theory::IAU_2006) ;
    /// @endcode
    ///
    /// @param [in] anEpoch An epoch instant
    /// @param [in] aTheory An IAU theory
    TOD(const Instant& anEpoch, const iau::Theory& aTheory);

    /// @brief Destructor.
    virtual ~TOD() override;

    /// @brief Clone the TOD provider.
    ///
    /// @code
    ///     TOD* clonePtr = provider.clone() ;
    /// @endcode
    ///
    /// @return A pointer to the cloned TOD provider
    virtual TOD* clone() const override;

    /// @brief Check if the TOD provider is defined.
    ///
    /// @code
    ///     provider.isDefined() ; // True
    /// @endcode
    ///
    /// @return True if the TOD provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the epoch.
    ///
    /// @code
    ///     Instant epoch = provider.getEpoch() ;
    /// @endcode
    ///
    /// @return The epoch instant
    Instant getEpoch() const;

    /// @brief Get the IAU theory.
    ///
    /// @code
    ///     iau::Theory theory = provider.getTheory() ;
    /// @endcode
    ///
    /// @return The IAU theory
    iau::Theory getTheory() const;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from MOD to TOD at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;

   private:
    Instant epoch_;
    iau::Theory theory_;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
