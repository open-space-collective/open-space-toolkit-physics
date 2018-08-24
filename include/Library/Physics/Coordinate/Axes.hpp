////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Axes.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Axes__
#define __Library_Physics_Coordinate_Axes__

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Shared ;

using library::math::obj::Vector3d ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Frame ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Axes

class Axes
{

    public:

                                Axes                                        (   const   Vector3d&                   aXAxis,
                                                                                const   Vector3d&                   aYAxis,
                                                                                const   Vector3d&                   aZAxis,
                                                                                const   Shared<const Frame>&        aFrame                                      ) ;

        bool                    operator ==                                 (   const   Axes&                       anAxes                                      ) const ;
        
        bool                    operator !=                                 (   const   Axes&                       anAxes                                      ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Axes&                       anAxes                                      ) ;

        bool                    isDefined                                   ( ) const ;

        const Vector3d&         x                                           ( ) const ;

        const Vector3d&         y                                           ( ) const ;

        const Vector3d&         z                                           ( ) const ;

        static Axes             Undefined                                   ( ) ;

    private:

        Vector3d                x_ ;
        Vector3d                y_ ;
        Vector3d                z_ ;

        Shared<const Frame>     frameSPtr_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////