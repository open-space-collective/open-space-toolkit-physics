////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Duration.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Time_Duration__
#define __Library_Physics_Time_Duration__

#include <Library/Physics/Units/Time.hpp>

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

using library::core::types::Int64 ;
using library::core::types::Real ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Instant ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Duration

class Duration
{

    public:

        friend Instant ;

        enum class Format
        {

            Undefined,
            ISO8601
            
        } ;

                                Duration                                    (           Int64                       aNanosecondCount                            ) ;

        bool                    operator ==                                 (   const   Duration&                   aDuration                                   ) const ;
        
        bool                    operator !=                                 (   const   Duration&                   aDuration                                   ) const ;

        bool                    operator <                                  (   const   Duration&                   aDuration                                   ) const ;
        
        bool                    operator <=                                 (   const   Duration&                   aDuration                                   ) const ;
        
        bool                    operator >                                  (   const   Duration&                   aDuration                                   ) const ;
        
        bool                    operator >=                                 (   const   Duration&                   aDuration                                   ) const ;

        Duration                operator +                                  (   const   Duration&                   aDuration                                   ) const ;

        Duration                operator -                                  (   const   Duration&                   aDuration                                   ) const ;

        Duration                operator *                                  (   const   Real&                       aMultiplier                                 ) const ;

        Duration                operator /                                  (   const   Real&                       aDivider                                    ) const ;

        Duration                operator +                                  ( ) const ;

        Duration                operator -                                  ( ) const ;

        Duration&               operator +=                                 (   const   Duration&                   aDuration                                   ) ;

        Duration&               operator -=                                 (   const   Duration&                   aDuration                                   ) ;

        Duration&               operator *=                                 (   const   Real&                       aMultiplier                                 ) ;

        Duration&               operator /=                                 (   const   Real&                       aDivider                                    ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Duration&                   aDuration                                   ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isZero                                      ( ) const ;

        bool                    isPositive                                  ( ) const ;
        
        bool                    isStrictlyPositive                          ( ) const ;

        Real                    inNanoseconds                               ( ) const ;

        Real                    inMicroseconds                              ( ) const ;

        Real                    inMilliseconds                              ( ) const ;

        Real                    inSeconds                                   ( ) const ;

        Real                    inMinutes                                   ( ) const ;

        Real                    inHours                                     ( ) const ;

        Real                    inDays                                      ( ) const ;

        Real                    inWeeks                                     ( ) const ;

        Real                    in                                          (   const   units::Time::Unit&          aTimeUnit                                   ) const ;

        Duration                getAbsolute                                 ( ) const ;

        String                  getString                                   (   const   Duration::Format&           aFormat                                     =   Duration::Format::Undefined ) const ;

        static Duration         Undefined                                   ( ) ;

        static Duration         Zero                                        ( ) ;

        static Duration         Nanoseconds                                 (   const   Real&                       aNanosecondCount                            ) ;

        static Duration         Microseconds                                (   const   Real&                       aMicrosecondCount                           ) ;

        static Duration         Milliseconds                                (   const   Real&                       aMillisecondCount                           ) ;

        static Duration         Seconds                                     (   const   Real&                       aSecondCount                                ) ;

        static Duration         Minutes                                     (   const   Real&                       aMinuteCount                                ) ;

        static Duration         Hours                                       (   const   Real&                       anHourCount                                 ) ;

        static Duration         Days                                        (   const   Real&                       aDayCount                                   ) ;

        static Duration         Weeks                                       (   const   Real&                       aWeekCount                                  ) ;

        static Duration         Between                                     (   const   Instant&                    aFirstInstant,
                                                                                const   Instant&                    aSecondInstant                              ) ;

        static Duration         Parse                                       (   const   String&                     aString                                     ) ;

    private:

        bool                    defined_ ;
        Int64                   count_ ;

                                Duration                                    ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////