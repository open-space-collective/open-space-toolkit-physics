////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Time/Date.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Time_Date__
#define __Library_Physics_Time_Date__

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Uint8 ;
using library::core::types::Uint16 ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Date as year, month and day

class Date
{

    public:

        /// @brief              Date format

        enum class Format
        {

            Undefined,          ///< Undefined format
            Standard,           ///< Standard format (YYYY:MM:DD)
            STK                 ///< STK format (d Mon YYYY)

        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Date date(2018, 1, 2) ; // 2018-01-02
        /// @endcode
        ///
        /// @param              [in] aYear A year (1400 - 9999)
        /// @param              [in] aMonth A month (1 - 12)
        /// @param              [in] aDay A day (1 - 31)

                                Date                                        (           Uint16                      aYear,
                                                                                        Uint8                       aMonth,
                                                                                        Uint8                       aDay                                        ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Date(2018, 1, 2) == Date(2018, 1, 2) ; // True
        /// @endcode
        ///
        /// @param              [in] aDate A date
        /// @return             True if dates are equal

        bool                    operator ==                                 (   const   Date&                       aDate                                       ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Date(2018, 1, 2) != Date(2018, 1, 1) ; // True
        /// @endcode
        ///
        /// @param              [in] aDate A date
        /// @return             True if dates are not equal

        bool                    operator !=                                 (   const   Date&                       aDate                                       ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Date(2018, 1, 2) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aDate A date
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Date&                       aDate                                       ) ;

        /// @brief              Check if date is defined
        ///
        /// @code
        ///                     Date(2018, 1, 2).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if date is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Get year (1400 - 9999)
        ///
        /// @return             Year

        Uint16                  getYear                                     ( ) const ;

        /// @brief              Get month (1 - 12)
        ///
        /// @return             Month

        Uint8                   getMonth                                    ( ) const ;

        /// @brief              Get day (1 - 31)
        ///
        /// @return             Day

        Uint8                   getDay                                      ( ) const ;

        /// @brief              Get string representation of date
        ///
        /// @code
        ///                     Date(2018, 1, 2).toString() ; // 2018-01-02
        /// @endcode
        ///
        /// @param              [in] (optional) aFormat A date format
        /// @return             Serialized date

        String                  toString                                    (   const   Date::Format&               aFormat                                     =   Date::Format::Standard ) const ;

        /// @brief              Set year
        ///
        /// @param              [in] aYear A year (1400 - 9999)

        void                    setYear                                     (           Uint16                      aYear                                       ) ;

        /// @brief              Set month
        ///
        /// @param              [in] aMonth A month (1 - 12)

        void                    setMonth                                    (           Uint8                       aMonth                                      ) ;

        /// @brief              Set day
        ///
        /// @param              [in] aDay A day (1 - 31)

        void                    setDay                                      (           Uint8                       aDay                                        ) ;

        /// @brief              Constructs an undefined date
        ///
        /// @code
        ///                     Date date = Date::Undefined() ;
        ///                     date.isDefined() ; // False
        /// @endcode
        ///
        /// @return             Undefined date

        static Date             Undefined                                   ( ) ;

        /// @brief              J2000 epoch (2000-01-01)
        ///
        /// @ref                https://en.wikipedia.org/wiki/Epoch_(astronomy)#Julian_years_and_J2000
        ///
        /// @return             Date at J2000 epoch

        static Date             J2000                                       ( ) ;

        /// @brief              GPS epoch (1980-01-06)
        ///
        /// @ref                http://tycho.usno.navy.mil/gpstt.html
        ///
        /// @return             Date at GPS epoch

        static Date             GPSEpoch                                    ( ) ;

        /// @brief              Unix epoch (1970-01-01)
        ///
        /// @ref                https://en.wikipedia.org/wiki/Unix_time
        ///
        /// @return             Date at Unix epoch

        static Date             UnixEpoch                                   ( ) ;

        /// @brief              Modified julian dates epoch (1858-11-17)
        ///
        /// @ref                https://en.wikipedia.org/wiki/Julian_day
        ///
        /// @return             Date at Modified Julian epoch

        static Date             ModifiedJulianDateEpoch                     ( ) ;

        /// @brief              Constructs a date from a string representation
        ///
        /// @code
        ///                     Date date = Date::Parse("2018-01-02") ; // 2018-01-02
        /// @endcode
        ///
        /// @param              [in] aString A string
        /// @param              [in] (optional) aFormat A date format
        /// @return             Date

        static Date             Parse                                       (   const   String&                     aString,
                                                                                const   Date::Format&               aFormat                                     =   Date::Format::Undefined ) ;

    private:

        bool                    defined_ ;

        Uint16                  year_ ;
        Uint8                   month_ ;
        Uint8                   day_ ;

                                Date                                        ( ) ;

        static void             ValidateDate                                (           Uint16                      aYear,
                                                                                        Uint8                       aMonth,
                                                                                        Uint8                       aDay                                        ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
