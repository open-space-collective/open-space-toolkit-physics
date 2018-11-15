////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/Static.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/Static.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{
namespace frame
{
namespace provider
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Static::Static                              (   const   Transform&                  aTransform                                  )
                                :   transform_(aTransform)
{

}

                                Static::~Static                             ( )
{

}

Static*                         Static::clone                               ( ) const
{
    return new Static(*this) ;
}

bool                            Static::isDefined                           ( ) const
{
    return transform_.isDefined() ;
}

Transform                       Static::getTransformAt                      (   const   Instant&                    anInstant                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Static provider") ;
    }
    
    return { anInstant, transform_.accessTranslation(), transform_.accessVelocity(), transform_.accessOrientation(), transform_.accessAngularVelocity(), Transform::Type::Passive } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////