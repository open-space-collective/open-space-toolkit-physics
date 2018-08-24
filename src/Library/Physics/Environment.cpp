////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
#include <Library/Physics/Environment/Objects/Celestial.hpp>
#include <Library/Physics/Environment.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Environment::Environment                    (   const   Instant&                    anInstant,
                                                                                const   Array<Shared<Object>>&      anObjectArray                               )
                                :   instant_(anInstant),
                                    objects_(Array<Shared<Object>>::Empty())
{

    for (const auto& objectSPtr : anObjectArray)
    {
        objects_.add(Shared<Object>(objectSPtr->clone())) ;
    }

}

                                Environment::Environment                    (   const   Environment&                anEnvironment                               )
                                :   instant_(anEnvironment.instant_),
                                    objects_(Array<Shared<Object>>::Empty())
{

    for (const auto& objectSPtr : anEnvironment.objects_)
    {
        objects_.add(Shared<Object>(objectSPtr->clone())) ;
    }

}

Environment&                    Environment::operator =                     (   const   Environment&                anEnvironment                               )
{

    if (this != &anEnvironment)
    {

        instant_ = anEnvironment.instant_ ;
        
        objects_.clear() ;

        for (const auto& objectSPtr : anEnvironment.objects_)
        {
            objects_.add(Shared<Object>(objectSPtr->clone())) ;
        }

    }

    return (*this) ;

}

bool                            Environment::isDefined                      ( ) const
{
    return instant_.isDefined() ;
}

Weak<const Object>              Environment::accessObjectWithName           (   const   String&                     aName                                       ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    for (const auto& objectSPtr : objects_)
    {

        if (objectSPtr->accessName() == aName)
        {
            return objectSPtr ;
        }

    }

    throw library::core::error::RuntimeError("No object with name [{}].", aName) ;

    return Weak<const Object>() ;

}

Instant                         Environment::getInstant                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    return instant_ ;

}

void                            Environment::setInstant                     (   const   Instant&                    anInstant                                   )
{

    if (!anInstant.isDefined())
    {
        throw library::core::error::runtime::Undefined("Instant") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    instant_ = anInstant ;

    this->updateObjects() ;

}

bool                            Environment::intersects                     (   const   GeometricalObject&          aGeometricalObject                          ) const
{

    if (!aGeometricalObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometrical object") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    for (const auto& objectSPtr : objects_)
    {

        if (objectSPtr->accessGeometry().intersects(aGeometricalObject))
        {
            return true ;
        }

    }

    return false ;

}

Environment                     Environment::Undefined                      ( )
{
    return Environment(Instant::Undefined(), Array<Shared<Object>>::Empty()) ;
}

Environment                     Environment::Default                        ( )
{

    using library::physics::coord::Frame ;
    using library::physics::env::obj::Celestial ;
    using library::physics::env::obj::celest::Earth ;

    const Instant instant = Instant::J2000() ;

    const Array<Shared<Object>> objects =
    {
        std::make_shared<Earth>(Earth::Analytical(instant))
    } ;

    return Environment(instant, objects) ;

}

void                            Environment::updateObjects                  ( )
{

    for (auto& objectSPtr : objects_)
    {
        objectSPtr->setInstant(instant_) ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////