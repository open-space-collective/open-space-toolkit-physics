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

// EclipsePhase implementation
EclipsePhase::EclipsePhase(const Region& aRegion, const Interval& anInterval, const bool& anIsComplete)
    : region(aRegion),
      interval(anInterval),
      is_complete(anIsComplete)
{
}

String EclipsePhase::getRegionString() const
{
    switch (region)
    {
        case Region::UMBRA:
            return "Umbra";
        case Region::PENUMBRA:
            return "Penumbra";
        default:
            throw ostk::core::error::runtime::Undefined("Eclipse phase region");
    }
}

// Eclipse implementation
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
        throw ostk::core::error::runtime::Wrong("Eclipse has no phases.");
    }

    // Sort phases by start time
    std::sort(
        phases_.begin(),
        phases_.end(),
        [](const EclipsePhase& a, const EclipsePhase& b)
        {
            return a.interval.getStart() < b.interval.getStart();
        }
    );

    // Check if phases are contiguous
    for (Size i = 1; i < phases_.getSize(); ++i)
    {
        if (phases_[i].interval.getStart() != phases_[i - 1].interval.getEnd())
        {
            throw ostk::core::error::runtime::Wrong("Eclipse phases are not contiguous.");
        }
    }
}

const Celestial& Eclipse::getOccultedCelestialObject() const
{
    return occultedCelestialObject_;
}

const Celestial& Eclipse::getOccultingCelestialObject() const
{
    return occultingCelestialObject_;
}

const Array<EclipsePhase>& Eclipse::getPhases() const
{
    return phases_;
}

Duration Eclipse::getDuration(const bool& includePenumbras) const
{
    Array<Interval> intervalsToConsider = Array<Interval>::Empty();

    for (const auto& phase : phases_)
    {
        if (includePenumbras || phase.region == EclipsePhase::Region::UMBRA)
        {
            intervalsToConsider.add(phase.interval);
        }
    }

    if (intervalsToConsider.isEmpty())
    {
        return Duration::Zero();
    }

    Real totalSeconds = 0.0;
    for (const auto& interval : intervalsToConsider)
    {
        totalSeconds += interval.getDuration().inSeconds();
    }

    return Duration::Seconds(totalSeconds);
}

Interval Eclipse::getInterval(const bool& includePenumbras) const
{
    if (includePenumbras)
    {
        return Interval::Closed(phases_[0].interval.getStart(), phases_[phases_.getSize() - 1].interval.getEnd());
    }

    Array<Interval> umbras = Array<Interval>::Empty();
    for (const auto& phase : phases_)
    {
        if (phase.region == EclipsePhase::Region::UMBRA)
        {
            umbras.add(phase.interval);
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

    throw ostk::core::error::runtime::Wrong("Eclipse has multiple umbra phases.");
}

// Montenbruck-Gill shadow function implementation
Real montenbruckGillShadowFunction(
    const Instant& anInstant,
    const Position& aPosition,
    const Celestial& anOccultedCelestialObject,
    const Celestial& anOccultingCelestialObject
)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::object::Vector3d;

    using ostk::physics::coordinate::Frame;

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
        return std::asin(
            celestialObject.getEquatorialRadius().inMeters() / objectToCelestialObjectPositionCoordinates.norm()
        );
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
    const Interval& anAnalysisInterval, const Position& aPosition, const Environment& anEnvironment
)
{
    using ostk::mathematics::geometry::d3::object::Segment;

    using ostk::physics::environment::Object;
    using ostk::physics::time::Duration;
    using ostk::physics::time::Instant;

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

    const Duration timeStep = Duration::Minutes(1.0);  // [TBM] Param

    Array<Interval> eclipseIntervals = Array<Interval>::Empty();

    Instant eclipseStartInstant = Instant::Undefined();
    Instant eclipseEndInstant = Instant::Undefined();

    for (const auto& instant : anAnalysisInterval.generateGrid(timeStep))
    {
        environment.setInstant(instant);

        const bool inEclipse = environment.isPositionInEclipse(aPosition);

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
