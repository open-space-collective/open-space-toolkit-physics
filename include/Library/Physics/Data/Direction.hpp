////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Data/Direction.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Data_Direction__
#define __Library_Physics_Data_Direction__

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Data/Vector.hpp>

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

using library::physics::time::Instant ;
using library::physics::coord::Frame ;
using library::physics::data::Vector ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Direction
///
///                             A unit vector, expressed in a given frame.

class Direction : public Vector
{

    public:

                                Direction                                   (   const   Vector3d&                   aValue,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  ) ;

        bool                    operator ==                                 (   const   Direction&                  aDirection                                  ) const ;

        bool                    operator !=                                 (   const   Direction&                  aDirection                                  ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Vector&                     aVector                                     ) ;

        static Direction        Undefined                                   ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
