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
                                    frameWPtr_(aFrame)
{

}

bool                            Velocity::operator ==                       (   const   Velocity&                   aVelocity                                   ) const
{

    if ((!this->isDefined()) || (!aVelocity.isDefined()))
    {
        return false ;
    }

    if (auto leftFrameSPtr = frameWPtr_.lock())
    {

        if (auto rightFrameSPtr = aVelocity.frameWPtr_.lock())
        {
            return (coordinates_ == aVelocity.coordinates_) && (unit_ == aVelocity.unit_) && ((*leftFrameSPtr) == (*rightFrameSPtr)) ;
        }

    }
    
    return false ;

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
    
    if (auto frameSPtr = aVelocity.frameWPtr_.lock())
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

bool                            Velocity::isDefined                         ( ) const
{
    
    if (auto frameSPtr = frameWPtr_.lock())
    {
        return coordinates_.isDefined() && (unit_ != Velocity::Unit::Undefined) && frameSPtr->isDefined() ;
    }
    
    return false ;

}


const Vector3d&                 Velocity::accessCoordinates                 ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    return coordinates_ ;

}

Shared<const Frame>             Velocity::accessFrame                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    if (auto frameSPtr = frameWPtr_.lock())
    {
        return frameSPtr ;
    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

}

Velocity::Unit                  Velocity::getUnit                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    return unit_ ;

}

Velocity                        Velocity::inUnit                            (   const   Velocity::Unit&             aUnit                                       ) const
{

    if (aUnit == Velocity::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Unit") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    if (auto frameSPtr = frameWPtr_.lock())
    {

        const Real conversionFactor = Derived(1.0, Velocity::DerivedUnitFromVelocityUnit(unit_)).in(Velocity::DerivedUnitFromVelocityUnit(aUnit)) ;
        
        return Velocity(coordinates_ * conversionFactor, aUnit, frameSPtr) ;
        
    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

    return Velocity::Undefined() ;

}

Velocity                        Velocity::inFrame                           (   const   Position&                   aPosition,
                                                                                const   Shared<const Frame>&        aFrame,
                                                                                const   Instant&                    anInstant                                   ) const
{

    if ((aFrame == nullptr) || (!aFrame->isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    if (auto frameSPtr = frameWPtr_.lock())
    {
        return Velocity(frameSPtr->getTransformTo(*aFrame, anInstant).applyToVelocity(aPosition.inFrame(frameSPtr, anInstant).accessCoordinates(), coordinates_), unit_, aFrame) ;
    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

    return Velocity::Undefined() ;

}

String                          Velocity::toString                          (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Velocity") ;
    }

    if (auto frameSPtr = frameWPtr_.lock())
    {
        return String::Format("{} [{}] @ {}", coordinates_.toString(aPrecision), Velocity::StringFromUnit(unit_), frameSPtr->getName()) ;
    }

    throw library::core::error::RuntimeError("Cannot access frame.") ;

    return String::Empty() ;

}

Velocity                        Velocity::Undefined                         ( )
{
    return Velocity(Vector3d::Undefined(), Velocity::Unit::Undefined, nullptr) ;
}

Velocity                        Velocity::MetersPerSecond                   (   const   Vector3d&                   aCoordinateSet,
                                                                                const   Shared<const Frame>&        aFrame                                      )
{
    return Velocity(aCoordinateSet, Velocity::Unit::MeterPerSecond, aFrame) ;
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

Derived::Unit                   Velocity::DerivedUnitFromVelocityUnit       (   const   Velocity::Unit&             aUnit                                       )
{

    using library::physics::units::Length ;
    using library::physics::units::Time ;

    switch (aUnit)
    {

        case Velocity::Unit::Undefined:
            return Derived::Unit::Undefined() ;

        case Velocity::Unit::MeterPerSecond:
            return Derived::Unit::Velocity(Length::Unit::Meter, Time::Unit::Second) ;

        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return Derived::Unit::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////