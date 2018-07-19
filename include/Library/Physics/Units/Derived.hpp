////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Units/Derived.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Units_Derived__
#define __Library_Physics_Units_Derived__

#include <Library/Physics/Units/Derived/Angle.hpp>
#include <Library/Physics/Units/Time.hpp>
#include <Library/Physics/Units/Mass.hpp>
#include <Library/Physics/Units/Length.hpp>
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

using library::core::types::Int16 ;
using library::core::types::Integer ;
using library::core::types::Real ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Derived unit
///
/// @ref                        https://en.wikipedia.org/wiki/SI_derived_unit

class Derived : public Unit
{

    public:

        /// @brief              SI unit order

        class Order
        {

            public:

                                Order                                       (           Int16                       aNumerator                                  ) ;

                                Order                                       (           Int16                       aNumerator,
                                                                                        Int16                       aDenominator                                ) ;

                bool            operator ==                                 (   const   Order&                      anOrder                                     ) const ;

                bool            operator !=                                 (   const   Order&                      anOrder                                     ) const ;

                bool            isZero                                      ( ) const ;
                
                bool            isUnity                                     ( ) const ;

                const Int16&    accessNumerator                             ( ) const ;

                const Int16&    accessDenominator                           ( ) const ;

                Real            getValue                                    ( ) const ;

                String          toString                                    ( ) const ;

                static Order    Zero                                        ( ) ;
                
                static Order    One                                         ( ) ;

                static Order    Two                                         ( ) ;

            private:

                Int16           numerator_ ;
                Int16           denominator_ ;

        } ;


        /// @brief              Unit

        class Unit
        {

            public:

                                Unit                                        (   const   Length::Unit&               aLengthUnit,
                                                                                const   Order&                      aLengthOrder,
                                                                                const   Mass::Unit&                 aMassUnit,
                                                                                const   Order&                      aMassOrder,
                                                                                const   Time::Unit&                 aTimeUnit,
                                                                                const   Order&                      aTimeOrder,
                                                                                const   Angle::Unit&                anAngleUnit,
                                                                                const   Order&                      anAngleOrder                                ) ; // [TBI]

                bool            operator ==                                 (   const   Unit&                       aUnit                                       ) const ;

                bool            operator !=                                 (   const   Unit&                       aUnit                                       ) const ;

                bool            isDefined                                   ( ) const ;

                bool            isCompatibleWith                            (   const   Unit&                       aUnit                                       ) const ;

                const Length::Unit& accessLengthUnit                        ( ) const ;
                
                const Order&    accessLengthOrder                           ( ) const ;

                const Mass::Unit& accessMassUnit                            ( ) const ;

                const Derived::Order& accessMassOrder                       ( ) const ;

                const Time::Unit& accessTimeUnit                            ( ) const ;

                const Derived::Order& accessTimeOrder                       ( ) const ;

                const Angle::Unit& accessAngleUnit                          ( ) const ;

                const Derived::Order& accessAngleOrder                      ( ) const ;

                String          toString                                    ( ) const ;

                String          getSymbol                                   ( ) const ;

                static Unit     Undefined                                   ( ) ;

                static Unit     SquareMeter                                 ( ) ;
                
                static Unit     CubicMeter                                  ( ) ;

                static Unit     Hertz                                       ( ) ;
                
                static Unit     Watt                                        ( ) ;

                static Unit     AngularVelocity                             (   const   Angle::Unit&                anAngleUnit,
                                                                                const   Time::Unit&                 aTimeUnit                                   ) ;

                static Unit     Parse                                       (   const   String&                     aString                                     ) ;

            private:

                // S.I.

                Length::Unit    lengthUnit_ ;
                Order           lengthOrder_ ;
                
                Mass::Unit      massUnit_ ;
                Order           massOrder_ ;

                Time::Unit      timeUnit_ ;
                Order           timeOrder_ ;

                // Temperature::Unit temperatureUnit_ ;
                // Order           temperatureOrder_ ;
                
                // ElectricCurrent::Unit electricCurrentUnit_ ;
                // Order           electricCurrentOrder_ ;
                
                // LuminousIntensity::Unit luminousIntensityUnit_ ;
                // Order           luminousIntensityOrder_ ;

                // Derived

                Angle::Unit     angleUnit_ ;
                Order           angleOrder_ ;

        } ;

        /// @brief              Constructor
        ////
        /// @code
        ///                     
        /// @endcode
        ///
        /// @param              [in] 
        /// @param              [in] 

                                Derived                                     (   const   Real&                       aValue,
                                                                                const   Derived::Unit&              aUnit                                       ) ;

        bool                    operator ==                                 (   const   Derived&                    aDerivedUnit                                ) const ;

        bool                    operator !=                                 (   const   Derived&                    aDerivedUnit                                ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Derived&                    aDerivedUnit                                ) ;

        virtual bool            isDefined                                   ( ) const override ;

        Derived::Unit           getUnit                                     ( ) const ;

        Real                    in                                          (   const   Derived::Unit&              aUnit                                       ) const ;

        virtual String          toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const override ;

        static Derived          Undefined                                   ( ) ;

        static Derived          Parse                                       (   const   String&                     aString                                     ) ;

        static String           StringFromUnit                              (   const   Derived::Unit&              aUnit                                       ) ;

        static String           SymbolFromUnit                              (   const   Derived::Unit&              aUnit                                       ) ;

    private:

        Derived::Unit           unit_ ;

        static Real             SIRatio                                     (   const   Derived::Unit&              aUnit                                       ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////