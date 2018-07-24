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
                                                                                const   Velocity::Unit&             aUnit,
                                                                                const   Shared<const Frame>&        aFrame                                      )
                                :   coordinates_(aCoordinateSet),
                                    unit_(aUnit),
                                    frameSPtr_(aFrame)
{

}

bool                            Velocity::operator ==                       (   const   Velocity&                   aVelocity                                   ) const
{

    if ((!this->isDefined()) || (!aVelocity.isDefined()))
    {
        return false ;
    }

    return (coordinates_ == aVelocity.coordinates_) && (unit_ == aVelocity.unit_) && ((*frameSPtr_) == (*aVelocity.frameSPtr_)) ;

}

bool                            Velocity::operator !=                       (   const   Velocity&                   aVelocity                                   ) const
{
    return !((*this) == aVelocity) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Velocity&                   aVelocity                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Velocity") ;

    library::core::utils::Print::Line(anOutputStream) << "Coordinates:"         << (aVelocity.isDefined() ? aVelocity.coordinates_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:"                << (aVelocity.isDefined() ? Velocity::StringFromUnit(aVelocity.unit_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Frame:"               << (aVelocity.isDefined() ? aVelocity.frameSPtr_->getName() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Velocity::isDefined                         ( ) const
{
    return coordinates_.isDefined() && (unit_ != Velocity::Unit::Undefined) && (frameSPtr_ != nullptr) && frameSPtr_->isDefined() ;
}


const Vector3d&                 Velocity::accessCoordinates                 ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    return coordinates_ ;

}

const Frame&                    Velocity::accessFrame                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    return *frameSPtr_ ;

}

Velocity::Unit                  Velocity::getUnit                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    return unit_ ;

}

String                          Velocity::toString                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    return String::Format("{} [{}] @ {}", coordinates_.toString(), Velocity::StringFromUnit(unit_), frameSPtr_->getName()) ;

}

Velocity                        Velocity::Undefined                         ( )
{
    return Velocity(Vector3d::Undefined(), Velocity::Unit::MeterPerSecond, nullptr) ;
}

String                          Velocity::StringFromUnit                    (   const   Velocity::Unit&             aUnit                                       )
{

    switch (aUnit)
    {

        case Velocity::Unit::Undefined:
            return "Undefined" ;

        case Velocity::Unit::MeterPerSecond:
            return "m/s" ;

        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////