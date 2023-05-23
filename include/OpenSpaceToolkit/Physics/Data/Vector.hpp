/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Data_Vector__
#define __OpenSpaceToolkit_Physics_Data_Vector__

#include <OpenSpaceToolkit/Physics/Coordinate/Frame.hpp>
#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>
#include <OpenSpaceToolkit/Physics/Unit.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace data
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Shared ;
using ostk::core::types::Integer ;
using ostk::core::types::String ;

using ostk::math::obj::Vector3d ;

using ostk::physics::Unit ;
using ostk::physics::time::Instant ;
using ostk::physics::coord::Frame ;

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
