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

        bool                    operator ==                                 (   const   Unit&                       aUnit                                       ) const ;
        
        bool                    operator !=                                 (   const   Unit&                       aUnit                                       ) const ;

        virtual bool            isDefined                                   ( ) const ;

        bool                    isZero                                      ( ) const ;

        const Real&             accessValue                                 ( ) const ;

        Unit::Type              getType                                     ( ) const ;

        Real                    getValue                                    ( ) const ;

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