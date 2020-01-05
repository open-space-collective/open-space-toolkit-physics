////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Unit.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Unit__
#define __OpenSpaceToolkit_Physics_Unit__

#include <Library/Physics/Units/Derived/Angle.hpp>
#include <Library/Physics/Units/Derived.hpp>
#include <Library/Physics/Units/Time.hpp>
#include <Library/Physics/Units/Mass.hpp>
#include <Library/Physics/Units/Length.hpp>
#include <Library/Physics/Units/Unit.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Unique.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::Real ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Unit
///
///                             A unit of measurement is a definite magnitude of a quantity, defined and adopted by convention or by law,
///                             that is used as a standard for measurement of the same kind of quantity.
///                             Any other quantity of that kind can be expressed as a multiple of the unit of measurement.
///
/// @ref                        https://en.wikipedia.org/wiki/Unit_of_measurement

class Unit
{

    public:

        enum class Type
        {

            Undefined,
            None,
            Length,
            Mass,
            Time,
            Temperature,
            ElectricCurrent,
            LuminousIntensity,
            Derived

        } ;

                                Unit                                        ( ) = delete ;

                                Unit                                        (   const   Unit&                       aUnit                                       ) ;

        Unit&                   operator =                                  (   const   Unit&                       aUnit                                       ) ;

        bool                    operator ==                                 (   const   Unit&                       aUnit                                       ) const ;

        bool                    operator !=                                 (   const   Unit&                       aUnit                                       ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Unit&                       aUnit                                       ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isNone                                      ( ) const ;

        Unit::Type              getType                                     ( ) const ;

        Real                    ratioTo                                     (   const   Unit&                       aUnit                                       ) const ;

        String                  toString                                    ( ) const ;

        static Unit             Undefined                                   ( ) ;

        static Unit             None                                        ( ) ;

        static Unit             Length                                      (   const   units::Length::Unit&        aLengthUnit                                 ) ;

        static Unit             Derived                                     (   const   units::Derived::Unit&       aDerivedUnit                                ) ;

        static String           StringFromType                              (   const   Unit::Type&                 aType                                       ) ;

    private:

        Unit::Type              type_ ;
        Unique<units::Unit>     unitUPtr_ ;

                                Unit                                        (   const   Unit::Type&                 aType,
                                                                                const   Unique<units::Unit>&        aUnitUPtr                                   ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
