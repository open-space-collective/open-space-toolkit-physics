/// Apache License 2.0

#include <cmath>

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
Real getTaiMinusUtcAt(const Instant& anInstant)
{
    return std::round(
        (anInstant.getModifiedJulianDate(Scale::TAI) - anInstant.getModifiedJulianDate(Scale::UTC)) * 86400.0
    );
}

}  // namespace

Real interpolateUt1MinusUtc(
    const Real& aPreviousUt1MinusUtc,
    const Real& aPreviousMjd_UTC,
    const Real& aNextUt1MinusUtc,
    const Real& aNextMjd_UTC,
    const Real& aRatio,
    const Instant& anInstant
)
{
    if (!aPreviousUt1MinusUtc.isDefined() || !aNextUt1MinusUtc.isDefined())
    {
        return Real::Undefined();
    }

    // UT1 - UTC changes by a few milliseconds per day: a step larger than half a second can only be a leap second

    if ((aNextUt1MinusUtc - aPreviousUt1MinusUtc).abs() < 0.5)
    {
        return aPreviousUt1MinusUtc + aRatio * (aNextUt1MinusUtc - aPreviousUt1MinusUtc);
    }

    const Real previousUt1MinusTai =
        aPreviousUt1MinusUtc - getTaiMinusUtcAt(Instant::ModifiedJulianDate(aPreviousMjd_UTC, Scale::UTC));
    const Real nextUt1MinusTai =
        aNextUt1MinusUtc - getTaiMinusUtcAt(Instant::ModifiedJulianDate(aNextMjd_UTC, Scale::UTC));

    const Real ut1MinusTai = previousUt1MinusTai + aRatio * (nextUt1MinusTai - previousUt1MinusTai);

    return ut1MinusTai + getTaiMinusUtcAt(anInstant);
}

}  // namespace utilities
}  // namespace iers
}  // namespace provider
}  // namespace frame
}  // namespace coordinate
}  // namespace physics
}  // namespace ostk
