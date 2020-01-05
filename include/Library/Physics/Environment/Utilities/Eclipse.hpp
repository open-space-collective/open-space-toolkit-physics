////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Utilities/Eclipse.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Environment_Utilities_Eclipse__
#define __OpenSpaceToolkit_Physics_Environment_Utilities_Eclipse__

#include <Library/Physics/Environment.hpp>
#include <Library/Physics/Coordinate/Position.hpp>
#include <Library/Physics/Time/Interval.hpp>

#include <Library/Core/Containers/Array.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace env
{
namespace utilities
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::ctnr::Array ;

using ostk::physics::coord::Position ;
using ostk::physics::time::Interval ;
using ostk::physics::Environment ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Is position in eclipse
///
/// @param                      [in] aPosition A position (in GCRF)
/// @param                      [in] anEnvironment An environment
/// @return                     True if position is in eclipse

bool                            isPositionInEclipse                         (   const   Position&                   aPosition,
                                                                                const   Environment&                anEnvironment                               ) ;

/// @brief                      Calculate eclipse intervals for a given position
///
/// @param                      [in] anAnalysisInterval An analysis interval
/// @param                      [in] aPosition A position
/// @param                      [in] anEnvironment An environment
/// @return                     Array of eclipse intervals for a given position

Array<Interval>                 eclipseIntervalsAtPosition                  (   const   Interval&                   anAnalysisInterval,
                                                                                const   Position&                   aPosition,
                                                                                const   Environment&                anEnvironment                               ) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
