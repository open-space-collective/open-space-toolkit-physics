////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           OpenSpaceToolkit/Physics/Data/Scalar.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Physics_Data_Scalar__
#define __OpenSpaceToolkit_Physics_Data_Scalar__

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace data
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Integer ;
using ostk::core::types::Real ;
using ostk::core::types::String ;

using ostk::physics::Unit ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Scalar quantity
///
///                             A scalar quantity is a physical quantity that can be described by a single element of a number field such as a real number,
///                             often accompanied by units of measurement.
///
/// @ref                        https://en.wikipedia.org/wiki/Scalar_(physics)

class Scalar
{

    public:

                                Scalar                                      (   const   Real&                       aValue,
                                                                                const   Unit&                       aUnit                                       ) ;

        bool                    operator ==                                 (   const   Scalar&                     aScalar                                     ) const ;

        bool                    operator !=                                 (   const   Scalar&                     aScalar                                     ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Scalar&                     aScalar                                     ) ;

        bool                    isDefined                                   ( ) const ;

        Real                    getValue                                    ( ) const ;

        Unit                    getUnit                                     ( ) const ;

        Scalar                  inUnit                                      (   const   Unit&                       aUnit                                       ) const ;

        String                  toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const ;

        static Scalar           Undefined                                   ( ) ;

    private:

        Real                    value_ ;
        Unit                    unit_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
