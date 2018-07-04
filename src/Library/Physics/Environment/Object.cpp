////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

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
                                    instant_(anInstant)
{

}

                                Object::~Object                             ( )
{

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