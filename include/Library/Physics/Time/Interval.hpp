////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Time/Interval.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Time_Interval__
#define __Library_Physics_Time_Interval__

#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Time/Scale.hpp>

#include <Library/Mathematics/Objects/Interval.hpp>

#include <Library/Core/Containers/Array.hpp>
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

using library::core::types::Real ;
using library::core::types::String ;
using library::core::ctnr::Array ;

using library::physics::time::Scale ;
using library::physics::time::Instant ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Interval

class Interval : public math::obj::Interval<Instant>
{

    public:

        typedef math::obj::Interval<Instant>::Type Type ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Interval interval(Instant::J2000(), Instant::Now(), Interval::Type::Closed) ;
        /// @endcode
        ///
        /// @param              [in] aLowerBound A lower bound
        /// @param              [in] anUpperBound An upper bound
        /// @param              [in] anIntervalType An interval type

                                Interval                                    (   const   Instant&                    aLowerBound,
                                                                                const   Instant&                    anUpperBound,
                                                                                const   Interval::Type&             anIntervalType                              ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Interval&                   anInterval                                  ) ;

        bool                    isDefined                                   ( ) const ;

        const Instant&          accessStart                                 ( ) const ;

        const Instant&          accessEnd                                   ( ) const ;

        Instant                 getStart                                    ( ) const ;

        Instant                 getEnd                                      ( ) const ;

        Duration                getDuration                                 ( ) const ;

        Instant                 getCenter                                   ( ) const ;

        String                  toString                                    (   const   Scale&                      aTimeScale                                  =   Scale::UTC ) const ;

        Array<Instant>          generateGrid                                (   const   Duration&                   aTimeStep                                   ) const ;

        static Interval         Undefined                                   ( ) ;

        /// @brief              Constructs a closed interval
        ///
        /// @code
        ///                     Interval interval = Interval::Closed(Instant::J2000(), Instant::Now()) ; // [J2000, Now]
        /// @endcode
        ///
        /// @return             Closed interval

        static Interval         Closed                                      (   const   Instant&                    aLowerBound,
                                                                                const   Instant&                    anUpperBound                                ) ;

        static Interval         Centered                                    (   const   Instant&                    aCentralInstant,
                                                                                const   Duration&                   aDuration,
                                                                                const   Interval::Type&             anIntervalType                              ) ;

        /// @brief              Constructs an interval from a string representation
        ///
        /// @code
        ///                     ...
        /// @endcode
        ///
        /// @param              [in] aString A string
        /// @return             Interval

        static Interval         Parse                                       (   const   String&                     aString                                     ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
