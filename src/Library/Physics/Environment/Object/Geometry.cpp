////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object/Geometry.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Object/Geometry.hpp>
#include <Library/Physics/Coordinate/Transform.hpp>

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

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

    if (aGeometry.objectUPtr_ != nullptr)
    {
        anOutputStream << (*aGeometry.objectUPtr_) ;
    }

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
    using library::math::geom::d3::Transformation ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
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

    const Transformation transformation = Transformation::Rotation(RotationVector::Quaternion(transform.getOrientation())).getInverse() * Transformation::Translation(transform.getTranslation()) ;

    objectUPtr->applyTransformation(transformation) ;

    return { objectUPtr, aFrameSPtr } ;

}

Geometry                        Geometry::intersectionWith                  (   const   Geometry&                   aGeometry                                   ) const
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::LineString ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::Intersection ;

    if (!aGeometry.isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    Intersection intersection = Intersection::Undefined() ;

    if ((*frameSPtr_) == (*aGeometry.frameSPtr_))
    {
        intersection = objectUPtr_->intersectionWith(*aGeometry.objectUPtr_) ;
    }
    else
    {
        throw library::core::error::RuntimeError("Only same frame intersection supported at the moment.") ;
        // intersection = objectUPtr_->intersectionWith(*aGeometry.in(frameSPtr_, anInstant).objectUPtr_) ;
    }

    // const Intersection intersection = objectUPtr_->intersectionWith(*aGeometry.objectUPtr_) ;

    if (!intersection.isEmpty())
    {

        if (intersection.is<Point>())
        {
            return { intersection.as<Point>(), frameSPtr_ } ;
        }

        if (intersection.is<PointSet>())
        {
            return { intersection.as<PointSet>(), frameSPtr_ } ;
        }

        if (intersection.is<LineString>())
        {
            return { intersection.as<LineString>(), frameSPtr_ } ;
        }
        
        throw library::core::error::runtime::ToBeImplemented("Intersection type is not supported.") ;

    }

    return Geometry::Undefined() ;

}

Geometry                        Geometry::Undefined                         ( )
{
    return { nullptr, nullptr } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////