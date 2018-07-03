////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Time.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Units_Time__
#define __Library_Physics_Units_Time__

#include <Library/Physics/Units/Unit.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Real ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Time
///
/// @ref                        https://en.wikipedia.org/wiki/Unit_of_time

class Time : public Unit
{

    public:

        enum class Unit
        {

            Undefined,          ///< Undefined
            Nanosecond,         ///< Nanosecond
            Microsecond,        ///< Microsecond
            Millisecond,        ///< Millisecond
            Second,             ///< Second (SI)
            Minute,             ///< Minute
            Hour,               ///< Hour
            Day,                ///< Day
            Week                ///< Week
        
        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Time time(1.0, Time::Unit::Second) ;
        /// @endcode
        ///
        /// @param              [in] aValue A value
        /// @param              [in] aUnit A time unit

                                Time                                        (   const   Real&                       aValue,
                                                                                const   Time::Unit&                 aUnit                                       ) ;

        virtual bool            isDefined                                   ( ) const override ;
        
        virtual String          toString                                    ( ) const override ;

        static Time             Undefined                                   ( ) ;

        static String           StringFromUnit                              (   const   Time::Unit&                 aUnit                                       ) ;

        static String           SymbolFromUnit                              (   const   Time::Unit&                 aUnit                                       ) ;

    private:

        Time::Unit              unit_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////