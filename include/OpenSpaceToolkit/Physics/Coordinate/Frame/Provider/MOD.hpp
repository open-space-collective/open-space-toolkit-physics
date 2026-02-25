/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_MOD__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_MOD__

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

/// @brief Mean of Date (MOD) frame provider.
///
/// Transformation from the Geocentric Celestial Reference Frame (GCRF) frame to the Mean of
/// Date (MOD) frame. This algorithm uses the IAU-76/FK5 theory.
///
/// The Mean of Date (MOD) frame is rotated into the Geocentric Celestial Reference Frame
/// (GCRF) considering the IAU 1976 Precession model. Notice that if the conversion `TOD =>
/// MOD` is performed **without** considering the EOP corrections, then the GCRF obtained by
/// this rotation is what is usually called the J2000 reference frame.
///
/// @ref https://en.wikipedia.org/wiki/Earth-centered_inertial
/// @ref https://github.com/JuliaSpace/SatelliteToolbox.jl/blob/master/src/Transformation/fk5/fk5.jl#L396

class MOD : public Provider
{
   public:
    /// @brief Constructor.
    ///
    /// @code
    ///     MOD provider(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anEpoch An epoch instant
    MOD(const Instant& anEpoch);

    /// @brief Destructor.
    virtual ~MOD() override;

    /// @brief Clone the MOD provider.
    ///
    /// @code
    ///     MOD* clonePtr = provider.clone() ;
    /// @endcode
    ///
    /// @return A pointer to the cloned MOD provider
    virtual MOD* clone() const override;

    /// @brief Check if the MOD provider is defined.
    ///
    /// @code
    ///     provider.isDefined() ; // True
    /// @endcode
    ///
    /// @return True if the MOD provider is defined
    virtual bool isDefined() const override;

    /// @brief Get the epoch.
    ///
    /// @code
    ///     Instant epoch = provider.getEpoch() ;
    /// @endcode
    ///
    /// @return The epoch instant
    Instant getEpoch() const;

    /// @brief Get the transform at a given instant.
    ///
    /// @code
    ///     Transform transform = provider.getTransformAt(Instant::J2000()) ;
    /// @endcode
    ///
    /// @param [in] anInstant An instant
    /// @return The transform from GCRF to MOD at the given instant
    virtual Transform getTransformAt(const Instant& anInstant) const override;

   private:
    Instant epoch_;
};

}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
