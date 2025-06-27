/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Utility_Eclipse__
#define __OpenSpaceToolkit_Physics_Environment_Utility_Eclipse__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <OpenSpaceToolkit/Physics/Coordinate/Position.hpp>
#include <OpenSpaceToolkit/Physics/Environment.hpp>
#include <OpenSpaceToolkit/Physics/Environment/Object/Celestial.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
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
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;

using ostk::physics::coordinate::Position;
using ostk::physics::Environment;
using ostk::physics::environment::object::Celestial;
using ostk::physics::time::Duration;
using ostk::physics::time::Instant;
using ostk::physics::time::Interval;

/// @brief                      Phase of an eclipse
class EclipsePhase
{
   public:
    /// @brief                  Type of an eclipse phase
    enum class Region
    {
        UMBRA,    ///< Umbra region
        PENUMBRA  ///< Penumbra region
    };

    Region region;      ///< The region of the eclipse phase
    Interval interval;  ///< The time interval of the phase
    bool is_complete;   ///< Whether the phase is complete

    /// @brief                  Constructor
    ///
    /// @param                  [in] aRegion The region of the eclipse phase
    /// @param                  [in] anInterval The time interval of the phase
    /// @param                  [in] anIsComplete Whether the phase is complete
    EclipsePhase(const Region& aRegion, const Interval& anInterval, const bool& anIsComplete);

    /// @brief                  Get the region as string
    ///
    /// @return                 String representation of the region
    String getRegionString() const;
};

/// @brief                      Eclipse
class Eclipse
{
   public:
    /// @brief                  Constructor
    ///
    /// @param                  [in] anOccultedCelestialObject The occulted celestial object
    /// @param                  [in] anOccultingCelestialObject The occulting celestial object
    /// @param                  [in] somePhases The phases of the eclipse
    ///
    /// @throw                  std::runtime_error If the phases are not contiguous
    Eclipse(
        const Celestial& anOccultedCelestialObject,
        const Celestial& anOccultingCelestialObject,
        const Array<EclipsePhase>& somePhases
    );

    /// @brief                  Get the occulted celestial object
    ///
    /// @return                 The occulted celestial object
    const Celestial& getOccultedCelestialObject() const;

    /// @brief                  Get the occulting celestial object
    ///
    /// @return                 The occulting celestial object
    const Celestial& getOccultingCelestialObject() const;

    /// @brief                  Get the phases of the eclipse
    ///
    /// @return                 The phases of the eclipse
    const Array<EclipsePhase>& getPhases() const;

    /// @brief                  Get the duration of the eclipse
    ///
    /// @param                  [in] includePenumbras Whether to include the penumbra phases. Defaults to true
    /// @return                 The duration of the eclipse
    Duration getDuration(const bool& includePenumbras = true) const;

    /// @brief                  Get the interval of the eclipse
    ///
    /// @param                  [in] includePenumbras Whether to include the penumbra phases. Defaults to true
    /// @return                 The interval of the eclipse. Returns Interval::Undefined() if there are no umbra phases
    ///                         and penumbras are not included
    ///
    /// @throw                  std::runtime_error If there are multiple umbra phases and penumbras are not included
    Interval getInterval(const bool& includePenumbras = true) const;

   private:
    Celestial occultedCelestialObject_;   ///< The occulted celestial object
    Celestial occultingCelestialObject_;  ///< The occulting celestial object
    Array<EclipsePhase> phases_;          ///< The phases of the eclipse
};

/// @brief                      Calculate eclipse intervals for a given position
///
/// @param                      [in] anAnalysisInterval An analysis interval
/// @param                      [in] aPosition A position
/// @param                      [in] anEnvironment An environment
/// @param                      [in] includePenumbra Whether to include penumbra phases. Defaults to true
/// @param                      [in] timeStep The time step for analysis, the lower the more accuraty the result will
/// be. Defaults to one minute
/// @return                     Array of eclipse intervals for a given position

Array<Interval> eclipseIntervalsAtPosition(
    const Interval& anAnalysisInterval,
    const Position& aPosition,
    const Environment& anEnvironment,
    const bool& includePenumbra = true,
    const Duration& timeStep = Duration::Minutes(1.0)
);

/// @brief                      Montenbruck-Gill shadow function
///
/// Reference: Montenbruck and Gill, Satellite Orbits: Models, Methods, and Applications, 4th edition, Springer.
///
/// @param                      [in] anInstant The instant at which the shadow function is evaluated
/// @param                      [in] aPosition The position for which the shadow function is evaluated
/// @param                      [in] anOccultedCelestialObject The occulted celestial object
/// @param                      [in] anOccultingCelestialObject The occulting celestial object
/// @return                     The value of the shadow function (0.0 for umbra, 1.0 for fully illuminated, and between
/// 0.0 and 1.0 for penumbra)

Real montenbruckGillShadowFunction(
    const Instant& anInstant,
    const Position& aPosition,
    const Celestial& anOccultedCelestialObject,
    const Celestial& anOccultingCelestialObject
);

}  // namespace utilities
}  // namespace environment
}  // namespace physics
}  // namespace ostk

#endif
