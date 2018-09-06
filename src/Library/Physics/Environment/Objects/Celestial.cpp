////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/Celestial.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Coordinate/Frame/Utilities.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/Static.hpp>
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

Shared<const Frame>             Celestial::accessFrame                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return ephemeris_->accessFrame() ;

}

Position                        Celestial::getPositionIn                    (   const   Shared<const Frame>&        aFrameSPtr                                  ) const
{

    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return ephemeris_->accessFrame()->getOriginIn(aFrameSPtr, this->accessInstant()) ;

}

Velocity                        Celestial::getVelocityIn                    (   const   Shared<const Frame>&        aFrameSPtr                                  ) const
{
    return Velocity(this->getTransformTo(aFrameSPtr).applyToVelocity(Vector3d::Zero(), Vector3d::Zero()), Velocity::Unit::MeterPerSecond, aFrameSPtr) ;
}

Transform                       Celestial::getTransformTo                   (   const   Shared<const Frame>&        aFrameSPtr                                  ) const
{

    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return ephemeris_->accessFrame()->getTransformTo(aFrameSPtr, this->accessInstant()) ;

}

Axes                            Celestial::getAxesIn                        (   const   Shared<const Frame>&        aFrameSPtr                                  ) const
{

    if ((aFrameSPtr == nullptr) || (!aFrameSPtr->isDefined()))
    {
        throw library::core::error::runtime::Undefined("Frame") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    return ephemeris_->accessFrame()->getAxesIn(aFrameSPtr, this->accessInstant()) ;

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

Shared<const Frame>             Celestial::getFrameAt                       (   const   LLA&                        aLla,
                                                                                const   Celestial::FrameType&       aFrameType                                  ) const
{

    using StaticProvider = library::physics::coord::frame::provider::Static ;

    if (!aLla.isDefined())
    {
        throw library::core::error::runtime::Undefined("LLA") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Celestial") ;
    }

    switch (aFrameType)
    {

        case Celestial::FrameType::NED:
        {

            const String frameName = String::Format("{} NED @ {}", this->accessName(), aLla.toString()) ;

            if (const auto frameSPtr = Frame::WithName(frameName))
            {
                return frameSPtr ;
            }
            
            const Transform transform = library::physics::coord::frame::utilities::NorthEastDownTransformAt(aLla, this->getEquatorialRadius(), this->getFlattening()) ;

            const Shared<const Frame> nedSPtr = Frame::Construct(frameName, false, ephemeris_->accessFrame(), std::make_shared<const StaticProvider>(transform)) ;

            return nedSPtr ;

        }

        default:
            throw library::core::error::runtime::Wrong("Frame type") ;
            break ;

    }

    return nullptr ;
    
}

Celestial                       Celestial::Undefined                        ( )
{
    return { String::Empty(), Celestial::Type::Undefined, Derived::Undefined(), Length::Undefined(), Real::Undefined(), Real::Undefined(), nullptr, Instant::Undefined() } ;
}

String                          Celestial::StringFromFrameType              (   const   Celestial::FrameType&       aFrameType                                  )
{

    switch (aFrameType)
    {

        case Celestial::FrameType::Undefined:
            return "Undefined" ;

        case Celestial::FrameType::NED:
            return "NED" ;

        default:
            throw library::core::error::runtime::Wrong("Frame type") ;
            break ;

    }

    return String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////