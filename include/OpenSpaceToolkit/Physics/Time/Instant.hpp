/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Time_Instant__
#define __OpenSpaceToolkit_Physics_Time_Instant__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Time/DateTime.hpp>
#include <OpenSpaceToolkit/Physics/Time/Duration.hpp>
#include <OpenSpaceToolkit/Physics/Time/Scale.hpp>
#include <OpenSpaceToolkit/Physics/Units/Time.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

using ostk::core::type::Int64;
using ostk::core::type::Uint64;
using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::physics::time::Scale;
using ostk::physics::time::Duration;

#define DEFAULT_TIME_SCALE Scale::UTC
#define DEFAULT_DATE_TIME_FORMAT DateTime::Format::Standard

/// @brief                      Point in time
///
/// @ref                        https://en.wikipedia.org/wiki/Instant
/// @ref https://www.boost.org/doc/libs/1_67_0/doc/html/date_time/details.html#date_time.calculations
/// @ref                        http://rhodesmill.org/skyfield/time.html
/// @ref                        http://www.madore.org/~david/computers/unix-leap-seconds.html
/// @ref                        http://help.agi.com/AGIComponentsJava/html/TimeAndTimeStandards.htm

class Instant
{
   public:
    /// @brief              Default constructor (deleted)

    Instant() = delete;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) ==
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) ; // True
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @return             True if instants are equal

    bool operator==(const Instant& anInstant) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) !=
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) ; // True
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @return             True if instants are not equal

    bool operator!=(const Instant& anInstant) const;

    /// @brief              Less than operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) <
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) ; // True
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @return             True if lhs duration is less than rhs duration

    bool operator<(const Instant& anInstant) const;

    /// @brief              Less than or equal to operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) <=
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) ; // True
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @return             True if lhs duration is less than or equal to rhs duration

    bool operator<=(const Instant& anInstant) const;

    /// @brief              Greater than operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) >
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) ; // True
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @return             True if lhs duration is greater than rhs duration

    bool operator>(const Instant& anInstant) const;

    /// @brief              Greater than operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) >=
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) ; // True
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @return             True if lhs duration is greater than or equal to rhs duration

    bool operator>=(const Instant& anInstant) const;

    /// @brief              Addition operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) + Duration::Days(1.0) ; //
    ///                     2018-01-02 00:00:00
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Instant

    Instant operator+(const Duration& aDuration) const;

    /// @brief              Subtraction operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) - Duration::Days(1.0) ; //
    ///                     2018-01-01 00:00:00
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Instant

    Instant operator-(const Duration& aDuration) const;

    /// @brief              Subtraction operator
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) -
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) ; // 1.0 [day]
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @return             Duration

    Duration operator-(const Instant& anInstant) const;

    /// @brief              Addition assignement operator
    ///
    /// @code
    ///                     Instant instant = Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::TT) ;
    ///                     instant += Duration::Days(1.0) ; // 2018-01-02 00:00:00 [TT]
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Reference to instant

    Instant& operator+=(const Duration& aDuration);

    /// @brief              Subtraction assignement operator
    ///
    /// @code
    ///                     Instant instant = Instant::DateTime(DateTime(2018, 1, 2, 0, 0, 0), Scale::TT) ;
    ///                     instant -= Duration::Days(1.0) ; // 2018-01-01 00:00:00 [TT]
    /// @endcode
    ///
    /// @param              [in] aDuration A duration
    /// @return             Reference to instant

    Instant& operator-=(const Duration& aDuration);

    /// @brief              Output stream operator
    ///
    /// @code
    ///                     std::cout << Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anInstant An instant
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Instant& anInstant);

    /// @brief              Check if instant is defined
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if instant is defined

    bool isDefined() const;

    /// @brief              Check if instant is post-epoch (J2000)
    ///
    /// @code
    ///                     Instant::DateTime(DateTime(2018, 1, 1, 0, 0, 0), Scale::UTC).isPostEpoch() ; // True
    /// @endcode
    ///
    /// @return             True if instant is post-epoch

    bool isPostEpoch() const;

    /// @brief              Check if instant is near another instant
    ///
    /// @code
    ///                     Instant::J2000().isNear(Instant::J2000(), Duration::Zero()) ; // True
    /// @endcode
    ///
    /// @param              [in] anInstant An instant
    /// @param              [in] aTolerance A tolerance
    /// @return             True if instant is near another instant

    bool isNear(const Instant& anInstant, const Duration& aTolerance) const;

    /// @brief              Get date-time expressed in given time scale
    ///
    /// @code
    ///                     Instant::J2000().getDateTime(Scale::TT) ; // 2000-01-01 12:00:00
    /// @endcode
    ///
    /// @param              [in] aTimeScale A time scale
    /// @return             Date-time

    time::DateTime getDateTime(const Scale& aTimeScale) const;

    /// @brief              Get Julian Date expressed in given time scale
    ///
    /// @code
    ///                     Instant::J2000().getJulianDate(Scale::TT) ; // 2451545.0
    /// @endcode
    ///
    /// @param              [in] aTimeScale A time scale
    /// @return             Julian Date

    Real getJulianDate(const Scale& aTimeScale) const;

    /// @brief              Get Modified Julian Date expressed in given time scale
    ///
    /// @code
    ///                     Instant::J2000().getModifiedJulianDate(Scale::TT) ; // 51544.0
    /// @endcode
    ///
    /// @param              [in] aTimeScale A time scale
    /// @return             Modified Julian Date

    Real getModifiedJulianDate(const Scale& aTimeScale) const;

    /// @brief              Get Leap Second count
    ///
    ///                     The Leap Second count is the number of seconds between TAI and UTC scales.
    ///
    /// @code
    ///                     Instant::J2000().getLeapSecondCount() ;
    /// @endcode
    ///
    /// @return             Leap Second

    Int64 getLeapSecondCount() const;

    /// @brief              Get string representation of instant
    ///
    /// @code
    ///                     Instant::J2000().toString(Scale::TT) ; // 2000-01-01 12:00:00 [TT]
    /// @endcode
    ///
    /// @param              [in] aTimeScale A time scale
    /// @return             Serialized instant

    String toString(
        const Scale& aTimeScale = DEFAULT_TIME_SCALE, const DateTime::Format& aDateTimeFormat = DEFAULT_DATE_TIME_FORMAT
    ) const;

    /// @brief              Constructs an undefined instant
    ///
    /// @code
    ///                     Instant instant = Instant::Undefined() ;
    ///                     instant.isDefined() ; // False
    /// @endcode
    ///
    /// @return             Undefined instant

    static Instant Undefined();

    /// @brief              Constructs an instant at current time
    ///
    /// @code
    ///                     Instant instant = Instant::Now() ;
    /// @endcode
    ///
    /// @return             Instant at current time

    static Instant Now();

    /// @brief              Constructs instant at J2000 epoch
    ///
    ///                     The currently-used standard epoch "J2000" is defined by international agreement to be
    ///                     equivalent to:
    ///                     - The Gregorian date January 1, 2000 at 12:00 TT (Terrestrial Time).
    ///                     - The Julian date 2451545.0 TT (Terrestrial Time).
    ///                     - January 1, 2000, 11:59:27.816 TAI (International Atomic Time).
    ///                     - January 1, 2000, 11:58:55.816 UTC (Coordinated Universal Time).
    ///
    /// @ref                https://en.wikipedia.org/wiki/Epoch_(astronomy)#Julian_years_and_J2000
    ///
    /// @return             Instant at J2000 epoch

    static Instant J2000();

    /// @brief              Constructs instant from date-time
    ///
    /// @code
    ///                     Instant instant = Instant::DateTime(DateTime(2000, 1, 1, 12, 0, 0), Scale::TT) ; //
    ///                     2000-01-01 12:00:00 [TT]
    /// @endcode
    ///
    /// @input              [in] aDateTime A date-time
    /// @input              [in] aTimeScale A time scale
    /// @return             Instant

    static Instant DateTime(const time::DateTime& aDateTime, const Scale& aTimeScale);

    /// @brief              Constructs instant from Julian Date
    ///
    /// @code
    ///                     Instant instant = Instant::JulianDate(2451545.0, Scale::TT) ; // 2000-01-01 12:00:00 [TT]
    /// @endcode
    ///
    /// @ref                https://en.wikipedia.org/wiki/Julian_day
    ///
    /// @input              [in] aJulianDate A Julian Date
    /// @input              [in] aTimeScale A time scale
    /// @return             Instant

    static Instant JulianDate(const Real& aJulianDate, const Scale& aTimeScale);

    /// @brief              Constructs instant from Modified Julian Date
    ///
    /// @code
    ///                     Instant instant = Instant::ModifiedJulianDate(51544.0, Scale::TT) ; // 2000-01-01 12:00:00
    ///                     [TT]
    /// @endcode
    ///
    /// @ref                https://en.wikipedia.org/wiki/Julian_day
    ///
    /// @input              [in] aJulianDate A Modified Julian Date
    /// @input              [in] aTimeScale A time scale
    /// @return             Instant

    static Instant ModifiedJulianDate(const Real& aModifiedJulianDate, const Scale& aTimeScale);

   private:
    class Count
    {
       public:
        Uint64 countFromEpoch_;
        bool postEpoch_;

        Count(Uint64 aNanosecondCountFromEpoch, bool isPostEpoch);

        bool operator==(const Count& aCount) const;

        bool operator!=(const Count& aCount) const;

        bool operator<(const Count& aCount) const;

        bool operator<=(const Count& aCount) const;

        bool operator>(const Count& aCount) const;

        bool operator>=(const Count& aCount) const;

        Count operator+(const Count& aCount) const;

        Count operator+(Int64 aNanosecondDisplacement) const;

        Count operator-(Int64 aNanosecondDisplacement) const;

        String toString() const;
    };

    Instant::Count count_;
    Scale scale_;

    Instant(const Instant::Count& aCount, const Scale& aTimeScale);

    Instant inScale(const Scale& aTimeScale) const;

    static Instant::Count ConvertCountScale(
        const Instant::Count& aCount, const Scale& anInputTimeScale, const Scale& anOutputTimeScale
    );

    static Instant::Count UTC_TAI(const Instant::Count& aCount_TAI);

    static Instant::Count TAI_UTC(const Instant::Count& aCount_UTC);

    static Instant::Count TAI_TT(const Instant::Count& aCount_TT);

    static Instant::Count TT_TAI(const Instant::Count& aCount_TAI);

    static Instant::Count UT1_UTC(const Instant::Count& aCount_UTC);

    static Instant::Count UTC_UT1(const Instant::Count& aCount_UT1);

    static Instant::Count GPST_TAI(const Instant::Count& aCount_TAI);

    static Instant::Count TAI_GPST(const Instant::Count& aCount_GPST);

    static Int64 dAT_UTC(const Instant::Count& aCount_UTC);

    static Int64 dAT_TAI(const Instant::Count& aCount_TAI);

    static Int64 DUT1_UTC(const Instant::Count& aCount_UTC);

    static Int64 DUT1_UT1(const Instant::Count& aCount_UT1);
};

}  // namespace time
}  // namespace physics
}  // namespace ostk

#endif
