////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Physics
/// @file           Library/Physics/Environment/Objects/CelestialBodies/Earth.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Physics/Environment/Ephemerides/Analytical.hpp>
#include <Library/Physics/Environment/Objects/CelestialBodies/Earth.hpp>
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

// EGM96

Derived                         Earth::GravitationalConstant                    =       Derived(398600441500000.0, { Length::Unit::Meter, Derived::Order(3), Mass::Unit::Undefined, Derived::Order::Zero(), Time::Unit::Second, Derived::Order(-2), Angle::Unit::Undefined, Derived::Order::Zero() }) ;
Length                          Earth::EquatorialRadius                         =       Length::Meters(6378136.3) ;
Real                            Earth::Flattening                               =       0.003352810664747 ;
Real                            Earth::C20                                      =       -4.841653717360e-04 ;
Real                            Earth::J2                                       =       -Earth::C20 * std::sqrt(5.0) ;

// WGS84

// Derived                         Earth::GravitationalConstant                    =       Derived(398600441800000.0, { Length::Unit::Meter, Derived::Order(3), Mass::Unit::Undefined, Derived::Order::Zero(), Time::Unit::Second, Derived::Order(-2), Angle::Unit::Undefined, Derived::Order::Zero() }) ;
// Length                          Earth::EquatorialRadius                         =       Length::Meters(6378137.0) ;
// Real                            Earth::Flattening                               =       0.003352810664747 ;
// Real                            Earth::C20                                      =       -4.841668500000e-04 ;
// Real                            Earth::J2                                       =       -Earth::C20 * std::sqrt(5.0) ;

// EGM96 + WGS84

// Derived                         Earth::GravitationalConstant                    =       Derived(398600441800000.0, { Length::Unit::Meter, Derived::Order(3), Mass::Unit::Undefined, Derived::Order::Zero(), Time::Unit::Second, Derived::Order(-2), Angle::Unit::Undefined, Derived::Order::Zero() }) ;
// Length                          Earth::EquatorialRadius                         =       Length::Meters(6378137.0) ;
// Real                            Earth::Flattening                               =       0.003352810664747 ;
// Real                            Earth::C20                                      =       -4.841653717360e-04 ;
// Real                            Earth::J2                                       =       -Earth::C20 * std::sqrt(5.0) ; // 0.0010826266835531513

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Earth::Earth                                (   const   Shared<Ephemeris>&          anEphemerisSPtr,
                                                                                const   Instant&                    anInstant                                   )
                                :   Celestial
                                    (
                                        "Earth",
                                        Celestial::Type::Earth,
                                        Earth::GravitationalConstant,
                                        Earth::EquatorialRadius,
                                        Earth::Flattening,
                                        Earth::J2,
                                        anEphemerisSPtr,
                                        anInstant,
                                        Earth::Geometry(anEphemerisSPtr->accessFrame())
                                    )
{

}

                                Earth::~Earth                               ( )
{

}

Earth*                          Earth::clone                                ( ) const
{
    return new Earth(*this) ;
}

Earth                           Earth::Default                              ( )
{

    using library::physics::coord::Frame ;
    using library::physics::env::ephem::Analytical ;

    const Shared<const Frame> earthFrameSPtr = Frame::ITRF() ;

    return { std::make_shared<Analytical>(earthFrameSPtr), Instant::J2000() } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object::Geometry                Earth::Geometry                             (   const   Shared<const Frame>&        aFrameSPtr                                  )
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::trf::rot::Quaternion ;

    const Real equatorialRadius_m = Earth::EquatorialRadius.inMeters() ;
    const Real polarRadius_m = equatorialRadius_m * (1.0 - Earth::Flattening) ;
    
    const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m, Quaternion::Unit() } ;

    return { ellipsoid, aFrameSPtr } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////