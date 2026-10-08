/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Utility__
#define __OpenSpaceToolkit_Physics_Coordinate_Frame_Provider_IERS_Utility__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

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
namespace iers
{
namespace utilities
{

using ostk::core::type::Real;

using ostk::physics::time::Instant;

/// @brief Linearly interpolate UT1 - UTC between two tabulated values
///
/// UT1 - UTC jumps by +1 s across a leap second, while UT1 - TAI is continuous. Interpolating UT1 - UTC directly
/// spreads that jump over the whole day that ends with the leap second. Across a leap second, UT1 - TAI is
/// interpolated instead and converted back to UT1 - UTC with TAI - UTC at the requested instant.
///
/// @code
///     Real ut1MinusUtc = utilities::interpolateUt1MinusUtc(
///         previousUt1MinusUtc, previousMjd_UTC, nextUt1MinusUtc, nextMjd_UTC, ratio, instant
///     );
/// @endcode
///
/// @param [in] aPreviousUt1MinusUtc UT1 - UTC at the previous tabulated date [s]
/// @param [in] aPreviousMjd_UTC Previous tabulated date (UTC modified Julian date)
/// @param [in] aNextUt1MinusUtc UT1 - UTC at the next tabulated date [s]
/// @param [in] aNextMjd_UTC Next tabulated date (UTC modified Julian date)
/// @param [in] aRatio Interpolation ratio
/// @param [in] anInstant Instant at which UT1 - UTC is interpolated
/// @return UT1 - UTC at the instant [s]
Real interpolateUt1MinusUtc(
    const Real& aPreviousUt1MinusUtc,
    const Real& aPreviousMjd_UTC,
    const Real& aNextUt1MinusUtc,
    const Real& aNextMjd_UTC,
    const Real& aRatio,
    const Instant& anInstant
);

}  // namespace utilities
}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk

#endif
