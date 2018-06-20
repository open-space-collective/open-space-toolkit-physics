////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Mass.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Units_Mass__
#define __Library_Physics_Units_Mass__

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

/// @brief                      Mass
///
/// @ref                        https://en.wikipedia.org/wiki/Mass

class Mass : public Unit
{

    public:

        enum class Unit
        {

            Undefined,          ///< Undefined
            Kilogram,           ///< Kilogram (SI)
            Tonne,              ///< Tonne
            Pound               ///< Pound
        
        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Mass mass(1.0, Mass::Unit::Kilogram) ;
        /// @endcode
        ///
        /// @param              [in] aValue A value
        /// @param              [in] aUnit A mass unit

                                Mass                                        (   const   Real&                       aValue,
                                                                                const   Mass::Unit&                 aUnit                                       ) ;

        virtual bool            isDefined                                   ( ) const override ;
        
        virtual String          getString                                   ( ) const override ;

        static Mass             Undefined                                   ( ) ;

        static String           StringFromUnit                              (   const   Mass::Unit&                 aUnit                                       ) ;

        static String           SymbolFromUnit                              (   const   Mass::Unit&                 aUnit                                       ) ;

    private:

        Mass::Unit              unit_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////