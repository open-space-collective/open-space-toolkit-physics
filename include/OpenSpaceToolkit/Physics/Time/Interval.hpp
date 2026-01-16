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

    /// @brief              Check if the interval is defined.
    ///
    /// @return             True if defined.
    bool isDefined() const;

    /// @brief              Access the start instant.
    ///
    /// @return             Start instant.
    const Instant& accessStart() const;

    /// @brief              Access the end instant.
    ///
    /// @return             End instant.
    const Instant& accessEnd() const;

    /// @brief              Get the start instant.
    ///
    /// @return             Start instant.
    Instant getStart() const;

    /// @brief              Get the end instant.
    ///
    /// @return             End instant.
    Instant getEnd() const;

    /// @brief              Get the duration.
    ///
    /// @return             Duration.
    Duration getDuration() const;

    /// @brief              Get the center instant.
    ///
    /// @return             Center instant.
    Instant getCenter() const;

    /// @brief              Get the intersection with another interval.
    ///
    /// @param              [in] anInterval Another interval.
    /// @return             Intersection interval (Undefined if there is no intersection).
    Interval getIntersectionWith(const Interval& anInterval) const;

    /// @brief              Get the union with another interval.
    ///
    /// @param              [in] anInterval Another interval.
    /// @return             Union interval (Undefined if there is no single-interval union).
    Interval getUnionWith(const Interval& anInterval) const;

    /// @brief              Convert the interval to a string.
    ///
    /// @param              [in] aTimeScale Time scale.
    /// @return             String representation of the interval.
    String toString(const Scale& aTimeScale = Scale::UTC) const;

    /// @brief              Generate a grid of instants with a given time step.
    ///
    /// @param              [in] aTimeStep Time step.
    /// @return             Grid of instants.
    Array<Instant> generateGrid(const Duration& aTimeStep) const;

    /// @brief              Create an undefined interval.
    ///
    /// @return             Undefined interval.
    static Interval Undefined();

    /// @brief              Constructs a closed interval
    ///
    /// @code
    ///                     Interval interval = Interval::Closed(Instant::J2000(), Instant::Now()) ; // [J2000, Now]
    /// @endcode
    ///
    /// @param              [in] aLowerBound Start instant.
    /// @param              [in] anUpperBound End instant.
    /// @return             Closed interval.
    static Interval Closed(const Instant& aLowerBound, const Instant& anUpperBound);

    /// @brief              Constructs an open interval
    ///
    /// @code
    ///                     Interval interval = Interval::Open(Instant::J2000(), Instant::Now()) ; // (J2000, Now)
    /// @endcode
    ///
    /// @param              [in] aLowerBound Start instant.
    /// @param              [in] anUpperBound End instant.
    /// @return             Open interval.
    static Interval Open(const Instant& aLowerBound, const Instant& anUpperBound);

    /// @brief              Constructs an half-open left interval
    ///
    /// @code
    ///                     Interval interval = Interval::HalfOpenLeft(Instant::J2000(), Instant::Now()) ; // (J2000,
    ///                     Now]
    /// @endcode
    ///
    /// @param              [in] aLowerBound Start instant.
    /// @param              [in] anUpperBound End instant.
    /// @return             Half-open left interval.
    static Interval HalfOpenLeft(const Instant& aLowerBound, const Instant& anUpperBound);

    /// @brief              Constructs an half-open right interval
    ///
    /// @code
    ///                     Interval interval = Interval::HalfOpenRight(Instant::J2000(), Instant::Now()) ; // [J2000,
    ///                     Now)
    /// @endcode
    ///
    /// @param              [in] aLowerBound Start instant.
    /// @param              [in] anUpperBound End instant.
    /// @return             Half-open right interval.
    static Interval HalfOpenRight(const Instant& aLowerBound, const Instant& anUpperBound);

    /// @brief              Create a centered interval.
    ///
    /// @code
    ///                     Interval interval = Interval::Centered(Instant::J2000(), Duration::Seconds(1.0),
    ///                     Interval::Type::Closed) ; // [1999-12-31 23:59:59.500.000.000, 2000-01-01
    ///                     00:00:00.500.000.000]
    /// @endcode
    ///
    /// @param              [in] aCentralInstant Central instant.
    /// @param              [in] aDuration Duration.
    /// @param              [in] anIntervalType Interval type.
    /// @return             Centered interval.
    static Interval Centered(
        const Instant& aCentralInstant, const Duration& aDuration, const Interval::Type& anIntervalType
    );

    /// @brief              Creates a clipped list of intervals.
    ///
    /// @code
    ///                     Array<Interval> intervals = { Interval::Closed(Instant::2000(), Instant::2001()),
    ///                     Interval::Closed(Instant::2002(), Instant::2004()) } ;
    ///                     Interval interval = Interval::Closed(Instant::2001(), Instant::2003()) ;
    ///                     Array<Interval> clippedIntervals = Interval::Clip(intervals, interval) ; // { [2001,
    ///                     2001], [2002, 2003] }
    /// @endcode
    ///
    /// @param              [in] anIntervalArray A list of intervals.
    /// @param              [in] anInterval The clipping interval.
    /// @return             Clipped intervals.
    static Array<Interval> Clip(const Array<Interval>& anIntervalArray, const Interval& anInterval);

    /// @brief              Creates a sorted list of intervals.
    ///
    /// @param              [in] anIntervalArray A list of intervals.
    /// @param              [in] byLowerBound Use lower bound for sorting. Defaults to True.
    /// @param              [in] ascending Sort in ascending order. Defaults to True.
    /// @return             Sorted intervals.
    static Array<Interval> Sort(
        const Array<Interval>& anIntervalArray, const bool& byLowerBound = true, const bool& ascending = true
    );

    /// @brief              Creates a merged list of intervals.
    ///
    /// @code
    ///                     Array<Interval> intervals = { Interval::Closed(Instant::2000(), Instant::2002()),
    ///                     Interval::Closed(Instant::2001(), Instant::2003()) } ;
    ///                     Array<Interval> mergedIntervals = Interval::Merge(intervals) ; // { [2000, 2003] }
    /// @endcode
    ///
    /// @param              [in] anIntervalArray A list of intervals.
    /// @return             Merged intervals.
    static Array<Interval> Merge(const Array<Interval>& anIntervalArray);

    /// @brief              Creates a list of intervals gaps.
    ///
    /// @code
    ///                     Array<Interval> intervals = { Interval::Closed(Instant::2000(), Instant::2001()),
    ///                     Interval::Closed(Instant::2002(), Instant::2004()) } ;
    ///                     Interval interval = Interval::Closed(Instant::1999(), Instant::2005()) ;
    ///                     Array<Interval> gaps = Interval::GetGaps(intervals) ; // { [2001, 2002] }
    /// @endcode
    ///
    /// @param              [in] anIntervalArray A list of intervals.
    /// @param              [in] anInterval The analysis interval. Used to compute gaps for the first and last interval.
    /// Defaults to Undefined.
    /// @return             Intervals gaps.
    static Array<Interval> GetGaps(
        const Array<Interval>& anIntervalArray, const Interval& anInterval = Interval::Undefined()
    );

    /// @brief              Creates a list of intervals by a logical-or conjunction.
    ///
    /// @code
    ///                     Array<Interval> intervals = { Interval::Closed(Instant::2000(), Instant::2002()),
    ///                     Interval::Closed(Instant::2001(), Instant::2004()),  Interval::Closed(Instant::2006(),
    ///                     Instant::2007()) } ;
    ///                     Array<Interval> anotherIntervals = { Interval::Closed(Instant::2001(), Instant::2003()) } ;
    ///                     Array<Interval> logicalOrIntervals = Interval::LogicalOr(intervals, anotherIntervals) ; //
    ///                     { [2000, 2004], [2006, 2007] }
    /// @endcode
    ///
    /// @param              [in] anIntervalArray A list of intervals.
    /// @param              [in] anotherIntervalArray Another list of intervals.
    /// @return             Logical-or intervals.
    static Array<Interval> LogicalOr(
        const Array<Interval>& anIntervalArray, const Array<Interval>& anotherIntervalArray
    );

    /// @brief              Creates a list of intervals by a logical-and conjunction.
    ///
    /// @code
    ///                     Array<Interval> intervals = { Interval::Closed(Instant::2000(), Instant::2002()),
    ///                     Interval::Closed(Instant::2001(), Instant::2004()),  Interval::Closed(Instant::2006(),
    ///                     Instant::2007()) } ;
    ///                     Array<Interval> anotherIntervals = { Interval::Closed(Instant::2001(), Instant::2003()) } ;
    ///                     Array<Interval> logicalAndIntervals = Interval::LogicalAnd(intervals, anotherIntervals) ; //
    ///                     { [2001, 2002], [2001, 2003] }
    /// @endcode
    ///
    /// @param              [in] anIntervalArray A list of intervals.
    /// @param              [in] anotherIntervalArray Another list of intervals.
    /// @return             Logical-and intervals.
    static Array<Interval> LogicalAnd(
        const Array<Interval>& anIntervalArray, const Array<Interval>& anotherIntervalArray
    );

    ///
    /// @brief              Parse an interval from a string representation.
    ///
    /// @code
    ///                     Interval interval = Interval::Parse("[2000-01-01 12:00:00 - 2000-01-01 12:00:01] [UTC]") ;
    ///                     Interval halfOpenRightInterval = Interval::Parse("[2000-01-01 12:00:00 - 2000-01-01
    ///                     12:00:01[ [UTC]") ;
    /// @endcode
    ///
    /// @param              [in] aString String representation.
    /// @return             Interval.
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
