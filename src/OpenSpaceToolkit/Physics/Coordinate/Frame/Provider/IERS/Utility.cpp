/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Physics/Coordinate/Frame/Provider/IERS/Utility.hpp>

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

using ostk::physics::time::Scale;

namespace
{

/// @brief TAI - UTC at an instant [s]
///
/// Computed from the TAI and UTC representations of the instant, which UT1 - UTC is applied to. During a leap second,
/// the UTC representation already uses the offset after the leap second, while Instant::getLeapSecondCount still
/// reports the offset before it.
///
/// @param anInstant An instant
/// @return TAI - UTC [s]
double getTaiMinusUtcAt(const Instant& anInstant)
{
    return std::round(
        (anInstant.getModifiedJulianDate(Scale::TAI) - anInstant.getModifiedJulianDate(Scale::UTC)) * 86400.0
    );
}

}  // namespace

double interpolateUt1MinusUtc(
    const double& aPreviousUt1MinusUtc,
    const double& aPreviousMjd_UTC,
    const double& aNextUt1MinusUtc,
    const double& aNextMjd_UTC,
    const double& aRatio,
    const Instant& anInstant
)
{
    if (std::isnan(aPreviousUt1MinusUtc) || std::isnan(aNextUt1MinusUtc))
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    // UT1 - UTC changes by a few milliseconds per day: a step larger than half a second can only be a leap second

    if (std::abs(aNextUt1MinusUtc - aPreviousUt1MinusUtc) < 0.5)
    {
        return aPreviousUt1MinusUtc + aRatio * (aNextUt1MinusUtc - aPreviousUt1MinusUtc);
    }

    const double previousUt1MinusTai =
        aPreviousUt1MinusUtc - getTaiMinusUtcAt(Instant::ModifiedJulianDate(aPreviousMjd_UTC, Scale::UTC));
    const double nextUt1MinusTai =
        aNextUt1MinusUtc - getTaiMinusUtcAt(Instant::ModifiedJulianDate(aNextMjd_UTC, Scale::UTC));

    const double ut1MinusTai = previousUt1MinusTai + aRatio * (nextUt1MinusTai - previousUt1MinusTai);

    return ut1MinusTai + getTaiMinusUtcAt(anInstant);
}

}  // namespace utilities
}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
