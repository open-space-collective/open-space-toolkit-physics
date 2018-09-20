////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Moon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

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

Derived                         Moon::GravitationalConstant                     =       Derived(4902.8000e9, { Length::Unit::Meter, Derived::Order(3), Mass::Unit::Undefined, Derived::Order::Zero(), Time::Unit::Second, Derived::Order(-2), Angle::Unit::Undefined, Derived::Order::Zero() }) ;
Length                          Moon::EquatorialRadius                          =       Length::Meters(1738.14e3) ;
Real                            Moon::Flattening                                =       0.00125 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Moon::Moon                                  (   const   Shared<Ephemeris>&          anEphemerisSPtr,
                                                                                const   Instant&                    anInstant                                   )
                                :   Celestial
                                    (
                                        "Moon",
                                        Celestial::Type::Moon,
                                        Moon::GravitationalConstant,
                                        Moon::EquatorialRadius,
                                        Moon::Flattening,
                                        0.0,
                                        anEphemerisSPtr,
                                        anInstant,
                                        Moon::Geometry(anEphemerisSPtr->accessFrame())
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

    return { std::make_shared<SPICE>(SPICE::Object::Moon), Instant::J2000() } ;

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