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
                                                                                const   Vector3d&                   anAngularVelocity,
                                                                                const   Transform::Type&            aType                                       )
                                :   instant_(anInstant),
                                    translation_(aTranslation),
                                    velocity_(aVelocity),
                                    orientation_(anOrientation),
                                    angularVelocity_(anAngularVelocity)
{

    switch (aType)
    {

        case Transform::Type::Active:
            (*this) = this->getInverse() ;
            break ;

        case Transform::Type::Undefined:
        case Transform::Type::Passive:
            break ;

        default:
            throw library::core::error::runtime::Wrong("Type") ;
            break ;

    }

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

    // C_A = C_B * B_A

    // t_C_A_in_A = t_B_A_in_A + q_A_B * t_C_B_in_B

    const Vector3d translation = aTransform.translation_ + aTransform.orientation_.toConjugate() * translation_ ; 
    
    // v_C_A_in_A = v_B_A_in_A + q_A_B * v_C_B_in_B + Ω_B_C_in_A x t_B_A_in_A
    
    const Vector3d velocity = aTransform.velocity_ + aTransform.orientation_.toConjugate() * velocity_ + angularVelocity_.cross(aTransform.translation_) ;

    // q_C_A = q_C_B * q_B_A

    const Quaternion orientation = orientation_ * aTransform.orientation_ ;

    // Ω_C_A_in_C = Ω_C_B_in_C + q_C_B * Ω_B_A_in_B

    const Vector3d angularVelocity = angularVelocity_ + orientation_ * aTransform.angularVelocity_ ;

    translation_ = translation ;
    velocity_ = velocity ;
    orientation_ = orientation ;
    angularVelocity_ = angularVelocity ;

    return *this ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Transform&                  aTransform                                  )
{

    using library::math::geom::trf::rot::RotationVector ;

    using library::physics::time::Scale ;

    library::core::utils::Print::Header(anOutputStream, "Transform") ;

    library::core::utils::Print::Line(anOutputStream) << "Instant:"             << (aTransform.isDefined() ? aTransform.accessInstant().toString(Scale::UTC) : "Undefined") ;
    
    library::core::utils::Print::Line(anOutputStream) << "Translation:"         << (aTransform.isDefined() ? (aTransform.accessTranslation().toString() + " [m]") : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Velocity:"            << (aTransform.isDefined() ? (aTransform.accessVelocity().toString() + " [m/s]") : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "Orientation:"         << (aTransform.isDefined() ? String::Format("{} == {}", aTransform.accessOrientation().toString(), RotationVector::Quaternion(aTransform.accessOrientation()).toString()) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Angular Velocity:"    << (aTransform.isDefined() ? (aTransform.accessAngularVelocity().toString() + " [rad/s]") : "Undefined") ;

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

bool                            Transform::isIdentity                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transform") ;
    }

    return (translation_ == Vector3d::Zero())
        && (velocity_ == Vector3d::Zero())
        && (orientation_ == Quaternion::Unit())
        && (angularVelocity_ == Vector3d::Zero()) ;

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

    // t_A_B_in_B = - q_B_A * t_B_A_in_A

    const Vector3d translation = - (orientation_ * translation_) ;

    // v_A_B_in_B = - q_B_A * v_B_A_in_A + Ω_B_A_in_B x (q_B_A * t_B_A_in_A)

    const Vector3d velocity = - (orientation_ * velocity_) + angularVelocity_.cross(orientation_ * translation_) ;

    // q_A_B = q_B_A'

    const Quaternion orientation = orientation_.toConjugate() ;

    // Ω_A_B_in_A = - q_A_B * Ω_B_A_in_B

    const Vector3d angularVelocity = - (orientation * angularVelocity_) ;

    return { instant_, translation, velocity, orientation, angularVelocity, Transform::Type::Passive } ;

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

    // x_B = q_B_A * (x_A + t_B_A_in_A)

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

    // std::cout << "aPosition = " << aPosition.toString() << std::endl ;
    // std::cout << "aVelocity = " << aVelocity.toString() << std::endl ;
    
    // std::cout << "translation_ = " << translation_.toString() << std::endl ;
    // std::cout << "velocity_ = " << velocity_.toString() << std::endl ;
    // std::cout << "orientation_ = " << orientation_.toString() << std::endl ;
    // std::cout << "angularVelocity_ = " << angularVelocity_.toString() << std::endl ;

    // v_B_in_B = q_B_A * (v_A_in_A + v_B_A_in_A) - Ω_B_A_in_B x (q_B_A * (x_A + t_B_A_in_A))

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
    return { Instant::Undefined(), Vector3d::Undefined(), Vector3d::Undefined(), Quaternion::Undefined(), Vector3d::Undefined(), Transform::Type::Undefined } ;
}

Transform                       Transform::Identity                         (   const   Instant&                    anInstant                                   )
{
    return { anInstant, Vector3d::Zero(), Vector3d::Zero(), Quaternion::Unit(), Vector3d::Zero(), Transform::Type::Passive } ;
}

Transform                       Transform::Active                           (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity                           )
{
    return { anInstant, aTranslation, aVelocity, anOrientation, anAngularVelocity, Transform::Type::Active } ;
}

Transform                       Transform::Passive                          (   const   Instant&                    anInstant,
                                                                                const   Vector3d&                   aTranslation,
                                                                                const   Vector3d&                   aVelocity,
                                                                                const   Quaternion&                 anOrientation,
                                                                                const   Vector3d&                   anAngularVelocity                           )
{
    return { anInstant, aTranslation, aVelocity, anOrientation, anAngularVelocity, Transform::Type::Passive } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////