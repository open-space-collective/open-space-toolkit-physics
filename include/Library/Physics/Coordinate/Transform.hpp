////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Transform.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Physics_Coordinate_Transform__
#define __Library_Physics_Coordinate_Transform__

#include <Library/Physics/Time/Instant.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Real ;
using library::core::types::String ;

using library::math::obj::Vector3d ;
using library::math::geom::d3::trf::rot::Quaternion ;

using library::physics::time::Instant ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Transform
///
///                             Passive transformation
///
/// @ref                        https://en.wikipedia.org/wiki/Active_and_passive_transformation
/// @ref                        https://core.ac.uk/download/pdf/77055186.pdf

class Transform
{

    public:

        enum class Type
        {

            Undefined,
            Active,
            Passive

        } ;

                                Transform                                   (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity,
                                                                                const   Transform::Type&            aType                                       ) ;

        bool                    operator ==                                 (   const   Transform&                  aTransform                                  ) const ;
        
        bool                    operator !=                                 (   const   Transform&                  aTransform                                  ) const ;

        Transform               operator *                                  (   const   Transform&                  aTransform                                  ) const ;

        Transform&              operator *=                                 (   const   Transform&                  aTransform                                  ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Transform&                  aTransform                                  ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isIdentity                                  ( ) const ;

        const Instant&          accessInstant                               ( ) const ;

        const Vector3d&         accessTranslation                           ( ) const ;

        const Vector3d&         accessVelocity                              ( ) const ;

        const Quaternion&       accessOrientation                           ( ) const ;
        
        const Vector3d&         accessAngularVelocity                       ( ) const ;

        Instant                 getInstant                                  ( ) const ;
        
        Vector3d                getTranslation                              ( ) const ;
        
        Vector3d                getVelocity                                 ( ) const ;

        Quaternion              getOrientation                              ( ) const ;
        
        Vector3d                getAngularVelocity                          ( ) const ;

        Transform               getInverse                                  ( ) const ;

        Vector3d                applyToPosition                             (   const   Vector3d&                   aPosition                                   ) const ;

        Vector3d                applyToVelocity                             (   const   Vector3d&                   aPosition,
                                                                                const   Vector3d&                   aVelocity                                   ) const ;

        Vector3d                applyToVector                               (   const   Vector3d&                   aVector                                     ) const ;

        static Transform        Undefined                                   ( ) ;

        static Transform        Identity                                    (   const   Instant&                    anInstant                                   ) ;

        static Transform        Active                                      (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity                           ) ;

        static Transform        Passive                                     (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity                           ) ;

    private:

        Instant                 instant_ ;
        
        Vector3d                translation_ ;
        Vector3d                velocity_ ;

        Quaternion              orientation_ ;
        Vector3d                angularVelocity_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////