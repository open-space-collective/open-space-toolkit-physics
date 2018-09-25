////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Unit.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Units_Unit__
#define __Library_Physics_Units_Unit__

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace units
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Integer ;
using library::core::types::Real ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Unit
///
/// @ref                        https://en.wikipedia.org/wiki/SI_base_unit
///
/// @note                       Could be (greatly) improved using templating...
/// @note                       https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
/// @note                       https://github.com/nholthaus/units
/// @note                       https://www.boost.org/doc/libs/1_67_0/doc/html/boost_units.html

class Unit
{

    public:

        enum class Type
        {

            Undefined,
            Length,
            Mass,
            Time,
            Temperature,
            ElectricCurrent,
            LuminousIntensity,
            Derived
        
        } ;

                                Unit                                        (   const   Unit::Type&                 aType,
                                                                                const   Real&                       aValue                                      ) ;

        virtual                 ~Unit                                       ( ) = 0 ;

        virtual Unit*           clone                                       ( ) const = 0 ;

        bool                    operator ==                                 (   const   Unit&                       aUnit                                       ) const ;
        
        bool                    operator !=                                 (   const   Unit&                       aUnit                                       ) const ;

        virtual bool            isDefined                                   ( ) const ;

        bool                    isZero                                      ( ) const ;

        const Real&             accessValue                                 ( ) const ;

        Unit::Type              getType                                     ( ) const ;

        Real                    getValue                                    ( ) const ;

        virtual String          toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const = 0 ;

        Real&                   accessValue                                 ( ) ;

        void                    setValue                                    (   const   Real&                       aValue                                      ) ;

    private:

        Unit::Type              type_ ;
        Real                    value_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////