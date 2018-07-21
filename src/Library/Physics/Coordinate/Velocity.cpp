////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Velocity.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Velocity.hpp>

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

                                Velocity::Velocity                          (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrame                                      )
                                :   coordinates_(aCoordinateSet),
                                    frameSPtr_(aFrame)
{

}

bool                            Velocity::operator ==                       (   const   Velocity&                   aVelocity                                   ) const
{

    if ((!this->isDefined()) || (!aVelocity.isDefined()))
    {
        return false ;
    }

    return (coordinates_ == aVelocity.coordinates_) && ((*frameSPtr_) == (*aVelocity.frameSPtr_)) ;

}

bool                            Velocity::operator !=                       (   const   Velocity&                   aVelocity                                   ) const
{
    return !((*this) == aVelocity) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Velocity&                   aVelocity                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Velocity") ;

    library::core::utils::Print::Line(anOutputStream) << "Coordinates:" << (aVelocity.isDefined() ? aVelocity.coordinates_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Frame:" << (aVelocity.isDefined() ? aVelocity.frameSPtr_->getName() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Velocity::isDefined                         ( ) const
{
    return coordinates_.isDefined() && (frameSPtr_ != nullptr) && frameSPtr_->isDefined() ;
}

String                          Velocity::toString                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    return String::Format("{} [{}]", coordinates_.toString(), frameSPtr_->getName()) ;

}

Velocity                        Velocity::Undefined                         ( )
{
    return Velocity(Vector3d::Undefined(), nullptr) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////