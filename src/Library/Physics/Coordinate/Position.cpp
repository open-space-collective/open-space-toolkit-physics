////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Physics
/// @file           Library/Physics/Coordinate/Position.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame.hpp>
#include <Library/Physics/Coordinate/Position.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/stacktrace.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace coord
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Position::Position                          (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Position::Unit&             aUnit,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
                                :   coordinates_(aCoordinateSet),
                                    unit_(aUnit),
                                    frameSPtr_(aFrameSPtr)
{

}

                                Position::Position                          (   const   Position&                   aPosition                                   )
                                :   coordinates_(aPosition.coordinates_),
                                    unit_(aPosition.unit_),
                                    frameSPtr_(aPosition.frameSPtr_)
{

}

Position&                       Position::operator =                        (   const   Position&                   aPosition                                   )
{

    if (this != &aPosition)
    {

        coordinates_ = aPosition.coordinates_ ;
        unit_ = aPosition.unit_ ;
        frameSPtr_ = aPosition.frameSPtr_ ;

    }

    return *this ;

}

bool                            Position::operator ==                       (   const   Position&                   aPosition                                   ) const
{

    if ((!this->isDefined()) || (!aPosition.isDefined()))
    {
        return false ;
    }

    return (coordinates_ == aPosition.coordinates_) && (unit_ == aPosition.unit_) && ((*frameSPtr_) == (*aPosition.frameSPtr_)) ;

}

bool                            Position::operator !=                       (   const   Position&                   aPosition                                   ) const
{
    return !((*this) == aPosition) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Position&                   aPosition                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Position") ;

    library::core::utils::Print::Line(anOutputStream) << "Coordinates:"         << (aPosition.coordinates_.isDefined() ? aPosition.coordinates_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:"                << ((aPosition.unit_ != Position::Unit::Undefined) ? Length::StringFromUnit(aPosition.unit_) : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Frame:"               << (((aPosition.frameSPtr_ != nullptr) && aPosition.frameSPtr_->isDefined()) ? aPosition.frameSPtr_->getName() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Position::isDefined                         ( ) const
{
    return coordinates_.isDefined() && (unit_ != Position::Unit::Undefined) && (frameSPtr_ != nullptr) && frameSPtr_->isDefined() ;
}

bool                            Position::isNear                            (   const   Position&                   aPosition,
                                                                                const   Length&                     aLength                                     ) const
{

    if (!aPosition.isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (!aLength.isDefined())
    {
        throw library::core::error::runtime::Undefined("Length") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (frameSPtr_ != aPosition.frameSPtr_)
    {
        throw library::core::error::RuntimeError("Position are expressed in different frames.") ;
    }

    if (unit_ == aPosition.unit_)
    {
        return (coordinates_ - aPosition.coordinates_).norm() <= aLength.in(unit_) ;
    }
    else
    {
        return (coordinates_ - aPosition.inUnit(unit_).coordinates_).norm() <= aLength.in(unit_) ;
    }

    return false ;

}

const Vector3d&                 Position::accessCoordinates                 ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    return coordinates_ ;

}

Shared<const Frame>             Position::accessFrame                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    return frameSPtr_ ;

}

Vector3d                        Position::getCoordinates                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    return coordinates_ ;

}

Position::Unit                  Position::getUnit                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    return unit_ ;

}

Position                        Position::inUnit                            (   const   Position::Unit&             aUnit                                       ) const
{

    if (aUnit == Position::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Unit") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    return { coordinates_ * Length(1.0, unit_).in(aUnit), aUnit, frameSPtr_ } ;

}

Position                        Position::inMeters                          ( ) const
{
    return this->inUnit(Position::Unit::Meter) ;
}

Position                        Position::inFrame                           (   const   Shared<const Frame>&        aFrameSPtr,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        // std::cout << boost::stacktrace::stacktrace() ;
        throw library::core::error::runtime::Undefined("Position") ;
    }

    return { frameSPtr_->getTransformTo(aFrameSPtr, anInstant).applyToPosition(coordinates_), unit_, aFrameSPtr } ;

}

String                          Position::toString                          (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    return String::Format("{} [{}] @ {}", (aPrecision.isDefined() ? coordinates_.toString(aPrecision) : coordinates_.toString()), Length::SymbolFromUnit(unit_), frameSPtr_->getName()) ;

}

Position                        Position::Undefined                         ( )
{
    return { Vector3d::Undefined(), Position::Unit::Undefined, nullptr } ;
}

Position                        Position::Meters                            (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrameSPtr                                  )
{
    return { aCoordinateSet, Position::Unit::Meter, aFrameSPtr } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
