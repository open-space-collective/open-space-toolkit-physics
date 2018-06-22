////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/DateTime.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Time_DateTime__
#define __Library_Physics_Time_DateTime__

#include <Library/Physics/Time/Date.hpp>
#include <Library/Physics/Time/Time.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace time
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::String ;
using library::physics::time::Date ;
using library::physics::time::Time ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Date-Time

class DateTime
{

    public:

        /// @brief              Date-Time format

        enum class Format
        {

            Undefined,          ///< Undefined format
            Standard,           ///< Standard format (YYYY:MM:DD hh:mm:ss.sss.sss.sss)
            ISO8601             ///< ISO 8601 format (YYYY:MM:DDThh:mm:ss.sssssssss)

        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     DateTime dateTime(Date(2018, 1, 2), Time(12, 34, 56, 123, 456, 789)) ; // 2018-01-02 12:34:56.123.456.789
        /// @endcode
        ///
        /// @param              [in] aDate A date
        /// @param              [in] aTime A time

                                DateTime                                    (   const   Date&                       aDate,
                                                                                const   Time&                       aTime                                       ) ;

        bool                    operator ==                                 (   const   DateTime&                   aDateTime                                   ) const ;
        
        bool                    operator !=                                 (   const   DateTime&                   aDateTime                                   ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   DateTime&                   aDateTime                                   ) ;

        bool                    isDefined                                   ( ) const ;

        const Date&             accessDate                                  ( ) const ;

        const Time&             accessTime                                  ( ) const ;

        String                  getString                                   (   const   DateTime::Format&           aFormat                                     =   DateTime::Format::Standard ) const ;

        /// @brief              Constructs an undefined date-time
        ///
        /// @code
        ///                     DateTime dateTime = DateTime::Undefined() ;
        ///                     dateTime.isDefined() ; // False
        /// @endcode
        ///
        /// @return             Undefined date-time

        static DateTime         Undefined                                   ( ) ;

        /// @brief              J2000 epoch (2000-01-01 12:00:00.000.000.00)
        ///
        /// @ref                https://en.wikipedia.org/wiki/Epoch_(astronomy)#Julian_years_and_J2000
        ///
        /// @return             DateTime at J2000 epoch

        static DateTime         J2000                                       ( ) ;

        /// @brief              GPS epoch (1980-01-06 00:00:00.000.000.000)
        ///
        /// @ref                http://tycho.usno.navy.mil/gpstt.html
        ///
        /// @return             DateTime at GPS epoch
        
        static DateTime         GPS                                         ( ) ;

        /// @brief              Unix epoch (1970-01-01 00:00:00.000.000.000)
        ///
        /// @ref                https://en.wikipedia.org/wiki/Unix_time
        ///
        /// @return             DateTime at Unix epoch

        static DateTime         Unix                                        ( ) ;

        /// @brief              Julian dates epoch (-4712-01-01 12:00:00.000.000.00)
        ///
        /// @ref                https://en.wikipedia.org/wiki/Julian_day
        ///
        /// @return             DateTime at Julian dates epoch

        static DateTime         JulianDate                                  ( ) ;

        /// @brief              Modified julian dates epoch (1858-11-17 00:00:00.000.000.000)
        ///
        /// @ref                https://en.wikipedia.org/wiki/Julian_day
        ///
        /// @return             DateTime at Modified Julian epoch

        static DateTime         ModifiedJulianDate                          ( ) ;

    private:

        Date                    date_ ;
        Time                    time_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////