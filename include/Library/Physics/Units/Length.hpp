////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Length.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Units_Length__
#define __Library_Physics_Units_Length__

#include <Library/Physics/Units/Unit.hpp>

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

/// @brief                      Length
///
/// @ref                        https://en.wikipedia.org/wiki/Length

class Length : public Unit
{

    public:

        enum class Unit
        {

            Undefined,          ///< Undefined
            Meter,              ///< Meter (SI)
            Foot,               ///< Foot
            TerrestrialMile,    ///< Terrestrial mile
            NauticalMile,       ///< Nautical mile
            AstronomicalUnit    ///< Astronomical Unit
        
        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Length length(1.0, Length::Unit::Meter) ;
        /// @endcode
        ///
        /// @param              [in] aValue A value
        /// @param              [in] aUnit A length unit

                                Length                                      (   const   Real&                       aValue,
                                                                                const   Length::Unit&               aUnit                                       ) ;

        virtual Length*         clone                                       ( ) const override ;

        bool                    operator ==                                 (   const   Length&                     aLength                                     ) const ;

        bool                    operator !=                                 (   const   Length&                     aLength                                     ) const ;

        bool                    operator <                                  (   const   Length&                     aLength                                     ) const ;

        bool                    operator <=                                 (   const   Length&                     aLength                                     ) const ;

        bool                    operator >                                  (   const   Length&                     aLength                                     ) const ;

        bool                    operator >=                                 (   const   Length&                     aLength                                     ) const ;

        Length                  operator +                                  (   const   Length&                     aLength                                     ) const ;
        
        Length                  operator -                                  (   const   Length&                     aLength                                     ) const ;
        
        Length                  operator *                                  (   const   Real&                       aReal                                       ) const ;
        
        Length                  operator /                                  (   const   Real&                       aReal                                       ) const ;

        Length&                 operator +=                                 (   const   Length&                     aLength                                     ) ;
        
        Length&                 operator -=                                 (   const   Length&                     aLength                                     ) ;
        
        Length&                 operator *=                                 (   const   Real&                       aReal                                       ) ;
        
        Length&                 operator /=                                 (   const   Real&                       aReal                                       ) ;

        friend Length           operator *                                  (   const   Real&                       aReal,
                                                                                const   Length&                     aLength                                     ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Length&                     aLength                                     ) ;

        virtual bool            isDefined                                   ( ) const override ;

        Length::Unit            getUnit                                     ( ) const ;

        Real                    in                                          (   const   Length::Unit&               aUnit                                       ) const ;

        Real                    inMeters                                    ( ) const ;

        Real                    inKilometers                                ( ) const ;

        virtual String          toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const override ;

        static Length           Undefined                                   ( ) ;

        static Length           Millimeters                                 (   const   Real&                       aValue                                      ) ;
        
        static Length           Meters                                      (   const   Real&                       aValue                                      ) ;
        
        static Length           Kilometers                                  (   const   Real&                       aValue                                      ) ;
        
        static Length           Parse                                       (   const   String&                     aString                                     ) ;

        static String           StringFromUnit                              (   const   Length::Unit&               aUnit                                       ) ;

        static String           SymbolFromUnit                              (   const   Length::Unit&               aUnit                                       ) ;

    private:

        Length::Unit            unit_ ;

        static Real             SIRatio                                     (   const   Length::Unit&               aUnit                                       ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////