////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Coordinate/Position.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Position.hpp>

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

                                Position::Position                          (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrame                                      )
                                :   coordinates_(aCoordinateSet),
                                    frameSPtr_(aFrame)
{

}

bool                            Position::operator ==                       (   const   Position&                   aPosition                                   ) const
{

    if ((!this->isDefined()) || (!aPosition.isDefined()))
    {
        return false ;
    }

    return (coordinates_ == aPosition.coordinates_) && ((*frameSPtr_) == (*aPosition.frameSPtr_)) ;

}

bool                            Position::operator !=                       (   const   Position&                   aPosition                                   ) const
{
    return !((*this) == aPosition) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Position&                   aPosition                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Position") ;

    library::core::utils::Print::Line(anOutputStream) << "Coordinates:" << (aPosition.isDefined() ? aPosition.coordinates_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Frame:" << (aPosition.isDefined() ? aPosition.frameSPtr_->getName() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Position::isDefined                         ( ) const
{
    return coordinates_.isDefined() && (frameSPtr_ != nullptr) && frameSPtr_->isDefined() ;
}

Position                        Position::Undefined                         ( )
{
    return Position(Vector3d::Undefined(), nullptr) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////