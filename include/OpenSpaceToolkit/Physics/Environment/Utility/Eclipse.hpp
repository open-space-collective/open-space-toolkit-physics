/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Utility_Eclipse__
#define __OpenSpaceToolkit_Physics_Environment_Utility_Eclipse__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Time/Interval.hpp>

namespace ostk
{
namespace physics
{
namespace environment
{
namespace utilities
{

using ostk::core::container::Array;

using ostk::physics::coordinate::Position;
using ostk::physics::Environment;
using ostk::physics::time::Interval;

/// @brief                      Calculate eclipse intervals for a given position
///
/// @param                      [in] anAnalysisInterval An analysis interval
/// @param                      [in] aPosition A position
/// @param                      [in] anEnvironment An environment
/// @return                     Array of eclipse intervals for a given position

Array<Interval> eclipseIntervalsAtPosition(
    const Interval& anAnalysisInterval, const Position& aPosition, const Environment& anEnvironment
);

}  // namespace utilities
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
