////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Sun.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/SPICE.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Sun.hpp>
#include <Library/Physics/Coordinate/Frame/Providers/Static.hpp>
#include <Library/Physics/Coordinate/Frame.hpp>

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
namespace celest
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::physics::units::Mass ;
using library::physics::units::Time ;
using library::physics::units::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Derived                         Sun::GravitationalParameter                     =       Derived(132712440018e9, { Length::Unit::Meter, Derived::Order(3), Mass::Unit::Undefined, Derived::Order::Zero(), Time::Unit::Second, Derived::Order(-2), Angle::Unit::Undefined, Derived::Order::Zero() }) ;
Length                          Sun::EquatorialRadius                           =       Length::Meters(6.955e8) ;
Real                            Sun::Flattening                                 =       0.0 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Sun::Sun                                    (   const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Shared<GravitationalModel>& aGravitationalModel,
                                                                                const   Instant&                    anInstant                                   )
                                :   Celestial
                                    (
                                        "Sun",
                                        Celestial::Type::Sun,
                                        Sun::GravitationalParameter,
                                        Sun::EquatorialRadius,
                                        Sun::Flattening,
                                        0.0,
                                        anEphemeris,
                                        aGravitationalModel,
                                        anInstant,
                                        Sun::Geometry(anEphemeris->accessFrame())
                                    )
{

}

                                Sun::~Sun                                   ( )
{

}

Sun*                            Sun::clone                                  ( ) const
{
    return new Sun(*this) ;
}

Sun                             Sun::Default                                ( )
{

    using library::physics::env::ephem::SPICE ;

    return { std::make_shared<SPICE>(SPICE::Object::Sun), nullptr, Instant::J2000() } ; // [TBI]

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object::Geometry                Sun::Geometry                               (   const   Shared<const Frame>&        aFrame                                      )
{

    using library::math::geom::d3::objects::Point ;

    const Real equatorialRadius_m = Sun::EquatorialRadius.inMeters() ;
    
    const Sphere sphere = { Point::Origin(), equatorialRadius_m } ;

    return { sphere, aFrame } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////