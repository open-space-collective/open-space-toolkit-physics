////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Moon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/SPICE.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Moon.hpp>
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

Derived                         Moon::GravitationalParameter                    =       { 4902.8000e9, Derived::Unit::GravitationalParameter(Length::Unit::Meter, Time::Unit::Second) } ;
Length                          Moon::EquatorialRadius                          =       Length::Meters(1738.14e3) ;
Real                            Moon::Flattening                                =       0.00125 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Moon::Moon                                  (   const   Shared<Ephemeris>&          anEphemeris,
                                                                                const   Instant&                    anInstant                                   )
                                :   Celestial
                                    (
                                        "Moon",
                                        Celestial::Type::Moon,
                                        Moon::GravitationalParameter,
                                        Moon::EquatorialRadius,
                                        Moon::Flattening,
                                        0.0,
                                        anEphemeris,
                                        nullptr, // [TBI] Add gravitational model
                                        nullptr,
                                        anInstant,
                                        Moon::Geometry(anEphemeris->accessFrame())
                                    )
{

}

                                Moon::~Moon                                 ( )
{

}

Moon*                           Moon::clone                                 ( ) const
{
    return new Moon(*this) ;
}

Moon                            Moon::Default                               ( )
{

    using library::physics::env::ephem::SPICE ;

    return { std::make_shared<SPICE>(SPICE::Object::Moon), Instant::J2000() } ; // [TBI]

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object::Geometry                Moon::Geometry                              (   const   Shared<const Frame>&        aFrame                                      )
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::trf::rot::Quaternion ;

    const Real equatorialRadius_m = Moon::EquatorialRadius.inMeters() ;
    const Real polarRadius_m = equatorialRadius_m * (1.0 - Moon::Flattening) ;

    const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m, Quaternion::Unit() } ;

    return { ellipsoid, aFrame } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
