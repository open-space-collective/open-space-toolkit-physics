////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Object.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Object::Object                              (   const   String&                     aName,
                                                                                const   Instant&                    anInstant                                   )
                                :   name_(aName),
                                    instant_(anInstant),
                                    geometry_(Geometry::Undefined())
{

}

                                Object::Object                              (   const   String&                     aName,
                                                                                const   Instant&                    anInstant,
                                                                                const   Object::Geometry&           aGeometry                                   )
                                :   name_(aName),
                                    instant_(anInstant),
                                    geometry_(aGeometry)
{

}

                                Object::Object                              (   const   Object&                     anObject                                    )
                                :   name_(anObject.name_),
                                    instant_(anObject.instant_),
                                    geometry_(anObject.geometry_)
{

}


                                Object::~Object                             ( )
{

}

Object&                         Object::operator =                          (   const   Object&                     anObject                                    )
{

    if (this != &anObject)
    {

        name_ = anObject.name_ ;
        instant_ = anObject.instant_ ;
        geometry_ = anObject.geometry_ ;

    }

    return *this ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Object&                     anObject                                    )
{

    library::core::utils::Print::Header(anOutputStream, "Object") ;

    library::core::utils::Print::Line(anOutputStream) << "Name:" << (!anObject.name_.isEmpty() ? anObject.name_ : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Instant:" << (anObject.instant_.isDefined() ? anObject.instant_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Object::isDefined                           ( ) const
{
    return !name_.isEmpty() ;
}

const String&                   Object::accessName                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }
    
    return name_ ;

}

const Instant&                  Object::accessInstant                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }
    
    return instant_ ;

}

const Object::Geometry&         Object::accessGeometry                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }
    
    return geometry_ ;

}

String                          Object::getName                             ( ) const
{
    return this->accessName() ;
}

Instant                         Object::getInstant                          ( ) const
{
    return this->accessInstant() ;
}

Object::Geometry                Object::getGeometry                         ( ) const
{
    return this->accessGeometry() ;
}

Object::Geometry                Object::getGeometryIn                       (   const   Shared<const Frame>&        aFrameSPtr                                  ) const
{
    return this->accessGeometry().in(aFrameSPtr, instant_) ;
}

void                            Object::setInstant                          (   const   Instant&                    anInstant                                   )
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    instant_ = anInstant ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////