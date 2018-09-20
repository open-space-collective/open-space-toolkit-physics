////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Sun.hpp>
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

    objects_.reserve(anObjectArray.getSize()) ;

    for (const auto& objectSPtr : anObjectArray)
    {
        objects_.add(Shared<Object>(objectSPtr->clone())) ;
    }

}

                                Environment::Environment                    (   const   Environment&                anEnvironment                               )
                                :   instant_(anEnvironment.instant_),
                                    objects_(Array<Shared<Object>>::Empty())
{

    objects_.reserve(anEnvironment.objects_.getSize()) ;

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

        objects_.reserve(anEnvironment.objects_.getSize()) ;

        for (const auto& objectSPtr : anEnvironment.objects_)
        {
            objects_.add(Shared<Object>(objectSPtr->clone())) ;
        }

    }

    return *this ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Environment&                anEnvironment                               )
{

    library::core::utils::Print::Header(anOutputStream, "Environment") ;

    library::core::utils::Print::Line(anOutputStream) << "Instant:"             << (anEnvironment.isDefined() ? anEnvironment.instant_.toString() : "Undefined") ;
    
    library::core::utils::Print::Line(anOutputStream) << "Objects:" ;

    for (const auto& objectSPtr : anEnvironment.objects_)
    {
        library::core::utils::Print::Line(anOutputStream) << (*objectSPtr) ;
    }

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Environment::isDefined                      ( ) const
{
    return instant_.isDefined() ;
}

bool                            Environment::hasObjectWithName              (   const   String&                     aName                                       ) const
{

    if (aName.isEmpty())
    {
        throw library::core::error::runtime::Undefined("Name") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    for (const auto& objectSPtr : objects_)
    {

        if (objectSPtr->accessName() == aName)
        {
            return true ;
        }

    }

    return false ;

}

bool                            Environment::intersects                     (   const   Object::Geometry&           aGeometry,
                                                                                const   Array<Shared<const Object>>& anObjectToIgnoreArray                      ) const
{

    if (!aGeometry.isDefined())
    {
        throw library::core::error::runtime::Undefined("Geometry") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    for (const auto& objectSPtr : objects_)
    {

        if (!anObjectToIgnoreArray.contains(objectSPtr))
        {
            
            if (objectSPtr->getGeometryIn(aGeometry.accessFrame()).intersects(aGeometry))
            {
                return true ;
            }
            
        }

    }

    return false ;

}

Array<Shared<const Object>>     Environment::accessObjects                  ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    Array<Shared<const Object>> objects = Array<Shared<const Object>>::Empty() ;

    objects.reserve(objects_.getSize()) ;

    for (const auto& objectSPtr : objects_)
    {
        objects.add(objectSPtr) ;
    }
    
    return objects ;

}

Shared<const Object>            Environment::accessObjectWithName           (   const   String&                     aName                                       ) const
{

    if (aName.isEmpty())
    {
        throw library::core::error::runtime::Undefined("Name") ;
    }

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

    return nullptr ;

}

Shared<const Celestial>         Environment::accessCelestialObjectWithName  (   const   String&                     aName                                       ) const
{

    if (const auto objectSPtr = this->accessObjectWithName(aName))
    {

        if (const auto celestialObjectSPtr = std::dynamic_pointer_cast<const Celestial>(objectSPtr))
        {
            return celestialObjectSPtr ;
        }

    }

    throw library::core::error::RuntimeError("No celestial object with name [{}].", aName) ;

    return nullptr ;

}

Instant                         Environment::getInstant                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    return instant_ ;

}

Array<String>                   Environment::getObjectNames                 ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Environment") ;
    }

    Array<String> objectNames = Array<String>::Empty() ;

    objectNames.reserve(objects_.getSize()) ;

    for (const auto& objectSPtr : objects_)
    {
        objectNames.add(objectSPtr->getName()) ;
    }

    return objectNames ;

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

Environment                     Environment::Undefined                      ( )
{
    return { Instant::Undefined(), Array<Shared<Object>>::Empty() } ;
}

Environment                     Environment::Default                        ( )
{

    using library::physics::env::obj::celest::Earth ;
    using library::physics::env::obj::celest::Sun ;
    using library::physics::env::obj::celest::Moon ;

    const Instant instant = Instant::J2000() ;

    const Array<Shared<Object>> objects =
    {
        std::make_shared<Earth>(Earth::Default()),
        std::make_shared<Sun>(Sun::Default()),
        std::make_shared<Moon>(Moon::Default())
    } ;

    return { instant, objects } ;

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