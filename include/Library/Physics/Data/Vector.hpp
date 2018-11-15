////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Data/Vector.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Data_Vector__
#define __Library_Physics_Data_Vector__

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Time/Instant.hpp>
#include <Library/Physics/Unit.hpp>

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace data
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;
using library::core::types::Integer ;
using library::core::types::String ;

using library::math::obj::Vector3d ;

using library::physics::Unit ;
using library::physics::time::Instant ;
using library::physics::coord::Frame ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Vector quantity

class Vector
{

    public:

                                Vector                                      (   const   Vector3d&                   aValue,
                                                                                const   Unit&                       aUnit,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

        bool                    operator ==                                 (   const   Vector&                     aVector                                     ) const ;
        
        bool                    operator !=                                 (   const   Vector&                     aVector                                     ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Vector&                     aVector                                     ) ;

        bool                    isDefined                                   ( ) const ;

        Vector3d                getValue                                    ( ) const ;

        Unit                    getUnit                                     ( ) const ;

        Shared<const Frame>     getFrame                                    ( ) const ;

        Vector                  inUnit                                      (   const   Unit&                       aUnit                                       ) const ;

        Vector                  inFrame                                     (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const ;

        String                  toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const ;

        static Vector           Undefined                                   ( ) ;

    private:

        Vector3d                value_ ;
        Unit                    unit_ ;
        Shared<const Frame>     frameSPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////