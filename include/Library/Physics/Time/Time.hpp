////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Time.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Time_Time__
#define __Library_Physics_Time_Time__

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

using library::core::types::Uint8 ;
using library::core::types::Uint16 ;
using library::core::types::Real ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Time as hour, minute, second, millisecond, microsecond and nanosecond

class Time
{

    public:

        /// @brief              Time format

        enum class Format
        {

            Undefined,          ///< Undefined format
            Standard,           ///< Standard format (hh:mm:ss.sss.sss.sss)
            ISO8601             ///< ISO 8601 format (hh:mm:ss.sssssssss)

        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Time time(12, 34, 56) ; // 12:34:56.000.000.000
        ///                     Time time(12, 34, 56, 123, 456, 789) ; // 12:34:56.123.456.789
        /// @endcode
        ///
        /// @param              [in] anHour An hour (0 - 23)
        /// @param              [in] aMinute A minute (0 - 59)
        /// @param              [in] aSecond A second (0 - 60)
        /// @param              [in] (optional) aMillisecond A millisecond (0 - 999)
        /// @param              [in] (optional) aMicrosecond A microsecond (0 - 999)
        /// @param              [in] (optional) aNanosecond A nanosecond (0 - 999)

                                Time                                        (           Uint8                       anHour,
                                                                                        Uint8                       aMinute,
                                                                                        Uint8                       aSecond,
                                                                                        Uint16                      aMillisecond                                =   0,
                                                                                        Uint16                      aMicrosecond                                =   0,
                                                                                        Uint16                      aNanosecond                                 =   0 ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Time(12, 34, 56) == Time(12, 34, 56) ; // True
        /// @endcode
        ///
        /// @param              [in] aTime A time
        /// @return             True if times are equal

        bool                    operator ==                                 (   const   Time&                       aTime                                       ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Time(12, 34, 56) != Time(12, 34, 57) ; // True
        /// @endcode
        ///
        /// @param              [in] aTime A time
        /// @return             True if times are not equal
        
        bool                    operator !=                                 (   const   Time&                       aTime                                       ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Time(12, 34, 56) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aTime A time
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Time&                       aTime                                       ) ;

        /// @brief              Check if time is defined
        ///
        /// @code
        ///                     Time(12, 34, 56).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if time is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Get hour (0 - 23)
        ///
        /// @return             Hour
        
        Uint8                   getHour                                     ( ) const ;

        /// @brief              Get minute (0 - 59)
        ///
        /// @return             Minute
        
        Uint8                   getMinute                                   ( ) const ;

        /// @brief              Get second (0 - 60)
        ///
        /// @return             Second
        
        Uint8                   getSecond                                   ( ) const ;

        /// @brief              Get millisecond (0 - 999)
        ///
        /// @return             Millisecond
        
        Uint16                  getMillisecond                              ( ) const ;

        /// @brief              Get microsecond (0 - 999)
        ///
        /// @return             Microsecond
        
        Uint16                  getMicrosecond                              ( ) const ;

        /// @brief              Get nanosecond (0 - 999)
        ///
        /// @return             Nanosecond
        
        Uint16                  getNanosecond                               ( ) const ;

        /// @brief              Get floating seconds (0.0 - 59.999999999)
        ///
        /// @return             Floating second

        Real                    getFloatingSeconds                          ( ) const ;

        /// @brief              Get string representation of time
        ///
        /// @code
        ///                     Time(12, 34, 56).toString() ; // 12:34:56.000.000.000
        /// @endcode
        ///
        /// @param              [in] (optional) aFormat A time format
        /// @return             Serialized time

        String                  toString                                    (   const   Time::Format&               aFormat                                     =   Time::Format::Standard ) const ;

        /// @brief              Set hour
        ///
        /// @param              [in] anHour An hour (0 - 23)
        
        void                    setHour                                     (           Uint8                       anHour                                      ) ;

        /// @brief              Set minute
        ///
        /// @param              [in] aMinute A minute (0 - 59)
        
        void                    setMinute                                   (           Uint8                       aMinute                                     ) ;

        /// @brief              Set second
        ///
        /// @param              [in] aSecond A second (0 - 60)
        
        void                    setSecond                                   (           Uint8                       aSecond                                     ) ;

        /// @brief              Set millisecond
        ///
        /// @param              [in] aMillisecond A millisecond (0 - 999)
        
        void                    setMillisecond                              (           Uint16                      aMillisecond                                ) ;

        /// @brief              Set microsecond
        ///
        /// @param              [in] aMicrosecond A microsecond (0 - 999)
        
        void                    setMicrosecond                              (           Uint16                      aMicrosecond                                ) ;

        /// @brief              Set nanosecond
        ///
        /// @param              [in] aNanosecond A nanosecond (0 - 999)
        
        void                    setNanosecond                               (           Uint16                      aNanosecond                                 ) ;

        /// @brief              Constructs an undefined time
        ///
        /// @code
        ///                     Time time = Time::Undefined() ;
        ///                     time.isDefined() ; // False
        /// @endcode
        ///
        /// @return             Undefined time
        
        static Time             Undefined                                   ( ) ;

        /// @brief              Constructs a time at midnight
        ///
        /// @code
        ///                     Time time = Time::Midnight() ; // 00:00:00.000.000.000
        /// @endcode
        ///
        /// @return             Midnight time

        static Time             Midnight                                    ( ) ;

        /// @brief              Constructs a time at noon
        ///
        /// @code
        ///                     Time time = Time::Noon() ; // 12:00:00.000.000.000
        /// @endcode
        ///
        /// @return             Noon time

        static Time             Noon                                        ( ) ;

        /// @brief              Constructs a time from a string representation
        ///
        /// @code
        ///                     Time time = Time::Parse("12:34:56") ; // 12:34:56
        ///                     Time time = Time::Parse("12:34:56.123") ; // 12:34:56.123
        ///                     Time time = Time::Parse("12:34:56.123.456") ; // 12:34:56.123.456
        ///                     Time time = Time::Parse("12:34:56.123.456.789", Time::Format::Standard) ; // 12:34:56.123.456.789
        ///                     Time time = Time::Parse("12:34:56.123456789", Time::Format::ISO8601) ; // 12:34:56.123.456.789
        /// @endcode
        ///
        /// @param              [in] aString A string
        /// @param              [in] (optional) aFormat A time format (automatic detection if Undefined)
        /// @return             Time

        static Time             Parse                                       (   const   String&                     aString,
                                                                                const   Time::Format&               aFormat                                     =   Time::Format::Undefined ) ;

    private:

        bool                    defined_ ;

        Uint8                   hour_ ;
        Uint8                   minute_ ;
        Uint8                   second_ ;
        Uint16                  millisecond_ ;
        Uint16                  microsecond_ ;
        Uint16                  nanosecond_ ;

                                Time                                        ( ) ;

        static void             ValidateHour                                (           Uint8                       anHour                                      ) ;
        static void             ValidateMinute                              (           Uint8                       aMinute                                     ) ;
        static void             ValidateSecond                              (           Uint8                       aSecond                                     ) ;
        static void             ValidateMillisecond                         (           Uint16                      aMillisecond                                ) ;
        static void             ValidateMicrosecond                         (           Uint16                      aMicrosecond                                ) ;
        static void             ValidateNanosecond                          (           Uint16                      aNanosecond                                 ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////