/// Apache License 2.0

#include <algorithm>
#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

#include <OpenSpaceToolkit/Physics/Environment/Object.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Utility/Eclipse.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace utilities
{

using ostk::core::type::Shared;
using ostk::core::type::Size;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d3::object::Segment;
using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Frame;
using ostk::physics::environment::Object;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;

EclipsePhase::EclipsePhase(const Region& aRegion, const Interval& anInterval, const bool& anIsComplete)
    : region_(aRegion),
      interval_(anInterval),
      isComplete_(anIsComplete)
{
}

EclipsePhase::Region EclipsePhase::getRegion() const
{
    return region_;
}

const Interval& EclipsePhase::getInterval() const
{
    return interval_;
}

bool EclipsePhase::isComplete() const
{
    return isComplete_;
}

std::ostream& operator<<(std::ostream& anOutputStream, const EclipsePhase& anEclipsePhase)
{
    ostk::core::utils::Print::Header(anOutputStream, "Eclipse Phase");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Region:" << (anEclipsePhase.getRegion() == EclipsePhase::Region::Umbra ? "Umbra" : "Penumbra");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Interval:"
        << (anEclipsePhase.getInterval().isDefined() ? anEclipsePhase.getInterval().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Complete:" << (anEclipsePhase.isComplete() ? "True" : "False");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool EclipsePhase::operator==(const EclipsePhase& anEclipsePhase) const
{
    return region_ == anEclipsePhase.region_ && interval_ == anEclipsePhase.interval_ &&
           isComplete_ == anEclipsePhase.isComplete_;
}

bool EclipsePhase::operator!=(const EclipsePhase& anEclipsePhase) const
{
    return !(*this == anEclipsePhase);
}

Eclipse::Eclipse(
    const Celestial& anOccultedCelestialObject,
    const Celestial& anOccultingCelestialObject,
    const Array<EclipsePhase>& somePhases
)
    : occultedCelestialObject_(anOccultedCelestialObject),
      occultingCelestialObject_(anOccultingCelestialObject),
      phases_(somePhases)
{
    if (phases_.isEmpty())
    {
        throw ostk::core::error::RuntimeError("Eclipse has no phases.");
    }

    // Sort phases by start time
    std::sort(
        phases_.begin(),
        phases_.end(),
        [](const EclipsePhase& a, const EclipsePhase& b)
        {
            return a.getInterval().getStart() < b.getInterval().getStart();
        }
    );

    // Check if phases are contiguous
    for (Size i = 1; i < phases_.getSize(); ++i)
    {
        if (phases_[i].getInterval().getStart() != phases_[i - 1].getInterval().getEnd())
        {
            throw ostk::core::error::RuntimeError("Eclipse phases are not contiguous.");
        }
    }
}

const Celestial& Eclipse::accessOccultedCelestialObject() const
{
    return occultedCelestialObject_;
}

const Celestial& Eclipse::accessOccultingCelestialObject() const
{
    return occultingCelestialObject_;
}

const Array<EclipsePhase>& Eclipse::getPhases() const
{
    return phases_;
}

Duration Eclipse::getDuration(const bool& includePenumbra) const
{
    Array<Interval> intervalsToConsider = Array<Interval>::Empty();

    for (const auto& phase : phases_)
    {
        if (includePenumbra || phase.getRegion() == EclipsePhase::Region::Umbra)
        {
            intervalsToConsider.add(phase.getInterval());
        }
    }

    Duration duration = Duration::Zero();

    for (const auto& interval : intervalsToConsider)
    {
        duration += interval.getDuration();
    }

    return duration;
}

Interval Eclipse::getInterval(const bool& includePenumbra) const
{
    if (includePenumbra)
    {
        return Interval::Closed(
            phases_.accessFirst().getInterval().getStart(), phases_.accessLast().getInterval().getEnd()
        );
    }

    Array<Interval> umbras = Array<Interval>::Empty();
    for (const auto& phase : phases_)
    {
        if (phase.getRegion() == EclipsePhase::Region::Umbra)
        {
            umbras.add(phase.getInterval());
        }
    }

    if (umbras.isEmpty())
    {
        return Interval::Undefined();
    }

    if (umbras.getSize() == 1)
    {
        return umbras[0];
    }

    throw ostk::core::error::RuntimeError("Eclipse has multiple umbra phases.");
}

std::ostream& operator<<(std::ostream& anOutputStream, const Eclipse& anEclipse)
{
    ostk::core::utils::Print::Header(anOutputStream, "Eclipse");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Occulted Object:" << anEclipse.accessOccultedCelestialObject().getName();
    ostk::core::utils::Print::Line(anOutputStream)
        << "Occulting Object:" << anEclipse.accessOccultingCelestialObject().getName();
    ostk::core::utils::Print::Line(anOutputStream) << "Number of Phases:" << anEclipse.getPhases().getSize();

    const Interval intervalWithPenumbra = anEclipse.getInterval(true);
    ostk::core::utils::Print::Line(anOutputStream)
        << "Interval (with penumbra):"
        << (intervalWithPenumbra.isDefined() ? intervalWithPenumbra.toString() : "Undefined");

    const Interval intervalWithoutPenumbra = anEclipse.getInterval(false);
    ostk::core::utils::Print::Line(anOutputStream)
        << "Interval (umbra only):"
        << (intervalWithoutPenumbra.isDefined() ? intervalWithoutPenumbra.toString() : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

Real montenbruckGillShadowFunction(
    const Instant& anInstant,
    const Position& aPosition,
    const Celestial& anOccultedCelestialObject,
    const Celestial& anOccultingCelestialObject
)
{
    const Shared<const Frame> frame = anOccultingCelestialObject.accessFrame();

    // Get object position coordinates in the occulting object's frame
    const Position objectPositionInFrame = aPosition.inFrame(frame, anInstant);
    const Vector3d objectPositionCoordinates = objectPositionInFrame.inMeters().getCoordinates();

    // Get occulted object position relative to the object
    const Position occultedPositionInFrame = anOccultedCelestialObject.getPositionIn(frame, anInstant);
    const Vector3d objectToOccultedPositionCoordinates =
        occultedPositionInFrame.inMeters().getCoordinates() - objectPositionCoordinates;

    // Get occulting object position relative to the object
    const Position occultingPositionInFrame = anOccultingCelestialObject.getPositionIn(frame, anInstant);
    const Vector3d objectToOccultingPositionCoordinates =
        occultingPositionInFrame.inMeters().getCoordinates() - objectPositionCoordinates;

    // Helper function to compute apparent angular radius
    auto computeApparentAngularRadius = [](const Celestial& celestialObject,
                                           const Vector3d& objectToCelestialObjectPositionCoordinates) -> Real
    {
        const Real equatorialRadius = celestialObject.getEquatorialRadius().inMeters();
        const Real distance = objectToCelestialObjectPositionCoordinates.norm();

        if (distance <= equatorialRadius)
        {
            return M_PI / 2.0;
        }

        return std::asin(equatorialRadius / distance);
    };

    // Apparent angular radius of the occulted celestial object
    const Real a = computeApparentAngularRadius(anOccultedCelestialObject, objectToOccultedPositionCoordinates);

    // Apparent angular radius of the occulting celestial object
    const Real b = computeApparentAngularRadius(anOccultingCelestialObject, objectToOccultingPositionCoordinates);

    // Apparent angular separation between the occulted and occulting celestial objects
    const Real c =
        Angle::Between(objectToOccultedPositionCoordinates, objectToOccultingPositionCoordinates).inRadians();

    if (c >= a + b)
    {
        return 1.0;  // Fully illuminated
    }

    if (c < std::abs(b - a))
    {
        return 0.0;  // Umbra
    }

    // Penumbra calculation
    const Real x = (c * c + a * a - b * b) / (2.0 * c);
    const Real y = std::sqrt(a * a - x * x);
    const Real A = a * a * std::acos(x / a) + b * b * std::acos((c - x) / b) - c * y;

    return std::clamp(1.0 - A / (M_PI * a * a), Real(0.0), Real(1.0));  // Penumbra
}

Array<Interval> eclipseIntervalsAtPosition(
    const Interval& anAnalysisInterval,
    const Position& aPosition,
    const Environment& anEnvironment,
    const bool& includePenumbra,
    const Duration& timeStep
)
{
    if (!anAnalysisInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Analysis interval");
    }

    if (!aPosition.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Position");
    }

    if (!anEnvironment.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Environment");
    }

    Environment environment = anEnvironment;

    Array<Interval> eclipseIntervals = Array<Interval>::Empty();

    Instant eclipseStartInstant = Instant::Undefined();
    Instant eclipseEndInstant = Instant::Undefined();

    for (const auto& instant : anAnalysisInterval.generateGrid(timeStep))
    {
        environment.setInstant(instant);

        const bool inEclipse = environment.isPositionInEclipse(aPosition, includePenumbra);

        if (inEclipse && (!eclipseStartInstant.isDefined()))
        {
            eclipseStartInstant = instant;
        }
        else if ((!inEclipse) && eclipseStartInstant.isDefined())
        {
            eclipseIntervals.add(Interval::Closed(eclipseStartInstant, eclipseEndInstant));

            eclipseStartInstant = Instant::Undefined();
            eclipseEndInstant = Instant::Undefined();
        }

        eclipseEndInstant = instant;
    }

    if (eclipseStartInstant.isDefined())
    {
        eclipseIntervals.add(Interval::Closed(eclipseStartInstant, eclipseEndInstant));
    }

    return eclipseIntervals;
}

}  // namespace utilities
}  // namespace environment
}  // namespace physics
}  // namespace ostk
