////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Time/Instant.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Time_Instant__
#define __Library_Physics_Time_Instant__

#include <Library/Physics/Time/DateTime.hpp>
#include <Library/Physics/Time/Duration.hpp>
#include <Library/Physics/Time/Scale.hpp>
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
using library::core::types::Uint64 ;
using library::core::types::Real ;
using library::core::types::String ;
using library::physics::time::Scale ;
using library::physics::time::Duration ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Point in time
///
/// @ref                        https://en.wikipedia.org/wiki/Instant
/// @ref                        https://www.boost.org/doc/libs/1_67_0/doc/html/date_time/details.html#date_time.calculations
/// @ref                        http://rhodesmill.org/skyfield/time.html
/// @ref                        http://www.madore.org/~david/computers/unix-leap-seconds.html
/// @ref                        http://help.agi.com/AGIComponentsJava/html/TimeAndTimeStandards.htm

class Instant
{

    public:

                                Instant                                     ( ) = delete ;

        bool                    operator ==                                 (   const   Instant&                    anInstant                                   ) const ;
        
        bool                    operator !=                                 (   const   Instant&                    anInstant                                   ) const ;
        
        bool                    operator <                                  (   const   Instant&                    anInstant                                   ) const ;
        
        bool                    operator <=                                 (   const   Instant&                    anInstant                                   ) const ;
        
        bool                    operator >                                  (   const   Instant&                    anInstant                                   ) const ;
        
        bool                    operator >=                                 (   const   Instant&                    anInstant                                   ) const ;

        Instant                 operator +                                  (   const   Duration&                   aDuration                                   ) const ;

        Instant                 operator -                                  (   const   Duration&                   aDuration                                   ) const ;

        Duration                operator -                                  (   const   Instant&                    anInstant                                   ) const ;

        Instant&                operator +=                                 (   const   Duration&                   aDuration                                   ) ;

        Instant&                operator -=                                 (   const   Duration&                   aDuration                                   ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Instant&                    anInstant                                   ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isPostEpoch                                 ( ) const ;

        time::DateTime          getDateTime                                 (   const   Scale&                      aTimeScale                                  ) const ;

        Real                    getJulianDate                               (   const   Scale&                      aTimeScale                                  ) const ;

        Real                    getModifiedJulianDate                       (   const   Scale&                      aTimeScale                                  ) const ;

        Uint64                  getCountSinceEpoch                          (   const   units::Time::Unit&          aTimeUnit,
                                                                                const   Instant&                    anEpoch                                     ) ;

        String                  getString                                   (   const   Scale&                      aTimeScale                                  ) const ;

        static Instant          Undefined                                   ( ) ;

        static Instant          Now                                         ( ) ;

        /// @brief              J2000 epoch
        ///
        ///                     The currently-used standard epoch "J2000" is defined by international agreement to be equivalent to:
        ///                     - The Gregorian date January 1, 2000 at 12:00 TT (Terrestrial Time).
        ///                     - The Julian date 2451545.0 TT (Terrestrial Time).
        ///                     - January 1, 2000, 11:59:27.816 TAI (International Atomic Time).
        ///                     - January 1, 2000, 11:58:55.816 UTC (Coordinated Universal Time).
        ///
        /// @ref                https://en.wikipedia.org/wiki/Epoch_(astronomy)#Julian_years_and_J2000
        ///
        /// @return             Instant at J2000 epoch

        static Instant          J2000                                       ( ) ;

        static Instant          DateTime                                    (   const   time::DateTime&             aDateTime,
                                                                                const   Scale&                      aTimeScale                                  ) ;

        static Instant          JulianDate                                  (   const   Real&                       aJulianDate,
                                                                                const   Scale&                      aTimeScale                                  ) ;

        static Instant          ModifiedJulianDate                          (   const   Real&                       aModifiedJulianDate,
                                                                                const   Scale&                      aTimeScale                                  ) ;

    private:

        class Count
        {

            public:

                Uint64          countFromEpoch_ ;
                bool            postEpoch_ ;

                                Count                                       (           Uint64                      aNanosecondCountFromEpoch,
                                                                                        bool                        isPostEpoch                                 ) ;

                bool            operator ==                                 (   const   Count&                      aCount                                      ) const ;

                bool            operator !=                                 (   const   Count&                      aCount                                      ) const ;

                bool            operator <                                  (   const   Count&                      aCount                                      ) const ;

                bool            operator <=                                 (   const   Count&                      aCount                                      ) const ;

                bool            operator >                                  (   const   Count&                      aCount                                      ) const ;

                bool            operator >=                                 (   const   Count&                      aCount                                      ) const ;

                Count           operator +                                  (   const   Count&                      aCount                                      ) const ;

                Count           operator +                                  (           Int64                       aNanosecondDisplacement                     ) const ;

                Count           operator -                                  (           Int64                       aNanosecondDisplacement                     ) const ;

                String          getString                                   ( ) const ;

        } ;

        Instant::Count          count_ ;
        Scale                   scale_ ;

                                Instant                                     (   const   Instant::Count&             aCount,
                                                                                const   Scale&                      aTimeScale                                  ) ;

        Instant                 inScale                                     (   const   Scale&                      aTimeScale                                  ) const ;

        static Instant::Count   ConvertCountScale                           (   const   Instant::Count&             aCount,
                                                                                const   Scale&                      anInputTimeScale,
                                                                                const   Scale&                      anOutputTimeScale                           ) ;

        static Instant::Count   UTC_TAI                                     (   const   Instant::Count&             aCount_TAI                                  ) ;

        static Instant::Count   TAI_UTC                                     (   const   Instant::Count&             aCount_UTC                                  ) ;

        static Instant::Count   TAI_TT                                      (   const   Instant::Count&             aCount_TT                                   ) ;

        static Instant::Count   TT_TAI                                      (   const   Instant::Count&             aCount_TAI                                  ) ;

        static Instant::Count   UT1_UTC                                     (   const   Instant::Count&             aCount_UTC                                  ) ;

        static Instant::Count   UTC_UT1                                     (   const   Instant::Count&             aCount_UT1                                  ) ;

        static Instant::Count   GPST_TAI                                    (   const   Instant::Count&             aCount_TAI                                  ) ;

        static Instant::Count   TAI_GPST                                    (   const   Instant::Count&             aCount_GPST                                 ) ;

        static Int64            dAT_UTC                                     (   const   Instant::Count&             aCount_UTC                                  ) ;

        static Int64            dAT_TAI                                     (   const   Instant::Count&             aCount_TAI                                  ) ;

        static Int64            DUT1_UTC                                    (   const   Instant::Count&             aCount_UTC                                  ) ;

        static Int64            DUT1_UT1                                    (   const   Instant::Count&             aCount_UT1                                  ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////