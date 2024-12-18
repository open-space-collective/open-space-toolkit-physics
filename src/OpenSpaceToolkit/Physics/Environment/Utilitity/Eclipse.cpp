/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>

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

Array<Interval> eclipseIntervalsAtPosition(
    const Interval& anAnalysisInterval, const Position& aPosition, const Environment& anEnvironment
)
{
    using ostk::core::type::Shared;

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
