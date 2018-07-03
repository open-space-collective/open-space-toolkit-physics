////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Transform.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Transform::Transform                        (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity                           )
                                :   instant_(anInstant),
                                    translation_(aTranslation),
                                    velocity_(aVelocity),
                                    orientation_(anOrientation),
                                    angularVelocity_(anAngularVelocity)
{

}

bool                            Transform::operator ==                      (   const   Transform&                  aTransform                                  ) const
{

    if ((!this->isDefined()) || (!aTransform.isDefined()))
    {
        return false ;
    }
    
    return (instant_ == aTransform.instant_)
        && (translation_ == aTransform.translation_)
        && (velocity_ == aTransform.velocity_)
        && (orientation_ == aTransform.orientation_)
        && (angularVelocity_ == aTransform.angularVelocity_) ;

}

bool                            Transform::operator !=                      (   const   Transform&                  aTransform                                  ) const
{
    return !((*this) == aTransform) ;
}

Transform                       Transform::operator *                       (   const   Transform&                  aTransform                                  ) const
{

    if ((!this->isDefined()) || (!aTransform.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }

    if (instant_ != aTransform.instant_)
    {
        throw library::core::error::RuntimeError("Instants are different.") ;
    }

    Transform transform(*this) ;

    transform *= aTransform ;

    return transform ;

}

Transform&                      Transform::operator *=                      (   const   Transform&                  aTransform                                  )
{

    if ((!this->isDefined()) || (!aTransform.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }

    if (instant_ != aTransform.instant_)
    {
        throw library::core::error::RuntimeError("Instants are different.") ;
    }

    // (*this) = t_C_B
    // aTransform = t_B_A

    // t_C_A_in_A = t_B_A_in_A + q_A_B * t_C_B_in_B

    translation_ = aTransform.translation_ + aTransform.orientation_.toConjugate() * translation_ ;

    // v_C_A_in_A = v_B_A_in_A + q_A_B * v_C_B_in_B + Ω_B_C_in_A x t_B_A_in_A
    
    velocity_ = aTransform.velocity_ + aTransform.orientation_.toConjugate() * velocity_ + angularVelocity_.cross(aTransform.translation_) ;

    // q_C_A = q_C_B * q_B_A

    orientation_ = orientation_ * aTransform.orientation_ ;

    // Ω_C_A_in_C = Ω_C_B_in_C + Ω_B_A_in_C
    //            = Ω_C_B_in_C + q_B_C * Ω_B_A_in_B

    angularVelocity_ = angularVelocity_ + orientation_ * aTransform.angularVelocity_ ;

    return (*this) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Transform&                  aTransform                                  )
{

    using library::physics::time::Scale ;

    library::core::utils::Print::Header(anOutputStream, "Transform") ;

    library::core::utils::Print::Line(anOutputStream) << "Instant:" << (aTransform.isDefined() ? aTransform.accessInstant().toString(Scale::UTC) : "Undefined") ;
    
    library::core::utils::Print::Line(anOutputStream) << "Translation:" << (aTransform.isDefined() ? aTransform.accessTranslation().toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Velocity:" << (aTransform.isDefined() ? aTransform.accessVelocity().toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "Orientation:" << (aTransform.isDefined() ? aTransform.accessOrientation().toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Angular Velocity:" << (aTransform.isDefined() ? aTransform.accessAngularVelocity().toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Transform::isDefined                        ( ) const
{

    return instant_.isDefined() 
        && translation_.isDefined() 
        && velocity_.isDefined() 
        && orientation_.isDefined() 
        && angularVelocity_.isDefined() ;

}

const Instant&                  Transform::accessInstant                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return instant_ ;

}

const Vector3d&                 Transform::accessTranslation                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return translation_ ;

}

const Vector3d&                 Transform::accessVelocity                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return velocity_ ;

}

const Quaternion&               Transform::accessOrientation                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return orientation_ ;

}
        
const Vector3d&                 Transform::accessAngularVelocity            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return angularVelocity_ ;

}

Instant                         Transform::getInstant                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return instant_ ;

}

Vector3d                        Transform::getTranslation                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return translation_ ;

}

Vector3d                        Transform::getVelocity                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return velocity_ ;

}

Quaternion                      Transform::getOrientation                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return orientation_ ;

}
        
Vector3d                        Transform::getAngularVelocity               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }
    
    return angularVelocity_ ;

}

Transform                       Transform::getInverse                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }

    const Vector3d translation = - (orientation_ * translation_) ;
    const Vector3d velocity = orientation_ * (angularVelocity_.cross(translation_) - velocity_) ;

    const Quaternion orientation = orientation_.toConjugate() ;
    const Vector3d angularVelocity = - (orientation_ * angularVelocity_) ;

    return Transform(instant_, translation, velocity, orientation, angularVelocity) ;

}

Vector3d                        Transform::applyToPosition                  (   const   Vector3d&                   aPosition                                   ) const
{

    if (!aPosition.isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }

    // using library::math::geom::trf::rot::RotationVector ;

    // std::cout << "translation_ = " << translation_.toString() << std::endl ;
    // std::cout << "orientation_ QT = " << std::endl << orientation_ << std::endl ;
    // std::cout << "orientation_ RV = " << std::endl << RotationVector::Quaternion(orientation_) << std::endl ;

    // std::cout << "orientation_ * (aPosition + translation_) = " << (orientation_ * (aPosition + translation_)).toString() << std::endl ;

    return orientation_ * (aPosition + translation_) ;

}

Vector3d                        Transform::applyToVelocity                  (   const   Vector3d&                   aPosition,
                                                                                const   Vector3d&                   aVelocity                                   ) const
{

    if (!aPosition.isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (!aVelocity.isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }

    return orientation_ * (aVelocity + velocity_) - angularVelocity_.cross(orientation_ * (aPosition + translation_)) ;

}

Vector3d                        Transform::applyToVector                    (   const   Vector3d&                   aVector                                     ) const
{

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }

    return orientation_ * aVector ;

}

Transform                       Transform::Undefined                        ( )
{
    return Transform(Instant::Undefined(), Vector3d::Undefined(), Vector3d::Undefined(), Quaternion::Undefined(), Vector3d::Undefined()) ;
}

Transform                       Transform::Identity                         (   const   Instant&                    anInstant                                   )
{
    return Transform(anInstant, Vector3d::Zero(), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero()) ;
}

Transform                       Transform::Active                           (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity                           )
{
    return Transform(anInstant, aTranslation, aVelocity, anOrientation, anAngularVelocity).getInverse() ;
}

Transform                       Transform::Passive                          (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity                           )
{
    return Transform(anInstant, aTranslation, aVelocity, anOrientation, anAngularVelocity) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////