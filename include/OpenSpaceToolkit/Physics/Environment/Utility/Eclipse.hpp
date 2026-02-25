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

/// @brief Phase of an eclipse
class EclipsePhase
{
   public:
    /// @brief Type of an eclipse phase
    enum class Region
    {
        Umbra,    ///< Umbra region
        Penumbra  ///< Penumbra region
    };

    /// @brief Constructor
    ///
    /// @code
    ///     EclipsePhase phase = EclipsePhase(EclipsePhase::Region::Umbra, anInterval, true) ;
    /// @endcode
    ///
    /// @param [in] aRegion The region of the eclipse phase
    /// @param [in] anInterval The time interval of the phase
    /// @param [in] anIsComplete Whether the phase is complete
    EclipsePhase(const Region& aRegion, const Interval& anInterval, const bool& anIsComplete);

    /// @brief Get the region of the eclipse phase
    ///
    /// @code
    ///     EclipsePhase::Region region = phase.getRegion() ;
    /// @endcode
    ///
    /// @return The region of the eclipse phase
    Region getRegion() const;

    /// @brief Get the time interval of the eclipse phase
    ///
    /// @code
    ///     const Interval& interval = phase.getInterval() ;
    /// @endcode
    ///
    /// @return The time interval of the eclipse phase
    const Interval& getInterval() const;

    /// @brief Check if the eclipse phase is complete
    ///
    /// @code
    ///     phase.isComplete() ; // True
    /// @endcode
    ///
    /// @return True if the phase is complete, false otherwise
    bool isComplete() const;

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anEclipsePhase An eclipse phase
    /// @return The output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const EclipsePhase& anEclipsePhase);

    /// @brief Equality operator
    ///
    /// @code
    ///     phaseA == phaseB ;
    /// @endcode
    ///
    /// @param [in] anEclipsePhase The other EclipsePhase to compare with
    /// @return True if the phases are equal, false otherwise
    bool operator==(const EclipsePhase& anEclipsePhase) const;

    /// @brief Inequality operator
    ///
    /// @code
    ///     phaseA != phaseB ;
    /// @endcode
    ///
    /// @param [in] anEclipsePhase The other EclipsePhase to compare with
    /// @return True if the phases are not equal, false otherwise
    bool operator!=(const EclipsePhase& anEclipsePhase) const;

   private:
    Region region_;      ///< The region of the eclipse phase
    Interval interval_;  ///< The time interval of the phase
    bool isComplete_;    ///< Whether the phase is complete
};

/// @brief Eclipse
class Eclipse
{
   public:
    /// @brief Constructor
    ///
    /// @code
    ///     Eclipse eclipse = Eclipse(sun, earth, phases) ;
    /// @endcode
    ///
    /// @param [in] anOccultedCelestialObject The occulted celestial object
    /// @param [in] anOccultingCelestialObject The occulting celestial object
    /// @param [in] somePhases The phases of the eclipse
    ///
    /// @throw ostk::core::error::RuntimeError If the phases are not contiguous
    Eclipse(
        const Celestial& anOccultedCelestialObject,
        const Celestial& anOccultingCelestialObject,
        const Array<EclipsePhase>& somePhases
    );

    /// @brief Access the occulted celestial object
    ///
    /// @code
    ///     const Celestial& occulted = eclipse.accessOccultedCelestialObject() ;
    /// @endcode
    ///
    /// @return The occulted celestial object
    const Celestial& accessOccultedCelestialObject() const;

    /// @brief Access the occulting celestial object
    ///
    /// @code
    ///     const Celestial& occulting = eclipse.accessOccultingCelestialObject() ;
    /// @endcode
    ///
    /// @return The occulting celestial object
    const Celestial& accessOccultingCelestialObject() const;

    /// @brief Get the phases of the eclipse
    ///
    /// @code
    ///     const Array<EclipsePhase>& phases = eclipse.getPhases() ;
    /// @endcode
    ///
    /// @return The phases of the eclipse
    const Array<EclipsePhase>& getPhases() const;

    /// @brief Get the duration of the eclipse
    ///
    /// @code
    ///     Duration duration = eclipse.getDuration() ;
    /// @endcode
    ///
    /// @param [in] includePenumbra Whether to include the penumbra phases. Defaults to true
    /// @return The duration of the eclipse
    Duration getDuration(const bool& includePenumbra = true) const;

    /// @brief Get the interval of the eclipse
    ///
    /// @code
    ///     Interval interval = eclipse.getInterval() ;
    /// @endcode
    ///
    /// @param [in] includePenumbra Whether to include the penumbra phases. Defaults to true
    /// @return The interval of the eclipse. Returns Interval::Undefined() if there are no umbra phases
    /// and penumbras are not included
    ///
    /// @throw ostk::core::error::RuntimeError If there are multiple umbra phases and penumbras are not included
    Interval getInterval(const bool& includePenumbra = true) const;

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anEclipse An eclipse
    /// @return The output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Eclipse& anEclipse);

   private:
    Celestial occultedCelestialObject_;   ///< The occulted celestial object
    Celestial occultingCelestialObject_;  ///< The occulting celestial object
    Array<EclipsePhase> phases_;          ///< The phases of the eclipse
};

/// @brief Calculate eclipse intervals for a given position
///
/// @code
///     Array<Interval> intervals = eclipseIntervalsAtPosition(anInterval, aPosition, anEnvironment) ;
/// @endcode
///
/// @param [in] anAnalysisInterval An analysis interval
/// @param [in] aPosition A position
/// @param [in] anEnvironment An environment
/// @param [in] includePenumbra Whether to include penumbra phases. Defaults to true
/// @param [in] timeStep The time step for analysis, the lower the more accuraty the result will
/// be. Defaults to one minute
/// @return Array of eclipse intervals for a given position

Array<Interval> eclipseIntervalsAtPosition(
    const Interval& anAnalysisInterval,
    const Position& aPosition,
    const Environment& anEnvironment,
    const bool& includePenumbra = true,
    const Duration& timeStep = Duration::Minutes(1.0)
);

/// @brief Montenbruck-Gill shadow function
///
/// Reference: Montenbruck and Gill, Satellite Orbits: Models, Methods, and Applications, 4th edition, Springer.
///
/// @code
///     Real shadowValue = montenbruckGillShadowFunction(anInstant, aPosition, sun, earth) ;
/// @endcode
///
/// @param [in] anInstant The instant at which the shadow function is evaluated
/// @param [in] aPosition The position for which the shadow function is evaluated
/// @param [in] anOccultedCelestialObject The occulted celestial object
/// @param [in] anOccultingCelestialObject The occulting celestial object
/// @return The value of the shadow function (0.0 for umbra, 1.0 for fully illuminated, and between
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
