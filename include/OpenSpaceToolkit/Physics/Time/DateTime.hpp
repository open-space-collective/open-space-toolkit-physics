/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Time_DateTime__
#define __OpenSpaceToolkit_Physics_Time_DateTime__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Physics/Time/Date.hpp>
#include <OpenSpaceToolkit/Physics/Time/Time.hpp>

namespace ostk
{
namespace physics
{
namespace time
{

using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::physics::time::Date;
using ostk::physics::time::Time;

#define DEFAULT_HOUR 0
#define DEFAULT_MINUTE 0
#define DEFAULT_SECOND 0
#define DEFAULT_MILLISECOND 0
#define DEFAULT_MICROSECOND 0
#define DEFAULT_NANOSECOND 0

/// @brief Date-time
class DateTime
{
   public:
    /// @brief Date-time format
    enum class Format
    {

        Undefined,  ///< Undefined format
        Standard,   ///< Standard format (YYYY-MM-DD hh:mm:ss.sss.sss.sss)
        ISO8601,    ///< ISO 8601 format (YYYY-MM-DDThh:mm:ss.sssssssss)
        STK         ///< STK format (d Mon YYYY hh:mm:ss.sssssssss)

    };

    /// @brief Constructor
    ///
    /// @code
    ///     DateTime dateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456, 789)); // 2018-01-02
    ///     12:34:56.123.456.789
    /// @endcode
    ///
    /// @param [in] aDate A date
    /// @param [in] aTime A time
    DateTime(const Date& aDate, const Time& aTime);

    /// @brief Constructor
    ///
    /// @code
    ///     DateTime dateTime(2018, 1, 2); // 2018-01-02 00:00:00.000.000.000
    ///     DateTime dateTime(2018, 1, 2, 12, 34, 56); // 2018-01-02 12:34:56.000.000.000
    ///     DateTime dateTime(2018, 1, 2, 12, 34, 56, 123, 456, 789); // 2018-01-02
    ///     12:34:56.123.456.789
    /// @endcode
    ///
    /// @param [in] aYear aYear A year
    /// @param [in] aMonth aMonth A month (1 - 12)
    /// @param [in] aDay aDay A day (1 - 31)
    /// @param [in] (optional) anHour An hour (0 - 23)
    /// @param [in] (optional) aMinute A minute (0 - 59)
    /// @param [in] (optional) aSecond A second (0 - 60)
    /// @param [in] (optional) aMillisecond A millisecond (0 - 999)
    /// @param [in] (optional) aMicrosecond A microsecond (0 - 999)
    /// @param [in] (optional) aNanosecond A nanosecond (0 - 999)
    DateTime(
        Uint16 aYear,
        Uint8 aMonth,
        Uint8 aDay,
        Uint8 anHour = DEFAULT_HOUR,
        Uint8 aMinute = DEFAULT_MINUTE,
        Uint8 aSecond = DEFAULT_SECOND,
        Uint16 aMillisecond = DEFAULT_MILLISECOND,
        Uint16 aMicrosecond = DEFAULT_MICROSECOND,
        Uint16 aNanosecond = DEFAULT_NANOSECOND
    );

    /// @brief Equal to operator
    ///
    /// @code
    ///     DateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456, 789)) == DateTime(Date(2018, 1, 2),
    ///     Time(12, 34, 56, 123, 456, 789)); // True
    /// @endcode
    ///
    /// @param [in] aDateTime A date-time
    /// @return True if date-times are equal
    bool operator==(const DateTime& aDateTime) const;

    /// @brief Not equal to operator
    ///
    /// @code
    ///     DateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456, 789)) != DateTime(Date(2018, 1, 3),
    ///     Time(12, 34, 56, 123, 456, 789)); // True
    /// @endcode
    ///
    /// @param [in] aDateTime A date-time
    /// @return True if date-times are not equal
    bool operator!=(const DateTime& aDateTime) const;

    /// @brief Output stream operator
    ///
    /// @code
    ///     std::cout << DateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456, 789));
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aDateTime A date-time
    /// @return A reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const DateTime& aDateTime);

    /// @brief Check if date-time is defined
    ///
    /// @code
    ///     DateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456, 789)).isDefined(); // True
    /// @endcode
    ///
    /// @return True if date-time is defined
    bool isDefined() const;

    /// @brief Get reference to date
    ///
    /// @code
    ///     const Date& date = DateTime(2018, 1, 2, 12, 34, 56).accessDate();
    /// @endcode
    ///
    /// @return Reference to date
    const Date& accessDate() const;

    /// @brief Get reference to time
    ///
    /// @code
    ///     const Time& time = DateTime(2018, 1, 2, 12, 34, 56).accessTime();
    /// @endcode
    ///
    /// @return Reference to time
    const Time& accessTime() const;

    /// @brief Get date
    ///
    /// @code
    ///     Date date = DateTime(2018, 1, 2, 12, 34, 56).getDate(); // 2018-01-02
    /// @endcode
    ///
    /// @return Date
    Date getDate() const;

    /// @brief Get time
    ///
    /// @code
    ///     Time time = DateTime(2018, 1, 2, 12, 34, 56).getTime(); // 12:34:56
    /// @endcode
    ///
    /// @return Time
    Time getTime() const;

    /// @brief Get Julian Date
    ///
    /// @code
    ///     DateTime(AAA).getJulianDate(); // XXX.X
    /// @endcode
    ///
    /// @return Julian Date
    Real getJulianDate() const;

    /// @brief Get Modified Julian Date
    ///
    /// @code
    ///     DateTime(AAA).getModifiedJulianDate(); // XXX.X
    /// @endcode
    ///
    /// @return Modified Julian Date
    Real getModifiedJulianDate() const;

    /// @brief Get string representation of date-time
    ///
    /// @code
    ///     DateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456,
    ///     789)).toString(DateTime::Format::Standard); // 2018-01-02 12:34:56.123.456.789
    ///     DateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456,
    ///     789)).toString(DateTime::Format::ISO8601); // 2018-01-02T12:34:56.123.456.789
    /// @endcode
    ///
    /// @return Serialized date-time
    String toString(const DateTime::Format& aFormat = DateTime::Format::Standard) const;

    /// @brief Constructs an undefined date-time
    ///
    /// @code
    ///     DateTime dateTime = DateTime::Undefined();
    ///     dateTime.isDefined(); // False
    /// @endcode
    ///
    /// @return Undefined date-time
    static DateTime Undefined();

    /// @brief J2000 epoch (2000-01-01 12:00:00.000.000.00)
    ///
    /// @code
    ///     DateTime dateTime = DateTime::J2000(); // 2000-01-01 12:00:00
    /// @endcode
    ///
    /// @ref https://en.wikipedia.org/wiki/Epoch_(astronomy)#Julian_years_and_J2000
    ///
    /// @return Date-time at J2000 epoch
    static DateTime J2000();

    /// @brief GPS epoch (1980-01-06 00:00:00.000.000.000)
    ///
    /// @code
    ///     DateTime dateTime = DateTime::GPSEpoch(); // 1980-01-06 00:00:00
    /// @endcode
    ///
    /// @ref http://tycho.usno.navy.mil/gpstt.html
    ///
    /// @return Date-time at GPS epoch
    static DateTime GPSEpoch();

    /// @brief Unix epoch (1970-01-01 00:00:00.000.000.000)
    ///
    /// @code
    ///     DateTime dateTime = DateTime::UnixEpoch(); // 1970-01-01 00:00:00
    /// @endcode
    ///
    /// @ref https://en.wikipedia.org/wiki/Unix_time
    ///
    /// @return Date-time at Unix epoch
    static DateTime UnixEpoch();

    /// @brief Modified Julian Date epoch (1858-11-17 00:00:00.000.000.000)
    ///
    /// @code
    ///     DateTime dateTime = DateTime::ModifiedJulianDateEpoch(); // 1858-11-17 00:00:00
    /// @endcode
    ///
    /// @ref https://en.wikipedia.org/wiki/Julian_day
    ///
    /// @return Date-time
    static DateTime ModifiedJulianDateEpoch();

    /// @brief Date-time from Julian Date
    ///
    /// @code
    ///     DateTime dateTime = DateTime::JulianDate(2451545.0); // 2000-01-01 12:00:00
    /// @endcode
    ///
    /// @ref https://en.wikipedia.org/wiki/Julian_day
    ///
    /// @input [in] aJulianDate A Julian Date
    /// @return Date-time
    static DateTime JulianDate(const Real& aJulianDate);

    /// @brief Date-time from Modified Julian Date
    ///
    /// @code
    ///     DateTime dateTime = DateTime::ModifiedJulianDate(51544.5); // 2000-01-01 12:00:00
    /// @endcode
    ///
    /// @ref https://en.wikipedia.org/wiki/Julian_day
    ///
    /// @input [in] aModifiedJulianDate A Modified Julian Date
    /// @return Date-time
    static DateTime ModifiedJulianDate(const Real& aModifiedJulianDate);

    /// @brief Constructs a date-time from a string representation
    ///
    /// @code
    ///     DateTime dateTime = DateTime::Parse("2018-01-02 12:34:56.123.456.789"); // 2018-01-02
    /// @endcode
    ///
    /// @param [in] aString A string
    /// @param [in] (optional) aFormat A date-time format (automatic detection if Undefined)
    /// @return Date-time
    static DateTime Parse(const String& aString, const DateTime::Format& aFormat = DateTime::Format::Undefined);

   private:
    Date date_;
    Time time_;

    static Real ModifiedJulianDateFromJulianDate(const Real& aJulianDate);

    static Real JulianDateFromModifiedJulianDate(const Real& aModifiedJulianDate);
};

}  // namespace time
}  // namespace physics
}  // namespace ostk

#endif
