////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Frame/Providers/Fixed.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Providers/Fixed.hpp>

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

                                Fixed::Fixed                                (   const   Transform&                  aTransform                                  )
                                :   transform_(aTransform)
{

}

                                Fixed::~Fixed                               ( )
{

}

Fixed*                          Fixed::clone                                ( ) const
{
    return new Fixed(*this) ;
}

bool                            Fixed::isDefined                            ( ) const
{
    return transform_.isDefined() ;
}

Transform                       Fixed::getTransformAt                       (   const   Instant&                    anInstant                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Fixed provider") ;
    }
    
    return Transform(anInstant, transform_.accessTranslation(), transform_.accessVelocity(), transform_.accessOrientation(), transform_.accessAngularVelocity(), Transform::Type::Passive) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////