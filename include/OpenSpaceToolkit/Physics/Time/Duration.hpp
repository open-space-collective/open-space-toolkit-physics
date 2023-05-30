/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Time_Duration__
#define __OpenSpaceToolkit_Physics_Time_Duration__

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Physics/Units/Time.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

using ostk::core::types::Int64;
using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;

class Instant;

/// @brief                      Amount of time

class Duration
{
   public:
    friend Instant;

    /// @brief              Duration format

    enum class Format
    {

        Undefined,  ///< Undefined format
        Standard,   ///< Standard format (d hh:mm:ss.mmm.uuu.nnn)
        ISO8601     ///< ISO 8601 format (PnDTnHnMnS)

    };

    /// @brief              Constructor
    ///
    /// @code
    ///                     Duration duration(123) ; // 123 [ns]
    /// @endcode
    /// @param              [in] aNanosecondCount A nanosecond count

    Duration(Int64 aNanosecondCount);

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Duration(123) == Duration(123) ; // True
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             True if durations are equal

    bool operator==(const Duration& aDuration) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Duration(123) != Duration(456) ; // True
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             True if durations are not equal

    bool operator!=(const Duration& aDuration) const;

    /// @brief              Less than operator
    ///
    /// @code
    ///                     Duration(123) < Duration(456) ; // True
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             True if lhs duration is less than rhs duration

    bool operator<(const Duration& aDuration) const;

    /// @brief              Less than or equal to operator
    ///
    /// @code
    ///                     Duration(123) <= Duration(456) ; // True
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             True if lhs duration is less than or equal to rhs duration

    bool operator<=(const Duration& aDuration) const;

    /// @brief              Greater than operator
    ///
    /// @code
    ///                     Duration(456) > Duration(123) ; // True
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             True if lhs duration is greater than rhs duration

    bool operator>(const Duration& aDuration) const;

    /// @brief              Greater than operator
    ///
    /// @code
    ///                     Duration(456) >= Duration(123) ; // True
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             True if lhs duration is greater than or equal to rhs duration

    bool operator>=(const Duration& aDuration) const;

    /// @brief              Addition operator
    ///
    /// @code
    ///                     Duration::Seconds(1.0) + Duration::Seconds(1.0) ; // 2.0 [s]
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Duration

    Duration operator+(const Duration& aDuration) const;

    /// @brief              Subtraction operator
    ///
    /// @code
    ///                     Duration::Seconds(1.0) - Duration::Seconds(1.0) ; // 0.0 [s]
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Duration

    Duration operator-(const Duration& aDuration) const;

    /// @brief              Multiplication operator
    ///
    /// @code
    ///                     Duration::Seconds(1.0) * 2.0 ; // 2.0 [s]
    /// @endcode
    ///
    /// @param              [in] aMultiplier A multiplier
    /// @return             Duration

    Duration operator*(const Real& aMultiplier) const;

    /// @brief              Division operator
    ///
    /// @code
    ///                     Duration::Seconds(1.0) / 2.0 ; // 0.5 [s]
    /// @endcode
    ///
    /// @param              [in] aDivider A divider
    /// @return             Duration

    Duration operator/(const Real& aDivider) const;

    /// @brief              Unary plus operator
    ///
    /// @code
    ///                     Duration duration = +Duration::Seconds(1.0) ; // +1.0 [s]
    /// @endcode
    ///
    /// @return             Duration

    Duration operator+() const;

    /// @brief              Unary minus operator
    ///
    /// @code
    ///                     Duration duration = -Duration::Seconds(1.0) ; // -1.0 [s]
    /// @endcode
    ///
    /// @return             Duration

    Duration operator-() const;

    /// @brief              Addition assignement operator
    ///
    /// @code
    ///                     Duration duration = Duration::Seconds(1.0) ;
    ///                     duration += Duration::Seconds(1.0) ; // 2.0 [s]
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Reference to duration

    Duration& operator+=(const Duration& aDuration);

    /// @brief              Subtraction assignement operator
    ///
    /// @code
    ///                     Duration duration = Duration::Seconds(1.0) ;
    ///                     duration -= Duration::Seconds(1.0) ; // 0.0 [s]
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Reference to duration

    Duration& operator-=(const Duration& aDuration);

    /// @brief              Multiplication assignement operator
    ///
    /// @code
    ///                     Duration duration = Duration::Seconds(1.0) ;
    ///                     duration *= 2.0 ; // 2.0 [s]
    /// @endcode
    ///
    /// @param              [in] aMultiplier A multiplier
    /// @return             Reference to duration

    Duration& operator*=(const Real& aMultiplier);

    /// @brief              Division assignement operator
    ///
    /// @code
    ///                     Duration duration = Duration::Seconds(1.0) ;
    ///                     duration /= 2.0 ; // 0.5 [s]
    /// @endcode
    ///
    /// @param              [in] aDivider A divider
    /// @return             Reference to duration

    Duration& operator/=(const Real& aDivider);

    /// @brief              Multiplication operator
    ///
    /// @code
    ///                     2.0 * Duration::Seconds(1.0) ; // 2.0 [s]
    /// @endcode
    ///
    /// @param              [in] aMultiplier A multiplier
    /// @param              [in] aDuration A duration
    /// @return             Duration

    friend Duration operator*(double aMultiplier, const Duration& aDuration);

    /// @brief              Output stream operator
    ///
    /// @code
    ///                     std::cout << Duration(123) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] aDuration A duration
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Duration& aDuration);

    /// @brief              Check if duration is defined
    ///
    /// @code
    ///                     Duration(123).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if duration is defined

    bool isDefined() const;

    /// @brief              Check if duration is zero
    ///
    /// @code
    ///                     Duration(0).isZero() ; // True
    /// @endcode
    ///
    /// @return             True if duration is zero

    bool isZero() const;

    /// @brief              Check if duration is positive
    ///
    /// @code
    ///                     Duration(+1).isPositive() ; // True
    ///                     Duration(-1).isPositive() ; // False
    ///                     Duration(0).isPositive() ; // True
    /// @endcode
    ///
    /// @return             True if duration is positive

    bool isPositive() const;

    /// @brief              Check if duration is strictly positive
    ///
    /// @code
    ///                     Duration(+1).isStrictlyPositive() ; // True
    ///                     Duration(-1).isStrictlyPositive() ; // False
    ///                     Duration(0).isStrictlyPositive() ; // False
    /// @endcode
    ///
    /// @return             True if duration is strictly positive

    bool isStrictlyPositive() const;

    /// @brief              Check if duration is near another duration
    ///
    /// @code
    ///                     Duration::Seconds(2.0).isNear(Duration::Seconds(1.0), Duration::Seconds(1.0)) ; // True
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @param              [in] aTolerance A tolerance
    /// @return             True if instant is near another instant

    bool isNear(const Duration& aDuration, const Duration& aTolerance) const;

    /// @brief              Get the number of nanoseconds in duration
    ///
    /// @code
    ///                     Duration::Seconds(15).nanoseconds() ; // 0
    /// @endcode
    ///
    /// @return             Number of nanoseconds in duration

    Integer getNanoseconds() const;

    /// @brief              Get the number of microseconds in duration
    ///
    /// @code
    ///                     Duration::Seconds(15).microseconds() ; // 0
    /// @endcode
    ///
    /// @return             Number of microseconds in duration

    Integer getMicroseconds() const;

    /// @brief              Get the number of milliseconds in duration
    ///
    /// @code
    ///                     Duration::Seconds(15).milliseconds() ; // 0
    /// @endcode
    ///
    /// @return             Number of milliseconds in duration

    Integer getMilliseconds() const;

    /// @brief              Get the number of seconds in duration
    ///
    /// @code
    ///                     Duration::Seconds(15).seconds() ; // 15
    /// @endcode
    ///
    /// @return             Number of seconds in duration

    Integer getSeconds() const;

    /// @brief              Get the number of minutes in duration
    ///
    /// @code
    ///                     Duration::Seconds(15).minutes() ; // 0
    /// @endcode
    ///
    /// @return             Number of minutes in duration

    Integer getMinutes() const;

    /// @brief              Get the number of hours in duration
    ///
    /// @code
    ///                     Duration::Seconds(15).hours() ; // 0
    /// @endcode
    ///
    /// @return             Number of hours in duration

    Integer getHours() const;

    /// @brief              Get the number of days in duration
    ///
    /// @code
    ///                     Duration::Days(15).days() ; // 15
    /// @endcode
    ///
    /// @return             Number of days in duration

    Integer getDays() const;

    /// @brief              Get the number of weeks in duration
    ///
    /// @code
    ///                     Duration::Days(15).weeks() ; // 2
    /// @endcode
    ///
    /// @return             Number of weeks in duration

    Integer getWeeks() const;

    /// @brief              Get nanosecond count
    ///
    /// @code
    ///                     Duration::Nanoseconds(123).inNanoseconds() ; // 123.0
    /// @endcode
    ///
    /// @return             Nanosecond count

    Real inNanoseconds() const;

    /// @brief              Get microsecond count
    ///
    /// @code
    ///                     Duration::Microseconds(123).inMicroseconds() ; // 123.0
    /// @endcode
    ///
    /// @return             Microsecond count

    Real inMicroseconds() const;

    /// @brief              Get millisecond count
    ///
    /// @code
    ///                     Duration::Milliseconds(123).inMilliseconds() ; // 123.0
    /// @endcode
    ///
    /// @return             Millisecond count

    Real inMilliseconds() const;

    /// @brief              Get second count
    ///
    /// @code
    ///                     Duration::Seconds(123).inSeconds() ; // 123.0
    /// @endcode
    ///
    /// @return             Second count

    Real inSeconds() const;

    /// @brief              Get minute count
    ///
    /// @code
    ///                     Duration::Minutes(123).inMinutes() ; // 123.0
    /// @endcode
    ///
    /// @return             Minute count

    Real inMinutes() const;

    /// @brief              Get hour count
    ///
    /// @code
    ///                     Duration::Hours(123).inHours() ; // 123.0
    /// @endcode
    ///
    /// @return             Hour count

    Real inHours() const;

    /// @brief              Get day count
    ///
    /// @code
    ///                     Duration::Days(123).inDays() ; // 123.0
    /// @endcode
    ///
    /// @return             Day count

    Real inDays() const;

    /// @brief              Get week count
    ///
    /// @code
    ///                     Duration::Weeks(123).inWeeks() ; // 123.0
    /// @endcode
    ///
    /// @return             Week count

    Real inWeeks() const;

    /// @brief              Get count in given time unit
    ///
    /// @code
    ///                     Duration::Weeks(123).in(Time::Unit::Week) ; // 123.0
    /// @endcode
    ///
    /// @param              [in] aTimeUnit A time unit
    /// @return             Count in given time unit

    Real in(const units::Time::Unit& aTimeUnit) const;

    /// @brief              Get absolute duration
    ///
    /// @code
    ///                     Duration::Seconds(-123.456).getAbsolute() ; // +123.456 [s]
    /// @endcode
    ///
    /// @return             Absolute duration

    Duration getAbsolute() const;

    /// @brief              Get string representation of duration
    ///
    /// @code
    ///                     Duration::Seconds(123.456).toString(Duration::Format::Standard) ; // 02:03.456
    ///                     Duration::Seconds(123.456).toString(Duration::Format::ISO8601) ; // PT2M3.456S
    /// @endcode
    ///
    /// @param              [in] aFormat A representation format
    /// @return             Serialized duration

    String toString(const Duration::Format& aFormat = Duration::Format::Standard) const;

    /// @brief              Constructs an undefined duration
    ///
    /// @code
    ///                     Duration duration = Duration::Undefined() ;
    ///                     duration.isDefined() ; // False
    /// @endcode
    ///
    /// @return             Undefined duration

    static Duration Undefined();

    /// @brief              Constructs a zero duration
    ///
    /// @code
    ///                     Duration duration = Duration::Zero() ;
    ///                     duration.isZero() ; // True
    /// @endcode
    ///
    /// @return             Zero duration

    static Duration Zero();

    /// @brief              Constructs a duration from a nanosecond count
    ///
    /// @code
    ///                     Duration duration = Duration::Nanoseconds(123) ;
    /// @endcode
    ///
    /// @param              [in] aNanosecondCount A nanosecond count
    /// @return             Duration

    static Duration Nanoseconds(const Real& aNanosecondCount);

    /// @brief              Constructs a duration from a microsecond count
    ///
    /// @code
    ///                     Duration duration = Duration::Microseconds(123) ;
    /// @endcode
    ///
    /// @param              [in] aMicrosecondCount A microsecond count
    /// @return             Duration

    static Duration Microseconds(const Real& aMicrosecondCount);

    /// @brief              Constructs a duration from a millisecond count
    ///
    /// @code
    ///                     Duration duration = Duration::Milliseconds(123) ;
    /// @endcode
    ///
    /// @param              [in] aMillisecondCount A millisecond count
    /// @return             Duration

    static Duration Milliseconds(const Real& aMillisecondCount);

    /// @brief              Constructs a duration from a second count
    ///
    /// @code
    ///                     Duration duration = Duration::Seconds(123) ;
    /// @endcode
    ///
    /// @param              [in] aSecondCount A second count
    /// @return             Duration

    static Duration Seconds(const Real& aSecondCount);

    /// @brief              Constructs a duration from a minute count
    ///
    /// @code
    ///                     Duration duration = Duration::Minutes(123) ;
    /// @endcode
    ///
    /// @param              [in] aMinuteCount A minute count
    /// @return             Duration

    static Duration Minutes(const Real& aMinuteCount);

    /// @brief              Constructs a duration from a hour count
    ///
    /// @code
    ///                     Duration duration = Duration::Hours(123) ;
    /// @endcode
    ///
    /// @param              [in] anHourCount A hour count
    /// @return             Duration

    static Duration Hours(const Real& anHourCount);

    /// @brief              Constructs a duration from a day count
    ///
    /// @code
    ///                     Duration duration = Duration::Days(123) ;
    /// @endcode
    ///
    /// @param              [in] aDayCount A day count
    /// @return             Duration

    static Duration Days(const Real& aDayCount);

    /// @brief              Constructs a duration from a week count
    ///
    /// @code
    ///                     Duration duration = Duration::Weeks(123) ;
    /// @endcode
    ///
    /// @param              [in] aWeekCount A week count
    /// @return             Duration

    static Duration Weeks(const Real& aWeekCount);

    /// @brief              Constructs a duration between two instants
    ///
    ///                     Duration is positive is firstInstant < secondInstant.
    ///
    /// @code
    ///                     Duration duration = Duration::Between(firstInstant, secondInstant) ;
    /// @endcode
    ///
    /// @param              [in] aFirstInstant A first instant
    /// @param              [in] aSecondInstant A second instant
    /// @return             Duration

    static Duration Between(const Instant& aFirstInstant, const Instant& aSecondInstant);

    /// @brief              Constructs a duration from a string representation
    ///
    /// @code
    ///                     Duration duration = Duration::Parse("12:34:56.123.456.789") ;
    ///                     Duration duration = Duration::Parse("12:34:56.123.456.789", Duration::Format::Standard) ;
    ///                     Duration duration = Duration::Parse("12:34:56.123456789", Duration::Format::ISO8601) ;
    /// @endcode
    ///
    /// @param              [in] aString A string
    /// @param              [in] (optional) aFormat A duration format (automatic detection if Undefined)
    /// @return             Duration

    static Duration Parse(const String& aString, const Duration::Format& aFormat = Duration::Format::Undefined);

   private:
    bool defined_;
    Int64 count_;

    Duration();
};

}  // namespace time
}  // namespace physics
}  // namespace ostk

#endif
