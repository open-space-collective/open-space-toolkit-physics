////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/Celestial.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Objects/Celestial.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace physics
{
namespace env
{
namespace obj
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Celestial::Celestial                        (   const   String&                     aName,
                                                                                const   Celestial::Type&            aType,
                                                                                const   Derived&                    aGravitationalConstant,
                                                                                const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Real&                       aJ2,
                                                                                const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Instant&                    anInstant                                   )
                                :   Object(aName, anInstant),
                                    type_(aType),
                                    gravitationalConstant_(aGravitationalConstant),
                                    equatorialRadius_(anEquatorialRadius),
                                    flattening_(aFlattening),
                                    j2_(aJ2),
                                    ephemeris_(anEphemeris)
{

}

                                Celestial::Celestial                        (   const   String&                     aName,
                                                                                const   Celestial::Type&            aType,
                                                                                const   Derived&                    aGravitationalConstant,
                                                                                const   Length&                     anEquatorialRadius,
                                                                                const   Real&                       aFlattening,
                                                                                const   Real&                       aJ2,
                                                                                const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Instant&                    anInstant,
                                                                                const   Object::Geometry&           aGeometry                                   )
                                :   Object(aName, anInstant, aGeometry),
                                    type_(aType),
                                    gravitationalConstant_(aGravitationalConstant),
                                    equatorialRadius_(anEquatorialRadius),
                                    flattening_(aFlattening),
                                    j2_(aJ2),
                                    ephemeris_(anEphemeris)
{

}

                                Celestial::~Celestial                       ( )
{

}

Celestial*                      Celestial::clone                            ( ) const
{
    return new Celestial(*this) ;
}

bool                            Celestial::isDefined                        ( ) const
{
    return Object::isDefined() && (ephemeris_ != nullptr) && ephemeris_->isDefined() ;
}

Shared<const Ephemeris>         Celestial::accessEphemeris                  ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return ephemeris_ ;

}

Celestial::Type                 Celestial::getType                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return type_ ;

}

Derived                         Celestial::getGravitationalConstant         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return gravitationalConstant_ ;

}
        
Length                          Celestial::getEquatorialRadius              ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return equatorialRadius_ ;

}

Real                            Celestial::getFlattening                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return flattening_ ;

}

Real                            Celestial::getJ2                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return j2_ ;

}

Weak<const Frame>               Celestial::accessFrame                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return ephemeris_->accessFrame() ;

}

Position                        Celestial::getPositionIn                    (   const   Frame&                      aFrame                                      ) const
{

    if (!aFrame.isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    if (auto frameSPtr = ephemeris_->accessFrame().lock())
    {
        return frameSPtr->getOriginIn(aFrame, this->accessInstant()) ;
    }
    else
    {
        throw library::core::error::RuntimeError("Cannot access frame.") ;
    }

    return Position::Undefined() ;

}

Transform                       Celestial::getTransformTo                   (   const   Frame&                      aFrame                                      ) const
{

    if (!aFrame.isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    if (auto frameSPtr = ephemeris_->accessFrame().lock())
    {
        return frameSPtr->getTransformTo(aFrame, this->accessInstant()) ;
    }
    else
    {
        throw library::core::error::RuntimeError("Cannot access frame.") ;
    }

    return Transform::Undefined() ;

}

Axes                            Celestial::getAxesIn                        (   const   Frame&                      aFrame                                      ) const
{

    if (!aFrame.isDefined())
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    if (auto frameSPtr = ephemeris_->accessFrame().lock())
    {
        return frameSPtr->getAxesIn(aFrame, this->accessInstant()) ;
    }
    else
    {
        throw library::core::error::RuntimeError("Cannot access frame.") ;
    }

    return Axes::Undefined() ;

}

Vector3d                        Celestial::getGravitationalFieldAt          (   const   Position&                   aPosition                                   ) const
{

    if (!aPosition.isDefined())
    {
        throw library::core::error::runtime::Undefined("Position") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    (void) aPosition ;

    // [TBI]

    return Vector3d::Undefined() ;

}

Celestial                       Celestial::Undefined                        ( )
{
    return Celestial(String::Empty(), Celestial::Type::Undefined, Derived::Undefined(), Length::Undefined(), Real::Undefined(), Real::Undefined(), nullptr, Instant::Undefined()) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////