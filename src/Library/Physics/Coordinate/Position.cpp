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
                                                                                const   Position::Unit&             aUnit,
                                                                                const   Shared<const Frame>&        aFrame                                      )
                                :   coordinates_(aCoordinateSet),
                                    unit_(aUnit),
                                    frameWPtr_(aFrame)
{

    // std::cout << "Position :: Position (...) | Shared<const Frame> @ " << &aFrame << " / " << aFrame.get() << " frameWPtr_ | frameWPtr_.expired = " << frameWPtr_.expired() << std::endl ;

    // std::cout << "Position :: Position (...) :: use_count = " << aFrame.use_count() << std::endl ;

    // if (auto frameSPtr = frameWPtr_.lock())
    // {
    //     std::cout << "this @ " << this << " >> LOCK @ " << frameSPtr.get() << std::endl ;
    // }
    // else
    // {
    //     std::cout << "this @ " << this << " >> CANNOT LOCK" << std::endl ;
    // }

    // std::cout << "Position :: Position (...) >> &frameWPtr_ = " << &frameWPtr_ << " ? " << frameWPtr_.expired() << " - " << frameWPtr_.use_count() << std::endl ;

}

                                Position::Position                          (   const   Position&                   aPosition                                   )
                                :   coordinates_(aPosition.coordinates_),
                                    unit_(aPosition.unit_),
                                    frameWPtr_(aPosition.frameWPtr_)
{

    // std::cout << "Position :: Position (const Position&) ..." << std::endl ;

    // if (auto frameSPtr = aPosition.frameWPtr_.lock())
    // {

    //     std::cout << "aPosition @ " << &aPosition << " >> LOCK @ " << frameSPtr.get() << std::endl ;
    //     // frameWPtr_ = frameSPtr ;

    //     std::cout << "Position :: Position (const Position&) :: use_count = " << frameSPtr.use_count() << std::endl ;

    // }
    // else
    // {
    //     std::cout << "aPosition @ " << &aPosition << " >> CANNOT LOCK" << std::endl ;
    // }

    // std::cout << "Position :: Position (const Position&) >> &frameWPtr_ = " << &aPosition.frameWPtr_ << " ? " << aPosition.frameWPtr_.expired() << " - " << aPosition.frameWPtr_.use_count() << std::endl ;

    // if (auto frameSPtr = frameWPtr_.lock())
    // {
    //     std::cout << "this @ " << this << " >> LOCK @ " << frameSPtr.get() << std::endl ;
    //     std::cout << "Position :: Position (const Position&) :: use_count = " << frameSPtr.use_count() << std::endl ;
    // }
    // else
    // {
    //     std::cout << "this @ " << this << " >> CANNOT LOCK" << std::endl ;
    // }

    // std::cout << "Position :: Position (const Position&) >> &frameWPtr_ = " << &frameWPtr_ << " ? " << frameWPtr_.expired() << " - " << frameWPtr_.use_count() << std::endl ;

}

bool                            Position::operator ==                       (   const   Position&                   aPosition                                   ) const
{

    if ((!this->isDefined()) || (!aPosition.isDefined()))
    {
        return false ;
    }

    if (auto leftFrameSPtr = frameWPtr_.lock())
    {

        if (auto rightFrameSPtr = aPosition.frameWPtr_.lock())
        {
            return (coordinates_ == aPosition.coordinates_) && (unit_ == aPosition.unit_) && ((*leftFrameSPtr) == (*rightFrameSPtr)) ;
        }

    }
    
    return false ;

}

bool                            Position::operator !=                       (   const   Position&                   aPosition                                   ) const
{
    return !((*this) == aPosition) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Position&                   aPosition                                   )
{

    library::core::utils::Print::Header(anOutputStream, "Position") ;

    library::core::utils::Print::Line(anOutputStream) << "Coordinates:"         << (aPosition.isDefined() ? aPosition.coordinates_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:"                << (aPosition.isDefined() ? Length::StringFromUnit(aPosition.unit_) : "Undefined") ;

    if (auto frameSPtr = aPosition.frameWPtr_.lock())
    {
        library::core::utils::Print::Line(anOutputStream) << "Frame:"           << frameSPtr->getName() ;
    }
    else
    {
        library::core::utils::Print::Line(anOutputStream) << "Frame:"           << "Undefined" ;
    }

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Position::isDefined                         ( ) const
{

    // std::cout << "Position :: isDefined @ " << this << std::endl ;
    // std::cout << "Position :: isDefined >> &frameWPtr_ = " << &frameWPtr_ << " ? " << frameWPtr_.expired() << " - " << frameWPtr_.use_count() << std::endl ;

    if (auto frameSPtr = frameWPtr_.lock())
    {
        return coordinates_.isDefined() && (unit_ != Position::Unit::Undefined) && frameSPtr->isDefined() ;
    }
    // else
    // {
    //     std::cout << "CANNOT LOCK" << std::endl ;
    // }
    
    
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

    if (auto frameSPtr = frameWPtr_.lock())
    {
        return frameSPtr ;
    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

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

    if (auto frameSPtr = frameWPtr_.lock())
    {
        return Position(coordinates_ * Length(1.0, unit_).in(aUnit), aUnit, frameSPtr) ;
    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

    return Position::Undefined() ;

}

Position                        Position::inFrame                           (   const   Shared<const Frame>&        aFrame,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if ((aFrame == nullptr) || (!aFrame->isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (auto frameSPtr = frameWPtr_.lock())
    {

        // if ((*frameSPtr) == (*aFrame))
        // {
        //     return ??? ; // Frame is a function of time... to be improved
        // }

        return Position(frameSPtr->getTransformTo(*aFrame, anInstant).applyToPosition(coordinates_), unit_, aFrame) ;

    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

    return Position::Undefined() ;

}

String                          Position::toString                          (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (auto frameSPtr = frameWPtr_.lock())
    {
        return String::Format("{} [{}] @ {}", coordinates_.toString(aPrecision), Length::SymbolFromUnit(unit_), frameSPtr->getName()) ;
    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

    return String::Empty() ;

}

Position                        Position::Undefined                         ( )
{
    return Position(Vector3d::Undefined(), Position::Unit::Undefined, nullptr) ;
}

Position                        Position::Meters                            (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrame                                      )
{

    // std::cout << "Position :: Meters :: use_count = " << aFrame.use_count() << std::endl ;
    
    return Position(aCoordinateSet, Position::Unit::Meter, aFrame) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////