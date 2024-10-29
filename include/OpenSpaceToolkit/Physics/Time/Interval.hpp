/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Time_Interval__
#define __OpenSpaceToolkit_Physics_Time_Interval__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

using ostk::core::container::Array;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::physics::time::Instant;
using ostk::physics::time::Scale;

/// @brief                      Interval

class Interval : public mathematics::object::Interval<Instant>
{
   public:
    typedef mathematics::object::Interval<Instant>::Type Type;

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

    Interval getIntersectionWith(const Interval& anInterval) const;

    Interval getUnionWith(const Interval& anInterval) const;

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

    /// @brief              Constructs an open interval
    ///
    /// @code
    ///                     Interval interval = Interval::Open(Instant::J2000(), Instant::Now()) ; // (J2000, Now)
    /// @endcode
    ///
    /// @return             Open interval

    static Interval Open(const Instant& aLowerBound, const Instant& anUpperBound);

    /// @brief              Constructs an half-open left interval
    ///
    /// @code
    ///                     Interval interval = Interval::HalfOpenLeft(Instant::J2000(), Instant::Now()) ; // (J2000,
    ///                     Now]
    /// @endcode
    ///
    /// @return             Half-open left interval

    static Interval HalfOpenLeft(const Instant& aLowerBound, const Instant& anUpperBound);

    /// @brief              Constructs an half-open right interval
    ///
    /// @code
    ///                     Interval interval = Interval::HalfOpenRight(Instant::J2000(), Instant::Now()) ; // [J2000,
    ///                     Now)
    /// @endcode
    ///
    /// @return             Half-open right interval

    static Interval HalfOpenRight(const Instant& aLowerBound, const Instant& anUpperBound);

    static Interval Centered(
        const Instant& aCentralInstant, const Duration& aDuration, const Interval::Type& anIntervalType
    );

    static Array<Interval> Clip(const Array<Interval>& anIntervalArray, const Interval& anInterval);

    static Array<Interval> Sort(
        const Array<Interval>& anIntervalArray, const bool& byLowerBound = true, const bool& ascending = true
    );

    static Array<Interval> Merge(const Array<Interval>& anIntervalArray);

    static Array<Interval> GetGaps(
        const Array<Interval>& anIntervalArray, const Interval& anInterval = Interval::Undefined()
    );

    static Array<Interval> LogicalOr(
        const Array<Interval>& anIntervalArray, const Array<Interval>& anotherIntervalArray
    );

    static Array<Interval> LogicalAnd(
        const Array<Interval>& anIntervalArray, const Array<Interval>& anotherIntervalArray
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

   private:
    static mathematics::object::Interval<Instant> ToBase(const Interval& derived);
    static Interval FromBase(const mathematics::object::Interval<Instant>& base);
    static Array<mathematics::object::Interval<Instant>> ToBaseArray(const Array<Interval>& derivedArray);
    static Array<Interval> FromBaseArray(const Array<mathematics::object::Interval<Instant>>& baseArray);
};

}  // namespace time
}  // namespace physics
}  // namespace ostk

#endif
