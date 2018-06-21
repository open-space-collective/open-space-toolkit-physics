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

/// @brief                      Instant

class Instant
{

    public:

                                Instant                                     (           Uint64                      aNanosecondCountFromEpoch,
                                                                                        bool                        isPostEpoch,
                                                                                const   Scale&                      aTimeScale                                  ) ;

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

        Scale                   getScale                                    ( ) const ;

        Real                    getJulianDate                               ( ) const ;

        Real                    getModifiedJulianDate                       ( ) const ;

        time::DateTime          getDateTime                                 ( ) const ;

        Uint64                  getCountSinceEpoch                          (   const   units::Time&                aTimeUnit,
                                                                                const   Instant&                    anEpoch                                     ) ;

        String                  getString                                   ( ) const ;

        Instant                 inScale                                     (   const   Scale&                      aTimeScale                                  ) const ;

        static Instant          Undefined                                   ( ) ;

        static Instant          Now                                         ( ) ;

        static Instant          Epoch                                       ( ) ;

        static Instant          J2000                                       ( ) ;

        static Instant          DateTime                                    (   const   time::DateTime&             aDateTime                                   ) ;

        static Instant          JulianDate                                  (   const   Real&                       aJulianDate,
                                                                                const   Scale&                      aTimeScale                                  ) ;

        static Instant          ModifiedJulianDate                          (   const   Real&                       aJulianDate,
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

        } ;

        Instant::Count          count_ ;
        Scale                   scale_ ;

                                Instant                                     (   const   Instant::Count&             aCount,
                                                                                const   Scale&                      aTimeScale                                  ) ;

        static Instant::Count   ConvertCountScale                           (   const   Instant::Count&             aCount,
                                                                                const   Scale&                      anInputTimeScale,
                                                                                const   Scale&                      anOutputTimeScale                           ) ;

        static Real             ModifiedJulianDateFromJulianDate            (   const   Real&                       aJulianDate                                 ) ;

        static Real             JulianDateFromModifiedJulianDate            (   const   Real&                       aModifiedJulianDate                         ) ;

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