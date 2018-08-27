////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object/Geometry.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Object/Geometry.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace object
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Geometry::Geometry                          (   const   Geometry::Object&           anObject,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
                                :   objectUPtr_(anObject.clone()),
                                    frameSPtr_(aFrameSPtr)
{

}

                                Geometry::Geometry                          (   const   Unique<Geometry::Object>&   anObjectUPtr,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
                                :   objectUPtr_((anObjectUPtr != nullptr) ? anObjectUPtr->clone() : nullptr),
                                    frameSPtr_(aFrameSPtr)
{

}

                                Geometry::Geometry                          (   const   Geometry&                   aGeometry                                   )
                                :   objectUPtr_((aGeometry.objectUPtr_ != nullptr) ? aGeometry.objectUPtr_->clone() : nullptr),
                                    frameSPtr_(aGeometry.frameSPtr_)
{

}

Geometry&                       Geometry::operator =                        (   const   Geometry&                   aGeometry                                   )
{

    if (this != &aGeometry)
    {

        objectUPtr_.reset((aGeometry.objectUPtr_ != nullptr) ? aGeometry.objectUPtr_->clone() : nullptr) ;

        frameSPtr_ = aGeometry.frameSPtr_ ;

    }

    return *this ;

}

bool                            Geometry::operator ==                       (   const   Geometry&                   aGeometry                                   ) const
{

    if ((!this->isDefined()) && (!aGeometry.isDefined()))
    {
        return false ;
    }

    return ((*objectUPtr_) == (*aGeometry.objectUPtr_)) && ((*frameSPtr_) == (*aGeometry.frameSPtr_)) ;

}

bool                            Geometry::operator !=                       (   const   Geometry&                   aGeometry                                   ) const
{
    return !((*this) == aGeometry) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Geometry&                   aGeometry                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Geometry") ;

    // library::core::utils::Print::Line(anOutputStream) << "Object:"              << (((aGeometry.objectUPtr_ != nullptr) && aGeometry.objectUPtr_->isDefined()) ? aGeometry.objectUPtr_->toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Frame:"               << (((aGeometry.frameSPtr_ != nullptr) && aGeometry.frameSPtr_->isDefined()) ? aGeometry.frameSPtr_->getName() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Geometry::isDefined                         ( ) const
{
    return (objectUPtr_ != nullptr) && objectUPtr_->isDefined() && (frameSPtr_ != nullptr) && frameSPtr_->isDefined() ;
}

bool                            Geometry::intersects                        (   const   Geometry&                   aGeometry                                   ) const
{

    if (!aGeometry.isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    if ((*frameSPtr_) == (*aGeometry.frameSPtr_))
    {
        return objectUPtr_->intersects(*aGeometry.objectUPtr_) ;
    }

    throw library::core::error::runtime::ToBeImplemented("Geometry :: intersects") ;

    return false ;

}

bool                            Geometry::contains                          (   const   Geometry&                   aGeometry                                   ) const
{

    if (!aGeometry.isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    if ((*frameSPtr_) == (*aGeometry.frameSPtr_))
    {
        return objectUPtr_->contains(*aGeometry.objectUPtr_) ;
    }

    throw library::core::error::runtime::ToBeImplemented("Geometry :: contains") ;

    return false ;

}

Shared<const Frame>             Geometry::accessFrame                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    return frameSPtr_ ;

}

Geometry                        Geometry::in                                (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    
    using library::physics::coord::Transform ;

    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    if ((*frameSPtr_) == (*aFrameSPtr))
    {
        return *this ;
    }

    const Unique<Geometry::Object> objectUPtr(objectUPtr_->clone()) ;

    const Transform transform = frameSPtr_->getTransformTo(aFrameSPtr, anInstant) ;

    const Vector3d translation = transform.getTranslation() ;
    const Quaternion rotation = transform.getOrientation() ;

    objectUPtr->translate(translation) ;
    objectUPtr->rotate(rotation) ;

    return Geometry(objectUPtr, aFrameSPtr) ;

}

Geometry                        Geometry::Undefined                         ( )
{
    return Geometry(nullptr, nullptr) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////