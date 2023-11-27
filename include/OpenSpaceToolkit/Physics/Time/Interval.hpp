/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Time_Interval__
#define __OpenSpaceToolkit_Physics_Time_Interval__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

using ostk::core::types::Real;
using ostk::core::types::String;
using ostk::core::ctnr::Array;

using ostk::physics::time::Scale;
using ostk::physics::time::Instant;

/// @brief                      Interval

class Interval : public math::object::Interval<Instant>
{
   public:
    typedef math::object::Interval<Instant>::Type Type;

    /// @brief              Constructor
    ///
    /// @code
    ///                     Interval interval(Instant::J2000(), Instant::Now(), Interval::Type::Closed) ;
    /// @endcode
    ///
    /// @param              [in] aLowerBound A lower bound
    /// @param              [in] anUpperBound An upper bound
    /// @param              [in] anIntervalType An interval type

    Interval(const Instant& aLowerBound, const Instant& anUpperBound, const Interval::Type& anIntervalType);

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Interval& anInterval);

    bool isDefined() const;

    const Instant& accessStart() const;

    const Instant& accessEnd() const;

    Instant getStart() const;

    Instant getEnd() const;

    Duration getDuration() const;

    Instant getCenter() const;

    String toString(const Scale& aTimeScale = Scale::UTC) const;

    Array<Instant> generateGrid(const Duration& aTimeStep) const;

    static Interval Undefined();

    /// @brief              Constructs a closed interval
    ///
    /// @code
    ///                     Interval interval = Interval::Closed(Instant::J2000(), Instant::Now()) ; // [J2000, Now]
    /// @endcode
    ///
    /// @return             Closed interval

    static Interval Closed(const Instant& aLowerBound, const Instant& anUpperBound);

    static Interval Centered(
        const Instant& aCentralInstant, const Duration& aDuration, const Interval::Type& anIntervalType
    );

    /// @brief              Constructs an interval from a string representation
    ///
    /// @code
    ///                     ...
    /// @endcode
    ///
    /// @param              [in] aString A string
    /// @return             Interval

    static Interval Parse(const String& aString);
};

}  // namespace time
}  // namespace physics
}  // namespace ostk

#endif
