/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Physics_Environment_Magnetic_Model__
#define __OpenSpaceToolkit_Physics_Environment_Magnetic_Model__

#include <OpenSpaceToolkit/Physics/Time/Instant.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace physics
{
namespace environment
{
namespace magnetic
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::math::obj::Vector3d ;

using ostk::physics::time::Instant ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Magnetic model (interface)

class Model
{

    public:

        /// @brief              Constructor (default)

                                Model                                       ( ) ;

        /// @brief              Destructor (pure virtual)

        virtual                 ~Model                                      ( ) = 0 ;

        /// @brief              Clone the magnetic model (pure virtual)
        ///
        /// @return             Pointer to magnetic model

        virtual Model*          clone                                       ( ) const = 0 ;

        /// @brief              Get the magnetic field value at a given position and instant (pure virtual)
        ///
        /// @param              [in] aPosition A position, expressed in the magnetic object frame [m]
        /// @param              [in] anInstant An instant
        /// @return             Magnetic field value, expressed in the magnetic object frame [T]

        virtual Vector3d        getFieldValueAt                             (   const   Vector3d&                   aPosition,
                                                                                const   Instant&                    anInstant                                   ) const = 0 ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
